# nofungi-lamp

## description/idea

...

## wiring for programming

...

## compile & and upload

```bash
make
```

or manually

```bash
# create .elf
avr-gcc -mmcu=atmega8 -Wall -Os -o main.elf main.c
# create hex
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# upload
avrdude -p m8 -c avrisp2 -e -U flash:w:main.hex 
```

## wiring in production

...
