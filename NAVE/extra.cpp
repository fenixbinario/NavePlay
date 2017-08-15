// reemplazar esto:

void exec(std::string args, bool block) {
    pid_t pid = fork();  // This process executes a given program

    if (pid == -1) {
        error("fatal fork error", true);
        exit(1);
    } else if (pid == 0) { // This is the child process
        child(args);
    } else { // This is the parent process.
        parent(pid, block);
    }
}


//con este:

void exec(std::string args, bool block) {
    pid_t pid = fork();  // This process executes a given program
    ((pid == -1) ? ((pid == 0) ? child(args) : parent(pid, block)) : error("fatal fork error", true));
}
