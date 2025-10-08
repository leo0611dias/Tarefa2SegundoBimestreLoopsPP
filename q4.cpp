#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

const int TAMANHO = 1000000;

int main() {
    vector<double> x(TAMANHO), y(TAMANHO), z(TAMANHO);
    vector<double> a(TAMANHO);
    
    // Inicializar vetores
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }
    
    double tempo_total_inicio, tempo_total_fim;
    vector<double> tempos_thread;
    int num_threads = 0;
    
    tempo_total_inicio = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            num_threads = omp_get_num_threads();
            tempos_thread.resize(num_threads);
            cout << "Número de threads utilizadas: " << num_threads << endl;
        }
        
        int thread_id = omp_get_thread_num();
        double thread_inicio = omp_get_wtime();
        
        #pragma omp for schedule(static)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
        
        double thread_fim = omp_get_wtime();
        tempos_thread[thread_id] = thread_fim - thread_inicio;
    }
    
    tempo_total_fim = omp_get_wtime();
    
    // a) Tempo total
    cout << "\nTempo total de execução: " << tempo_total_fim - tempo_total_inicio << " segundos" << endl;
    
    // b) Tempo por thread
    cout << "\nTempo por thread:" << endl;
    for (int i = 0; i < num_threads; i++) {
        cout << "Thread " << i << ": " << tempos_thread[i] << " segundos" << endl;
    }
      return 0;
}
