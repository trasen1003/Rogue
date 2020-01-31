# include<iostream>
# include <vector>
# include<string> 


using namespace std;	

class Rogue;

vector<int[2]> coordObjects;

class Objet {

public:

	virtual void interact(Rogue* perso);


};

vector<Objet*> objects;
/*
class potion : public Objet {
public:
	int regeneration;

	void interact(Rogue* perso);
};

class tresor : public Objet {
public:
	int valeur;

	void interact(Rogue* perso);
};

class arme : public Objet {
public:
	int attaque;

	void interact(Rogue* perso);
};

class armure : public Objet {
public:
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

	Monstre(vector<vector<int>>* _map);
	Monstre(int att, int def, int esq, int vit);

	~Monstre();
	
};
*/
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
	//arme* _arme;
	//armure* _armure;
	vector<vector<int>>* map;

	// Fonctions

	Rogue(vector<vector<int>>* _map,int** pos);
	
	void pickup(Objet* stuff);
	//void fight(Monstre* opponent);
	void drop();
	void action(int key);
};














