C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c shell/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h shell/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

# Change this if your cross-compiler is somewhere else
CC = /home/linuxbrew/.linuxbrew/bin/i386-elf-gcc
GDB = /home/linuxbrew/.linuxbrew/bin/i386-elf-gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g -I. -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wno-unused-variable -Wno-sign-compare

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	/home/linuxbrew/.linuxbrew/bin/i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	/home/linuxbrew/.linuxbrew/bin/i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os-image.bin
# -nographic -d int --no-shutdown --no-reboot -monitor stdio -serial mon:null 
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin -nographic &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -O0 -o $@

%.bin: %.asm
	nasm $< -f bin -O0 -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o shell/*.o