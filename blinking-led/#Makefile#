CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0
LDFLAGS = -T stm32f429.ld -nostdlib

all: main.o
	$(CC) $(LDFLAGS) -o blink.elf main.o

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c

clean:
	rm -rf *.o *.elf
