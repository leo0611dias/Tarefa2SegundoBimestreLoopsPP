#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

const int TAMANHO = 1000000;

void calcular_com_schedule(int num_threads, const string& tipo_schedule, int chunk_size) {
    vector<double> x(TAMANHO), y(TAMANHO), z(TAMANHO);
    vector<double> a(TAMANHO);
    
    // Inicializar vetores
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }
    
    omp_set_num_threads(num_threads);
    double inicio = omp_get_wtime();
    
    if (chunk_size > 0) {
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
    } else {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
    }
    
    double fim = omp_get_wtime();
    
    cout << "Threads: " << num_threads << ", Schedule: " << tipo_schedule 
         << ", Tempo: " << fim - inicio << " segundos" << endl;
}

int main() {
    vector<int> threads_config = {2, 4, 8};
    
    cout << "=== COMPARAÇÃO DE ESCALONAMENTOS ===" << endl << endl;
    
    // Testar com diferentes números de threads
    for (int threads : threads_config) {
        cout << "--- " << threads << " THREADS ---" << endl;
        
        // Schedule static
        calcular_com_schedule(threads, "static", 0);
        
        // Schedule dynamic com chunk size 1000
        calcular_com_schedule(threads, "dynamic, chunk=1000", 1000);
    }
    
    cout << "\n=== ANÁLISE DOS RESULTADOS ===" << endl;
    cout << "\nSCHEDULE STATIC:" << endl;
    cout << "- Mais adequado quando as iterações têm carga computacional uniforme" << endl;
    cout << "- Overhead menor pois o trabalho é distribuído uma única vez no início" << endl;
    cout << "- Ideal para loops regulares e previsíveis" << endl;
    
    cout << "\nSCHEDULE DYNAMIC:" << endl;
    cout << "- Mais adequado quando as iterações têm carga computacional variável" << endl;
    cout << "- Permite balanceamento dinâmico de carga entre threads" << endl;
    cout << "- Tem maior overhead devido ao gerenciamento dinâmico das tarefas" << endl;
    cout << "- Ideal quando o tempo de execução de cada iteração é imprevisível" << endl;
    
    cout << "\nCONCLUSÃO:" << endl;
    cout << "- Para este problema específico (carga uniforme), static geralmente" << endl;
    cout << "  terá melhor desempenho devido ao menor overhead." << endl;
    cout << "- Dynamic seria mais vantajoso se as operações dentro do loop fossem" << endl;
    cout << "  de complexidade variável para diferentes índices." << endl;
    
    return 0;
}
