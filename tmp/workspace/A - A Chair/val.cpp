#include"testlib.h"
#include<cstdio>
const int k=1;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    int n=inf.readInt(2, 1000);
    inf.readSpace();
    int m=inf.readInt(1, 100000);
    inf.readEoln();
    printf("n=%d, m=%d, k=%d\n", n, m, k);

    for(int t=0; t<m; t++)
    {
        int i=inf.readInt(1, n);
        inf.readSpace();
        int u=inf.readInt(0, k);
        inf.readSpace();
        int j=inf.readInt(1, n);
        inf.readSpace();
        int v=inf.readInt(0, k);
        inf.readEoln();
        ensure(i!=j);
    }

    inf.readEof();
}
