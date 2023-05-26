CC=gcc
CFLAGS=-I. -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra -g3 -Og
DEPS = enemy.h player.h
OBJ = main.o enemy.o player.o
EXE = MegaMorte

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

exe:
	.\$(EXE)

clean:
	rm *.o $(EXE).exe