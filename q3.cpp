/*
Lista de Exercícios — Programação Paralela (OpenMP)
Prof. Rodrigo Gonçalves

Exercício 3 — Expressão Vetorial
Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
a) Faça a versão sequencial.
b) Paralelize com #pragma omp parallel for schedule(static).
c) Mostre o tempo total de execução em cada versão.
*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

// Define o tamanho dos vetores como constante
const int TAMANHO = 1000000;

int main() {
    /*
    FUNÇÃO: Compara desempenho entre versão sequencial e paralela de expressão vetorial
    PARÂMETROS: Nenhum
    RETORNO: 0 em caso de sucesso
    */
    
    // Cria vetores para armazenar os dados
    // vector<double> cria vetores dinâmicos de ponto flutuante de dupla precisão
    vector<double> x(TAMANHO), y(TAMANHO), z(TAMANHO);
    vector<double> a_seq(TAMANHO), a_par(TAMANHO);
    
    // Inicializa os vetores x, y e z com valores progressivos
    // Valores são calculados para simular dados reais
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;  // Progressão linear com passo 0.1
        y[i] = i * 0.2;  // Progressão linear com passo 0.2
        z[i] = i * 0.3;  // Progressão linear com passo 0.3
    }
    
    // Variáveis para medição de tempo
    double inicio, fim;
    
    // a) Versão sequencial
    // omp_get_wtime() retorna o tempo atual em segundos com alta precisão
    inicio = omp_get_wtime();
    for (int i = 0; i < TAMANHO; i++) {
        // Calcula a soma dos quadrados: x² + y² + z²
        a_seq[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    fim = omp_get_wtime();
    cout << "Tempo sequencial: " << fim - inicio << " segundos" << endl;
    
    // b) Versão paralela com schedule(static)
    // #pragma omp parallel for cria threads e distribui o loop
    // schedule(static) divide as iterações em blocos iguais para cada thread
    inicio = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; i++) {
        // Cada thread calcula um subconjunto das iterações
        a_par[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    fim = omp_get_wtime();
    cout << "Tempo paralelo (static): " << fim - inicio << " segundos" << endl;
    
    // Verifica se os resultados das duas versões são equivalentes
    // fabs() calcula o valor absoluto para comparação de ponto flutuante
    bool correto = true;
    for (int i = 0; i < TAMANHO; i++) {
        // Compara com tolerância de 1e-10 para lidar com erros de ponto flutuante
        if (fabs(a_seq[i] - a_par[i]) > 1e-10) {
            correto = false;
            break;
        }
    }
    cout << "Resultados corretos? " << (correto ? "Sim" : "Não") << endl;
    
    return 0;
}
