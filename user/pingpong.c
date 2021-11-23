#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]){
    char msg = '0'; // signal
    int l_to_r[2], r_to_l[2];   // pipe
    pipe(l_to_r);
    pipe(r_to_l);
    if(fork() == 0){    // left-child
        // close the default stdin/stdout
        close(0);
        close(1);
        dup(l_to_r[1]); // write
        dup(r_to_l[0]); // read
        close(l_to_r[0]);
        close(l_to_r[1]);
        close(r_to_l[0]);
        close(r_to_l[1]);
        write(1, &msg, 1);
        printf("%d: ping", getpid());
        read(0, &msg, 1);
    }
    if(fork() == 0){    // right-child
        // close the default stdin/stdout
        close(0);
        close(1);
        dup(r_to_l[1]); // write
        dup(l_to_r[0]); // read
        close(l_to_r[0]);
        close(l_to_r[1]);
        close(r_to_l[0]);
        close(r_to_l[1]);
        read(0, &msg, 1);
        printf("%d: pong", getpid());
        write(1, &msg, 1);
    }
    close(l_to_r[0]);
    close(l_to_r[1]);
    close(r_to_l[0]);
    close(r_to_l[1]);
    wait(0);
    wait(0);
    exit(0);
}