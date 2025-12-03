#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Classe que representa uma cartela 5x5
class Cartela5x5 {
private:
    int numeros[5][5]; // Cartela 5x5
public:
    Cartela5x5() {
        srand(time(NULL));
        // Intervalos para cada coluna
        int minCol[5] = {1, 21, 41, 61, 81};
        int maxCol[5] = {20, 40, 60, 80, 100};

        for (int c = 0; c < 5; c++) {
            vector<int> pool;
            for (int n = minCol[c]; n <= maxCol[c]; n++) pool.push_back(n);
            random_shuffle(pool.begin(), pool.end());
            for (int l = 0; l < 5; l++) numeros[l][c] = pool[l];
        }
        // Casa do meio da coluna N vazia
        numeros[2][2] = 0;
    }

    void exibir(int id) {
        cout << "\nCarta " << id << ":\n\n";
        cout << " B   I   N   G   O\n";
        cout << "---------------------\n";
        for (int l = 0; l < 5; l++) {
            for (int c = 0; c < 5; c++) {
                if (numeros[l][c] == 0) cout << " * ";
                else cout << setw(2) << numeros[l][c] << " ";
            }
            cout << "\n";
        }
        cout << "---------------------\n";
    }
};

// Função para gerar N cartelas
void gerarCartoes() {
    int n;
    cout << "Quantos cartoes deseja gerar (1 a 500)? ";
    cin >> n;
    if (n < 1) n = 1;
    if (n > 500) n = 500;

    vector<Cartela5x5> cartoes(n);
    for (int i = 0; i < n; i++) {
        cartoes[i].exibir(i + 1);
    }
    cout << "\nTodos os cartoes foram gerados!\n";
}

int main() {
    gerarCartoes();
    return 0;
}
