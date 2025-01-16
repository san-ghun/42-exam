#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static void timeout_handler(int sig)
{
	(void)sig;
	_exit(SIGALRM);
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;
	struct sigaction sa = {0};

	pid = fork();
	if (pid < 0)
		return -1;

	if (pid == 0)
	{
		sa.sa_handler = timeout_handler;
		sa.sa_flags = 0;
		if (sigaction(SIGALRM, &sa, NULL) < 0)
			_exit(1);
		alarm(timeout);
		f();
		_exit(0);
	}

	pid_t wresult = waitpid(pid, &status, WUNTRACED);
	if (wresult < 0)
		return -1;
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (verbose)
			printf("bf: termsig %s\n", strsignal(sig));
		return 0;
	}
	else if (WIFSTOPPED(status))
	{
		int sig = WSTOPSIG(status);
		if (verbose)
			printf("bf: stopsig %s\n", strsignal(sig));
		return 0;
	}
	else if (WIFEXITED(status))
	{
		int code = WEXITSTATUS(status);
		if (code == 0)
		{
			if (verbose)
				printf("nf\n");
			return 1;
		}
		else if (code == SIGALRM)
		{
			if (verbose)
				printf("bf: timeout %u seconds\n", timeout);
			return 0;
		}
		else
		{
			if (verbose)
				printf("bf: exit with code %d\n", code);
			return 0;
		}
	}
	return -1;
}
