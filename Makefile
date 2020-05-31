
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gtk+-3.0) -I$(shell pwd)
LDFLAGS=$(shell pkg-config --libs gtk+-3.0)
SRC=$(wildcard dlg*.c)
OBJ=$(SRC:.c=.o)

dialog : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : dlg.h

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f *.o dialog
