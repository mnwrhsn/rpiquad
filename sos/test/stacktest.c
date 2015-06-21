#include "../rrm_config.h"
#include "../os_config.h"
#include "../os_task.h"

#define MY_STACK_SIZE	128

static uint8_t t1stack[MY_STACK_SIZE];
static uint8_t t2stack[MY_STACK_SIZE];

void blinker1(void *data)
{
	PORTC |= 0x00;
	DDRC |= 0x0f;
	while (1) {

		//switch context
	}
}

void blinker2(void *data)
{
	PORTC |= 0x00;
	DDRC |= 0xf0;
	while (1) {

		//switch context
	}
}

int main(void)
{
	cli();
	return 0;
}
