#include "personnages_def.h"
#include <iterator>
//#include <ncurse.h>

using namespace std;

/*void potion::interact(Rogue* perso) {
		if (regeneration >= (100 - perso->vie)) {
			perso->vie = 100;
		} else {
			perso->vie += regeneration;
		}
}

void tresor::interact(Rogue* perso) {
	perso -> argent += valeur;
}

void arme::interact(Rogue* perso) {
	perso -> _arme = this;
	perso -> attaque = this -> attaque;
}

void armure::interact(Rogue* perso){
	perso -> _armure = this;
	perso -> defense = this -> defense;
	perso -> esquive = this -> esquive;
}


Monstre::Monstre(vector<vector<int>>* _map): map(_map), attaque(2), defense(2), esquive(1), vitesse(1) {};

Monstre::Monstre(int att, int def, int esq, int vit): attaque(att), defense(def), esquive(esq), vitesse(vit) {};	
*/
Rogue::Rogue(vector<vector<int>>* _map, point pos): vie(100), argent(0), capacite_sac(5), sac(vector<Objet*> {}),map(_map), attaque(1), defense(1), esquive(1) {
	position.x = pos.x;
	position.y = pos.y;
};

void Rogue::action(int key, int* temp, vector<room>* rooms, vector<vector<bool>>* Matrix_revealed){

    int caseCible;
    //mvprintw(30, 30, "%c",(char) key);
    switch ((char)key)
{
   	int number;
    case 's':
        caseCible = (*map)[position.x+1][position.y];
        if (caseCible != 1 && caseCible != 4 && caseCible != 5 && caseCible != 7 && caseCible != 10){
        	break;
        }
		(*map)[position.x][position.y] = *temp;
        *temp = caseCible;
        switch(caseCible){
            case 1: //vide accessible
                position.x += 1;
				break;
            case 4: //porte
                position.x += 1;
                number = find_room(position, rooms);
                if (number != -1){
            		update_revealed_room(Matrix_revealed, rooms, number);
                }
                for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;
		    case 5: //couloir
                position.x += 1;
               	for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;
		    case 7: //escalier
				position.x += 1;
				break;
		    case 10: //objet
                position.x += 1;
				break;
            default:
                break;
        }
        break;
    
    case 'z':
        caseCible = (*map)[position.x-1][position.y];
        if (caseCible != 1 && caseCible != 4 && caseCible != 5 && caseCible != 7 && caseCible != 10){
        	break;
        }
		(*map)[position.x][position.y] = *temp;
        *temp = caseCible;

        switch(caseCible){
            case 1: //vide accessible
                position.x -= 1;
				break;
            case 4: //porte
                position.x -= 1;
            	number = find_room(position, rooms);
            	if (number != -1){
            		update_revealed_room(Matrix_revealed, rooms, number);
                }
                for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;

			case 5: //couloir
                position.x -= 1;
				for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;
			
			case 7: //escalier
				position.x -= 1;
				break;

			case 10: //objet
                position.x -= 1;
				break;

            default:
                break;
        }
        break;

    case 'd':
        caseCible = (*map)[position.x][position.y+1];
        if (caseCible != 1 && caseCible != 4 && caseCible != 5 && caseCible != 7 && caseCible != 10){
        	break;
        }
		(*map)[position.x][position.y] = *temp;
        *temp = caseCible;

        switch(caseCible){
            case 1: //vide accessible
                position.y += 1;
				break;
            case 4: //porte
                position.y += 1;
           		number = find_room(position, rooms);
            	if (number != -1) {
            		update_revealed_room(Matrix_revealed, rooms, number);
                } 
                for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;

			case 5: //couloir
                position.y += 1;
				for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;
			
			case 7: //escalier
				position.y += 1;
				break;

			case 10: //objet
                position.y += 1;
				break;

            default:
                break;
        }
        break;
    case 'q':
        caseCible = (*map)[position.x][position.y-1];
        if (caseCible != 1 && caseCible != 4 && caseCible != 5 && caseCible != 7 && caseCible != 10){
        	break;
        }
		(*map)[position.x][position.y] = *temp;
        *temp = caseCible;

        switch(caseCible){
            case 1: //vide accessible
                position.y -= 1;
				break;
            case 4: //porte
                position.y -= 1;
                //print_P(position);
                number = find_room(position, rooms);
            	if (number != -1){
            		update_revealed_room(Matrix_revealed, rooms, number);
                } 
                for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;

			case 5: //couloir
                position.y -= 1;
				for (int i = -1; i < 2; i++) {
			    	for (int j = -1; j < 2; j++){
			    		(*Matrix_revealed)[position.x + i][position.y + j] = true;
			    	}
			    }
				break;
			
			case 7: //escalier
				position.y -= 1;
				break;

			case 10: //objet
                position.y -= 1;
				break;

            default:
                break;
        }
        break;
/*		
    case 'a':
		if((*map)[position.x][position.y] == 6 && capacite_sac > sac.size()){
			int i = 0;
			while (coordObjects[i].x != position.x or coordObjects[i].y != position.y){i++;}
			sac.push_back(objects[i]);
			coordObjects.erase(coordObjects.begin() + i);
			objects.erase(objects.begin() + i);
			(*map)[position.x][position.y] = 0;
		}
		break;
*/    

    
    default:
        break;
    }
    (*map)[position.x][position.y] = 8;
}

void Rogue::pickup (Objet* stuff) {
	if ((int)capacite_sac > (int)sac.size()) {
		sac.push_back(stuff);
	} else {
		cout << "Le sac est plein !" << endl;
	}
}

void Rogue::drop() {
	// Afficher les objets du sac
	int selected = 0;
	int number_objects = sac.size();
	while (true) {
		vector<Objet*>::iterator it;
		for (it = sac.begin(); it != sac.end(); it++) {
			
		}
		int ch = getch();
		switch(ch){
			case KEY_DOWN:
				selected += 1;
				if (selected == number_objects) {
					selected = 0;
				} 
			case KEY_UP:
				selected -= 1;
				if (selected == -1) {
					selected = number_objects -1;
				}
		}
	}

}
