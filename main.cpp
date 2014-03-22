#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "eight-puzzle-solver.h"

using namespace std;

int main()
{
    initscr();
    cbreak();
    noecho();
    int h, w;
    getmaxyx(stdscr, h, w);
    WINDOW *win = newwin(h, w, 0, 0);
    EightPuzzleSolver solver {win,"results.txt"};
    solver.initialize(10,15);
    solver.start();
    wrefresh(win);
    endwin();
    return 0;
}

