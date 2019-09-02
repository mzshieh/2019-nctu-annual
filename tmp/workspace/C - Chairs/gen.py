from random import *
import os
from os.path import exists
from os.path import join

seed(12345)

K=4
N_MIN=2
N_MAX=44
M_MIN=1
M_MAX=4444

ID=19
TD_PATH='testdata/'
INP_NAME='input{}.txt'

def start():
    global ID
    ID+=1
    print(f'generating {join(TD_PATH, INP_NAME.format(ID))}')

def write(n, m, E):
    if n<N_MIN or n>N_MAX:
        raise
    if m<M_MIN or m>M_MAX:
        raise
    if len(E)!=m:
        raise
    for e in E:
        if len(e)!=4 or e[0]<1 or e[0]>n or e[2]<1 or e[2]>n:
            raise
        if e[1]<0 or e[1]>K or e[3]<0 or e[3]>K:
            raise
    
    with open(join(TD_PATH, INP_NAME.format(ID)), 'w', newline='\n', encoding='utf-8') as inp:
        print(n, m, file=inp)
        for e in E:
            print(*e, file=inp)
    print('done')

def gen(n, m, H, C):
    start()

    h = [randrange(*H) for _ in range(n)]
    c = [0]+[randrange(*C) for _ in range(4)]
    E = []

    for i in range(n):
      for j in range(n):
        if i == j:
          continue
        for k in range(5):
          for l in range(5):
            if h[i] + c[k] <= h[j] + c[l]:
              E.append((i+1,k,j+1,l))

    shuffle(E)
    write(n, m, E[:m])

if not exists(TD_PATH):
    os.mkdir(TD_PATH)

for i in range(ID+1, 101):
    inp=join(TD_PATH, INP_NAME.format(i))
    if exists(inp):
        os.remove(inp)

gen(10, 5, [1, 100], [1, 100])
gen(10, 20, [100, 200], [80, 120])
gen(10, 30, [100, 200], [1, 2])
gen(44, 4444, [100, 200], [0, 1])
gen(34, 4344, [324, 1200], [10, 3431])
gen(34, 4344, [1, 1000], [10000, 13431])
gen(44, 4444, [10*5, 10*5+123], [10*5-33, 10*5+55])
gen(44, 4444, [10*5, 10*5+123], [10*5-33, 10*5+55])
gen(44, 4444, [10*5, 10*5+123], [10*5-33, 10*5+55])
gen(44, 4444, [10*5, 10*5+123], [10*5-33, 10*5+55])
gen(44, 4444, [10*5, 10*5+123], [10*5-33, 10*5+55])

