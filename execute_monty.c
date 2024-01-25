#include "monty.h"
#include <string.h>

/**
 * frees_tokens - Frees the global op_toks array of strings.
 */
void frees_tokens(void)
{
	size_t i = 0;

	if (op_toks == NULL)
		return;

	for (i = 0; op_toks[i]; i++)
		free(op_toks[i]);

	free(op_toks);
}

/**
 * token_curr_len - Gets the length of current op_toks.
 *
 * Return: Length of current op_toks (as int).
 */
unsigned int token_curr_len(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

/**
 * empty_line - Checks if a line read from getline only contains delimiters.
 * @line: A pointer to the line.
 * @delims: A string of delimiter characters.
 *
 * Return: If the line only contains delimiters - 1.
 *         Otherwise - 0.
 */
int empty_line(char *line, char *delims)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[i] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}

	return (1);
}

/**
 * get_op_funcs - Matches an opcode with its corresponding function.
 * @opcode: The opcode to match.
 *
 * Return: A pointer to the corresponding function.
 */
void (*get_op_funcs(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", mon_push},
		{"pall", mon_pall},
		{"pint", mon_pint},
		{"pop", mon_pop},
		{"swap", mon_swap},
		{"add", mon_add},
		{"nop", mon_nop},
		{"sub", mon_sub},
		{"div", mon_div},
		{"mul", mon_mul},
		{"mod", mon_mod},
		{"pchar", mon_pchar},
		{"pstr", mon_pstr},
		{"rotl", mon_rotl},
		{"rotr", mon_rotr},
		{"stack", mon_stack},
		{"queue", mon_queue},
		{NULL, NULL}
	};
	int i;

	for (i = 0; op_funcs[i].opcode; i++)
	{
		if (strcmp(opcode, op_funcs[i].opcode) == 0)
			return (op_funcs[i].f);
	}

	return (NULL);
}

/**
 * execute_monty - Primary function to execute a Monty bytecodes script.
 * @script_fd: File descriptor for an open Monty bytecodes script.
 *
 * Return: EXIT_SUCCESS on success, respective error code on failure.
 */
int execute_monty(FILE *script_fd)
{
	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0, exit_status = EXIT_SUCCESS;
	unsigned int line_number = 0, prev_tok_len = 0;
	void (*op_func)(stack_t**, unsigned int);

	if (init_stacks(&stack) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	while (getline(&line, &len, script_fd) != -1)
	{
		line_number++;
		op_toks = strtow(line, DELIMS);
		if (op_toks == NULL)
		{
			if (empty_line(line, DELIMS))
				continue;
			free_stacks(&stack);
			return (malloc_errors());
		}
		else if (op_toks[0][0] == '#') /* comment line */
		{
			frees_tokens();
			continue;
		}
		op_func = get_op_funcs(op_toks[0]);
		if (op_func == NULL)
		{
			free_stacks(&stack);
			exit_status = unknown_op_errors(op_toks[0], line_number);
			frees_tokens();
			break;
		}
		prev_tok_len = token_curr_len();
		op_func(&stack, line_number);
		if (token_curr_len() != prev_tok_len)
		{
			if (op_toks && op_toks[prev_tok_len])
				exit_status = atoi(op_toks[prev_tok_len]);
			else
				exit_status = EXIT_FAILURE;
			frees_tokens();
			break;
		}
		frees_tokens();
	}
	free_stacks(&stack);

	if (line && *line == 0)
	{
		free(line);
		return (malloc_errors());
	}

	free(line);
	return (exit_status);
}
