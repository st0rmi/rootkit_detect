obj-m += sasuke.o
sasuke-y := check_syscalls.o include.o main.o
#ccflags-y = -std=gnu99 -Wno-declaration-after-statement
ccflags-y = -DDEBUG -std=gnu99 -Wno-declaration-after-statement

all:	sysmap
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

sysmap:
	./gensysmap.sh
	@echo "Generated sysmap.h"

clean:
	@rm -f sysmap.h
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

