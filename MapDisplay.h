#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> display_grid (vector<vector<int>> IntMap){
    vector<char> vect(IntMap[0].size(), ' ');
    vector<vector<char>> StrMap(IntMap.size(), vect);

    for (int i = 0; i< (int)IntMap.size(); i++)
    {
        for (int j = 0; j< (int)IntMap[0].size(); j++){
            //cout << "i is : " << i << " and j is : " << j << endl;
            switch(IntMap[i][j])
            {
                case 0: // case vide non accessible
                    StrMap[i][j] = ' ';
                    break;
                case 1: // case vide accessible
                    StrMap[i][j] = '.';
                    break;
                case 2: // mur horizontal
                    StrMap[i][j] = '-';
                    break;
                case 3: // mur vertical
                    StrMap[i][j] = '|';
                    break;
                case 4: // porte
                    StrMap[i][j] = '+';
                    break;
                case 5: // couloir
                    StrMap[i][j] = '#';
                    break;
                case 6: // coin 
                    StrMap[i][j] = '/';
                    break;
                case 7: // passage au niveau suivant 
                    StrMap[i][j] = '=';
                    break;
                case 8: // personnage
                    StrMap[i][j] = '@';
                    break;
                case 9: //monstre
                    StrMap[i][j] = 'M';
                    break;
                case 10: //objet
                    StrMap[i][j] = '*';
                    break;
            }
        }
    }
    return StrMap;
}
