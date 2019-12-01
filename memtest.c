#include "types.h"
#include "user.h"

int
main(void)
{

    for(int x=0; x<26; x++)
    {
        void* m = p2malloc(12);
        printf(1, "address: %p\n", m);
        memset(m, x, 12);
        char* i = (char *)m;
        printf(1, "value: %d\n", *i);
        p2free(m);
    }

    int a = p2allocated();
    int t = p2totmem();

    printf(1, "allocated mem: %d\n", a);
    printf(1, "total mem: %d\n", t);

    exit();
}