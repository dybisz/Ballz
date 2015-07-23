CC = g++
INCLUDE = -I include/ -I include/glm/
L_FLAGS = -lSDL2 -lGL -lGLU -lGLEW
C_FLAGS = -Wall ${INCLUDE}
OBJ = main.o game.o main_menu.o button.o point.o floating_window.o gl_util.o \
	   buffer_object.o ball.o shader.o shader_program.o perspective_cam.o terrain.o
	   
BUILD = build/
SRC = src/

.PHONY: clean

all: ballz copy 

ballz: ${OBJ}
	${CC} -o ballz ${OBJ} ${L_FLAGS}

main.o: ${SRC}main.cc
	@echo "----- COMPILING main.o -----"
	${CC} ${C_FLAGS} -o main.o -c ${SRC}main.cc

buffer_object.o: ${SRC}buffer_object.cc
	@echo "----- COMPILING buffer_object.o -----"
	${CC} -o buffer_object.o -c ${SRC}buffer_object.cc ${C_FLAGS}

perspective_cam.o: ${SRC}perspective_cam.cc
	@echo "----- COMPILING perspective_cam.o -----"
	${CC} -o perspective_cam.o -c ${SRC}perspective_cam.cc ${C_FLAGS}

game.o: ${SRC}game.cc
	@echo "----- COMPILING game.o -----"
	${CC} -o game.o -c ${SRC}game.cc ${C_FLAGS}

main_menu.o: ${SRC}main_menu.cc
	@echo "----- COMPILING main_menu.o -----"
	${CC} -o main_menu.o -c ${SRC}main_menu.cc ${C_FLAGS}

gl_util.o: ${SRC}gl_util.cc
	@echo "----- COMPILING gl_util.o -----"
	${CC} -o gl_util.o -c ${SRC}gl_util.cc ${C_FLAGS}

button.o: ${SRC}button.cc
	@echo "----- COMPILING button.o -----"
	${CC} -o button.o -c ${SRC}button.cc ${C_FLAGS}

point.o: ${SRC}point.cc
	@echo "----- COMPILING point.o -----"
	${CC} -o point.o -c ${SRC}point.cc ${C_FLAGS}

floating_window.o: ${SRC}floating_window.cc
	@echo "----- COMPILING floating_window.o -----"
	${CC} -o floating_window.o -c ${SRC}floating_window.cc ${C_FLAGS}

shader.o: ${SRC}shader.cc
	@echo "----- COMPILING shader.o -----"
	${CC} -o shader.o -c ${SRC}shader.cc ${C_FLAGS}

ball.o: ${SRC}ball.cc
	@echo "----- COMPILING ball.o -----"
	${CC} -o ball.o -c ${SRC}ball.cc ${C_FLAGS}

shader_program.o: ${SRC}shader_program.cc
	@echo "----- COMPILING shader_program.o -----"
	${CC} -o shader_program.o -c ${SRC}shader_program.cc ${C_FLAGS}

terrain.o: ${SRC}terrain.cc
	@echo "----- COMPILING terrain.o -----"
	${CC} -o terrain.o -c ${SRC}terrain.cc ${C_FLAGS}

copy:
	mkdir -p ${BUILD}; mv *.o ${BUILD}
	
clean:
	rm ${BUILD}*.o

# CFLAGS = 'sdl2-config --cflags'
# LIBS = 'sd2-config --libs'
