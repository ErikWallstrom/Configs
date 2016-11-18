#include <ncurses.h>

int main(void)
{
    initscr();
	waddch(L'å');
	refresh();
	getch();
    endwin();
}
