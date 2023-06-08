#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <deque>

enum directions {UP, DOWN, LEFT, RIGHT};
enum status {LIVE, DED};
enum cause_of_death {NONE, AUTOSARCOPHAGY, WALL_BRUTALITY};

//GLOBALS
const int win_height = 20;
const int win_width = 41;

struct pos {
	int y, x;
	bool operator==(const pos& rhs) const {
		return y == rhs.y && x == rhs.x;
	}
};

class Player {
	public:
		Player(pos p) : position(p) {}
		pos position;
	private:

};

int main(int argc, char *argv[])
{
	initscr();			// Start curses mode
	cbreak();			// Line buffering disabled
	noecho();			// Don't echo() while we do getch
	keypad(stdscr, TRUE);		// Enable function keys
	curs_set(0);			// Hide cursor
	//timeout(0);			// Non-blocking getch()



	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	int c;
	WINDOW *win = newwin(win_height, win_width, 1, 0);
	box(win, 0, 0);

	int y = 1, x = 1;

	Player player(pos{y, x});
	
	do {

		wclear(stdscr);
		printw("CAVE OV EVIL >:(");

		wclear(win);
		box(win, 0, 0);

		for (int i = 1; i < win_height - 1; ++i) {
			for (int j = 1; j < win_width - 1; ++ ++j) {
				mvwaddch(win, i, j, '.');
			}
		}

		wmove(win, player.position.y, player.position.x);
		waddch(win, '@');

		refresh();
		wrefresh(win);

		c = getch();
		switch (c) {
			case KEY_UP: 	   --player.position.y; break;
			case KEY_DOWN: 	   ++player.position.y; break;
			case KEY_LEFT: 	-- --player.position.x; break;
			case KEY_RIGHT:	++ ++player.position.x; break;
		}
		



	} while (c != 'q' && c != 'Q');

	//printw(" DED");

	//timeout(-1);
	//getch();
	endwin();			

	printf("goodbye!\n");

	return 0;
}
