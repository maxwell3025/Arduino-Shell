out/shell.hex: out/shell.elf
	avr-objcopy -O ihex -R .eeprom out/shell.elf out/shell.hex

out/shell.elf: out/shell.o out/ivt.o out/usart.o src/shell.lds
	avr-ld -T src/shell.lds out/shell.o out/usart.o out/ivt.o -o out/shell.elf
	avr-objdump -Ds out/shell.elf > out/debug/shell.elf.dump

out/ivt.o: src/ivt.S
	avr-gcc \
		-Os \
		-DF_CPU=16000000UL \
		-mmcu=atmega328p \
		-c \
		src/ivt.S \
		-o out/ivt.o
	avr-objdump -Ds out/ivt.o > out/debug/ivt.o.dump

out/shell.o: src/shell.c src/util.h
	mkdir -p out/debug
	avr-gcc \
		-Os \
		-DF_CPU=16000000UL \
		-mmcu=atmega328p \
		-ffunction-sections \
		-fdata-sections \
		-c \
		src/shell.c \
		-o out/shell.o
	avr-objdump -Ds out/shell.o > out/debug/shell.o.dump

out/usart.o: src/usart.c
	mkdir -p out/debug
	avr-gcc \
		-Os \
		-DF_CPU=16000000UL \
		-mmcu=atmega328p \
		-ffunction-sections \
		-fdata-sections \
		-c \
		src/usart.c \
		-o out/usart.o
	avr-objdump -Ds out/usart.o > out/debug/usart.o.dump

run: out/shell.hex
	avrdude -c arduino -P /dev/ttyACM0 -b 115200 -p atmega328p -D -U flash:w:out/shell.hex:i
	screen /dev/ttyACM0

