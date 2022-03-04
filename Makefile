CC=gcc
LD_FLAGS:=
CC_FLAGS:=
DEFINES:=
INCLUDES:=
FLAGS= $(LD_FLAGS) $(CC_FLAGS) $(DEFINES) $(INCLUDES)

SRC=$(wildcard *.c)
OBJ=$(subst .c,.o,$(SRC))

BIN=prog

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

%.o: %.c
	@ echo "$< and $@"
	$(CC) -c $< -o $@ $(FLAGS)

.PHONY: clean run

clean:
	rm $(BIN) *.o

run: $(BIN)
	./$<
