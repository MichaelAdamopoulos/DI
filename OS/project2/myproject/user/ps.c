#include "../kernel/types.h"
#include "../kernel/param.h"
#include "ps.h"
#include "user.h"

void printstate(int state) {

    switch (state) {
        case 0:
            printf("UNUSED\t");
            break;
        case 1:
            printf("USED\t");
            break;
        case 2:
            printf("SLEEPING\t");
            break;
        case 3:
            printf("RUNNABLE\t");
            break;
        case 4:
            printf("RUNNING\t\t");
            break;
        case 5:
            printf("ZOMBIE\t");
            break;
    }
}

int main(void) {

    struct pstat ps;

    getpinfo(&ps);

    printf("NAME\tPID\tPPID\tPRIORITY\tSTATE\t\tSIZE\n\n");
    for (int i = 0; i < ps.count; i++) {
        printf("%s\t", ps.name[i]);
        printf(" %d\t", ps.pid[i]);
        printf("%d\t", ps.ppid[i]);
        printf("   %d\t\t", ps.priority[i]);
        printstate(ps.state[i]);
        printf("%l\n", ps.sz[i]);
    }

    exit(0);
}