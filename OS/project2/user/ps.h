struct pstat {
    int count;
    int pid[NPROC];
    int ppid[NPROC];
    int priority[NPROC];
    uint64 sz[NPROC];
    char name[16][NPROC];
    int state[NPROC];
};