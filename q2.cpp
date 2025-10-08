#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    const int TAMANHO = 100;
    vector<int> v(TAMANHO, 1); // Inicializa com 1s
    int soma_seq = 0, soma_par = 0;
    
    // b) Soma sequencial
    for (int i = 0; i < TAMANHO; i++) {
        soma_seq += v[i];
    }
    
    // c) Soma paralela com reduction
    #pragma omp parallel for reduction(+:soma_par)
    for (int i = 0; i < TAMANHO; i++) {
        soma_par += v[i];
    }
    
    // d) Comparação
    cout << "Soma sequencial: " << soma_seq << endl;
    cout << "Soma paralela: " << soma_par << endl;
    cout << "Resultados iguais? " << (soma_seq == soma_par ? "Sim" : "Não") << endl;
    
    // Explicação sobre reduction
    cout << "\nA diretiva reduction é necessária para evitar condições de corrida." << endl;
    cout << "Sem reduction, múltiplas threads tentariam atualizar a mesma variável" << endl;
    cout << "soma_par simultaneamente, resultando em valores inconsistentes." << endl;
    cout << "A reduction cria uma cópia privada da variável para cada thread e" << endl;
    cout << "combina os resultados no final usando a operação especificada (+)." << endl;
    
    return 0;
}
