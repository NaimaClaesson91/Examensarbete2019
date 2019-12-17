BIN=blinky
MCU=atmega328p
FREQ=8000000UL

CC=avr-gcc
OPTIMIZE=-Os
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
AVRSIZE=avr-size --format=avr --mcu=$(MCU)

CFLAGS=${OPTIMIZE} -DF_CPU=${FREQ} -mmcu=${MCU} -std=gnu99 -Wall -Wextra \
				-Werror -Wstrict-prototypes -Wundef -pedantic
LDFLAGS=-mmcu=$(MCU)
PORT=/dev/ttyACM0

OUT=${BIN}.elf ${BIN}.hex ${BIN}.lss

SOURCES=main.c

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
		avrdude -v -c avrisp2 -p ${MCU} -P ${PORT} -U flash:w:$<

clean:
		rm -f $(OUT) $(OBJS) *.map *.P
