# include <vector>
# include <iostream>
# include <string>
# include <stdio.h>     
# include <stdlib.h>    
# include <time.h>  
# include <unistd.h>
# include <chrono>
# include <algorithm>

using namespace std;

struct to_extract{
	int i1;
	int i2;
	int j1;
	int j2;
};

struct point{
	int x;
	int y;
};

struct room{
	point begin;
	point end;
	bool revealed;
};

struct setup {
	vector<vector<int>> map;
	vector<vector<bool>> Matrix_revealed;
	vector<room*> rooms;
	bool it_worked;
};

void print(string haha){
	cout << haha << endl;
}

void print(double haha) {
	cout << haha << endl;
}

void print_M(vector<vector<int>>* M){
	for (int i = 0; i < M -> size(); i++) {
		for (int j = 0; j < (M -> at(0)).size(); j++){
			cout << (M-> at(i))[j] << " ";
		}
		cout << endl;
	}
}

void print_M(vector<vector<bool>>* M){
	for (int i = 0; i < M -> size(); i++) {
		for (int j = 0; j < (M -> at(0)).size(); j++){
			cout << (M-> at(i))[j] << " ";
		}
		cout << endl;
	}
}

void print_P(point P){
	cout << "x is :" << P.x << endl;
	cout << "y is :" << P.y << endl;
}

point random_point(int max_x, int max_y) {
  	srand ((int)chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count());
  	int x = rand() % max_x + 1;
  	int y = rand() % max_y + 1;
  	return point {x,y};
}

int random_int(int max) {
  	srand ((int)chrono::duration_cast<chrono::microseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count());
	return rand() % max + 1 ;
}

bool probability(double proba) {
	int n = (int)(100*proba);
	int random = random_int(100);
	if (random < n){
		return true;
	} else {
		return false;
	}

}

vector<vector<bool>> make_matrix_bool(int hauteur, int longueur) {
	vector<vector<bool>> grid;
	for (int i = 0; i < hauteur; i++){
		vector<bool> line(longueur,false);
		grid.push_back(line);
	}
	return grid;
}

vector<vector<int>> make_matrix(int hauteur, int longueur) {
	vector<vector<int>> grid;
	for (int i = 0; i < hauteur; i++){
		vector<int> line(longueur,0);
		grid.push_back(line);
	}
	return grid;
}

to_extract find_extract(vector<vector<int>>* grid) {
	int i1 = 0;
	int i2 = 0;
	int j1 = 0;
	int j2 = 0;
	while(all_of((grid -> at(i1+1)).begin(), (grid -> at(i1+1)).end(), [](int i){return i == 0;}) ){
		i1++;
	}
	while(all_of((grid -> at(grid -> size() - i2 -2)).begin(), (grid -> at(grid -> size() - i2 - 2)).end(), [](int i){return i == 0;}) ){
		i2++;
	}
	vector<int> column_begin;
	vector<int> column_end;
	for (int i = 0; i < grid -> size(); i++) {
		column_begin.push_back((grid -> at(i))[j1 + 1]);
		column_end.push_back((grid -> at(i))[grid -> size() -j2 -2]);		
	}
	while(all_of(column_begin.begin(), column_begin.end(), [](int i){return i == 0;}) ){
		j1++;
		for (int i = 0; i < grid -> size(); i++) {
			column_begin.push_back((grid -> at(i))[j1 + 1]);
		}	
	}
	while(all_of(column_end.begin(), column_end.end(), [](int i){return i == 0;}) ){
		j2++;
		for (int i = 0; i < grid -> size(); i++) {
			column_end.push_back((grid -> at(i))[grid -> size() -j2 -2]);		
		}
	}
	return to_extract {i1, i2, j1, j2};
}

vector<vector<int>> extract(to_extract ex, vector<vector<int>>* grid) {
	int i1 = ex.i1;
	int i2 = ex.i2;
	int j1 = ex.j1;
	int j2 = ex.j2;	
	vector<vector<int>> exctracted;
	for (int i = i1; i < grid -> size() - i2; i++){
		vector<int> line;
		for (int j = j1; j < (grid -> at(0)).size() - j2; j++) {
			line.push_back((grid -> at(i))[j]);
		}
		exctracted.push_back(line);
	}
	return exctracted;
}

