#define _GNU_SOURCE

#include "monty.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

instruction_t ops[] = {
    {"push", push},
    {"pall", pall},
    {"pint", pint},
    {"pop", pop},
    {"swap", swap},
    {"add", add},
    {"nop", nop}
};

int main(int argc, char **argv)
{
    stack_t *stack;
    unsigned int line_number = 1;

    char *line = NULL;
    size_t len = 0;
    int read;

    FILE *file;
    int i = 0;

    if (argc != 2)
        fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);

    file = fopen(argv[1], "r");
    if (file == NULL)
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, file)) != -1)
    {
        if (read > 0)
        {
            char *token = strtok(line, " \t\n");

            if (token != NULL)
            {
                for (; i < (int)(sizeof(ops) / sizeof(ops[0])); i++)
                {
                    if (strcmp(token, ops[i].opcode) == 0)
                    {
                        ops[i].f(&stack, line_number);
                        break;
                    }
                }
            }
            line_number++;
        }
    }
    
    fclose(file);
    free(line);
    exit(EXIT_SUCCESS);
    return 0;
}
