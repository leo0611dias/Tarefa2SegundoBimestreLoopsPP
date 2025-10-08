#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

const int TAMANHO = 1000000;

int main() {
    vector<double> x(TAMANHO), y(TAMANHO), z(TAMANHO);
    vector<double> a_seq(TAMANHO), a_par(TAMANHO);
    
    // Inicializar vetores
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }
    
    double inicio, fim;
    
    // a) Versão sequencial
    inicio = omp_get_wtime();
    for (int i = 0; i < TAMANHO; i++) {
        a_seq[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    fim = omp_get_wtime();
    cout << "Tempo sequencial: " << fim - inicio << " segundos" << endl;
    
    // b) Versão paralela com schedule(static)
    inicio = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TAMANHO; i++) {
        a_par[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    fim = omp_get_wtime();
    cout << "Tempo paralelo (static): " << fim - inicio << " segundos" << endl;
    
    // Verificar resultados
    bool correto = true;
    for (int i = 0; i < TAMANHO; i++) {
        if (fabs(a_seq[i] - a_par[i]) > 1e-10) {
            correto = false;
            break;
        }
    }
    cout << "Resultados corretos? " << (correto ? "Sim" : "Não") << endl;
    
    return 0;
}
