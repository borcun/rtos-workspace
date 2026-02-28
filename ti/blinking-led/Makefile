all:
	arm-none-eabi-gcc -c -mcpu=cortex-r5 -mbig-endian -mthumb -mfloat-abi=hard -mfpu=vfpv3-d16 -g main.c -o main.o
	arm-none-eabi-gcc -T launchxl.ld -Wl,-Map=project.map -mcpu=cortex-r5 -mbig-endian -mthumb -nostartfiles -Wl,--gc-sections main.o -o project.out -lc -lgcc

clean:
	rm -rf *.o *.out
