#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <vector>
//#include "personnages_def.h"
#include "personnages.h"
#include "MapDisplay.h"
#include "RandomMapGenerator.h"
using namespace std;
int main(){
	vector<vector<int>> map = Generateur(); //carte des int
	initscr();
	noecho();
	char character;
	int ref_movement = time(NULL);
	int ch;
	Rogue perso = Rogue(&map);
	vector<vector<char>> grid = display_grid(map); //cart des char
	while(true){ //boucle principale
		ch = getch(); //quand une touche est appuyée
		perso.action(ch); //faire action
		for(int i = 0; i<grid.size();i ++){
			for(int j = 0; j < grid[0].size();j++){
				mvprintw(i, j, "%c",grid[j][i]);
			}
		}
	}
	return 1;
}
