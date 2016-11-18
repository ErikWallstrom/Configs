#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum
{
	OP_END = EOF,
	OP_INC = '+',
	OP_DEC = '-',
	OP_GET = ',',
	OP_PRT = '.',
	OP_INC_PTR = '>',
	OP_DEC_PTR = '<',
	OP_JMP_FWD = '[',
	OP_JMP_BCK = ']',
} Operator;

typedef struct
{
	Operator operator;
	size_t operand;
} Operation;

typedef struct
{
	Operation* operations;
	size_t num_ops;
} Program;

char* gets_file(FILE* file)
{
	fseek(file, 0, SEEK_END);
	long file_length = ftell(file);
	rewind(file);
	char* buffer = malloc(file_length + 1);
	fread(buffer, 1, file_length, file);
	buffer[file_length] = '\0';
	return buffer;
}

size_t total_chars(char* buffer, char ch)
{
	size_t num = 0;
	for(size_t i = 0; i < strlen(buffer); i++)
	{
		if(buffer[i] == ch)
			num++;
	}
	return num;
}

Program compile(FILE* file)
{
	Program program = {0};
	char* file_content = gets_file(file);
	program.num_ops = total_chars(file_content, OP_INC) + 
		total_chars(file_content, OP_DEC) + 
		total_chars(file_content, OP_GET) + 
		total_chars(file_content, OP_PRT) + 
		total_chars(file_content, OP_INC_PTR) + 
		total_chars(file_content, OP_DEC_PTR) + 
		total_chars(file_content, OP_JMP_FWD) + 
		total_chars(file_content, OP_JMP_BCK);
	program.operations = malloc(sizeof(Operation) * program.num_ops + 1);
	program.num_ops = 0;
	
	size_t* stack = malloc(sizeof(size_t) * total_chars(file_content, '['));
	size_t* stack_ptr = stack;

	for(size_t i = 0; i < strlen(file_content); i++)
	{
		switch(file_content[i])
		{
			case OP_INC:
				program.operations[program.num_ops] = (Operation){OP_INC};
			break;
			case OP_DEC:
				program.operations[program.num_ops] = (Operation){OP_DEC};
			break;
			case OP_PRT:
				program.operations[program.num_ops] = (Operation){OP_PRT};
			break;
			case OP_GET:
				program.operations[program.num_ops] = (Operation){OP_GET};
			break;
			case OP_INC_PTR:
				program.operations[program.num_ops] = (Operation){OP_INC_PTR};
			break;
			case OP_DEC_PTR:
				program.operations[program.num_ops] = (Operation){OP_DEC_PTR};
			break;
			case OP_JMP_FWD:
				stack[stack_ptr++ - stack] = program.num_ops;
				program.operations[program.num_ops] = (Operation){OP_JMP_FWD, program.num_ops};
			break;
			case OP_JMP_BCK:
				if(stack_ptr == stack)		
				{
					puts("Error: Contains non-matching brackets");
					exit(EXIT_FAILURE);
				}

				size_t jmp_pos = *(--stack_ptr);
				program.operations[program.num_ops] = (Operation){OP_JMP_BCK, jmp_pos};
				program.operations[jmp_pos].operand = program.num_ops;
				
			break;
			default:
				program.num_ops--;
		}
		program.num_ops++;
	}

	if(stack_ptr - stack)
	{
		puts("Error: Contains non-matching brackets");
		exit(EXIT_FAILURE);
	}

	free(stack);
	free(file_content);
	program.operations[program.num_ops - 1] = (Operation){OP_END};
	return program;
}

void run(Program program)
{
	char* memory = malloc(program.num_ops * 2);
	memset(memory, 0, program.num_ops * 2);
	char* mem_ptr = memory + program.num_ops;
	program.num_ops = 0;
	Operator op;
	do {
		op = program.operations[program.num_ops].operator;
		switch(op)
		{
			case OP_INC:
				(*mem_ptr)++;
			break;
			case OP_DEC:
				(*mem_ptr)--;
			break;
			case OP_GET:
				(*mem_ptr) = getchar();
			break;
			case OP_PRT:
				putchar(*mem_ptr);
			break;
			case OP_INC_PTR:
				mem_ptr++;
			break;
			case OP_DEC_PTR:
				mem_ptr--;
			break;
			case OP_JMP_FWD:
				if(!(*mem_ptr))
				{
					program.num_ops = program.operations[program.num_ops].operand;
				}
			break;
			case OP_JMP_BCK:
				if(*mem_ptr)
				{
					program.num_ops = program.operations[program.num_ops].operand;
				}
			break;
		}
		program.num_ops++;
	} while(op != OP_END);
	free(memory);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		if(argc && argv[0])
			printf("Usage: %s [FILE]\n", argv[0]);
		else
			puts("Usage: ./bfi [FILE_NAME]");
		return EXIT_FAILURE;
	}

	FILE* file = fopen(argv[1], "r");
	if(!file)
	{
		puts("Error: Unable to read from file");
		return EXIT_FAILURE;
	}

	Program program = compile(file);
	run(program);
	fclose(file);
	free(program.operations);
}
