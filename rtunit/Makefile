######################################################################
#  Top Level: STM32F103C8T6 Projects
######################################################################

PROJECTS = pru

.PHONY = libopencm3 clobber_libopencm3 clean_libopencm3 

all:	libopencm3
	for d in $(PROJECTS) ; do \
		$(MAKE) -C $$d ; \
	done

clean:	clean_libopencm3
	for d in $(PROJECTS) ; do \
		$(MAKE) -C $$d clean ; \
	done
	
clobber: 
	for d in $(PROJECTS) ; do \
		$(MAKE) -C $$d clobber ; \
	done
	
clean_libopencm3:
	$(MAKE) -C libopencm3 clean

libopencm3: 
	$(MAKE) -C libopencm3

# Uncomment if necessary:
# MAKE	= gmake

# End
