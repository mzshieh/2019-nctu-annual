
import sys
import glob
import subprocess

prob=sys.argv[1].strip()
glp='/tmp/glp.txt'

for i in range(1, 100):
  inp=glob.glob(f'{prob}*/testdata/input{i}.txt')
  out=glob.glob(f'{prob}*/testdata/output{i}.txt')
  if inp==[]:
    break
  inp=inp[0]
  out=out[0]
  with open(inp, 'r') as src:
    with open(glp, 'w') as dst:
      fp=dst
      n, m=map(int, src.readline().split())
      k=4
      print('Maximize', file=fp)
      print('\tobj: A', file=fp)
      print('Subject To', file=fp)
      cnt=1
      for i in range(1, 5):
        print(f'\tcon{cnt}: A - C{i} <= 0', file=fp)
        cnt+=1
      for i in range(m):
        i, u, j, v = map(int, src.readline().split())
        if i==j:
          continue
        elif u==v:
          print(f'\tcon{cnt}: H{i} - H{j} <= 0', file=fp)
        else:
          print(f'\tcon{cnt}: H{i} + C{u} - H{j} - C{v} <= 0', file=fp)
        cnt+=1
      print('Bounds', file=fp)
      for i in range(1, 5):
        print(f'\t0 <= C{i} <= +inf', file=fp)
      for i in range(1, n+1):
        print(f'\t0 <= H{i} <= +inf', file=fp)
      print('End', file=fp)
  res=subprocess.run(['glpsol', '--max', '--lp', glp], stdout=subprocess.PIPE, stderr=None)
  print(res.stdout)

  if 'HAS UNBOUNDED PRIMAL SOLUTION' in str(res.stdout):
    res='YES'
  else:
    res='NO'

  with open(out, 'r') as src:
    ans=src.readline().strip()
    print(ans, res, ans==res, sep='\t')





