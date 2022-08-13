//#include<termios.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<ncurses.h>

void sig_winch()
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
	resizeterm(size.ws_row, size.ws_col);
}

int main()
{
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	noecho();
	curs_set(0);
	attron(A_BOLD);
	move(5, 15);
	printw("Hello, brave new ncurses world!\n");
	attroff(A_BOLD);
	attron(A_BLINK);
	move(7, 16);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	return 0;
}
