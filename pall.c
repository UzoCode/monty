#include "monty.h"

/**
 * pall - prints all values on the stack,
 * from top of the stack
 * @stack: The doubly linked list representation of stack (or queue)
 * @line_number: The number of commands
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *curr = *stack;
	(void)line_number; /* Avoid unused variable warning */

	while (curr != NULL)
	{
		printf("%d\n", curr->n);
		curr = curr->next;
	}
}
