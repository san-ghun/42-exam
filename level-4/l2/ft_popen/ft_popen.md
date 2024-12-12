Write me a function in C.

- name of function: "my_popen"
- allowed functions: pipe, fork, dup2, execvp, close, exit
- prototype:
  ```c
  int my_popen(const char *file, char *const argv[], char type);
  ```
- description:
  The function must launch the executable file with the arguments argv (using execvp). If type 'r' the function must return a file descriptor connected to output of the command. If type 'w' the function must return a file descriptor connected to input of the command. In error or invalid parameter, return -1.
