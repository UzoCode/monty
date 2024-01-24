#include "monty.h"

/**
 * push - pushes an element to the stack
 * @stack: doubly linked list representation of a stack (or queue)
 * @line_number: number of commands
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *arguments;
	int values;
	stack_t *fresh_node = NULL;

	/* Tokenize the line to extract the push argument */
	arguments = strtok(NULL, " \t\n");

	/* Check if the argument exists */
	if (arguments == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Convert argument to an integer using atoi */
	values = atoi(arguments);

	/* Create a new stack node */
	fresh_node = malloc(sizeof(stack_t));

	if (fresh_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize the new node */
	fresh_node->n = values;
	fresh_node->prev = NULL;
	fresh_node->next = NULL;

	/* Add the new node to the stack */
	if (*stack != NULL)
	{
		fresh_node->next = *stack;
		(*stack)->prev = fresh_node;
	}

	*stack = fresh_node;
}
