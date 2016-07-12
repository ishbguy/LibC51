NAME	:= test
BIN 	:= $(NAME).bin
SRC 	:= $(NAME).c clock.c delay.c dht11.c lcd1602.c relay.c uart.c interrupt_service.c
INC	:= lib app
OBJ 	:= $(subst .c,.rel,$(SRC))
OUTPUT	:= *.bin *.hex *.ihx *.asm *.lk *.lst *.map *.mem *.rel *.rst *.sym

# Compiler options, tell compiler where to include files
CC  	:= sdcc
CFLAG 	:= -c
CFLAG	+= $(addprefix -I,$(INC))

# Tell make where the dependence files are.
#VPATH	:= $(INC)
vpath %.c %.h $(INC)

# Operations for flash, clean
FLASH 	:= /samba/project/git/stcflash/stcflash.py
RM    	:= rm -rf

.PHONY : all
all : $(BIN)
	
$(BIN) : $(NAME).hex
	objcopy -I ihex -O binary $^ $@

$(NAME).hex : $(NAME).ihx
	packihx  $^ > $@

$(NAME).ihx : $(OBJ)
	$(CC) $^

%.rel : %.c
	$(CC) $(CFLAG) $^

flash : $(BIN)
	sudo $(FLASH) $(BIN)

.PHONY : clean
clean :
	$(RM) $(OUTPUT)
