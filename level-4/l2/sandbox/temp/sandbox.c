#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

pid_t pid;
bool kill_failed = false;
bool killed_child = false;

static void kill_proc(int sig)
{
	(void)sig;
	if (kill(pid, SIGKILL) == -1)
		kill_failed = true;
	killed_child = true;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int status;
	struct sigaction sa = {0};

	pid = fork();
	if (pid < 0)
		return -1;

	if (pid == 0)
	{
		f();
		_exit(0);
	}
	sa.sa_handler = kill_proc;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGALRM, &sa, NULL))
		return -1;
	alarm(timeout);
	pid_t wresult = waitpid(pid, &status, WUNTRACED);
	if (wresult < 0)
		return -1;
	if (kill_failed)
		return -1;
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGKILL && killed_child)
		{
			if (verbose)
				printf("bf: timeout %u seconds\n", timeout);
			return 0;
		}
		else
		{
			if (verbose)
				printf("bf: termsig %s\n", strsignal(sig));
		}
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
		else
		{
			if (verbose)
				printf("bf: exit with code %d\n", code);
			return 0;
		}
	}
	return -1;
}
