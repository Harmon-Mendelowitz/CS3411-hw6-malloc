#include "types.h"
#include "user.h"

int
main(void)
{

    void **ptr = malloc(8 * sizeof(void *));
    for(int x=0; x<8; x++)
    {
        void* m = p2malloc(12);
        memset(m, 'a'+x, 12);
        ptr[x] = m;
    }

    int a = p2allocated();
    printf(1, "allocated mem (full): %d\n", a);

    char* i = (char *)ptr[2];
    printf(1, "value: %c\n", *i);
    p2free(ptr[2]);
    i = (char *)ptr[1];
    printf(1, "value: %c\n", *i);
    p2free(ptr[1]);
    i = (char *)ptr[3];
    printf(1, "value: %c\n", *i);
    p2free(ptr[3]);
    i = (char *)ptr[5];
    printf(1, "value: %c\n", *i);
    p2free(ptr[5]);

    a = p2allocated();
    printf(1, "allocated mem (half): %d\n", a);

    i = (char *)ptr[7];
    printf(1, "value: %c\n", *i);
    p2free(ptr[7]);
    i = (char *)ptr[0];
    printf(1, "value: %c\n", *i);
    p2free(ptr[0]);
    i = (char *)ptr[4];
    printf(1, "value: %c\n", *i);
    p2free(ptr[4]);
    i = (char *)ptr[6];
    printf(1, "value: %c\n", *i);
    p2free(ptr[6]);




    a = p2allocated();
    int t = p2totmem();
    printf(1, "allocated mem (0): %d\n", a);
    printf(1, "total mem: %d\n", t);

    exit();
}