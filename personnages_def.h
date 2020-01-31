# include<iostream>
# include <vector>
# include<string> 


using namespace std;	

class Rogue;

vector<int[2]> coordObjects;

class Objet {

public:

	Objet();
	~Objet();
	
	virtual void interact(Rogue* perso);


};

vector<Objet*> objects;

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

class Monstre
{
public:

	// Attribut

	int attaque;
	int defense;
	int esquive;
	int vitesse;
	vector<vector<int>>* map;

	// 

	Monstre();
	Monstre(int att, int def, int esq, int vit);

	~Monstre();
	
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
	int position[2];
	arme* _arme;
	armure* _armure;
	vector<vector<int>>* map;

	// Fonctions

	Rogue();
	~Rogue();
	
	void pickup(Objet* stuff);
	void fight(Monstre* opponent);
	void drop();
	void action(int key);
};














