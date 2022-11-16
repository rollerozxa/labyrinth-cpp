#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

struct Vec2 {
	int x;
	int y;
};

struct Object {
	int x;
	int y;
	int old_x;
	int old_y;
};

Object player = { 1,1, 0,0 };

Vec2 res = { 0,0 };
Vec2 res_old = { 0,0 };

// Allocate half a megabyte of mostly unused data... Wasteful! (:
bool wall[512][512];

#ifdef PDCURSES
// For some god forsaken reason PDCurses does not provide the proper dimensions.
# undef getmaxyx
# define getmaxyx(win,y,x) (y = 25, x = 80)
#endif

void reload();
void draw_noise();
void testlevel();

int main() {
	initscr();
	noecho();
	timeout(0);
	curs_set(0);
	srand(1);

	getmaxyx(stdscr, res.y, res.x);
	reload();

	while (true) {
		getmaxyx(stdscr, res.y, res.x);

		if (res.x != res_old.x || res.y != res_old.y) {
			clear();
			reload();
		}
		getmaxyx(stdscr, res_old.y, res_old.x);

		napms(1000/60);

		for (int x = 0; x < res.x; x++) {
			for (int y = 0; y < res.y; y++) {
				if (wall[x][y]) {
					mvaddch(y,x, ACS_BLOCK);
				}
			}
		}

		switch (getch()) {
			case 'w':
			case 'W':
				player.y--;
			break;

			case 'a':
			case 'A':
				player.x--;
			break;

			case 's':
			case 'S':
				player.y++;
			break;

			case 'd':
			case 'D':
				player.x++;
			break;

			case 'q':
			case 'Q':
				curs_set(1);
				endwin();
				return 0;
		}

		if (player.x != player.old_x || player.y != player.old_y) {
			if (!wall[player.x][player.y]) {
				mvaddstr(player.old_y, player.old_x, " ");

				player.old_x = player.x;
				player.old_y = player.y;
			} else {
				player.x = player.old_x;
				player.y = player.old_y;
			}
		}

		mvaddstr(player.y, player.x, "O");
	}

	endwin();

	return 0;
}

void reload() {
	memset(wall,0,sizeof(wall));

	for (int x = 0; x < res.x; x++) {
		wall[x][0] = true;
		wall[x][res.y-1] = true;
	}

	for (int y = 0; y < res.y; y++) {
		wall[0][y] = true;
		wall[res.x-1][y] = true;
	}

	testlevel();
}

void draw_noise() {
	for (int x = 20; x < 40; x++) {
		for (int y = 20; y < 40; y++) {
			if (rand()%2 == 0) {
				wall[x][y] = true;
			} else {
				mvaddch(y,x, ' ');
				wall[x][y] = false;
			}
		}
	}
}

