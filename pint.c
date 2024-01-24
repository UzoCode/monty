#include "monty.h"

/**
 * pint - prints the value at the top of the stack, followed by a new line.
 * @stack: The doubly linked list representation of stack (or queue)
 * @line_number: The number of commands
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}
