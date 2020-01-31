#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<string>> display_grid (vector<vector<int>> IntMap)
{
    vector<string> vect(IntMap.size(), " ");
    vector<vector<string>> StrMap(IntMap[0].size(), vect);

    for (int i = 0; i< IntMap.size(); i++)
    {
        for (int j = 0; j<IntMap[0].size(); j++){

            switch(IntMap[i][j])
            {
                case -1: // case vide non accessible
                    StrMap[i][j] = " ";
                    break;
                case 0: // case vide accessible
                    StrMap[i][j] = ".";
                    break;
                case 1: // mur horizontal
                    StrMap[i][j] = "-";
                    break;
                case 2: // mur vertical
                    StrMap[i][j] = "|";
                    break;
                case 3: // porte
                    StrMap[i][j] = "+";
                    break;
                case 4: // couloir
                    StrMap[i][j] = "#";
                    break;
                case 5: //passage niveau suivant 
                    StrMap[i][j] = "=";
                    break;
                case 6: // personnage 
                    StrMap[i][j] = "@";
                    break;
                case 7: // monstre
                    StrMap[i][j] = "M";
                    break;
                case 8: //objet
                    StrMap[i][j] = "*";
                    break;
            }
        }
    }
    return StrMap;
}
