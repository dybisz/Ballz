CC = g++
L_FLAGS = -lSDL2 -lGL -lGLU # -lglut -lGLU -lm
C_FLAGS = -Wall
OBJ = main.o game.o main_menu.o gl_util.o

.PHONY: game clean

all: ballz clean

ballz: ${OBJ}
	${CC} -o ballz ${OBJ} ${L_FLAGS}

main.o: main.cpp
	@echo "----- COMPILING main.o -----"
	${CC} -o main.o -c main.cpp ${C_FLAGS}

game.o: game.cpp
	@echo "----- COMPILING game.o -----"
	${CC} -o game.o -c game.cpp ${C_FLAGS}

main_menu.o: main_menu.cpp
	@echo "----- COMPILING main_menu.o -----"
	${CC} -o main_menu.o -c main_menu.cpp ${C_FLAGS}

gl_util.o: gl_util.cpp
	@echo "----- COMPILING gl_util.o -----"
	${CC} -o gl_util.o -c gl_util.cpp ${C_FLAGS}

clean:
	rm *.o

# CFLAGS = 'sdl2-config --cflags'
# LIBS = 'sd2-config --libs'