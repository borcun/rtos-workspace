CC=gcc
CFLAGS=-c -Wall
LFLAGS=-o
SRC=main.c
OBJ=main.o
EXEC=recursive-mutex
RM=rm -rf

.PHONY: clean

all: ${EXEC}

${OBJ}: ${SRC}
	${CC} ${CFLAGS} ${SRC}

${EXEC}: ${OBJ}
	${CC} ${OBJ} ${LFLAGS} ${EXEC}

clean:
	${RM} ${OBJ} ${EXEC} *~
