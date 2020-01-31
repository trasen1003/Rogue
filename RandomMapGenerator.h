#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "MapDisplay.h"
using namespace std;


vector<vector<int>> Generateur(int nombre_salles, int hauteur_grille, int longueur_grille)
{
    // initialisation :
    vector<int> vect(longueur_grille, 0);
    vector<vector<int>> etat(hauteur_grille, vect); // 0 : non occupe, 1: occupe

    vector<int> vect2(longueur_grille, -1);
    vector<vector<int>> IntMap(hauteur_grille, vect2);

    vector<int> portes;
    int posx;
    int posy;
    bool boolwhile = true;

    // PREMIERE SALLE : personnage present

            while (boolwhile)
            {
                srand(time(NULL));
                // position du coin haut gauche
                int x = 1 + rand()%(longueur_grille -1);
                int y = 1 + rand()%(hauteur_grille - 1); 

                // taille 
                int a = rand()%(longueur_grille/2) + 5; // on evite les salles de taille nulle
                int b = rand()%(hauteur_grille/2) + 5;

                if ((x+a-1< longueur_grille - 1 ) && (y + b - 1 < hauteur_grille- 1))
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

                        // mise des deux portes

                        for (int u =0; u<2; u++)
                        {
                            int l = rand()%4;
                            switch(l)
                            {
                                case 0 : // porte vers le haut 
                                    posx = x + 1 + rand()%(a-2);
                                    posy = y;
                                    IntMap[posx][y] = 3;
                                    break;

                                case 1: //porte vers le bas 
                                    posx = x + 1 + rand()%(a-2);
                                    posy = y+b-1;
                                    IntMap[posx][y+b-1] = 3;
                                    break;

                                case 2: // porte vers la gauche 
                                    posy = y + 1 + rand()%(b-2);
                                    posx = x;
                                    IntMap[x][posy] = 3;
                                    break;

                                case 3: // porte vers la droite
                                    posy = y + 1 + rand()%(b -2); 
                                    posx = x+a-1;
                                    IntMap[x+a-1][posy] = 3;
                                    break;
                            }
                            portes.push_back(posx);
                            portes.push_back(posy);
                        }
                    //mise du personnage 
                    IntMap[x + 1 + rand()%(a-1)][y + 1 + rand()%(b-1)] = 6;
                    boolwhile = false;
                }

                
            }

    // FIN PREMIERE SALLE 

    // AUTRES SALLES : 

    for (int i = 0; i< nombre_salles - 2; ++i)
    {
        boolwhile = true;
            while (boolwhile)
            {
                srand(time(NULL));
                // position du coin haut gauche
                int x = 1 + rand()%(longueur_grille -1);
                int y = 1 + rand()%(hauteur_grille - 1); 

                // taille 
                int a = rand()%(longueur_grille/2) + 5; // on evite les salles de taille nulle
                int b = rand()%(hauteur_grille/2) + 5;

                if ((x+a-1< longueur_grille - 1 ) && (y + b - 1 < hauteur_grille- 1))
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

                        // mise des deux portes

                        for (int u =0; u<2; u++)
                        {
                            int l = rand()%4;
                            switch(l)
                            {
                                case 0 : // porte vers le haut 
                                    posx = x + 1 + rand()%(a-2);
                                    posy = y;
                                    IntMap[posx][y] = 3;
                                    break;

                                case 1: //porte vers le bas 
                                    posx = x + 1 + rand()%(a-2);
                                    posy = y+b-1;
                                    IntMap[posx][y+b-1] = 3;
                                    break;

                                case 2: // porte vers la gauche 
                                    posy = y + 1 + rand()%(b-2);
                                    posx = x;
                                    IntMap[x][posy] = 3;
                                    break;

                                case 3: // porte vers la droite
                                    posy = y + 1 + rand()%(b -2); 
                                    posx = x+a-1;
                                    IntMap[x+a-1][posy] = 3;
                                    break;
                            }
                            portes.push_back(posx);
                            portes.push_back(posy);
                        }
                    boolwhile = false;
                    }

                }
            }
    }

    // DERNIERE SALLE : Monstre + escalier
    
    boolwhile = true;
            while (boolwhile)
            {
                srand(time(NULL));
                // position du coin haut gauche
                int x = 1 + rand()%(longueur_grille -1);
                int y = 1 + rand()%(hauteur_grille - 1); 

                // taille 
                int a = rand()%(longueur_grille/2) + 5; // on evite les salles de taille nulle
                int b = rand()%(hauteur_grille/2) + 5;

                if ((x+a-1< longueur_grille - 1 ) && (y + b - 1 < hauteur_grille- 1))
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

                        // mise des deux portes

                        for (int u =0; u<2; u++)
                        {
                            int l = rand()%4;
                            switch(l)
                            {
                                case 0 : // porte vers le haut 
                                    posx = x + 1 + rand()%(a-2);
                                    posy = y;
                                    IntMap[posx][y] = 3;
                                    break;

                                case 1: //porte vers le bas 
                                    posx = x + 1 + rand()%(a-2);
                                    posy = y+b-1;
                                    IntMap[posx][y+b-1] = 3;
                                    break;

                                case 2: // porte vers la gauche 
                                    posy = y + 1 + rand()%(b-2);
                                    posx = x;
                                    IntMap[x][posy] = 3;
                                    break;

                                case 3: // porte vers la droite
                                    posy = y + 1 + rand()%(b -2); 
                                    posx = x+a-1;
                                    IntMap[x+a-1][posy] = 3;
                                    break;
                            }
                            portes.push_back(posx);
                            portes.push_back(posy);
                        }

                        //monstre

                        IntMap[x + 1 + rand()%(a-1)][y + 1 + rand()%(b-1)] = 7;

                        //escalier

                        IntMap[x + 1 + rand()%(a-1)][y + 1 + rand()%(b-1)] = 5;
                    
                    boolwhile = false;
                    }

                }
            }
return IntMap;
}

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