#ifndef __MONTY_H__
#define __MONTY_H__

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STACK 0
#define QUEUE 1
#define DELIMS " \n\t\a\b"

/* GLOBAL OPCODE TOKENS */
extern char **op_toks;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* PRIMARY INTERPRETER FUNCTIONS */
void free_stacks(stack_t **stack);
int init_stacks(stack_t **stack);
int check_modes(stack_t *stack);
void frees_tokens(void);
unsigned int token_curr_len(void);
int execute_monty(FILE *script_fd);
void set_op_tok_errors(int error_code);

/* OPCODE FUNCTIONS */
void mon_push(stack_t **stack, unsigned int line_number);
void mon_pall(stack_t **stack, unsigned int line_number);
void mon_pint(stack_t **stack, unsigned int line_number);
void mon_pop(stack_t **stack, unsigned int line_number);
void mon_swap(stack_t **stack, unsigned int line_number);
void mon_add(stack_t **stack, unsigned int line_number);
void mon_nop(stack_t **stack, unsigned int line_number);
void mon_sub(stack_t **stack, unsigned int line_number);
void mon_div(stack_t **stack, unsigned int line_number);
void mon_mul(stack_t **stack, unsigned int line_number);
void mon_mod(stack_t **stack, unsigned int line_number);
void mon_pchar(stack_t **stack, unsigned int line_number);
void mon_pstr(stack_t **stack, unsigned int line_number);
void mon_rotl(stack_t **stack, unsigned int line_number);
void mon_rotr(stack_t **stack, unsigned int line_number);
void mon_stack(stack_t **stack, unsigned int line_number);
void mon_queue(stack_t **stack, unsigned int line_number);

/* CUSTOM STANDARD LIBRARY FUNCTIONS */
char **strtow(char *str, char *delims);
char *gets_int(int n);

/* ERROR MESSAGES & ERROR CODES */
int usage_errors(void);
int malloc_errors(void);
int fopen_error(char *filename);
int unknown_op_errors(char *opcode, unsigned int line_number);
int no_int_errors(unsigned int line_number);
int pop_errors(unsigned int line_number);
int pint_errors(unsigned int line_number);
int short_stack_errors(unsigned int line_number, char *op);
int div_errors(unsigned int line_number);
int pchar_errors(unsigned int line_number, char *message);

#endif
