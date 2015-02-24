CFLAGS+=-Wall -I../lib 
LDFLAGS+=-L../lib 

.PHONY: all clean

all: lm75

lm75: lm75.o
	$(CC) $(LDFLAGS) lm75.o -o lm75

lm75.o: lm75.c
	$(CC) $(CFLAGS) -c lm75.c

clean:
	rm *.o lm75
