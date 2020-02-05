#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <vector>
//#include "personnages_def.h"
#include "personnages.h"
#include "MapDisplay.h"
// #include "RandomMapGenerator.h" 
// #include "gen_carte.h"

using namespace std;
int main(){
	point pos {0,1};
	/*point begin {0,0};
	point end {2,2};
	room _room {begin, end};
	vector<room> rooms {_room};
	print(find_room(pos,&rooms));
	return 0;*/
	//vector<vector<int>> map = Generateur(&pos[0]); //carte des int
	setup set = setup_map(1,&pos);
	vector<vector<bool>> Matrix_revealed = set.Matrix_revealed;
	vector<room> rooms = set.rooms;
	vector<vector<int>> map = set.map;
	cout << "genere" << endl;
	initscr();
	noecho();
	int ch;
	int temp = 1;
	Rogue perso = Rogue(&map,pos);
	vector<vector<char>> grid = display_grid(map); //cart des char
	for(int i = 0; i< (int) grid.size();i ++){
		for(int j = 0; j < (int) grid[0].size();j++){
			if (Matrix_revealed[i][j]) {
				mvprintw(i, j, "%c",grid[i][j]);
			} else {
				mvprintw(i, j, "%c",' ');
			}
		}
	}
	while(true){ //boucle principale
		ch = getch(); //quand une touche est appuyée
		perso.action(ch, &temp, &rooms, &Matrix_revealed); //faire action
		grid = display_grid(map); //cart des char
		for(int i = 0; i< (int) grid.size();i ++){
			for(int j = 0; j < (int) grid[0].size();j++){
				if (Matrix_revealed[i][j]) {
					mvprintw(i, j, "%c",grid[i][j]);
				} else {
					mvprintw(i, j, "%c",' ');
				}
			}
		}
	}
	return 0;
}
