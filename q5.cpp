/*
Lista de Exercícios — Programação Paralela (OpenMP)
Prof. Rodrigo Gonçalves

Exercício 5 — Escalonamento
Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
a) Execute com schedule(static) e schedule(dynamic, 1000).
b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
c) Explique em quais situações static e dynamic são mais adequados.
*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;

const int TAMANHO = 1000000;

void calcular_com_schedule(int num_threads, const string& tipo_schedule, int chunk_size) {
    /*
    FUNÇÃO: Executa cálculo vetorial com política de escalonamento específica
    PARÂMETROS:
        num_threads: número de threads a serem utilizadas
        tipo_schedule: descrição textual do schedule usado
        chunk_size: tamanho do bloco para schedule dynamic (0 para static)
    RETORNO: Nenhum
    */
    
    // Aloca memória para vetores
    vector<double> x(TAMANHO), y(TAMANHO), z(TAMANHO);
    vector<double> a(TAMANHO);
    
    // Inicialização dos vetores
    for (int i = 0; i < TAMANHO; i++) {
        x[i] = i * 0.1;
        y[i] = i * 0.2;
        z[i] = i * 0.3;
    }
    
    // Configura número de threads para esta execução
    omp_set_num_threads(num_threads);
    
    // Inicia medição de tempo
    double inicio = omp_get_wtime();
    
    // Executa com schedule dynamic se chunk_size > 0, caso contrário static
    if (chunk_size > 0) {
        // schedule(dynamic, chunk_size): distribui blocos de 'chunk_size' iterações
        // Quando uma thread termina seu bloco, pega outro bloco disponível
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
    } else {
        // schedule(static): divide iterações igualmente no início
        // Cada thread recebe um bloco fixo de iterações
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < TAMANHO; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }
    }
    
    double fim = omp_get_wtime();
    
    // Exibe resultados desta configuração
    cout << "Threads: " << num_threads << ", Schedule: " << tipo_schedule 
         << ", Tempo: " << fim - inicio << " segundos" << endl;
}

int main() {
    /*
    FUNÇÃO: Compara diferentes políticas de escalonamento com variados números de threads
    PARÂMETROS: Nenhum
    RETORNO: 0 em caso de sucesso
    */
    
    // Configurações de threads a serem testadas
    vector<int> threads_config = {2, 4, 8};
    
    cout << "=== COMPARAÇÃO DE ESCALONAMENTOS ===" << endl << endl;
    
    // Testa cada configuração de threads
    for (int threads : threads_config) {
        cout << "--- " << threads << " THREADS ---" << endl;
        
        // Executa com schedule static
        // chunk_size = 0 indica schedule static
        calcular_com_schedule(threads, "static", 0);
        
        // Executa com schedule dynamic e chunk size 1000
        calcular_com_schedule(threads, "dynamic, chunk=1000", 1000);
    }
    
    // Explicação detalhada sobre escalonamentos
    cout << "\n=== ANÁLISE DETALHADA DOS ESCALONAMENTOS ===" << endl;
    
    cout << "\nSCHEDULE STATIC:" << endl;
    cout << "- Funcionamento: Divide as iterações em blocos iguais no INÍCIO da execução" << endl;
    cout << "- Cada thread recebe um conjunto FIXO de iterações para processar" << endl;
    cout << "- Overhead: Mínimo, pois a distribuição acontece apenas uma vez" << endl;
    cout << "- Ideal para:" << endl;
    cout << "  * Carga computacional UNIFORME entre iterações" << endl;
    cout << "  * Loops regulares e previsíveis" << endl;
    cout << "  * Quando o tempo por iteração é aproximadamente constante" << endl;
    cout << "  * Aplicações: Processamento de imagens, cálculos matriciais" << endl;
    
    cout << "\nSCHEDULE DYNAMIC:" << endl;
    cout << "- Funcionamento: Divide as iterações em blocos (chunks) e distribui DINAMICAMENTE" << endl;
    cout << "- Quando uma thread termina seu bloco, pega o próximo bloco disponível" << endl;
    cout << "- Overhead: Maior, devido ao gerenciamento dinâmico da fila de blocos" << endl;
    cout << "- Parâmetro chunk: Define o tamanho de cada bloco (ex: 1000 iterações)" << endl;
    cout << "- Ideal para:" << endl;
    cout << "  * Carga computacional VARIÁVEL entre iterações" << endl;
    cout << "  * Loops irregulares ou imprevisíveis" << endl;
    cout << "  * Quando algumas iterações são muito mais lentas que outras" << endl;
    cout << "  * Aplicações: Processamento de árvores, algoritmos recursivos" << endl;
    
    cout << "\nCONCLUSÃO PARA ESTE PROBLEMA:" << endl;
    cout << "- Neste exercício específico (a[i] = x[i]² + y[i]² + z[i]²):" << endl;
    cout << "  * A carga é PERFEITAMENTE UNIFORME - cada iteração tem o mesmo custo" << endl;
    cout << "  * Schedule STATIC geralmente terá melhor desempenho" << endl;
    cout << "  * O menor overhead do static é vantajoso para carga balanceada" << endl;
    cout << "- Em problemas com carga variável, DYNAMIC pode ser significativamente melhor" << endl;
    
    cout << "\nRECOMENDAÇÕES GERAIS:" << endl;
    cout << "1. Use STATIC para loops regulares com carga uniforme" << endl;
    cout << "2. Use DYNAMIC para loops irregulares com carga variável" << endl;
    cout << "3. Teste diferentes tamanhos de chunk no dynamic para otimizar" << endl;
    cout << "4. Considere schedule(guided) como alternativa balanceada" << endl;
    
    return 0;
}
