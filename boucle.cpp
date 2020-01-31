#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <vector>
using namespace std;
vector<vector<int>> map = generateur();
int main(){
	initscr();
	noecho();
	char character;
	int ref_movement = time(NULL);
	int ch;
	Rogue perso = Rogue();
	while(true){ //boucle principale
		ch = getch();
		perso.action(ch);
		for(int i = 0; i<map.size();i ++){
			for(int j = 0; j < map[0].size();j++){
				mvprintw(i, j, "%c",map[i][j]);
			}
		}
	}
	return 1;
}
