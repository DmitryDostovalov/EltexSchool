//#include<termios.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<ncurses.h>
#include<stdlib.h>

void sig_winch()
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
	resizeterm(size.ws_row, size.ws_col);
}

int main()
{
	WINDOW* wnd;
	WINDOW* subwnd;

	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(FALSE);
	start_color();
	refresh();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_YELLOW, COLOR_WHITE);
	wnd = newwin(5, 18, 2, 4);
	wattron(wnd, COLOR_PAIR(1));
	//box(wnd, '|', '-');
	wborder(wnd, '|', '|', '-', '-', '*', '*', '*', '*');
	subwnd = derwin(wnd, 3, 16, 1, 1);
	//box(subwnd, '@', '%');
	wbkgd(subwnd, COLOR_PAIR(2));
	wattron(subwnd, A_BOLD);
	wprintw(subwnd, "Hello, brave new ncurses world!\n");
	wrefresh(subwnd);
	wrefresh(wnd);
	delwin(subwnd);
	delwin(wnd);
	wmove(stdscr, 8, 1);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	return 0;
}
