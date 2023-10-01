#@copyright : Eng_Menna_Gabely =============> Makefile <=============

CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)                   # APP.o UART.o
As = $(wildcard *.s)                 #startup.o
AsOBJ = $(As:.s=.o)    
Project_name=learn_in_depth_cortex_m3

all: $(Project_name).bin
	@echo "_______________________Build-is-Done_______________________"

#startup.o:	startup.s
#	$(CC)as.exe $(CFLAGS) $< -o $@ 2> log */
%.o:	%.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf:	$(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(LIBS) $(AsOBJ) -o $@ -Map=Map_file.map

$(Project_name).bin:	$(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@
	
clean_all:	
	rm *.o *.bin *.elf
	@echo "_______________________Everything-is-Deleted_______________________"
clean:	
	rm *.bin *.elf