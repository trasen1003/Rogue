# include<iostream>
# include <vector>
# include<string>
#include <cmath>
using namespace std;

vector<vector<int>> find(int porteUn[2], int porteDeux[2], vector<vector<int>> map){

    vector<vector<int>> openList;
    int last[map.size()][map[0].size()][2];
    int gscore[map.size()][map[0].size()];
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++){
            gscore[i][j] = 100;
        }
    }
    int fscore[map.size()][map[0].size()];
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++){
            fscore[i][j] = 100;
        }
    }
    gscore[porteUn[0]][porteUn[1]] = 0;
    fscore[porteUn[0]][porteUn[1]] = sqrt(pow(porteUn[0] - porteDeux[0],2) + pow(porteUn[1] - porteDeux[1],2));

    openList.push_back(vector<int> {porteUn[0],porteUn[1]});
    while(openList.size() != 0){
        cout << "size is " << openList.size() << endl;
        vector<int> noeud = openList[0];
        cout << "noeud : " << noeud[0] << " " << noeud[1] << endl;
        int i = 1;
        int l;
        while(i < openList.size()){
            if(fscore[noeud[0]][noeud[1]] < fscore[openList[i][0]][openList[i][1]]){
                noeud = openList[i];
                l = i;
            }
            i++;
        }
        i = l;
        if(noeud[0] == porteDeux[0] && noeud[1] == porteDeux[1]){
            vector<vector<int>> res;
            while(noeud[0] != porteUn[0] || noeud[1] != porteUn[1]){
                noeud = vector<int> {last[noeud[0]][noeud[1]][0],last[noeud[0]][noeud[1]][1]};
                res.push_back(noeud);
            }
            res.erase(res.end());
            return res;
        } else {
            bool doNothing = false;
            openList.erase(openList.begin() + i);
            vector<vector<int>> voisins;
            cout << "noeud : " << noeud[0] << " " << noeud[1] << endl;
            if(noeud[0] > 0 && map[noeud[0] - 1][noeud[1]] == 0){
                voisins.push_back(vector<int> {noeud[0] - 1, noeud[1]});
            }
            if(noeud[1] > 0 && map[noeud[0]][noeud[1] - 1] == 0){
                voisins.push_back(vector<int> {noeud[0], noeud[1] - 1});
            }
            if(noeud[0] < map.size() - 1 && map[noeud[0] + 1][noeud[1]] == 0){
                voisins.push_back(vector<int> {noeud[0] + 1, noeud[1]});
            }
            if(noeud[1] < map[0].size() - 1 && map[noeud[0]][noeud[1] + 1] == 0){
                voisins.push_back(vector<int> {noeud[0], noeud[1] + 1});
            }

            cout << "il y a " << voisins.size() << " voisins" << endl;
            for(int j = 0; j < voisins.size(); j++){
                int tempGScore = gscore[noeud[0]][noeud[1]] + 1;
                if(tempGScore < gscore[voisins[j][0]][voisins[j][1]]){
                    last[voisins[j][0]][voisins[j][1]][0] = noeud[0];
                    last[voisins[j][0]][voisins[j][1]][1] = noeud[1];
                    gscore[voisins[j][0]][voisins[j][1]] = tempGScore;
                    fscore[voisins[j][0]][voisins[j][1]] = tempGScore + sqrt(pow(porteDeux[0] - voisins[j][0],2) + pow(porteDeux[1] - voisins[j][1],2));
                    bool pasdedans = true;
                    for(int k = 0; k < openList.size(); k++){
                        if(openList[k][0] == voisins[j][0] && openList[k][1] == voisins[j][1]){
                            pasdedans = false;
                        }
                    }

                    if(pasdedans){
                        openList.push_back(voisins[j]);
                        cout << "new node" << endl;
                    }
                }
            }
        }
    }
    cout << "aled" << endl;
}

vector<vector<int>> map {{0,0,0,0,0,0},{0,1,1,1,0,0},{0,0,0,1,0,0},{0,0,0,0,0,0}};
int porteUn[2] {2,1};
int porteDeux[2] {0,5};

int main(){
    vector<vector<int>> res = find(porteUn,porteDeux,map);
    cout << res[0][0] << endl;
    for(int i = 0; i < res.size(); i++){
        cout << res[i][0] << " " << res[i][1] << endl;
    }
}