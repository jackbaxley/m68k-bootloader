CC = m68k-elf-gcc
LD = m68k-elf-ld
AS = m68k-elf-as

CFLAGS = -c -O1
LFLAGS =
ASFLAGS = -m68030


SRCS = bootloader.s load.c

OBJ = build/bootloader.o build/load.o

build/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ $<

build/%.o: src/%.S
	$(AS) $(ASFLAGS) -o $@ $<

.PHONEY: clean
clean:
	rm -r build/*.o
	rm -r boot

boot: $(OBJ)
	$(LD) -o boot  -T src/ram.ld $(OBJ) $(LFLAGS)
	dd if=boot of=../fileserver/filesystem bs=1024 count=1 conv=notrunc