void testlevel() {

	wall[2][1] = true;
	wall[6][1] = true;
	wall[10][1] = true;
	wall[12][1] = true;
	wall[21][1] = true;
	wall[25][1] = true;

	wall[2][2] = true;
	wall[4][2] = true;
	wall[6][2] = true;
	wall[8][2] = true;
	wall[14][2] = true;
	wall[16][2] = true;
	wall[17][2] = true;
	wall[18][2] = true;
	wall[19][2] = true;
	wall[21][2] = true;
	wall[23][2] = true;
	wall[25][2] = true;

	wall[2][3] = true;
	wall[4][3] = true;
	wall[6][3] = true;
	wall[8][3] = true;
	wall[9][3] = true;
	wall[10][3] = true;
	wall[12][3] = true;
	wall[16][3] = true;
	wall[21][3] = true;
	wall[23][3] = true;
	wall[25][3] = true;

	wall[2][4] = true;
	wall[4][4] = true;
	wall[8][4] = true;
	wall[12][4] = true;
	wall[13][4] = true;
	wall[14][4] = true;
	wall[16][4] = true;
	wall[18][4] = true;
	wall[19][4] = true;
	wall[20][4] = true;
	wall[21][4] = true;
	wall[23][4] = true;
	wall[25][4] = true;

	wall[2][5] = true;
	wall[3][5] = true;
	wall[4][5] = true;
	wall[6][5] = true;
	wall[7][5] = true;
	wall[8][5] = true;
	wall[10][5] = true;
	wall[14][5] = true;
	wall[16][5] = true;
	wall[23][5] = true;
	wall[25][5] = true;
	wall[10][6] = true;
	wall[11][6] = true;
	wall[12][6] = true;
	wall[14][6] = true;
	wall[16][6] = true;
	wall[18][6] = true;
	wall[19][6] = true;
	wall[20][6] = true;
	wall[21][6] = true;
	wall[23][6] = true;
	wall[25][6] = true;

	wall[2][7] = true;
	wall[3][7] = true;
	wall[4][7] = true;
	wall[5][7] = true;
	wall[6][7] = true;
	wall[7][7] = true;
	wall[8][7] = true;
	wall[10][7] = true;
	wall[14][7] = true;
	wall[16][7] = true;
	wall[23][7] = true;
	wall[25][7] = true;

	wall[2][8] = true;
	wall[8][8] = true;
	wall[10][8] = true;
	wall[12][8] = true;
	wall[13][8] = true;
	wall[14][8] = true;
	wall[16][8] = true;
	wall[18][8] = true;
	wall[19][8] = true;
	wall[20][8] = true;
	wall[21][8] = true;
	wall[23][8] = true;
	wall[25][8] = true;

	wall[2][9] = true;
	wall[4][9] = true;
	wall[5][9] = true;
	wall[6][9] = true;
	wall[8][9] = true;
	wall[10][9] = true;
	wall[16][9] = true;
	wall[18][9] = true;
	wall[21][9] = true;
	wall[23][9] = true;
	wall[25][9] = true;
	wall[4][10] = true;
	wall[6][10] = true;
	wall[12][10] = true;
	wall[13][10] = true;
	wall[14][10] = true;
	wall[15][10] = true;
	wall[16][10] = true;
	wall[18][10] = true;
	wall[19][10] = true;
	wall[21][10] = true;
	wall[23][10] = true;
	wall[25][10] = true;

	wall[1][11] = true;
	wall[2][11] = true;
	wall[3][11] = true;
	wall[4][11] = true;
	wall[6][11] = true;
	wall[7][11] = true;
	wall[8][11] = true;
	wall[9][11] = true;
	wall[10][11] = true;
	wall[12][11] = true;
	wall[19][11] = true;
	wall[23][11] = true;
	wall[25][11] = true;

	wall[12][12] = true;
	wall[14][12] = true;
	wall[15][12] = true;
	wall[16][12] = true;
	wall[17][12] = true;
	wall[19][12] = true;
	wall[21][12] = true;
	wall[22][12] = true;
	wall[23][12] = true;
	wall[25][12] = true;

	wall[2][13] = true;
	wall[4][13] = true;
	wall[5][13] = true;
	wall[6][13] = true;
	wall[7][13] = true;
	wall[8][13] = true;
	wall[10][13] = true;
	wall[11][13] = true;
	wall[12][13] = true;
	wall[14][13] = true;
	wall[19][13] = true;
	wall[23][13] = true;
	wall[25][13] = true;

	wall[2][14] = true;
	wall[10][14] = true;
	wall[12][14] = true;
	wall[14][14] = true;
	wall[16][14] = true;
	wall[17][14] = true;
	wall[18][14] = true;
	wall[19][14] = true;
	wall[20][14] = true;
	wall[21][14] = true;
	wall[23][14] = true;
	wall[25][14] = true;

	wall[2][15] = true;
	wall[3][15] = true;
	wall[4][15] = true;
	wall[5][15] = true;
	wall[6][15] = true;
	wall[7][15] = true;
	wall[8][15] = true;
	wall[9][15] = true;
	wall[10][15] = true;
	wall[12][15] = true;
	wall[14][15] = true;
	wall[23][15] = true;
	wall[25][15] = true;

	wall[4][16] = true;
	wall[12][16] = true;
	wall[14][16] = true;
	wall[16][16] = true;
	wall[17][16] = true;
	wall[18][16] = true;
	wall[19][16] = true;
	wall[20][16] = true;
	wall[21][16] = true;
	wall[22][16] = true;
	wall[23][16] = true;
	wall[25][16] = true;

	wall[2][17] = true;
	wall[3][17] = true;
	wall[4][17] = true;
	wall[5][17] = true;
	wall[7][17] = true;
	wall[8][17] = true;
	wall[9][17] = true;
	wall[10][17] = true;
	wall[12][17] = true;
	wall[13][17] = true;
	wall[14][17] = true;
	wall[16][17] = true;
	wall[21][17] = true;
	wall[25][17] = true;

	wall[7][18] = true;
	wall[16][18] = true;
	wall[19][18] = true;
	wall[23][18] = true;
	wall[25][18] = true;

}
