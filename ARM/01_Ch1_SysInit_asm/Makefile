##########[Embedded C test firmware Makefile]##############
#
# NAME : Makefile - S3C2450 test Firmware Makefile
# Brief history
#----------------------------------------------------------
#
#	2015.08.10, Seonghye : Modified
#
###########################################################

.EXPORT_ALL_VARIABLES:

## If you want to change path, modify here

#TOPDIR = C:/cygwin/00_example/01_Ch1_SysInit_asm
TOPDIR = D:/ARM_DEV_CONRLAB/LAB01/01_Ch1_SysInit_asm
#TOOLPATH = C:/cygwin/GNUARM-4.1.0
TOOLPATH = C:\cygwin\arm-none-eabi

CC = $(TOOLPATH)/bin/arm-none-eabi-gcc
LD = $(TOOLPATH)/bin/arm-none-eabi-ld
OBJCOPY	= $(TOOLPATH)/bin/arm-none-eabi-objcopy
OBJDUMP	= $(TOOLPATH)/bin/arm-none-eabi-objdump

LIBCDIR =$(TOOLPATH)/arm-none-eabi
LIBGCCDIR =$(TOOLPATH)/lib/gcc/arm-none-eabi/6.3.1
LIBC =$(TOOLPATH)/arm-none-eabi/lib/libc.a
LIBGCC = $(TOOLPATH)/lib/gcc/arm-none-eabi/6.3.1/libgcc.a

## User library for UART1 Driver
MY_LIB_PATH = $(TOPDIR)/Libraries
LIBUART =  $(MY_LIB_PATH)/libUart1.a


#### Option Definition ####
INCLUDE	=  -I$(TOPDIR)/SOURCE -I$(LIBCDIR)/include -I$(LIBGCCDIR)/include

CFLAGS	+= $(INCLUDE) -g -Wall -Wstrict-prototypes -Wno-trigraphs -O0
CFLAGS	+= -fno-strict-aliasing -fno-common -pipe
CFLAGS += -march=armv4t -mtune=arm9tdmi -fno-builtin -mapcs

LDFLAGS	= -Bstatic -nostartfiles -T ../S3C2450-RAM.ld -Map 2450main.map
OCFLAGS = -O binary -R .note -R .comment -S

2450TEST = MDS2450.bin

all: $(2450TEST)

$(2450TEST) :
	make -C $(TOPDIR)/SOURCE || exit 1

	cp $(TOPDIR)/SOURCE/MDS2450 $(TOPDIR)/output
	$(OBJCOPY) $(OCFLAGS) $(TOPDIR)/SOURCE/MDS2450 $(TOPDIR)/output/$@

clean:
	make -C $(TOPDIR)/SOURCE clean
	rm -f $(TOPDIR)/output/$(2450TEST)
	rm -f $(TOPDIR)/output/MDS2450

dep:
	make -C $(TOPDIR)/SOURCE dep
