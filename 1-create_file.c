#include "shell.h"

/**
 * create_file - function that creates a file.
 * @filename: a pointer to the name of the file to be created
 * @text_content: a pointer to a string that will be written to the file
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int len = 0;
	int fd, w;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (text_content != NULL)
	{
		while (text_content[len] != '\0')
			len++;
		w = write(fd, text_content, len);
		if (w == -1)
			return (-1);
	}

	close(fd);
	return (1);
}
