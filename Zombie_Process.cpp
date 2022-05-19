#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sig_child(int signo)
{
    pid_t  pid;

    //处理僵尸进程, -1 代表等待任意一个子进程, WNOHANG代表不阻塞
    while( (pid = waitpid(-1, NULL, WNOHANG)) > 0 ){
        printf("child %d terminated.\n", pid);
    }
}

int main()
{
    pid_t pid;

    // 创建捕捉子进程退出信号
    // 只要子进程退出，触发SIGCHLD，自动调用sig_child()
    signal(SIGCHLD, sig_child);

    pid = fork();	// 创建进程

    if (pid < 0){ // 出错
        perror("fork error:");
        exit(1);
    }else if(pid == 0){ // 子进程
        printf("I am child process,pid id %d.I am exiting.\n",getpid());
        exit(0);

    }else if(pid > 0){ // 父进程
        sleep(2);	// 保证子进程先运行
        printf("I am father, i am exited\n\n");
        system("ps -ef | grep defunct"); // 查看有没有僵尸进程

    }

    return 0;
}