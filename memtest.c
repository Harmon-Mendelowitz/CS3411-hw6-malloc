#include "types.h"
#include "user.h"

int
main(void)
{

    void* m = p2malloc(4);
    p2free(m);
    p2allocated();
    p2totmem();

    exit();
}