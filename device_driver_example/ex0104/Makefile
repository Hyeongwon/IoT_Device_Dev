KFILE := hello-4

obj-m += $(KFILE).o

#KDIR := /lib/modules/$(shell uname -r)/build
KDIR := /tftpboot/kernel-mds2450-3.0.22

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean

target:
	cp $(KFILE).ko /nfsroot/root
