TOPC Problem setting
===

## David's Factoring Problem
A well known NP-intermediate problem, integer factoring, serve as an important role in many RSA crypto-systems. David, as a number theorist, created another kind of factoring as following.

Given $a_0, a_1\in\{0,1,\dots p-1\}$ and $2\leq p<2^{31}$ a prime. Find $b_0, b_1\in\{0,1,\dots p-1\}$ so the following holds,
$$
a_0=b_0\cdot b_1 \mod p\\
a_1=b_0+b_1\mod p.
$$

"This factoring is way more cool, in the sense that it can now be computed efficiently," said David. Now, he invites you to enjoy this new variant of factoring.




### Input
The first line contains an integer $1\leq T\leq 100$ indicating the number of test cases.
For each test cases, there's a line of $p, a_0, a_1$ seperated by a single blank.

### Output
For each test case, output a line containing $b_0, b_1$ in acending order seperated by a single blank. If there's no solution, output a line of $-1$.

### Sample

- Input/Output 1
```
2
2 1 0
2 1 1
```
---
```
1 1
-1
```

## P-adic Equations
Kurt's got some equations to solve, help him out! You will be given the following items:
- a prime $p$, integer $2\leq n\leq 200$, integer $1\leq k$
- a square matrix $A\mod p$ of size $n\times n$
- an integer vector $0\leq b=\pmatrix{b_1\\b_2\\\vdots\\b_n}$ of size $n\times 1$
- an integer $k$

Matrix A is guaranteed to be invertible mod p. Try to solve for $x\mod p^k$ where
$$
Ax\equiv b\mod p^k
$$
It is guaranteed that $p^k<2^{31}$ and $\forall b_i: 0\leq b_i<2^{31}$

### Input
The first line contains $p, n, k$ seperated by single blanks. The second line contains $b_1,...,b_n$ the elements of $b$. Then for the next $n$ lines, the i'th line contains $a_{i,1},a_{i,2},\dots,a_{i,n}$, where $a_{i,j}$ is the i'th row j'th column element of $A$.

### Output
Output a line containing $x_1,\dots x_n$ seperated by blanks.

### Sample

- Input/Output 1
```
3 2 1
2 1
1 1
1 2
```
---
```
0 2
```
- Input/Output 2
```
3 2 1
0 2
1 1
1 2
```
---
```
1 2
```

- Input/Output 3
```
3 2 2
0 2
1 1
1 2
```
---
```
7 2
```
- Input/Output 4
```
3 2 3
0 2
1 1
1 2
```
---
```
25 2
```

