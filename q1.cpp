/*
Lista de Exercícios — Programação Paralela (OpenMP)
Prof. Rodrigo Gonçalves

Exercício 1 — "Hello World" Paralelo
a) Crie uma região paralela com #pragma omp parallel.
b) Cada thread deve imprimir uma mensagem indicando seu número 
   (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
c) Configure o programa para rodar com 4 threads.
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    /*
    FUNÇÃO: Programa principal que demonstra criação de threads paralelas
    PARÂMETROS: Nenhum
    RETORNO: 0 em caso de sucesso
    */
    
    // Configura o número de threads para 4
    // omp_set_num_threads() define quantas threads OpenMP irá utilizar
    omp_set_num_threads(4);
    
    // #pragma omp parallel cria uma região paralela
    // Todas as threads executam o bloco de código simultaneamente
    #pragma omp parallel
    {
        // omp_get_thread_num() retorna o ID único da thread (0 a N-1)
        int thread_id = omp_get_thread_num();
        
        // omp_get_num_threads() retorna o número total de threads na região paralela
        int total_threads = omp_get_num_threads();
        
        // Cada thread imprime sua identificação
        cout << "Thread " << thread_id << " de " << total_threads << ": Hello World!" << endl;
    }
    
    return 0;
}
