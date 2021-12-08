#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]){
    // implement of memcount
    printf("%d\n", memtop());
    exit(0);
}