bool room_is_good(point begin, point end, vector<vector<bool>>* Good_for_room, vector<vector<int>>* grid){
	for (int x = begin.x; x < end.x; x++){
		for (int y = begin.y; y < end.y; y++) {
			if ((Good_for_room -> at(x))[y] == 1) {
				return false;
			}
			if (((x == begin.x && y == begin.y) || (x == begin.x && y == end.y -1) 
					|| (x == end.x -1 && y == begin.y) || (x == end.x -1 && y == end.y -1)) && (grid -> at(x))[y] == 5){
				return false;
			}
		}
	}
	return true;
}

bool find_in(point reached, room _room){
	bool in = reached.x <= _room.end.x && _room.begin.x <= reached.x && _room.end.y <= reached.y && reached.y <= _room.begin.y;
	if (in) {
		if (reached.x == _room.begin.x && reached.y == _room.end.y) {
			return false;
		} else if (reached.x == _room.begin.x && reached.y == _room.end.y) {
			return false;
		} else if (reached.y == _room.begin.y && reached.x == _room.end.x) {
			return false;
		} else if (reached.y == _room.end.y && reached.x == _room.begin.x) {
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

int find_indice(point reached, vector<room*>* rooms) {
	int indice = -1;
	for (int k = 0; k < rooms -> size(); k++) {
		if (find_in(reached, *((*rooms)[k]))) {
			indice = k;
		}
	}
	return indice;
}

point try_add_path(vector<point> path, vector<vector<bool>>* matrix_con, vector<room*>* rooms, vector<vector<int>>* grid) {
	vector<point>::iterator it;
	for (it = path.begin(); it != path.end(); it++){
		int i = (*it).x;
		int j = (*it).y;
		if ((grid -> at(i))[j]== 2 || (grid -> at(i))[j] == 3) {
			point reached {i, j};
			int indice = find_indice(reached, rooms);
			if (indice == -1) {
				return point {-1, -1};
			}
			int indice_new_room = rooms -> size() - 1;
			if ((matrix_con -> at(indice))[indice_new_room]  == 1) {
				return point {-1, -1};
			} else {
				(matrix_con -> at(indice))[indice_new_room]  = 1;
				(matrix_con -> at(indice_new_room))[indice]  = 1;
				(grid -> at(i))[j]= 4;
				return point {i, j};
			}
		} else if ((grid -> at(i))[j] == 4) {
			return point {-1, -1};
		}
	}
	return path[path.size() - 1];
}

vector<point> compute_path(point door,int main_dir,int  dir_x,int  dir_y,int len_x,int len_y) {
	vector<point> path;
	point p;
	if (main_dir == 0){
		int j = 0;
		if (dir_x == 0) {
			for(int i = 1; i < len_x; i++) {
				p = {door.x - i, door.y};
				path.push_back(p); 
			}
			int i = len_x - 1;
			if (dir_y == 0) {
				for (j = 0; j < len_y; j++) {
					p = {door.x - i, door.y - j};
					path.push_back(p);
				}
			} else if (dir_y == 1) {
				for (j = 0; j < len_y; j++) {
					p = {door.x - i, door.y + j};
					path.push_back(p);
				}
			}
		} else if (dir_x == 1) {
			for(int i = 1; i < len_x; i++) {
				p = {door.x + i, door.y};
				path.push_back(p); 
			}
			int i = len_x - 1;
			if (dir_y == 0) {
				for (j = 0; j < len_y; j++) {
					p = {door.x + i, door.y - j};
					path.push_back(p);
				}
			} else if (dir_y == 1) {
				for (j = 0; j < len_y; j++) {
					p = {door.x + i, door.y + j};
					path.push_back(p);
				}
			}			
		}
	} else if (main_dir == 1) {
		int i = 0;
		if (dir_y == 0) {
			for(int j = 1; j < len_y; j++) {
				p = {door.x, door.y - j};
				path.push_back(p); 
			}
			int j = len_y - 1;
			if (dir_x == 0) {
				for (i = 0; i < len_x; i++) {
					p = {door.x - i, door.y - j};
					path.push_back(p);
				}
			} else if (dir_x == 1) {
				for (i = 0; i < len_x; i++) {
					p = {door.x + i, door.y - j};
					path.push_back(p);
				}
			}
		} else if (dir_y == 1) {
			for(int j = 1; j < len_y; j++) {
				p = {door.x, door.y + j};
				path.push_back(p); 
			}
			int j = len_y - 1;
			if (dir_x == 0) {
				for (i = 0; i < len_x; i++) {
					p = {door.x - i, door.y + j};
					path.push_back(p);
				}
			} else if (dir_x == 1) {
				for (i = 0; i < len_x; i++) {
					p = {door.x + i, door.y + j};
					path.push_back(p);
				}
			}			
		}		
	}
	return path;
}

point add_to_good_for_room( vector<vector<bool>>* Good_for_room, vector<vector<int>>* grid, room& new_room, vector<vector<bool>>* matrix_con, vector<room*>* rooms, bool make_path) {
	point new_door {-1, -1};
	for (int x = min(new_room.begin.x, new_room.end.x); x < max(new_room.begin.x, new_room.end.x); x++) {
		for (int y = min(new_room.begin.y, new_room.end.y); y < max(new_room.end.y,new_room.begin.y); y++) {
			if (x < 0 || x >= Good_for_room -> size() || y < 0 || y >= (Good_for_room -> at(0)).size()) {
				return point {-1, -1};
			} else if (((grid->at(x))[y] == 5)) {
				if ((x == new_room.begin.x && y == new_room.begin.y) || (x == new_room.begin.x && y == new_room.end.y -1) 
					|| (x == new_room.end.x -1 && y == new_room.begin.y) || (x == new_room.end.x -1 && y == new_room.end.y -1)) {
					return point {-1, -1};
				}
			}
		}
	}
	for (int x = min(new_room.begin.x, new_room.end.x); x < max(new_room.begin.x, new_room.end.x); x++) {
		for (int y = min(new_room.begin.y, new_room.end.y); y < max(new_room.end.y,new_room.begin.y); y++) {
			(Good_for_room -> at(x))[y]  = 1;
			if ((grid->at(x))[y] == 5) {
				if (x != new_room.begin.x && x != new_room.end.x -1 && y != new_room.begin.y && y != new_room.end.y -1){
					(grid -> at(x))[y] = 0;
				} else {
					(grid -> at(x))[y] = 4;
					new_door = {x, y};
				}
			}
			if ((grid -> at(x))[y] == 0){
				if (x == new_room.begin.x || x == new_room.end.x - 1) {
					if ((x == new_room.begin.x && y == new_room.begin.y) || (x == new_room.begin.x && y == new_room.end.y -1) 
							|| (x == new_room.end.x -1 && y == new_room.begin.y) || (x == new_room.end.x -1 && y == new_room.end.y -1)){
						(grid -> at(x))[y]  = 6;						
					} else {
						(grid -> at(x))[y]  = 2;						
					}
				} else if (y == new_room.begin.y || y == new_room.end.y - 1) {
					if ((x == new_room.begin.x && y == new_room.begin.y) || (x == new_room.begin.x && y == new_room.end.y -1) 
							|| (x == new_room.end.x -1 && y == new_room.begin.y) || (x == new_room.end.x -1 && y == new_room.end.y -1)){
						(grid -> at(x))[y]  = 6;
					} else {
						(grid -> at(x))[y]  = 3;
					}
				} else {
					(grid -> at(x))[y]  = 1;
				}
			} 
		}
	}
	if (make_path) {
		point door {0, 0};
		int previous_value = 0;
		for (int essai_porte = 0; essai_porte < 30; essai_porte++) {
			if (essai_porte != 0){
				(grid -> at(door.x))[door.y] = previous_value;
			}
			int total = random_int(2*abs(new_room.begin.x - new_room.end.x) + 2*abs(new_room.begin.y - new_room.end.y) - 5);
			int incr = 0;
			for (int x = min(new_room.begin.x, new_room.end.x); x < max(new_room.begin.x, new_room.end.x); x++) {
				for (int y = min(new_room.begin.y, new_room.end.y); y < max(new_room.end.y,new_room.begin.y); y++) {
					if ((grid -> at(x))[y] == 2 || (grid -> at(x))[y] == 3) {
						if (incr == total) {
							(grid -> at(x))[y] = 4;
							door = {x, y};
							incr++;
							if ((grid -> at(x))[y] == 2) {
								previous_value = 2;
							} else {
								previous_value = 3;
							}
						} else {
							incr++;
						}
					}
				}
			}
			for (int k = 0; k < 30; k++) {
				int dir_x = random_int(2) - 1;
				int dir_y = random_int(2) - 1;
				int main_dir = 0;
				int len_x = 0;
				int len_y = 0;
				if (door.x == new_room.begin.x) {
					dir_x = 0;
					main_dir = 0;
				} else if (door.x == new_room.end.x - 1) {
					main_dir = 0;
					dir_x = 1;
				} else if (door.y == new_room.end.y - 1) {
					dir_y = 1;
					main_dir = 1;
				} else if (door.y == new_room.begin.y) {
					dir_y = 0;
					main_dir = 1;
				}
				if (-door.x + (int)(Good_for_room -> size()) - 4 <= 1 || -door.y + (int)((Good_for_room -> at(0)).size()) - 4 <= 1
					|| door.y - 4 < 1 || door.x - 4 < 1) {
					continue;
				}
				if (dir_x){
					len_x = random_int(min(6,-door.x + (int)(Good_for_room -> size()) - 4)) + 4;
				} else {
					len_x = random_int(min(6, door.x - 4)) + 4;
				}
				if (dir_y) { 
					len_y = random_int(min(6,-door.y + (int)((Good_for_room -> at(0)).size()) - 4)) + 4;
				} else {
					len_y = random_int(min(6, door.y - 4)) + 4;
				}
				if (len_x + door.x >= (Good_for_room -> size()) - 5 || len_y + door.y >= (Good_for_room -> at(0)).size() - 5 
					|| -len_x + door.x < 2 || -len_y + door.y < 2){
					continue;
				} 
				vector<point> path = compute_path(door, main_dir, dir_x, dir_y, len_x, len_y);
				point point_final = try_add_path(path, matrix_con, rooms, grid);
				if (point_final.x != -1) {
					vector<point>::iterator it;
					for (it = path.begin(); it != path.end(); it++) {
						point current_point = *it;
						if (current_point.x == point_final.x && current_point.y == point_final.y) {
							if ((grid -> at(point_final.x))[point_final.y] == 4) {
								continue;
							} else {
								(grid -> at(current_point.x))[current_point.y] = 5;
							}
						} else {
							(grid -> at(current_point.x))[current_point.y] = 5;
						}
					}
					return point_final;
				} else {
					continue;
				}
			}
		}
	}
	return point {-1, -1};
}

point make_room (point begin, vector<vector<bool>>* Good_for_room, vector<vector<int>>* grid) {
	for (int n_try = 0; n_try < 30; n_try++){
		point end = random_point(min((int)((Good_for_room -> at(0)).size()) - begin.x-2,8), min((int)(Good_for_room -> size()) - begin.y -2 ,8));
		end.x += 4 + begin.x;
		end.y += 4 + begin.y;
		if ((end.x >= Good_for_room -> size()) || (end.y >= (Good_for_room -> at(0)).size())){
			continue;
		}
		if (room_is_good(begin, end, Good_for_room, grid)) {
			return end;
		} else {
			continue;
		}
	}
	return point {-1,-1};
}

setup create_map(int stage) {
	int hauteur_grille = stage * 80;
	int longueur_grille = stage * 80;
	int n_rooms_min = stage;
	int n_rooms_max = n_rooms_min + random_int(stage) + 4;
	vector<vector<int>>	grid = make_matrix(hauteur_grille, longueur_grille);
	vector<vector<bool>> Matrix_connection = make_matrix_bool(n_rooms_max, n_rooms_max);
	vector<vector<bool>> Good_for_room = make_matrix_bool(hauteur_grille, longueur_grille);
	vector<vector<bool>> Matrix_revealed = make_matrix_bool(hauteur_grille, longueur_grille);
	vector<room*>  rooms;
	for( int i = 0; i < 2; i++) {
		for ( int j = 0; j < longueur_grille; j++){
			Good_for_room[i][j] = 1;
		}
	}
	for( int i = 0; i < 2; i++) {
		for ( int j = 0; j < longueur_grille; j++){
			Good_for_room[hauteur_grille - 1 -i][longueur_grille -1 - j] = 1;
		}
	}
	for( int j = 0; j < 2; j++) {
		for ( int i = 0; i < hauteur_grille ; i++){
			Good_for_room[hauteur_grille - 1 -i][longueur_grille -1 - j] = 1;
		}
	}
	for( int j = 0; j < 2; j++) {
		for ( int i = 0; i < hauteur_grille ; i++){
			Good_for_room[i][j] = 1;
		}
	}
	point begin = random_point(stage * 10, stage * 10);
	begin.x += stage * 40;
	begin.y += stage * 40;
	for (int i = 0; i < n_rooms_max; i++) {
		if (i != 0) {
			Matrix_connection[i][i-1] = 1;
			Matrix_connection[i-1][i] = 1;
		}
		point end = make_room(begin, &Good_for_room, &grid);
		if (end.x == -1){
			return setup {vector<vector<int>> {}, vector<vector<bool>> {}, rooms, false}; 
		}
		room new_room = room {begin, end, false};
		rooms.push_back(&new_room);
		bool make_path;
		if (i == n_rooms_max -1) {
			make_path = false;
		} else {
			make_path = true;
		}
		point test = add_to_good_for_room(&Good_for_room, &grid, new_room, &Matrix_connection, &rooms, make_path);
		if (make_path) {
			if (test.x == -1 && i < n_rooms_min) {
				return setup {vector<vector<int>> {}, vector<vector<bool>> {}, rooms, false}; 
			} else if (test.x == -1 && i < n_rooms_max) {
				return setup {grid, Matrix_revealed, rooms, true};
			} else {
				begin = test;
				begin.x -= 1;
				begin.y -= 1;
			}
		}
	}
	return setup {grid, Matrix_revealed, rooms, true};
}

setup setup_map(int stage) {
	setup _setup {vector<vector<int>> {}, vector<vector<bool>> {}, vector<room*> {}, false};
	while (not _setup.it_worked){
		_setup = create_map(stage);
	}
	vector<vector<int>> grid = _setup.map;
	vector<room*> rooms = _setup.rooms;
	print(rooms.size());
	int number_room_begin = random_int(rooms.size()) - 1;
	print("h1");
	room room_begin = *(rooms[number_room_begin]);
	print_P(room_begin.begin);
	print(number_room_begin);
	_setup.map[room_begin.begin.x + 1][room_begin.begin.y + 1] = 7;
	int number_room_end = random_int(rooms.size()) - 1;
	print("h2");
	while ((number_room_end - number_room_begin) == 0) {
		number_room_end = random_int(rooms.size()) - 1;
	}
	print("h3");
	print(number_room_end);
	room room_end = *(rooms[number_room_end]);
	print_P(room_end.begin);
	_setup.map[room_end.end.x - 1][room_end.end.y - 1] = 8;
	print("h4");
	_setup.map = extract(find_extract(&grid), &grid);
	print_M(&_setup.map);
	cout << "number of room : " << _setup.rooms.size() << endl; 
	return _setup;
}

