import os
from os.path import exists
from os.path import join


TD_PATH='testdata/'
INP_NAME='input{}.txt'

for i in range(1, 101):
    inpf=join(TD_PATH, INP_NAME.format(i))
    if exists(inpf):
      with open(inpf, 'r') as inp:
        n,m = inp.readline().split()
        e = []
        for line in inp:
          i,u,j,v = line.split()
          if i != j:
            e.append((i,u,j,v))

      with open(inpf, 'w') as inp:
        inp.write(f"{n} {len(e)}\n")
        for x in e:
          inp.write("{}\n".format(" ".join(x)))

