#include <graphics.h>
#include <ctime>
#include <cstdlib>
#include "QuanLyGame.h"
int main() {
    initwindow(700, 700, "Pac-Man");
    srand(time(0));
    QuanLyGame game;
    game.chayMenu();
    closegraph();
    return 0;
}