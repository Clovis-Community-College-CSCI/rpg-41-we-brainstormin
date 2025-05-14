//main file
#include "characters.h"
//#include "linkedlist.h"
#include "ncurses.h"
using namespace std;

int main(int argc, char **argv) {
	vector<unique_ptr<Hero>> party;
	party.push_back(make_unique<Karen>());
	party.push_back(make_unique<Goth>());
	party.push_back(make_unique<Cop>());
	party.push_back(make_unique<Unattended_Child>());

	readyUp(party);

	return 0;
}
