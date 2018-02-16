EXECS=random_walk
MPICXX?=mpicxx

all: ${EXECS}

random_walk: random_walk.cpp
	${MPICXX} random_walk.cpp -o random_walk

clean: 
	rm -f ${EXECS}
