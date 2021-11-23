#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]){
    char buf1, buf2 = 0;
    int l_to_r[2], r_to_l[2];   // pipe
    int counter = 0;
    pipe(l_to_r);
    pipe(r_to_l);
    if(fork() == 0){    // left-child
        // close the default stdin/stdout
        // dup(l_to_r[1]); // write
        // dup(r_to_l[0]); // read
        // close(l_to_r[0]);
        // close(l_to_r[1]);
        // close(r_to_l[0]);
        // close(r_to_l[1]);
        while(1){
            if(counter > 10) break;
            if(write(l_to_r[1], &buf1, 1) == 1){
                printf("%d: ping\n", getpid());
            }
            if(read(r_to_l[0], &buf2, 1) == 1){
                printf("%d: pong\n", getpid());
                counter++;
            }
        }
        // write(l_to_r[1], &msg, 1);
        // printf("%d: ping\n", getpid());
        // read(r_to_l[0], &msg, 1);
        exit(0);
    }
    else{
        // wait(0);
        while(1){
            if(counter > 10) break;
            if(read(l_to_r[0], &buf2, 1) == 1){
                printf("%d: pong\n", getpid());
                counter++;
            }
            if(write(r_to_l[1], &buf1, 1) == 1){
                printf("%d: ping\n", getpid());
            }
        }
    }
    // pingpang();
    exit(0);
}