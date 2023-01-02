C=gcc
CFLAGS=-Wall
LIBS = -L./SDL2_ttf/.libs -L./SDL2_image/.libs
LDFLAGS= `sdl2-config --cflags --libs` -lSDL2_ttf -lm
INCLUDES= -I./SDL2_ttf -I./SDL2_image
EXEC=PacMan
SRC= main.c graphic.c niveau.c jeu.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

PacMan: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) -o $@ -c $<
clean:
		rm -rf *.o *~
mrproper: clean
		rm -rf $(EXEC)
