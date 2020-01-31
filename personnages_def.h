# include<iostream>
# include <vector>
# include<string> 
//# include "objets.h"


using namespace std;	

class Rogue;

class Objet {

public:

	Objet();
	~Objet();
	
	virtual void interact(Rogue* perso);


};

class potion : public Objet {
protected:
	int regeneration;

	void interact(Rogue* perso);
};



class Rogue {
public:

	// Attributs

	int vie;
	int argent;
	int capacite_sac;
	vector<Objet*> sac;
	int attaque;
	int defense;
	int esquive;

	// Fonctions

	Rogue();
	~Rogue();
	
	void pickup(Objet* stuff);

};














