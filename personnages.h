#include "personnages_def.h"

using namespace std;

void potion::interact(Rogue* perso) {
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

Monstre::Monstre(): attaque(2), defense(2), esquive(1), vitesse(1) {};

Monstre::Monstre(int att, int def, int esq, int vit): attaque(att), defense(def), esquive(esq), vitesse(vit) {};	

Rogue::Rogue(): vie(100), argent(0), capacite_sac(5), sac(vector<Objet*> {}), attaque(1), defense(1), esquive(1) {};

void Rogue::pickup (Objet* stuff) {
	if (capacite_sac < sac.size()) {
		sac.push_back(stuff);
	} else {
		cout << "Le sac est plein !" << endl;
	}
}

