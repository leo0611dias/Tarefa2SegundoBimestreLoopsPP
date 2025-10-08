/*
Lista de Exercícios — Programação Paralela (OpenMP)
Prof. Rodrigo Gonçalves

Exercício 4 — Medindo tempo por Thread
Adapte o código do exercício anterior para:
a) Medir e exibir o tempo total de execução.
b) Medir e exibir o tempo gasto por cada thread.
c) Mostrar quantas threads foram utilizadas no cálculo.
*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

const int TAMANHO = 1000000;

int main() {
    /*
    FUNÇÃO: Mede tempo de execução individual por thread e analisa balanceamento de carga
    PARÂMETROS: Nenhum
    RETORNO: 0 em caso de sucesso
    */
    
    // Cria e inicializa vetores
    vector<double> x(TAMANHO), y(TAMANHO), z(TAMANHO);
    vector<double> a(TAMANHO);
    
    // Inicialização dos vetores de entrada
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }
    
    // Variáveis para medição de tempo
    double tempo_total_inicio, tempo_total_fim;
    vector<double> tempos_thread;  // Armazena tempo individual de cada thread
    int num_threads = 0;           // Armazena número total de threads
    
    // Inicia medição do tempo total
    tempo_total_inicio = omp_get_wtime();
    
    // Região paralela que engloba todo o processamento
    #pragma omp parallel
    {
        // Bloco single: executa apenas uma vez por uma thread qualquer
        // Usado para inicializar variáveis compartilhadas
        #pragma omp single
        {
            // omp_get_num_threads() retorna o número de threads na região paralela atual
            num_threads = omp_get_num_threads();
            // Redimensiona o vetor para armazenar tempos de todas as threads
            tempos_thread.resize(num_threads);
            cout << "Número de threads utilizadas: " << num_threads << endl;
        }
        
        // Obtém ID da thread atual (0 a num_threads-1)
        int thread_id = omp_get_thread_num();
        
        // Mede tempo inicial específico desta thread
        double thread_inicio = omp_get_wtime();
        
        // Loop paralelizado com schedule static
        // As iterações são distribuídas igualmente entre as threads
        #pragma omp for schedule(static)
        for (int i = 0; i < TAMANHO; i++) {
            // Cada thread processa seu bloco de iterações
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
        
        // Mede tempo final desta thread e calcula duração
        double thread_fim = omp_get_wtime();
        tempos_thread[thread_id] = thread_fim - thread_inicio;
    }
    
    // Finaliza medição do tempo total
    tempo_total_fim = omp_get_wtime();
    
    // a) Exibe tempo total de execução
    cout << "\nTempo total de execução: " << tempo_total_fim - tempo_total_inicio << " segundos" << endl;
    
    // b) Exibe tempo individual de cada thread
    cout << "\nTempo por thread:" << endl;
    for (int i = 0; i < num_threads; i++) {
        cout << "Thread " << i << ": " << tempos_thread[i] << " segundos" << endl;
    }
    
    // Análise de balanceamento
    cout << "\n=== ANÁLISE DE BALANCEAMENTO ===" << endl;
    double tempo_max = tempos_thread[0];
    double tempo_min = tempos_thread[0];
    
    for (int i = 1; i < num_threads; i++) {
        if (tempos_thread[i] > tempo_max) tempo_max = tempos_thread[i];
        if (tempos_thread[i] < tempo_min) tempo_min = tempos_thread[i];
    }
    
    cout << "Maior tempo: " << tempo_max << " segundos" << endl;
    cout << "Menor tempo: " << tempo_min << " segundos" << endl;
    cout << "Diferença: " << tempo_max - tempo_min << " segundos" << endl;
    cout << "Balanceamento: " << (tempo_min/tempo_max * 100) << "%" << endl;
    
    return 0;
}
