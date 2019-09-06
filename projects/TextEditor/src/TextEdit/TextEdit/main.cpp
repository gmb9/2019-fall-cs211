#define PDC_DLL_BUILD 1
#include "curses.h"
#include <string>

using namespace std;

unsigned char border_char = 219;

int main(int argc, char* argv[])
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

	if (has_colors() == FALSE) 
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	//fun stuff happens here
	start_color();

	Mouse_status;

	//colors
	init_pair(1, COLOR_RED, COLOR_WHITE); //red
	init_pair(2, COLOR_YELLOW, COLOR_WHITE); //orange/yellow
	init_pair(3, COLOR_GREEN, COLOR_WHITE); //green
	init_pair(4, COLOR_BLUE, COLOR_WHITE); //blue
	init_pair(5, COLOR_CYAN, COLOR_WHITE); //light blue
	init_pair(6, COLOR_MAGENTA, COLOR_WHITE); //purple

	//highlights text
	wattron(main_window, A_REVERSE);
	wattron(main_window, A_BLINK);

	//top gui bar
	//mvaddstr(1, 1, "|  File  |  Edit  |  Options  |  Buffers  |  Tools  |  Help  |");

	attron(COLOR_PAIR(1));
	mvaddstr(1, 1, "|  File  ");
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	mvaddstr(1, 10, "|  Edit  ");
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(3));
	mvaddstr(1, 19, "|  Options  ");
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(4));
	mvaddstr(1, 30, "|  Buffers  ");
	attroff(COLOR_PAIR(4));

	attron(COLOR_PAIR(6));
	mvaddstr(1, 42, "|  Tools  ");
	attroff(COLOR_PAIR(6));

	attron(COLOR_PAIR(1));
	mvaddstr(1, 52, "|  Help  |");
	attroff(COLOR_PAIR(1));

	//bottom gui bars
	//mvaddstr(num_rows - 3, 1, "|  ^G Get Help  |  ^O Write Out  |  ^R Read File  |  ^Y Prev Page  |  ^C Cur Pos   |");

	attron(COLOR_PAIR(1));
	mvaddstr(num_rows - 3, 1, "|  ^G Get Help  ");
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	mvaddstr(num_rows - 3, 17, "|  ^O Write Out  ");
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(3));
	mvaddstr(num_rows - 3, 34, "|  ^R Read File  ");
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(4));
	mvaddstr(num_rows - 3, 51, "|  ^Y Prev Page  ");
	attroff(COLOR_PAIR(4));

	attron(COLOR_PAIR(6));
	mvaddstr(num_rows - 3, 68, "|  ^C Cur Pos   |");
	attroff(COLOR_PAIR(6));

	//mvaddstr(num_rows - 2, 1, "|  ^X Exit      |  ^J Justify    |  ^W Where Is   |  ^V Next Page  |  ^T To Spell  |");
	attron(COLOR_PAIR(1));
	mvaddstr(num_rows - 2, 1, "|  ^X Exit      ");
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	mvaddstr(num_rows - 2, 17, "|  ^J Justify     ");
	attroff(COLOR_PAIR(2));

	attron(COLOR_PAIR(3));
	mvaddstr(num_rows - 2, 34, "|  ^W Where Is   ");
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(4));
	mvaddstr(num_rows - 2, 51, "|  ^V Next Page  ");
	attroff(COLOR_PAIR(4));

	attron(COLOR_PAIR(6));
	mvaddstr(num_rows - 2, 68, "|  ^T To Spell  |");
	attroff(COLOR_PAIR(6));

	attron(COLOR_PAIR(5));

	for (int i = 0; i < num_cols; i++)
	{
		//top border
		mvaddch(0, i, ACS_CKBOARD);

		//bottom border
		mvaddch(num_rows - 1, i, ACS_CKBOARD);
	}
	
	for (int i = 62; i < num_cols; i++)
	{
		//finish checkerboard line next to top gui bar
		mvaddch(1, i, ACS_CKBOARD);
	}

	for (int i = 85; i < num_cols; i++)
	{
		//finish checkerboard line next to bottom gui bars
		mvaddch(num_rows - 3, i, ACS_CKBOARD);
	}

	for (int i = 85; i < num_cols; i++)
	{
		//finish line next to bottom gui bars
		mvaddch(num_rows - 2, i, ACS_CKBOARD);
	}

	for (int i = 0; i < num_rows; i++)
	{
		//left column
		mvaddch(i, 0, ACS_CKBOARD);
		
		//right column
		mvaddch(i, num_cols - 1, ACS_CKBOARD);
	}

	attroff(COLOR_PAIR(5));
	wattroff(main_window, A_REVERSE);
	wattroff(main_window, A_BLINK);

	for (int i = 1; i < num_cols - 1; i++)
	{
		//line directly under top gui bar
		mvaddch(2, i, ACS_HLINE);
	}

	for (int i = 1; i < num_cols - 1; i++)
	{
		//line directly above bottom gui bar
		mvaddch(num_rows - 4, i, ACS_HLINE);
	}

	//fun stuff ends here

	//tells curses to draw
	refresh();
	char result = getch();

	//revert back to normal console mode
	nodelay(main_window, TRUE);
	keypad(main_window, TRUE);
	mvaddstr(0, 0, "Press any key to continue...");
	endwin();
}