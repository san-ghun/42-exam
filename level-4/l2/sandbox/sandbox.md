Write the following function in C.

- name of function: "sandbox"
- allowed functions: fork, alarm, print, waitpid, sigaction, strsignal, exit, kill, errno.
- prototype:

  ```c
  #include <stdbool.h>
  int sandbox(void (\*f)(void), unsigned int timeout, bool verbose);
  ```

- description: Following function must test if the function f is a nice function or bad. If nice, it will return 1, if bad, return 0, if error, return -1. A function is considered bad if it is "terminated" or "stopped" by a signal like, "segfalut", "abort", etc.., and also if it exit with any other exit code than 0 or if it time out. If verbose is true, write message to print. Even in zombie state, this will be checked using wait.

---

- Update on 09.Jan.2025
    - It is very important to properly handle zombie processes during the test.
    - I couldn't pass the exam because I didn't expect to handle leaked processes in test cases.

