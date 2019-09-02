from random import *
import os
from os.path import exists
from os.path import join

seed(12345)

K=2
N_MIN=2
N_MAX=500
M_MIN=1
M_MAX=10000

ID=0
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

def gen(n, m, hrange, maxdcratio, randm):
    start()
    
    if min(maxdcratio)<=0 or max(maxdcratio)<1:
        raise
    maxdcratio=[0]+maxdcratio
    if randm<0 or randm>m:
        raise
    
    H=[-1]+choices(hrange, k=n)
    E=[choices(range(1, n+1), k=2) for _ in range(m)]
    maxd=max(map(lambda x: H[x[1]]-H[x[0]], E))
    print('maxd='+str(maxd))
    C=[max(1, round(maxd*x)) for x in maxdcratio]
    C[0]=0
    
    for i in range(m):
        can=[[E[i][1], u, E[i][0], v] for u in range(K+1) for v in range(K+1) if H[E[i][0]]+C[v]-C[u]>=H[E[i][1]]]
        if not can:
            raise
        E[i]=choice(can)
    
    for i in range(randm):
        E[i]=[randint(1, n), randint(0, K), randint(1, n), randint(0, K)]
    
    shuffle(E)
    
    write(n, m, E)

def gen2(cyc):
    start()
    
    s, F=0, []
    for n, randm, c, randc in cyc:
        if n<2 or randm<0:
            raise
        
        c=[-1]+c
        pos, neg=[], []
        for i in range(1, K+1):
            if c[i]>0:
                pos+=[i]*c[i]
            elif c[i]<0:
                neg+=[i]*-c[i]
        if randc<0 or max(len(pos), len(neg))+randc>n:
            raise
        for _ in range(randc):
            t=randint(1, K)
            pos+=[t]
            neg+=[t]
        
        E=[[u, u%n+1]+[0]*K for u in range(1, n+1)]
        
        sel=sample(range(n), k=len(pos))
        for i in range(len(pos)):
            E[sel[i]][pos[i]+1]+=1
        sel=sample(range(n), k=len(neg))
        for i in range(len(neg)):
            E[sel[i]][neg[i]+1]-=1
        
        totallength=0
        for _ in range(randm):
            u=randint(0, n-1)
            steps=randint(1, max(1, min(n//2, n//(max(1, max(len(pos), len(neg))-randc))*2)))
            p=u
            csum=[0]*(K+1)
            can=[]
            for step in range(steps):
                csum=[sum(x) for x in zip(csum, [0]+E[p][2:2+K])]
                if max(csum)<=1 and sum(x==1 for x in csum)<=1:
                    can+=[[p, step, csum]]
                p=(p+1)%n
            p, step, csum=choice(can)
            totallength+=step+1
            can=[]
            for i in range(K+1):
                for j in range(K+1):
                    if i==j and i>0:
                        continue
                    tsum=[0]*(K+1)
                    tsum[i]+=1
                    tsum[j]-=1
                    tsum[0]=0
                    if min(x[0]-x[1] for x in zip(tsum, csum))>=0:
                        can+=[tsum[1:1+K]]
            E+=[[E[u][0], E[p][1]]+choice(can)]
        print(f'n={n} randm={randm} c={c[1:1+K]} randc={randc} averagelength={str(totallength/max(1, randm))[:8]}')
        
        for e in E:
            i, j=e[1]+s, e[0]+s
            cnt=[0]+e[2:2+K]
            if max(map(abs, cnt))>1 or sum(x==1 for x in cnt)>1 or sum(x==-1 for x in cnt)>1:
                raise
            u=v=0
            for k in range(1, K+1):
                if cnt[k]<0:
                    u=k
                elif cnt[k]>0:
                    v=k
            F+=[[i, u, j, v]]
        s+=n
    
    p=list(range(1, s+1))
    shuffle(p)
    p=[-1]+p
    for e in F:
        e[0]=p[e[0]]
        e[2]=p[e[2]]
    shuffle(F)
    
    write(s, len(F), F)

if not exists(TD_PATH):
    os.mkdir(TD_PATH)

for i in range(1, 101):
    inp=join(TD_PATH, INP_NAME.format(i))
    if exists(inp):
        os.remove(inp)

for i in range(0, 3, 2):#i=0:yes, i>0:?
    gen(50, 100, range(1001, 1101), [1, 0.1], i)
    gen(50, 1000, range(1001, 1011), [1.5, 0.5], i)
    gen(100, 2000, range(10001, 11001), [1.1, 0.01], i)
    gen(100, 5000, range(10001, 11001), [1, 0.9], i)
    gen(100, 8000, range(10001, 10101), [1.1, 1], i)#weak
    gen(100, 10000, range(10001, 10011), [1, 1.1], i)
    gen(300, 6000, range(10001, 10006), [1.1, 0.7], i)
    gen(300, 8000, range(10001, 10006), [1.1, 0.7], i)
    gen(300, 10000, range(10001, 10006), [1.1, 0.7], i)
    gen(500, 4000, range(10001, 20001), [0.5, 1.3], i)
    gen(500, 7000, range(10001, 10101), [0.8, 1.1], i)
    gen(500, 10000, range(10001, 10011), [0.8, 1.1], i)
    gen(500, 9000, range(10001, 10011), [1, 0.2], i)
    gen(500, 10000, range(10001, 10011), [1, 0.2], i)
    gen(500, 10000, range(10001, 10101), [5, 4.5], i)#weak

gen2(cyc=[[36, 9000, [9, -11], 10], [79, 20, [-9, 11], 60]])#yes
gen2(cyc=[[48, 4000, [5, -7], 0], [64, 5000, [-5, 7], 1]])#yes
gen2(cyc=[[290, 5499, [-2, 7], 0], [98, 2000, [2, -7], 0], [98, 2000, [2, -6], 90], [9, 1, [2, -5], 0]])#yes
gen2(cyc=[[416, 6514, [251, -301], 100], [45, 1000, [-5, 6], 10], [11, 2000, [-2, 8], 1], [9, 5, [3, -2], 5]])#yes
gen2(cyc=[[300, 5000, [-76, 65], 10], [94, 2000, [76, -66], 10], [94, 2000, [5, -2], 10]])#no
gen2(cyc=[[416, 9000, [-100, 200], 100], [64, 100, [-3, 2], 50], [11, 400, [3, -5], 0]])#no
gen2(cyc=[[249, 5000, [-2, 2], 2], [249, 4500, [40, -45], 200]])#no
gen2(cyc=[[249, 400, [201, -202], 1], [251, 9000, [-203, 204], 40]])#no
