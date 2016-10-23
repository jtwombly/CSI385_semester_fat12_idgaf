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
		char ** fields;
		int num_params = 1;

		fields = malloc(num_params * sizeof(char*));
		fields[0] = strtok(buffer, " ");
		while (fields[num_params-1] != NULL) {
			//find number of parameters
			num_params += 1;
			fields = realloc(fields, num_params * sizeof(char*));
			fields[num_params - 1] = strtok(NULL, " ");
		}

		for(int i=0; i< num_params; i++)
		{
			fields[i] = strtok(fields[i], "\n");
		}
		num_params -= 1;

		//fields[num_params] = strtok(buffer, " \n");
		if (strcmp(fields[0], "cat") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "cd") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "df") == 0) {
			if (num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s takes no parameters.\n", fields[0]);
			}
		} else if (strcmp(fields[0], "ls") == 0) {
			if (num_params == 2 || num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s takes up to one additional parameter.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "mkdir") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter\n", fields[0]);
			}
		} else if (strcmp(fields[0], "pbs") == 0) {
			if (num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					pbs(BS);
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s takes no parameters.\n", fields[0]);
			}
		} else if (strcmp(fields[0], "pfe") == 0) {
			if (num_params == 3) {
				pid_t pid = fork();
				int params[2];
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					pfe(atoi(fields[1]), atoi(fields[2]), BS);
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires two additional parameters.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "pwd") == 0) {
			if (num_params == 1) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s takes no parameters.\n", fields[0]);
			}
		} else if (strcmp(fields[0], "rm") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "rmdir") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "touch") == 0) {
			if (num_params == 2) {
				pid_t pid = fork();
				if (pid == 0) {
					printf("Child process for %s.\n", fields[0]);
					printf("Child process killed\n");
					free(fields);
					exit(0);
				}
			} else {
				printf("Command %s requires an additional parameter.\n",
						fields[0]);
			}
		} else if (strcmp(fields[0], "exit") == 0 || strcmp(fields[0], "quit") == 0
				|| strcmp(fields[0], "logout") == 0) {
			return 0;
		} else {
			printf("Command %s does not exist.\n", fields[0]);
		}
		wait(NULL);
		free(fields);
	}
	free(BS.vol_id);
	free(BS.vol_label);
	free(BS.sys_type);
}
