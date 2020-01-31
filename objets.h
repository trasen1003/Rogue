
using namespace std;


class Objet {

public:



	Objet();
	~Objet();
	
	virtual void interact(Rogue perso);


};

class potion : public Objet {
protected:
	int regeneration;

	void interact(Rogue perso) {
		if (regeneration >= (100 - perso.vie)) {
			perso.vie = 100;
		} else {
			perso.vie += regeneration;
		}
	}
};