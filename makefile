NAME	:= test
BIN 	:= $(NAME).bin
SRC 	:= $(NAME).c delay.c dht11.c interrupt.c lcd1602.c relay.c timer.c uart.c
OBJ 	:= $(subst .c,.rel,$(SRC))
CC  	:= sdcc
CFLAG 	:= -c
OUTPUT	:= *.bin *.hex *.ihx *.asm *.lk *.lst *.map *.mem *.rel *.rst *.sym
FLASH 	:= /samba/project/git/stcflash/stcflash.py
RM    	:= rm -rf

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

clean :
	$(RM) $(OUTPUT)
