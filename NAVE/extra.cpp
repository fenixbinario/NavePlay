// reemplazar esto:

void exec(std::string args, bool block) {
    pid_t pid = fork(); 

    if (pid == -1) {
        error("fatal fork error", true);
        exit(1);
    } else if (pid == 0) { 
        child(args);
    } else { 
        parent(pid, block);
    }
}


//con este:

void exec(std::string args, bool block) {
    pid_t pid = fork();  
    ((pid == -1) ? ((pid == 0) ? child(args) : parent(pid, block)) : error("fatal fork error", true));
}
