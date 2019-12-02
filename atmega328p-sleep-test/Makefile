BIN=sleep-test
MCU=atmega328p

CC=avr-gcc
OPTIMIZE=-Os
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
AVRSIZE=avr-size --format=avr --mcu=$(MCU)

CFLAGS=${OPTIMIZE} -DF_CPU=16000000UL -mmcu=${MCU} -std=gnu99 -Wall -Wextra \
				-Werror -Wstrict-prototypes -Wundef -pedantic
LDFLAGS=-mmcu=$(MCU)
PORT=/dev/ttyACM0

OUT=${BIN}.elf ${BIN}.hex ${BIN}.lss

SOURCES=main.c \
		gpio.c \
		uart.c

OBJS=$(SOURCES:.c=.o)

all: $(OUT)
$(OBJS): Makefile

%.o:%.c
	$(COMPILE.c) -MD -o $@ $<
	@cp $*.d $*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

flash: ${BIN}.hex
		avrdude -v -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:$<

clean:
		rm -f $(OUT) $(OBJS) *.map *.P
