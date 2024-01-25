#include "monty.h"

/**
 * mon_push - Pushes a value to a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void mon_push(stack_t **stack, unsigned int line_number)
{
	stack_t *tmps, *fresh;
	int i;

	fresh = malloc(sizeof(stack_t));
	if (fresh == NULL)
	{
		set_op_tok_errors(malloc_errors());
		return;
	}

	if (op_toks[1] == NULL)
	{
		set_op_tok_errors(no_int_errors(line_number));
		return;
	}

	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i == 0)
			continue;
		if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
		{
			set_op_tok_errors(no_int_errors(line_number));
			return;
		}
	}
	fresh->n = atoi(op_toks[1]);

	if (check_modes(*stack) == STACK) /* STACK mode insert at front */
	{
		tmps = (*stack)->next;
		fresh->prev = *stack;
		fresh->next = tmps;
		if (tmps)
			tmps->prev = fresh;
		(*stack)->next = fresh;
	}
	else /* QUEUE mode insert at end */
	{
		tmps = *stack;
		while (tmps->next)
			tmps = tmps->next;
		fresh->prev = tmps;
		fresh->next = NULL;
		tmps->next = fresh;
	}
}

/**
 * mon_pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void mon_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmps = (*stack)->next;

	while (tmps)
	{
		printf("%d\n", tmps->n);
		tmps = tmps->next;
	}
	(void)line_number;
}

/**
 * mon_pint - Prints the top value of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void mon_pint(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL)
	{
		set_op_tok_errors(pint_errors(line_number));
		return;
	}

	printf("%d\n", (*stack)->next->n);
}

/**
 * mon_pop - Removes the top value element of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void mon_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *next = NULL;

	if ((*stack)->next == NULL)
	{
		set_op_tok_errors(pop_errors(line_number));
		return;
	}

	next = (*stack)->next->next;
	free((*stack)->next);
	if (next)
		next->prev = *stack;
	(*stack)->next = next;
}

/**
 * mon_swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void mon_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmps;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_op_tok_errors(short_stack_errors(line_number, "swap"));
		return;
	}

	tmps = (*stack)->next->next;
	(*stack)->next->next = tmps->next;
	(*stack)->next->prev = tmps;
	if (tmps->next)
		tmps->next->prev = (*stack)->next;
	tmps->next = (*stack)->next;
	tmps->prev = *stack;
	(*stack)->next = tmps;
}
