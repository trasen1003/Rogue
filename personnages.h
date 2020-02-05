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
Rogue::Rogue(vector<vector<int>>* _map, int* pos): vie(100), argent(0), capacite_sac(5), sac(vector<Objet*> {}),map(_map), attaque(1), defense(1), esquive(1) {
	position[0] = pos[0];
	position[1] = pos[1];
};

void Rogue::action(int key){

    int caseCible;
    //mvprintw(30, 30, "%c",(char) key);
    switch ((char)key)
{
    case 's':

        caseCible = (*map)[position[0]+1][position[1]];
	(*map)[position[0]][position[1]] = 0;

        switch(caseCible){
            case 1: //vide accessible
                position[0] += 1;
				break;
            case 4: //porte
                position[0] += 1;
				break;
	    case 5: //couloir
                position[0] += 1;
				break;
	    case 7: //escalier
				position[0] += 1;
				break;
	    case 10: //objet
                position[0] += 1;
				break;
            default:
                break;
        }
        break;
    
    case 'z':

        caseCible = (*map)[position[0]-1][position[1]];
	(*map)[position[0]][position[1]] = 0;

        switch(caseCible){
            case 1: //vide accessible
                position[0] -= 1;
				break;
            case 4: //porte
                position[0] -= 1;
				break;

			case 5: //couloir
                position[0] -= 1;
				break;
			
			case 7: //escalier
				position[0] -= 1;
				break;

			case 10: //objet
                position[0] -= 1;
				break;

            default:
                break;
        }
        break;
    case 'd':

        caseCible = (*map)[position[0]][position[1]+1];
	(*map)[position[0]][position[1]] = 0;

        switch(caseCible){
            case 1: //vide accessible
                position[1] += 1;
				break;
            case 4: //porte
                position[1] += 1;
				break;

			case 5: //couloir
                position[1] += 1;
				break;
			
			case 7: //escalier
				position[1] += 1;
				break;

			case 10: //objet
                position[1] += 1;
				break;

            default:
                break;
        }
        break;
    case 'q':

        caseCible = (*map)[position[0]][position[1]-1];
	(*map)[position[0]][position[1]] = 0;

        switch(caseCible){
            case 1: //vide accessible
                position[1] -= 1;
				break;
            case 4: //porte
                position[1] -= 1;
				break;

			case 5: //couloir
                position[1] -= 1;
				break;
			
			case 7: //escalier
				position[1] -= 1;
				break;

			case 10: //objet
                position[1] -= 1;
				break;

            default:
                break;
        }
        break;
/*		
    case 'a':
		if((*map)[position[0]][position[1]] == 6 && capacite_sac > sac.size()){
			int i = 0;
			while (coordObjects[i][0] != position[0] or coordObjects[i][1] != position[1]){i++;}
			sac.push_back(objects[i]);
			coordObjects.erase(coordObjects.begin() + i);
			objects.erase(objects.begin() + i);
			(*map)[position[0]][position[1]] = 0;
		}
		break;
*/    

    
    default:
        break;
    }
    (*map)[position[0]][position[1]] = 8;
}

void Rogue::pickup (Objet* stuff) {
	if (capacite_sac > sac.size()) {
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
