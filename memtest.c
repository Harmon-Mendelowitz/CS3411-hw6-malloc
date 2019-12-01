#include "types.h"
#include "user.h"

int
main(void)
{

    for(int x=0; x<1000; x++)
    {
        void* m = p2malloc(12);
        memset(m, 5, 12);
        p2free(m);
    }

    p2allocated();
    p2totmem();

    exit();
}