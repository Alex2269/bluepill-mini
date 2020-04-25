.PHONY: all clean load
# BUILD = build
TARGET = main
SOURCES = src

INC = inc/
LIB = lib/

CC=arm-none-eabi-gcc
LD = arm-none-eabi-ld 
CFLAGS = -Wall -g -O2 -specs=nosys.specs -specs=nano.specs \
-c -fno-common -D"assert_param(x)=" \
-mcpu=cortex-m3 -mthumb -march=armv7-m

#-std=c99 -lm -lc
#-nostartfiles 
#--specs=nosys.specs
LDFLAGS =   -marmelf --gc-sections 
#-lgcc
#-L/usr/lib/arm-none-eabi/lib/thumb/v7e-m/ -L/usr/lib/gcc/arm-none-eabi/7.3.1/ \
#-L/usr/lib/arm-none-eabi/lib/thumb/v7e-m/fpv4-sp/hard/
#LFLAGS = -nostartfiles -lm -lc \
		-L/usr/lib/arm-none-eabi/lib/thumb/v7e-m/fpv4-sp/hard/ #для FPU
LFLAGS_END = -lm -lc
#-L/usr/lib/arm-none-eabi/bin/
#-Xlinker
MCU = cortex-m3

all: $(TARGET).bin $(TARGET).lst $(TARGET).elf 

$(TARGET).bin: $(TARGET).elf
	arm-none-eabi-objcopy $(TARGET).elf $(TARGET).bin -O binary

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

$(TARGET).lst: $(TARGET).elf
	arm-none-eabi-objdump -D $(TARGET).elf > $(TARGET).lst

$(TARGET).elf: startup.o $(TARGET).o
	$(LD) -o $(TARGET).elf -T$(LIB)stm32f103.ld startup.o $(TARGET).o -I$(LIB) $(LDFLAGS) 
#$(CC) -o $(TARGET).elf -T$(LIB)stm32f407vg.ld startup.o system_stm32f4xx.o $(TARGET).o -I$(LIB)  
	arm-none-eabi-size $(TARGET).elf

#-L/usr/lib/arm-none-eabi/lib/thumb/v7e-m/ -L/usr/lib/gcc/arm-none-eabi/7.3.1/ -L/usr/lib/arm-none-eabi/bin/
#	--data-sections

startup.o: 	$(LIB)startup.s
	arm-none-eabi-as -mthumb -mcpu=cortex-m3 $(LIB)startup.s -o startup.o -I$(LIB) 
#$(CFLAGS) 

$(TARGET).o: $(SOURCES)/$(TARGET).cpp $(INC)
	$(CC)  -c $(SOURCES)/$(TARGET).cpp -o $(TARGET).o -I$(LIB) -I$(INC) $(CFLAGS) 
#	arm-none-eabi-objdump $(TARGET).o -h

clean:
	rm -rf *.o *.elf *.lst *.bin *.map

