#include "types.h"
#include "user.h"

int
main(void)
{
    //allocate
    void **ptr = malloc(10 * sizeof(void *));
    for(int x=1; x<=4; x++)
    {
        void* m = p2malloc(18*x);
        memset(m, 'a'+x, 18*x);
        ptr[x-1] = m;
    }

    int a = p2allocated();
    printf(1, "allocated mem (180): %d\n", a);
    int t = p2totmem();
    printf(1, "total mem (3*4096): %d\n", t);


    for(int x=0; x<5; x++){
        //free
        p2free(ptr[1]);
        //re-allocate
        void* m = p2malloc(38);
        memset(m, 'a'+2, 38);
        ptr[1] = m;

        a = p2allocated();
        printf(1, "allocated mem (182): %d\n", a);
        t = p2totmem();
        printf(1, "total mem (3*4096): %d\n", t);
    }

    void* m = p2malloc(4090);
    memset(m, 'a', 4090);
    ptr[4] = m;

    a = p2allocated();
    printf(1, "allocated mem (4272): %d\n", a);
    t = p2totmem();
    printf(1, "total mem (4*4096): %d\n", t);

    void* n = p2malloc(4090);
    memset(n, 'a', 4090);
    ptr[5] = n;

    a = p2allocated();
    printf(1, "allocated mem (8362): %d\n", a);
    t = p2totmem();
    printf(1, "total mem (5*4096): %d\n", t);

    p2free(ptr[5]);
    p2free(ptr[4]);
    p2free(ptr[0]);

    a = p2allocated();
    printf(1, "allocated mem (164): %d\n", a);
    t = p2totmem();
    printf(1, "total mem (5*4096): %d\n", t);

    exit();
}