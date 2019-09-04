#define PDC_DLL_BUILD 1
#include "curses.h"
#include <string>

using namespace std;

unsigned char border_char = 219;

int main(void)
{
	WINDOW* main_window = nullptr;
	int num_rows = 0;
	int num_cols = 0;

	//initialize screen, begin curses mode
	main_window = initscr();

	//take up most of the screen
	getmaxyx(main_window, num_rows, num_cols);
	resize_term(num_rows - 1, num_cols - 1);
	getmaxyx(main_window, num_rows, num_cols);

	//turn off key echo
	noecho();
	//nodelay(main_window, TRUE);
	keypad(main_window, TRUE);
	curs_set(0);

	//fun stuff happens here

	for (int i = 0; i < num_cols; i++)
	{
		//top border
		mvaddch(0, i, ACS_CKBOARD);

		//bottom border
		mvaddch(num_rows - 1, i, ACS_CKBOARD);
	}

	//top gui bar
	mvaddstr(1, 1, "|  File |  Edit  |  Options  |  Buffers  |  Tools  |  Help  |");

	//bottom gui bars
	mvaddstr(num_rows - 3, 1, "|  ^G Get Help  |  ^O Write Out  |  ^R Read File  |  ^Y Prev Page  |  ^C Cur Pos   |");
	mvaddstr(num_rows - 2, 1, "|  ^X Exit      |  ^J Justify    |  ^W Where Is   |  ^V Next Page  |  ^T To Spell  |");

	
	for (int i = 62; i < num_cols; i++)
	{
		//finish line next to top gui bar
		mvaddch(1, i, ACS_CKBOARD);
	}

	for (int i = 85; i < num_cols; i++)
	{
		//finish line next to bottom gui bars
		mvaddch(num_rows - 3, i, ACS_CKBOARD);
	}

	for (int i = 85; i < num_cols; i++)
	{
		//finish line next to bottom gui bars
		mvaddch(num_rows - 2, i, ACS_CKBOARD);
	}

	for (int i = 0; i < num_cols; i++)
	{
		//line under top bar
		mvaddch(2, i, ACS_HLINE);
	}

	for (int i = 0; i < num_cols; i++)
	{
		//line above bottom bar
		mvaddch(num_rows - 4, i, ACS_HLINE);
	}

	for (int i = 0; i < num_rows; i++)
	{
		//left column
		mvaddch(i, 0, ACS_CKBOARD);
		
		//right column
		mvaddch(i, num_cols - 1, ACS_CKBOARD);
	}

	//tells curses to draw
	refresh();
	char result = getch();

	//revert back to normal console mode
	nodelay(main_window, TRUE);
	keypad(main_window, TRUE);
	mvaddstr(0, 0, "Press any key to continue...");
	endwin();
}