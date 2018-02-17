EXECS=compare_bcast
MPICC?=mpicc

all: ${EXECS}

compare_bcast: compare_bcast.c
	${MPICC} compare_bcast.c -o compare_bcast

clean:
	rm -f ${EXECS}
