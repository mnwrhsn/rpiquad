#include <stdarg.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "pru_usart_print.h"

#ifdef DEBUG_PRINTF_ON
//---------------------------mini printf---------------------------------------------//
int mini_vprintf_cooked(void (*putc)(char),const char *format,va_list args);
int mini_vprintf_uncooked(void (*putc)(char),const char *format,va_list args);

int mini_snprintf(char *buf,unsigned maxbuf,const char *format,...)
        __attribute((format(printf,3,4)));

/*
 * Internal structure for I/O
 */
struct s_mini_args {
	void	(*putc)(char,void *);	// The putc() function to invoke
	void 	*argp;			// Associated data struct
};

typedef struct s_mini_args miniarg_t;	// Abbreviated ref to s_mini_args

/*
 * Internal: Write string msg until null byte, to the I/O
 *           routine described by s_mini_args.
 */
static void mini_write(miniarg_t *mini,const char *msg) 
{
	char ch;

	while ( (ch = *msg++) != 0 )
		mini->putc(ch,mini->argp);
}

/*
 * Internal: Pad % field to width, give text buffer.
 */
static void mini_pad(miniarg_t *mini,char pad,int width,const char *text) 
{
	int slen;

	if ( width > 0 ) {
		slen = strlen(text);

		for ( width -= slen; width > 0; --width )
			mini->putc(pad,mini->argp);
	}
}

/*
 * Internal: mini_printf() engine.
 */
static void internal_vprintf(miniarg_t *mini, const char *format, va_list arg) 
{
	char ch, pad, sgn;	/* Current char, pad char and sign char */
	int vint, width;	/* Integer value to print and field width */
	unsigned uint;		/* Unsigned value to print */
	const char *sptr;	/* String to print */
	char buf[32], *bptr;	/* Formatting buffer for int/uint */

	while ( (ch = *format++) != 0 ) {
		if ( ch != '%' ) {
			/* Non formatting field: copy as is */
			mini->putc(ch,mini->argp);
			continue;
		}

		/*
		 * Process a format item:
		 */
		pad = ' ';	/* Default pad char is space */
		sgn = 0;	/* Assume no format sign char */
		ch = *format++;	/* Grab next format char */

		if ( ch == '+' || ch == '-' ) {
			sgn = ch;	/* Make note of format sign */
			ch = *format++;	/* Next format char */
		}

		if ( ch == '0' ) {
			pad = ch;	/* Pad with zeros */
			ch = *format++;
		}

		/*
		 * Extract width when present:
		 */
		for ( width = 0; ch && ch >= '0' && ch <= '9'; ch = *format++ )
			width = width * 10 + (ch & 0x0F);

		if ( !ch )
			break;		/* Exit loop if we hit end of format string (in error) */

		/*
		 * Format according to type: d, x, or s
		 */
		switch ( ch ) {
		case 'c':
			vint = va_arg(arg,int);
			mini->putc((char)vint,mini->argp);
			break;
		case 'd':		/* Decimal format */
			vint = va_arg(arg,int);
			if ( vint < 0 ) {
				mini->putc('-',mini->argp);
				vint = -vint;
			} else if ( sgn == '+' )
				mini->putc(sgn,mini->argp);
			bptr = buf + sizeof buf;
			*--bptr = 0;
			do	{
				*--bptr = vint % 10 + '0';
				vint /= 10;
			} while ( vint != 0 );
			mini_pad(mini,pad,width,bptr);
			mini_write(mini,bptr);
			break;

		case 'x':		/* Hexadecimal format */
			uint = va_arg(arg,unsigned);
			bptr = buf + sizeof buf;
			*--bptr = 0;
			do	{
				ch = uint & 0x0F;
				*--bptr = ch + (ch <= 9 ? '0' : 'A'-10);
				uint >>= 4;
			} while ( uint != 0 );
			mini_pad(mini,pad,width,bptr);
			mini_write(mini,bptr);
			break;

		case 's':		/* String format */
			sptr = va_arg(arg,const char *);
			if ( sgn != '-' )
				mini_pad(mini,pad,width,sptr);
			mini_write(mini,sptr);
			if ( sgn == '-' )
				mini_pad(mini,pad,width,sptr);
			break;

		case '%':		/* "%%" outputs as "%" */
			mini->putc(ch,mini->argp);
			break;

		default:		/* Unsupported stuff here */
			mini->putc('%',mini->argp);
			mini->putc('?',mini->argp);
			mini->putc(ch,mini->argp);
		}
	}
}

