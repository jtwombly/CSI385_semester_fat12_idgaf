/*
 * shell_code.c
 *
 *  Created on: Oct 18, 2016
 *      Author: victoria
 */
#include "shell_code.h"

int shell() {
	if (FILE_SYSTEM_ID == NULL)
	{
	  printf("Could not open the floppy drive or image.\n");
	  exit(1);
	}
	struct boot_sector BS = rbs();
	printf("Welcome to shell.\n");
	while (1) {
		char buffer[128];
		printf(">>");
		fgets(buffer, 128, stdin);
		char * fields;
		int num_params = 0;
		fields = strtok(buffer, " ");
		while (fields != NULL) {
			fields = strtok(NULL, " ");
			num_params += 1;
		}
		fields = strtok(buffer, " \n");
		if (strcmp(fields, "cat") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields);
			}
		} else if (strcmp(fields, "cd") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields);
			}
		} else if (strcmp(fields, "df") == 0) {
			if (num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s takes no parameters.\n", fields);
			}
		} else if (strcmp(fields, "ls") == 0) {
			if (num_params == 2 || num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s takes up to one additional parameter.\n",
						fields);
			}
		} else if (strcmp(fields, "mkdir") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter\n", fields);
			}
		} else if (strcmp(fields, "pbs") == 0) {
			if (num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					//this is where I'd call pbs function
					pbs(BS);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s takes no parameters.\n", fields);
			}
		} else if (strcmp(fields, "pfe") == 0) {
			if (num_params == 3) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires two additional parameters.\n",
						fields);
			}
		} else if (strcmp(fields, "pwd") == 0) {
			if (num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s takes no parameters.\n", fields);
			}
		} else if (strcmp(fields, "rm") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields);
			}
		} else if (strcmp(fields, "rmdir") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields);
			}
		} else if (strcmp(fields, "touch") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields);
			}
		} else if (strcmp(fields, "exit") == 0 || strcmp(fields, "quit") == 0
				|| strcmp(fields, "logout") == 0) {
			return 0;
		} else {
			printf("Command %s does not exist.\n", fields);
		}
		wait(NULL);
	}
}
