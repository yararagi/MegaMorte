CC=gcc
CFLAGS=-I. -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra -O3
DEPS = enemy.h player.h laser.h
OBJ = main.o enemy.o player.o laser.o
EXE = MegaMorte

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

exe:
	.\$(EXE)

clean:
	rm *.o $(EXE).exe