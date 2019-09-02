from subprocess import run
from time import time
import os
from os.path import exists
from os.path import join

TD_PATH='testdata/'
INP_NAME='input{}.txt'
OUT_NAME='output{}.txt'

for i in range(1, 101):
    out=join(TD_PATH, OUT_NAME.format(i))
    if exists(out):
        os.remove(out)

if run(['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', '-pedantic', '-o', 'sol_ian.out', 'sol_ian_ac.cpp']).returncode!=0:
    raise

for i in range(1, 101):
    inp=join(TD_PATH, INP_NAME.format(i))
    out=join(TD_PATH, OUT_NAME.format(i))
    if not exists(inp):
        continue
    print(f'{inp}:')
    t=time()
    if run('./sol_ian.out', stdin=open(inp), stdout=open(out, 'w', newline='\n', encoding='utf-8')).returncode!=0:
        raise
    print(f'      {str((time()-t)*1000)[:8]} ms')
    print(' '*30+open(out).read().strip())

print('')
