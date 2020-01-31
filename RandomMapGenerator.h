#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

vector<vector<int>> Generateur(int nombre_salles = 4, int hauteur_grille = 50, int longueur_grille = 50)
{
    // initialisation :
    vector<int> vect(longueur_grille, 0);
    vector<vector<int>> etat(hauteur_grille, vect);

    vector<int> vect2(longueur_grille, -1);
    vector<vector<int>> IntMap(hauteur_grille, vect2);

    for (int i = 0; i< nombre_salles; ++i)
    {
        bool boolwhile = true;
        while (boolwhile)
        {
            srand(time(NULL));
            // position du coin haut gauche
            int x = rand()%longueur_grille;
            int y = rand()%hauteur_grille; 

            // taille 
            int a = rand()%(longueur_grille/2) + 3; // on évite les salles de taille nulle
            int b = rand()%(hauteur_grille/2) + 3;

            if ((x+a-1< longueur_grille) && (y + b - 1 < hauteur_grille))
            {
                // test pour voir s'il n'y a pas de salle à cet endroit
                bool test = true;
                for (int k = x; k < x+a; k++)
                {
                    for (int l = y; l< y +b; l++)
                    {
                        if (etat[k][l] == 1)
                            test = false;
                    }
                }
                // si pas de salle, on y met la salle.
                if (test)
                {
                    for (int k = x; k < x+a; k++)
                    {
                        for (int l = y; l< y +b; l++)
                        {
                            if ((k==x) || (k == x+a-1))
                                IntMap[k][l] = 1;
                            else if ((l == y) || (l == y + b -1))
                                IntMap[k][l] = 2;
                            else
                                IntMap[k][l] = 0;
                            etat[k][l] = 1;

                        }
                    }
                    boolwhile = false;
                }

            }
        }
    }

return IntMap;
}

/*
int main(){
    vector<vector<int>> IntMap =  Generateur(4, 50, 50);
    vector<vector<string>> StrMap = display_grid(IntMap);
    for (int i = 0; i< StrMap.size(); i++)
    {
        for (int j=0; j <StrMap[0].size(); j++)
        {
            cout << StrMap[i][j];
        }
        cout << endl;
    }
    return 0;
}
*/
