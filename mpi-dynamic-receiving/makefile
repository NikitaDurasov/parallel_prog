EXECS=check_status probe
MPICC?=mpicc

all: ${EXECS}

check_status: check_status.c
	${MPICC} check_status.c -o check_status

probe: probe.c
	${MPICC} probe.c -o probe

clean: 
	rm -f ${EXECS}
