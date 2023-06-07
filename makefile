CC=clang
CFLAGS=-I. -Wall -Wextra -O3
FLAGLIBS=-lraylib -lopengl32 -lgdi32 -lwinmm
DEPS = enemy.h player.h laser.h
OBJ = main.o enemy.o player.o laser.o
EXE = MegaMorte

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(FLAGLIBS)

exe:
	.\$(EXE)

clean:
	rm *.o $(EXE).exe