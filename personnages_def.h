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

class tresor : public Objet {
protected:
	int valeur;

	void interact(Rogue* perso);
};

class arme : public Objet {
protected:
	int attaque;

	void interact(Rogue* perso);
};

class armure : public Objet {
protected:
	int defense;
	int esquive;

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
	arme* _arme;
	armure* _armure;

	// Fonctions

	Rogue();
	~Rogue();
	
	void pickup(Objet* stuff);

};














