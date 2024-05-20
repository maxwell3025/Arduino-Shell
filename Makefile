C_SRC := $(wildcard src/*.c)
ASM_SRC := $(wildcard src/*.S)
OBJS := $(patsubst src/%.c,out/%.o,$(C_SRC)) $(patsubst src/%.S,out/%.o,$(ASM_SRC))

out/shell.hex: out/shell.elf
	avr-objcopy -O ihex -R .eeprom out/shell.elf out/shell.hex

out/shell.elf: $(OBJS) src/shell.lds
	avr-ld -T src/shell.lds $(OBJS) -o out/shell.elf
	avr-objdump -Ds out/shell.elf > out/debug/shell.elf.dump

out/%.o: src/%.S
	mkdir -p out/debug
	avr-gcc \
		-Os \
		-DF_CPU=16000000UL \
		-mmcu=atmega328p \
		-c \
		$< \
		-o $@
	avr-objdump -Ds $@ > $(patsubst out/%.o,out/debug/%.o.dump,$@)

out/%.o: src/%.c
	mkdir -p out/debug
	avr-gcc \
		-Os \
		-DF_CPU=16000000UL \
		-mmcu=atmega328p \
		-ffunction-sections \
		-fdata-sections \
		-c \
		-MMD \
		$< \
		-o $@
	avr-objdump -Ds $@ > $(patsubst out/%.o,out/debug/%.o.dump,$@)

run: out/shell.hex
	avrdude -c arduino -P /dev/ttyACM0 -b 115200 -p atmega328p -D -U flash:w:out/shell.hex:i
	screen /dev/ttyACM0

clean:
	rm -rf out

-include out/*.d
