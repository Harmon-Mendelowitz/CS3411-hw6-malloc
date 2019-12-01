#include "types.h"
#include "user.h"

int
main(void)
{
    int val = 0;
    for(int x=12; x<=4092; x+=7)
    {
        val += x;
    }
    printf(1, "expected allocated mem: %d\n", val);

    for(int x=12; x<4092; x+=7)
    {
        void* m = p2malloc(x);
        //printf(1, "address: %p\n", &m);
        memset(m, 'a', x);
        //char* i = (char *)m;
        //printf(1, "value: %d\n", *i);
        //p2free(m);
    }



    int a = p2allocated();
    int t = p2totmem();
    printf(1, "allocated mem: %d\n", a);
    printf(1, "total mem: %d\n", t);

    exit();
}