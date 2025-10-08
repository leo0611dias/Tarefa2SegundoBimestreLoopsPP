/*
Lista de Exercícios — Programação Paralela (OpenMP)
Prof. Rodrigo Gonçalves

Exercício 2 — Paralelizando um for simples
a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
b) Escreva um loop sequencial que soma todos os elementos.
c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
d) Compare os resultados e explique por que a diretiva reduction é necessária.
*/

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    /*
    FUNÇÃO: Demonstra paralelização de loop com reduction para evitar race conditions
    PARÂMETROS: Nenhum
    RETORNO: 0 em caso de sucesso
    */
    
    const int TAMANHO = 100;
    
    // a) Cria e inicializa vetor com 100 elementos de valor 1
    // vector<int> v(TAMANHO, 1) cria um vetor de tamanho TAMANHO inicializado com 1
    vector<int> v(TAMANHO, 1);
    int soma_seq = 0, soma_par = 0;
    
    // b) Loop sequencial para somar todos os elementos
    // Percorre cada elemento do vetor e acumula na variável soma_seq
    for (int i = 0; i < TAMANHO; i++) {
        soma_seq += v[i];
    }
    
    // c) Loop paralelo com reduction
    // #pragma omp parallel for cria threads e distribui as iterações do loop
    // reduction(+:soma_par) cria uma cópia privada de soma_par para cada thread
    // No final, combina todas as cópias privadas usando a operação +
    #pragma omp parallel for reduction(+:soma_par)
    for (int i = 0; i < TAMANHO; i++) {
        soma_par += v[i];
    }
    
    // d) Comparação dos resultados
    cout << "Soma sequencial: " << soma_seq << endl;
    cout << "Soma paralela: " << soma_par << endl;
    cout << "Resultados iguais? " << (soma_seq == soma_par ? "Sim" : "Não") << endl;
    
    // Explicação detalhada sobre a necessidade da reduction
    cout << "\n=== EXPLICAÇÃO SOBRE REDUCTION ===" << endl;
    cout << "A diretiva reduction é necessária para evitar condições de corrida (race conditions)." << endl;
    cout << "Sem reduction, múltiplas threads tentariam atualizar a mesma variável 'soma_par'" << endl;
    cout << "simultaneamente, resultando em valores inconsistentes e imprevisíveis." << endl;
    cout << "\nComo funciona reduction(+:var):" << endl;
    cout << "1. Cada thread cria uma cópia privada da variável inicializada com o valor neutro (0 para +)" << endl;
    cout << "2. Cada thread acumula na sua cópia privada durante as iterações" << endl;
    cout << "3. No final, todas as cópias privadas são combinadas usando a operação especificada (+)" << endl;
    cout << "4. O resultado final é armazenado na variável original compartilhada" << endl;
    
    return 0;
}
