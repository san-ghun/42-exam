#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

// Nice function that exits normally
void nice_function(void) {
    printf("I am nice\n");
}

// Bad function that segfaults
void segfault_function(void) {
    int *p = NULL;
    *p = 42;  // This will cause a segmentation fault
}

// Bad function that times out
void timeout_function(void) {
    while (1) {
        sleep(1);
    }
}

// Bad function that exits with non-zero code
void bad_exit_function(void) {
    exit(42);
}

// Bad function that aborts
void abort_function(void) {
    abort();
}

void stop_function(void) {
    sleep(1);
    kill(getpid(), SIGSTOP);
}

void extra_function(void) {
    kill(getpid(), SIGINT);
}

void zombie_producer(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) running\n", getpid());
        sleep(2); // Simulate some work
        printf("Child process (PID: %d) exiting\n", getpid());
        exit(0);  // Terminate child process
    } else {
        // Parent process
        printf("Parent process (PID: %d) spawned child process (PID: %d)\n", getpid(), pid);

        // Simulate parent not waiting for the child immediately
        printf("Parent process is sleeping, leaving child as a zombie...\n");
        sleep(5); // Let the child process become a zombie

        // Observe the zombie state: run `ps aux` in another terminal
        printf("Parent process is now reaping the child process\n");

        // Reap the child process to clean up the zombie
        int status;
        waitpid(pid, &status, 0);

        printf("Child process reaped, exiting parent process\n");
    }

    return ;
}

void f1(void) {
	(void)printf("I'm a nice function\n");
}

void f2(void) {
	(void)printf("I'm a bad function\n");
	exit(1);
}

void f3(void) {
	(void)printf("I'm a terrible function\n");
	*(char *)0 = 0;
}

void f4(void) {
	(void)printf("I'm a terrible function AGAIN\n");
	abort();
}

void f5(void) {
	(void)printf("I will run forevaaaa\n");
	while (true) {
	}
}

void f6(void) {
	(void)printf("I will block all signalsss (and run forever)!\n");
	(void)sigaction(SIGALRM, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGKILL, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGSTOP, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGTERM, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGSEGV, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGPIPE, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGBUS, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGCHLD, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGHUP, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGTSTP, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGTTIN, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGTTOU, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGURG, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	(void)sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN, .sa_flags = SA_RESTART}, NULL);
	while (true) {
	}
}

int main(void) {
    printf("\nTesting nice function:\n");
    sandbox(nice_function, 2, true);

    printf("\nTesting segfault function:\n");
    sandbox(segfault_function, 2, true);

    printf("\nTesting timeout function:\n");
    sandbox(timeout_function, 3, true);

    printf("\nTesting bad exit function:\n");
    sandbox(bad_exit_function, 2, true);

    printf("\nTesting abort function:\n");
    sandbox(abort_function, 2, true);

    printf("\nTesting stop function:\n");
    sandbox(stop_function, 2, true);

    printf("\nTesting extra function:\n");
    sandbox(extra_function, 2, true);

    void (*funcs[])(void) = {f1, f2, f3, f4, f5, f6};
    for (unsigned int i = 0; i < sizeof(funcs)/sizeof(funcs[0]); ++i)
    {
        (void)printf("sandbox ret: %d\n", sandbox(funcs[i], 2, true));
    }
    return 0;
}
