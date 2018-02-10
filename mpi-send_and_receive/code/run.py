#!/usr/bin/python
import sys
import os
import subprocess

sys_call = ''
if sys.argv[1] == 'send_recv':
    sys_call = 'mpirun -n 3 ./send_recv'
print(sys_call)
subprocess.call([sys_call], shell=True)
