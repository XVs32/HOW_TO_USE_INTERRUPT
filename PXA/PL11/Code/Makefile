OUTPUT_NAME=lab

PROJECT_PATH=./
COMMON_PATH=./common
INCLUDE_PATH1=$(PROJECT_PATH)
INCLUDE_PATH2=$(COMMON_PATH)/driver
INCLUDE_PATH3=$(COMMON_PATH)/gnu/include
VPATH = $(PROJECT_PATH):$(COMMON_PATH)

#
# Include the make variables (CC, etc...)
#
PREFIX=/usr/local
CROSS_COMPILE = arm-elf-
CC=$(PREFIX)/bin/$(CROSS_COMPILE)gcc
LD=$(PREFIX)/bin/$(CROSS_COMPILE)ld

DBGFLAGS= -g 
OPTFLAGS= -O0
AFLAGS_DEBUG := -Wa,-gstabs

CFLAGS= -nostartfiles $(DBGFLAGS) $(OPTFLAGS) -I$(INCLUDE_PATH1) -I$(INCLUDE_PATH2) -I$(INCLUDE_PATH3) -I. 
AFLAGS=-mapcs-32 -msoft-float -mno-fpu  $(AFLAGS_DEBUG) $(CFLAGS)
LFLAGS= -Wl,-M,-Map=$(OUTPUT_NAME).map

PROJECT_OBJS =  main.o uart.o
GNU_OBJS     =  gnu/src/sbrk.o  gnu/src/mmulib.o gnu/src/startup.o gnu/src/low-level-init.o
REUSE_OBJS   =  driver/common/src/mmu.o driver/common/src/creator_io.o driver/common/src/stdin_out.o 
REUSE_OBJS  +=  driver/irq/src/irq.o driver/lcd/src/lcd.o driver/timer/src/os_timer.o driver/common/src/scan.o
OBJS         = $(PROJECT_OBJS) $(GNU_OBJS) $(REUSE_OBJS)

all : $(OBJS) 
	$(CC)  -T$(OUTPUT_NAME).ld $(LFLAGS) -o "$(OUTPUT_NAME).axf" $(notdir $(OBJS)) $(LIBMODULES)	
	arm-elf-objcopy -O binary -S $(OUTPUT_NAME).axf $(OUTPUT_NAME).bin

	
%.o:	%.S
	$(CC) $(AFLAGS) -c -o $(notdir $@) $<
%.o:	%.c
	$(CC) $(CFLAGS) -c -o $(notdir $@) $<
	

.PHONY : clean
clean:
	rm *.bin *.axf *.o *.s *.map	

