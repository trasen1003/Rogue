#include "personnages_def.h"

using namespace std;

void potion::interact(Rogue* perso) {
		if (regeneration >= (100 - perso->vie)) {
			perso->vie = 100;
		} else {
			perso->vie += regeneration;
		}
}


Rogue::Rogue(): vie(100), argent(0), capacite_sac(5), sac(vector<Objet*> {}), attaque(1), defense(1), esquive(1) {};

void Rogue::pickup (Objet* stuff) {
	if (capacite_sac < sac.size()) {
		sac.push_back(stuff);
	} else {
		cout << "Le sac est plein !" << endl;
	}
}


