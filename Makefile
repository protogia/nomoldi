# Makefile for programming ATmega8-16PU using avrdude

# Compiler and flags
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Target microcontroller
MCU = m8

# Source files directory
SRC_DIR = ./atmega8xxx/src

# Source files
SRC = $(SRC_DIR)/main.c

# Output files
OUT_HEX = main.hex
OUT_ELF = main.elf

# avrdude settings
AVRDUDE_PROGRAMMER = avrisp2
AVRDUDE_PORT = /dev/ttyUSB0  # Change this to your actual programming port

# Compile options
CFLAGS = -mmcu=$(MCU) -Wall

# Link options
LDFLAGS = -mmcu=$(MCU)

all: $(OUT_HEX)

$(OUT_ELF): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(OUT_HEX): $(OUT_ELF)
	$(OBJCOPY) -j .text -j .data -O ihex $^ $@

flash: $(OUT_HEX)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -P $(AVRDUDE_PORT) -e -U flash:w:$^

clean:
	rm -f $(OUT_HEX) $(OUT_ELF)

.PHONY: all flash clean
