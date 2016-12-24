CC = gcc
LDFLAGS =
CFLAGS = -g -c
SRC = $(wildcard *.c src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(OBJ) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o src/*.o $(EXEC)