#include "main.h"


char *read_line(void)
{
	char *str = NULL;
	size_t len = 0;
	ssize_t read_len;

	do {
		if (!(str = realloc(str, len + 256))) {
			free(str);
			return NULL;
		}

		read_len = getline(&str, &len, stdin);
	} while (read_len < 0);

	if (read_len == -1) {
		free(str);
		return NULL;
	}

	// null terminate
}