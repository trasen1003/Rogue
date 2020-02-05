#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <vector>
//#include "personnages_def.h"
#include "personnages.h"
#include "MapDisplay.h"
// #include "RandomMapGenerator.h" 
#include <gen_carte.h>
using namespace std;
int main(){
	int pos [2] = {0,0};
	//vector<vector<int>> map = Generateur(&pos[0]); //carte des int
	setup set = setup_map(3);
	vector<vector<int>> map = set.map;
	cout << "genere" << endl;
	initscr();
	noecho();
	char character;
	int ref_movement = time(NULL);
	int ch;
	Rogue perso = Rogue(&map,&pos[0]);
	vector<vector<char>> grid = display_grid(map); //cart des char
	for(int i = 0; i<grid.size();i ++){
		for(int j = 0; j < grid[0].size();j++){
			mvprintw(i, j, "%c",grid[i][j]);
		}
	}
	while(true){ //boucle principale
		ch = getch(); //quand une touche est appuyée
		perso.action(ch); //faire action
		grid = display_grid(map); //cart des char
		for(int i = 0; i<grid.size();i ++){
			for(int j = 0; j < grid[0].size();j++){
				mvprintw(i, j, "%c",grid[i][j]);
			}
		}
	}
	return 0;
}
