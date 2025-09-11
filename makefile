hello:
	@echo ' _______________________________________________ '
	@echo '/ To build the whole thing and generate an ISO  |' 
	@echo '| make build-iso                                |'
	@echo '| To just build the kernel image                |'
	@echo '| make build                                    |'
	@echo '| To see some export examples for your toolchain|'
	@echo '| make export                                   |'
	@echo '| And of course the is always                   |'
	@echo '| make clean                                    |'
	@echo ' ----------------------------------------------- '
	@echo '        \   ^__^                                 '
	@echo '         \  (oo)\_______                        '
	@echo '            (__)\       )\/\                  '
	@echo '                ||----w | '
	@echo '                ||     || '

build myos.bin: kernel.c boot.s function.c linker.ld graphics.s
	nasm -f elf32 graphics.s -o graphics.o
	i686-elf-as boot.s -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c function.c -o function.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o function.o graphics.o -lgcc



build-iso: myos.bin 
	mkdir -p isodir/boot/grub
	mv myos.bin ./isodir/boot
	echo 'menuentry "myos" {' > ./isodir/boot/grub/grub.cfg
	echo 'multiboot /boot/myos.bin' >> ./isodir/boot/grub/grub.cfg
	echo '}' >> ./isodir/boot/grub/grub.cfg
	grub-mkrescue -o shitDraw.iso isodir


clean:
	rm -rf isodir/ boot.o kernel.o function.o

export:
	export PREFIX="$HOME/opt/cross"
	export TARGET="i686-elf"
	export PATH="$PREFIX/bin:$PATH"
