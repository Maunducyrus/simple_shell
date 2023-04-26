#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

// Built-in command functions
void cmd_exit() {
	exit(0);
}

void cmd_cd(char *arg) {
	if (arg == NULL) {
	printf("cd: missing argument\n");
	return;
	}
	if (chdir(arg) != 0) {
	perror("cd");
	}
}

void cmd_echo(char **args) {
	for (int i = 0; args[i] != NULL; i++) {
	printf("%s ", args[i]);
	}
	printf("\n");
}

// Built-in command table
struct {
	char *name;
	void (*func)(char *);
} builtin_cmds[] = {
	{ "exit", cmd_exit },
	{ "cd", cmd_cd },
	{ "echo", cmd_echo },
	{ NULL, NULL }
};

// Split a string into individual tokens
int tokenize(char *line, char **args) {
	int num_args = 0;	
	char *token = strtok(line, " \t\n");
	while (token != NULL && num_args < MAX_ARGS) {
	args[num_args++] = token;
	token = strtok(NULL, " \t\n");
	}
	args[num_args] = NULL;
	return num_args;
}

// Main shell loop
int main() {
	char line[256];
	char *args[MAX_ARGS];
	while (1) {
	// Prompt and read user input
	printf("$ ");
	fflush(stdout);
	if (fgets(line, sizeof(line), stdin) == NULL) {
		break;
	}

	// Tokenize input
	int num_args = tokenize(line, args);
	if (num_args == 0) {
	continue;
	}
			
	// Check for built-in commands
	for (int i = 0; builtin_cmds[i].name != NULL; i++) {
	if (strcmp(args[0], builtin_cmds[i].name) == 0) {
		builtin_cmds[i].func(args[1]);
		break;
	}
}

pid_t pid = fork();
if (pid < 0) {
perror("fork");
exit(1);
} else if (pid == 0) {
execvp(args[0], args);
perror(args[0]);
exit(1);
} else {
int status;
waitpid(pid, &status, 0);
}
}
return 0;
}

