// I/O no terminal (cout, cin, cerr)
#include <iostream>
// Escrever em ficheiros (ofstream)
#include <fstream>
// Lista dinâmica (vector)
#include <vector>
// Fila dupla (não usada)
#include <deque>
// Embaralhar (random_shuffle)
#include <algorithm>
// Converter string→int (atoi), random (srand, rand)
#include <cstdlib>
// Hora atual para seed (time)
#include <ctime>
// Formatar largura (setw)
#include <iomanip>
// Construir strings (stringstream)
#include <sstream>
// Criar pastas (mkdir)
#include <sys/stat.h>

using namespace std;

// Cria pasta no sistema
void criarPasta(const string& nomePasta) {
    #ifdef _WIN32
        mkdir(nomePasta.c_str());  // Windows: 1 arg
    #else
        mkdir(nomePasta.c_str(), 0777);  // Linux/Mac: 2 args + permissões
    #endif
}

// Cartão 5x5 de Bingo
class Cartela5x5 {
private:
    int numeros[5][5];  // Matriz para os números

public:
    // Construtor: gera cartão aleatório
    Cartela5x5() {
        // Limites de cada coluna: B(1-20), I(21-40), N(41-60), G(61-80), O(81-100)
        int minCol[5] = {1, 21, 41, 61, 81};
        int maxCol[5] = {20, 40, 60, 80, 100};

        // Para cada coluna
        for (int c = 0; c < 5; c++) {
            vector<int> pool;  // Pool de números possíveis
            
            // Encher pool com todos os números da coluna
            for (int n = minCol[c]; n <= maxCol[c]; n++) 
                pool.push_back(n);
            
            random_shuffle(pool.begin(), pool.end());  // Embaralhar
            
            // Pegar primeiros 5 números para a coluna
            for (int l = 0; l < 5; l++) 
                numeros[l][c] = pool[l];
        }
        
        numeros[2][2] = 0;  // Centro: espaço FREE
    }

    // Escreve cartão no ficheiro
    void escreverNoFicheiro(ofstream& ficheiro, int id) {
        ficheiro << "Carta " << id << ":\n\n";
        ficheiro << " B   I   N   G   O\n";  // Cabeçalho
        ficheiro << "---------------------\n";
        
        // Linhas do cartão
        for (int l = 0; l < 5; l++) {
            for (int c = 0; c < 5; c++) {
                if (numeros[l][c] == 0) 
                    ficheiro << " * ";  // Centro livre
                else 
                    ficheiro << setw(2) << numeros[l][c] << " ";  // Número alinhado
            }
            ficheiro << "\n";
        }
        ficheiro << "---------------------\n";
    }
};

// Gera n cartões na pasta "cartoes/"
void gerarCartoes(int n) {
    if (n < 1) n = 1;      // Min: 1
    if (n > 500) n = 500;  // Max: 500

    criarPasta("cartoes");  // Criar pasta se não existe
    cout << "A gerar " << n << " cartoes na pasta 'cartoes/'...\n\n";

    // Loop: gerar cada cartão
    for (int i = 1; i <= n; i++) {
        stringstream ss;
        ss << "cartoes/carta" << i << ".txt";  // Nome: carta1.txt, carta2.txt...
        string nomeFicheiro = ss.str();

        ofstream ficheiro(nomeFicheiro.c_str());  // Abrir ficheiro
        
        if (!ficheiro.is_open()) {  // Erro ao abrir?
            cerr << "Erro ao criar: " << nomeFicheiro << endl;
            continue;  // Pular para próximo
        }

        Cartela5x5 cartao;  // Criar cartão
        cartao.escreverNoFicheiro(ficheiro, i);  // Escrever
        ficheiro.close();  // Fechar (importante!)

        cout << " Gerado: " << nomeFicheiro << "\n";
    }

    cout << "\nTodos os " << n << " cartoes foram gerados!\n";
}

// Programa principal
// argc = nº de argumentos | argv = array de argumentos
int main(int argc, char* argv[]) {
    srand(time(NULL));  // Seed aleatória (hora atual)

    if (argc < 2) {  // Sem argumentos?
        cout << "Uso: " << argv[0] << " <numero_cartoes>\n";
        cout << "Exemplo: " << argv[0] << " 50\n";
        cout << "\nOs cartoes serao guardados em: cartoes/carta1.txt, cartoes/carta2.txt, ...\n";
        return 1;  // Erro
    }

    int numCartoes = atoi(argv[1]);  // Converter string → int
    gerarCartoes(numCartoes);  // Gerar!

    return 0;  // Sucesso
}

