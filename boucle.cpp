#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <vector>
using namespace std;
vector<vector<int>> map = generateur(); //carte des int
int main(){
	initscr();
	noecho();
	char character;
	int ref_movement = time(NULL);
	int ch;
	Rogue perso = Rogue();
	grid = display_grid(map) //cart des char
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
