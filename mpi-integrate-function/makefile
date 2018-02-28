EXEC=run
MPICC?=mpicc

all: run 

run: run.c func.c func.h
	${MPICC} run.c func.c -o run -std=c11