/*
 * s_internal trackes the count of bytes output:
 */
struct s_internal {
	void (*putc)(char);	/* User's putc() routine to be used */
	unsigned count;		/* Bytes output */
	unsigned cooked : 1;	/* When true, '\n' also emits '\r' */
};

static void mini_putc(char ch, void *argp) 
{
	struct s_internal *internp = (struct s_internal *)argp;

	internp->putc(ch);	/* Perform I/O */
	++internp->count;	/* Count bytes out */

	if ( ch == '\n' && internp->cooked != 0 ) {
		/* In cooked mode, issue CR after LF */
		internp->putc('\r');
		++internp->count;	/* Count CR */
	}
}

/*
 * Internal: Perform cooked/uncooked printf()
 */
static int mini_vprintf0(void (*putc)(char), int cooked, const char *format, va_list args) 
{
	miniarg_t mini;
	struct s_internal intern;

	intern.putc = putc;		/* User's putc() routine to be used */
	intern.count = 0u;		/* Byte counter */
	intern.cooked = !!cooked; 	/* True if LF to add CR */

	mini.putc = mini_putc;		/* Internal interlude routine */
	mini.argp = (void *)&intern; 	/* Ptr to internal struct */

	internal_vprintf(&mini,format,args);
	return intern.count;		/* Return byte count */
}

/*
 * External: Perform cooked mode printf()
 */
int mini_vprintf_cooked(void (*putc)(char), const char *format, va_list args) 
{
	return mini_vprintf0(putc,1,format,args);
}

/*
 * External: Perform uncooked (as is) printf()
 */
int mini_vprintf_uncooked(void (*putc)(char), const char *format, va_list args) 
{
	return mini_vprintf0(putc,0,format,args);
}

/*********************************************************************
 * Sprintf
 *********************************************************************/

struct s_mini_sprintf {
	char	*buf;			/* Ptr to output buffer */
	unsigned maxbuf;		/* Max bytes for buffer */
	char	*ptr;			/* Ptr to next byte */
};

static void mini_sputc(char ch, void *argp) 
{
	struct s_mini_sprintf *ctl = (struct s_mini_sprintf *)argp;

	if ( (unsigned)(ctl->ptr - ctl->buf) >= ctl->maxbuf )
		return;
	*ctl->ptr++ = ch;
}

/*
 * External: sprintf() to buffer (not cooked)
 */
int mini_snprintf(char *buf, unsigned maxbuf, const char *format, ...) 
{
	miniarg_t mini;			/* printf struct */
	struct s_mini_sprintf ctl;	/* sprintf control */
	va_list args;			/* format arguments */
	unsigned count;			/* Return count */

	mini.putc = mini_sputc;		/* Internal routine */
	mini.argp = (void *)&ctl;	/* Using ctl to guide it */

	ctl.ptr = ctl.buf = buf;	/* Destination for data */
	ctl.maxbuf = maxbuf;		/* Max size in bytes */

	va_start(args,format);
	internal_vprintf(&mini,format,args);
	va_end(args);

	count = (unsigned)(ctl.ptr - ctl.buf); /* Calculate count */
	mini_sputc(0,&ctl);		/* Null terminate output if possible */
	return count;			/* Return formatted count */
}
//----------------------------------------------------------------------------------------//

void usart_printf_setup(void)
{
	//enable clock
	//rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART1);

	//////////////////////////////////////////////////////////////
	// STM32F103C8T6:
	//	RX:	A9
	//	TX:	A10
	//	CTS:	A11 (not used)
	//	RTS:	A12 (not used)
	//	Baud:	38400
	//////////////////////////////////////////////////////////////

	// GPIO_USART1_TX/GPIO13 on GPIO port A for tx
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

	usart_set_baudrate(USART1, 38400);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_enable(USART1);
}

static inline void __usart_putc(char ch)
{
	usart_send_blocking(USART1, ch);
}

int usart_printf(const char *format, ...)
{
	va_list args;
	int rc;

	va_start(args, format);
	rc = mini_vprintf_cooked(__usart_putc, format, args);
	va_end(args);

	return rc;
}
#endif
