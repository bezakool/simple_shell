#include "shell.h"

char *_itoa(int num);
int custom_err(char **args, int err);
int num_len(int num);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */

int num_len(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}

	return (length);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer input
 *
 * Return: The converted string.
 */

char *_itoa(int num)
{
	char *buffer;
	int length = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == NULL)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * custom_err - Writes an error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */

int custom_err(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			error = err_env(args);
			break;
		case 1:
			error = err_1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = err_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				error = err_2_syn(args);
			else
				error = err_2_cd(args);
			break;
		case 126:
			error = err_126(args);
			break;
		case 127:
			error = err_127(args);
			break;
		}

	write(STDERR_FILENO, error, _strlen(error));
	if (error)
		free(error);

	return (err);
}
