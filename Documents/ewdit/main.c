#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include "../Vector/vec.h"

struct Option 
{
	char short_o;
	char* long_o;
	char* info;
	int used;
};

struct Parse_Result
{
	int invalid_arg;
	Vec(char*) args;
	struct Option* options;
};

void print_help(struct Option* options, size_t option_size)
{
	printf("Usage: ewdit [OPTIONS -");
	for(size_t i = 0; i < option_size; i++)
		putchar(options[i].short_o);
	puts("] [FILENAME]\nOptions:");
	for(size_t i = 0; i < option_size; i++)
	{
		printf("    -%c, --%s", options[i].short_o, options[i].long_o);
		int gap = 20 - strlen(options[i].long_o);
		for(int i = 0; i < gap; i++)
			putchar(' ');
		puts(options[i].info);
	}
	putchar('\n');
}

struct Parse_Result parse_options(
	int argc, 
	char* argv[], 
	struct Option* options,
	size_t options_size)
{
	struct Parse_Result result;
	result.options = options;
	result.invalid_arg = 0;
	result.args = Vec_ctor(sizeof(Vec(char)), 0);
	
	int next_is_arg = 0;
	for(int i = 1; i < argc; i++)
	{
		if(next_is_arg)
		{
			Vec_push_back(&result.args, argv[i]);
			next_is_arg = 0;
		}
		else if(argv[i][0] == '-')
		{
			if(argv[i][1] == '-')
			{
				if(argv[i][2] == '\0')
				{
					next_is_arg = 1;
				}
				else
				{
					int found = 0;
					for(size_t j = 0; j < options_size; j++)
					{
						if(!strcmp(&argv[i][2], result.options[j].long_o))
						{
							result.options[j].used = 1;
							found = 1;
							break;
						}
					}

					if(!found)
					{
						result.invalid_arg = 1;
						return result;
					}
				}
			}
			else
			{
				int found = 0;
				for(size_t j = 0; j < options_size; j++)
				{
					if(argv[i][1] == result.options[j].short_o)
					{
						result.options[j].used = 1;
						found = 1;
						break;
					}
				}

				if(!found)
				{
					result.invalid_arg = 1;
					return result;
				}
			}
		}
		else
		{
			Vec_push_back(&result.args, argv[i]);
		}
	}

	return result;
}

Vec(Vec(char)) get_lines(FILE* file)
{
	Vec(Vec(char)) lines = Vec_ctor(sizeof(Vec(char)), 0);
	int eof = 0;
	while(!eof)
	{
		Vec(char) line = Vec_ctor(1, 0);
		while(1)
		{
			int c = fgetc(file);
			if(c == EOF)
			{
				eof = 1;
				break;
			}
			else if(c == '\n')
			{
				Vec_push_back(&line, c);
				break;
			}
			else
				Vec_push_back(&line, c);
		}
		Vec_push_back(&lines, line);
	}
	return lines;
}

void cool(FILE* file)
{
	Vec(Vec(char)) lines = get_lines(file);
	scrollok(stdscr, 1);

	init_color(COLOR_GREEN, 0, 1000, 0);
	init_pair(1, COLOR_GREEN, -1);
	attron(COLOR_PAIR(1));

	size_t y, x;
	getmaxyx(stdscr, y, x);

	for(size_t i = 0; i < (/*(Vector(&lines).size > y) ? y :*/ Vector(&lines).size); i++)
	{
		for(size_t j = 0; j < ((Vector(&lines[i]).size > x) ? x : Vector(&lines[i]).size); j++)
		{
			if(lines[i][j] == '\t')
			{
				int y, x;
				getyx(stdscr, y, x);

				int spaces = x % 4;
				if(spaces)
					for(int i = 0; i < spaces; i++)
					{
						addch(' ');
					}
				else
					addstr("    ");
			}
			else
			{
				addch(lines[i][j]);
			}

			refresh();
			nanosleep(&(struct timespec){0, 10000000L}, NULL);
		}
	}

	attroff(COLOR_PAIR(1));
	refresh();
//	getch(); 

	for(size_t i = 0; i < Vector(&lines).size; i++)
		Vec_dtor(&lines[i]);
	Vec_dtor(&lines);
}

void notepad(FILE* file)
{
	Vec(Vec(char)) lines = get_lines(file);

	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);

//	scrollok(stdscr, 1);
	bkgd(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));

	size_t y, x;
	int displacement = 0;
	getmaxyx(stdscr, y, x);

	while(1)
	{
		for(size_t i = displacement; i < (((Vector(&lines).size > y + displacement) ? y + displacement : Vector(&lines).size)); i++)
			for(size_t j = 0; j < ((Vector(&lines[i]).size > x) ? x : Vector(&lines[i]).size); j++)
			{
				if(lines[i][j] == '\t')
				{
					int y, x;
					getyx(stdscr, y, x);

					int spaces = x % 4;
					if(spaces)
						for(int i = 0; i < spaces; i++)
						{
							addch(' ');
						}
					else
						addstr("    ");
				}
				else
					addch(lines[i][j]);
			}

		refresh();
		move(0, 0);
		int c = getch();
		if(c == 'j')
		{
			if(displacement < Vector(&lines).size - y - 1)
				displacement++;
		}
		else if(c == 'k')
		{
			if(displacement > 0)
				displacement--;
		}
		else if(c == 'q')
			break;
	}

	attroff(COLOR_PAIR(2));

	for(size_t i = 0; i < Vector(&lines).size; i++)
		Vec_dtor(&lines[i]);
	Vec_dtor(&lines);
}
	
int main(int argc, char* argv[])
{
	struct Option options[] = {
		{'h', "help", "Display this text", 0},
		{'c', "cool", "Cool editor with green text and delays", 0},
		{'n', "notepad", "Editor with white background and black text", 0},
	};
	size_t options_size = sizeof(options) / sizeof(*options);

	struct Parse_Result result = parse_options(argc, argv, options, options_size);
	if(result.invalid_arg || Vector(&result.args).size != 1)
	{
		print_help(options, options_size);
		return EXIT_FAILURE;
	}
	else if(options[0].used)
		print_help(options, options_size);
	else if(options[1].used && options[2].used)
	{
		print_help(options, options_size);
		puts("You cannot use -c and -n at the same time");
		return EXIT_FAILURE;
	}

	FILE* file = fopen(result.args[0], "r");
	if(!file)
	{
		perror("Error");
		return EXIT_FAILURE;
	}

	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	start_color();
	use_default_colors();
	refresh();

	if(options[1].used)
		cool(file);
	else
		notepad(file);

	Vec_dtor(&result.args);
	fclose(file);
	endwin();
}

