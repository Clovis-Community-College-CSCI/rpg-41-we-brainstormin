//Implenting UI
#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAP_WIDTH = 160;
const int MAP_HEIGHT = 33;

//declare player
int playerX = 110;
int playerY = 11;

int prevPlayerX = playerX;
int prevPlayerY = playerY;

void drawBox(WINDOW* win, int x, int y, int w, int h, const string& title){
    //borders
    for(int i = x; i < x + w; i++){ // top and bottom
        mvwaddch(win, y, i, '-');
        mvwaddch(win, y + h - 1, i, '_');
    }

    for (int i = y; i < y + h; i++){ // right and left
        mvwaddch(win, i, x, '|');
        mvwaddch(win, i, x + w - 1, '|');
    }

	//corners
    mvwaddch(win, y, x, '+');
    mvwaddch(win, y, x + w - 1, '+');
    mvwaddch(win, y + h - 1, x, '+');
    mvwaddch(win, y + h - 1, x + w - 1, '+');

	//title
    if (w >static_cast<int>(title.length()) + 2){
    mvwprintw(win, y, x + (w - static_cast<int>(title.length()))/2, "%s", title.c_str());
    }
}

void handleInput(int ch){
	prevPlayerX = playerX;
	prevPlayerY = playerY;

	//movement
    switch(ch){
        case KEY_UP: if(playerY > 1) playerY--; break;
        case KEY_DOWN: if(playerY < MAP_HEIGHT-2) playerY++; break;
        case KEY_LEFT: if(playerX > 1) playerX--; break;
        case KEY_RIGHT: if(playerX < MAP_WIDTH-2) playerX++; break;
    }
}

void drawMap(WINDOW* win, const vector<unique_ptr<Monster>> &monsters){
//    wclear(win); // clear screen (causing screen to flicker)

    //outer walls
    for (int y = 0; y < MAP_HEIGHT; y++){
        mvwaddch(win, y, 0, '#');
        mvwaddch(win, y, MAP_WIDTH -1, '#');
    }
	for (int x = 0; x < MAP_WIDTH; x++){
        mvwaddch(win, 0, x, '#');
        mvwaddch(win, MAP_HEIGHT-1, x, '#');
    }

    //rooms
    drawBox(win, 55, 2, 40, 5, "SEARS");
    drawBox(win, 30, 2, 18, 5, "Vendor Area");
    drawBox(win, 7, 2, 18, 5, "Never 21");
//    mvwaddch(win, 8, 25, 'c');
	drawBox(win, 7, 9, 80, 5, "Main Center");
	drawBox(win, 20, 16, 40, 5, "Food Court");
    drawBox(win, 100, 9, 25, 5, "Parking Lot");

    //doors
    mvwaddch(win, 6, 70, 'D'); //sears
    mvwaddch(win, 6, 35, 'D'); //vendor area
    mvwaddch(win, 6, 15, 'D'); // Never 21
    mvwaddch (win, 11, 86, 'D'); // food court

    //cop
//    mvwaddch(win, MAP_HEIGHT-2, MAP_WIDTH/2, 'C');

	//path
    for (int y = 7; y <= 8; y++){
        mvwaddch(win, y, 70, '|'); // towards sears
        mvwaddch(win, y, 35, '|'); // vendor area
        mvwaddch(win, y, 15, '|'); // never 21
    }
    for (int y = 14; y <= 15; y++){
        mvwaddch(win, y, 45, '|');
    }

	for (const auto &m : monsters) {
		 mvwaddch(win, m->y, m->x, m->get_sym());
	}

    //draw player
	mvwaddch(win, prevPlayerY, prevPlayerX, ' ');
    mvwaddch(win, playerY, playerX, '@');

    wrefresh(win);
}

Monster* catchEm(int x, int y, vector<unique_ptr<Monster>>& monsters) {
	//bumped into a monster
	for (auto &m : monsters) {
		if ((abs(m->x - x) + abs(m->y -y)) == 1) {
			return m.get();
		}
	}
	return nullptr;
}

void readyUp(vector<unique_ptr<Hero>> &party) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);//cursor hide

    //arrow keys
    mousemask(0, NULL);
    nodelay(stdscr, TRUE);

	//heroes
	Hero* player = party[0].get();
	player->x = playerX;
	player->y = playerY;

	//monsters
	vector<unique_ptr<Monster>> monsters;
	//Minivan Mom
    monsters.push_back(make_unique<Minivan_Mom>());
    monsters[0]->x = 105;
    monsters[0]->y = 11;
	//Leashed Kids
	monsters.push_back(make_unique<Leashed_Kids>());
	monsters[1]->x = 40;
	monsters[1]->y = 18;
	//Sneaker Head
	monsters.push_back(make_unique<Sneaker_Head>());
	monsters[2]->x = 42;
	monsters[2]->y = 5;
	//Vampires
	monsters.push_back(make_unique<Vampires>());
	monsters[3]->x = 12;
	monsters[3]->y = 5;
	//Spirit of Sierra Vista
	monsters.push_back(make_unique<Spirit>());
	monsters[4]->x = 90;
	monsters[4]->y = 4;
	
	Monster* currTarget = nullptr;
	bool inBattle = false;
	int chosenOne = 0;

	//game loop
	int ch;
    while((ch = getch()) != 'q') { // q to quit
        handleInput(ch);
        drawMap(stdscr, monsters);

		//battle
		if (ch == ' ') {
			currTarget = catchEm(playerX, playerY, monsters);
			inBattle = currTarget != nullptr;
			if (inBattle) {
				mvprintw(MAP_HEIGHT + 4, 0, "%s Encountered! Use: '1' to attack, '2' for special", currTarget->get_name().c_str());
				currTarget->speak();
			} else { mvprintw(MAP_HEIGHT + 4, 0, "You're all alone. Forever."); }
		}

		if (inBattle) {
			Hero* inAction = party[chosenOne].get();
			if (ch = KEY_RIGHT) chosenOne = (chosenOne + 1) % party.size();
			if (ch = KEY_LEFT) chosenOne = (chosenOne - 1 + party.size()) % party.size();

			if (ch == '1') {
				inAction->attack(*currTarget);
				mvprintw(MAP_HEIGHT + 5, 0, "Used ATTACK on %s: %d HP!", currTarget->get_name().c_str(), currTarget->get_health()); 
			} else if (ch == '2') {
				if (auto child = dynamic_cast<Unattended_Child*>(inAction)) {
					vector<Hero*> aided;
					for (auto &h : party) aided.push_back(h.get());
					child->special(aided);
				} else {
				inAction->special(*currTarget);
				mvprintw(MAP_HEIGHT + 5, 0, "Used SPECIAL on %s : %d HP!", currTarget->get_name().c_str(), currTarget->get_health());
				}
			}

			if (currTarget->get_health() <= 0) {
				mvprintw(MAP_HEIGHT + 6, 0, "PLAYER WINS!");
				auto snap = remove_if(monsters.begin(), monsters.end(), [currTarget](unique_ptr<Monster> &m) { return m.get() == currTarget; });
				monsters.erase(snap, monsters.end());
				currTarget = nullptr;
				inBattle = false;
			}
		}
		
        // display instructions
        mvprintw(MAP_HEIGHT + 2, 0, "Use : arrow keys to move, space to battle, and 'q' to quit");
        refresh();
    }

    endwin();
} 
