#include "main.h"

void exemd(char **argv)
{
	char *command = NULL, *act_command = NULL;

	if (argv) {
		command = argv[0];
		
		act_command = location(command);

		if (execve(act_command, argv, NULL) == -1) {
			perror("Error:");
		}
	}
}