#define _GNU_SOURCE
#include "monty.h"

/**
 * free_ops - frees the global variables
 * Return: 0
 */

void free_ops(void)
{
	free_dlistint(ops.h);
	free(ops.buffer);
	fclose(ops.fd);
}

/**
 * start_ops - initializes the global variables
 * @fd: file descriptor
 * Return: 0
 */

void start_ops(FILE *fd)
{
	ops.lifo = 1;
	ops.currt = 1;
	ops.arg = NULL;
	ops.h = NULL;
	ops.fd = fd;
	ops.buffer = NULL;
}

/**
 * input_to_check - checks if the file exists and if the file can open
 * @argc: argument count
 * @argv: argument vector
 * Return: file struct
 */

FILE *input_to_check(int argc, char *argv[])
{
	FILE *fd;

	if (argc == 1 || argc > 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fd = fopen(argv[1], "r");

	if (fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */

int main(int argc, char *argv[])
{
	void (*f)(stack_t **stack, unsigned int line_number);
	FILE *fd;
	size_t line_size = 256;
	ssize_t s_line = 0;
	char *line[2] = {NULL, NULL};

	fd = input_to_check(argc, argv);
	start_ops(fd);

	while (s_line != -1)
	{
		line[0] = _strtoky(ops.buffer, " \t\n");
		if (line[0] && line[0][0] != '#')
		{
			f = get_opcodes(line[0]);
			if (!f)
			{
				fprintf(stderr, "L%u: ", ops.currt);
				fprintf(stderr, "unknown instruction %s\n", line[0]);
				free_ops();
				exit(EXIT_FAILURE);
			}
			ops.arg = _strtoky(NULL, " \t\n");
			f(&ops.h, ops.currt);
		}

		s_line = getline(&ops.buffer, &line_size, fd);

		ops.currt++;
	}
	free_ops();

	return (0);
}
