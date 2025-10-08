# Tarefa2SegundoBimestreLoopsPP
Leonardo Dias dos Passos Brito - 23121300234

---------------------------------------------

Programação Paralela com OpenMP
📋 Exercícios de Programação Paralela
Este projeto contém 5 exercícios em C++ com OpenMP demonstrando conceitos fundamentais de paralelismo.

🚀 Compilação e Execução
bash
# Compilar todos os exercícios
g++ -fopenmp -o q1 q1.cpp
g++ -fopenmp -o q2 q2.cpp
g++ -fopenmp -o q3 q3.cpp
g++ -fopenmp -o q4 q4.cpp
g++ -fopenmp -o q5 q5.cpp

# Executar
./q1
./q2
./q3
./q4
./q5

 Descrição dos Exercícios
 
Q1: "Hello World" Paralelo
Introdução ao OpenMP com regiões paralelas

Cada thread imprime seu ID e número total de threads

Configurado para 4 threads

🔄 Q2: Paralelização com Reduction
Demonstra paralelização de loops com reduction

Compara versões sequencial e paralela

Explica importância da reduction para evitar race conditions

Q3: Expressão Vetorial
Calcula a[i] = x[i]² + y[i]² + z[i]² para 1M elementos

Compara tempos de execução sequencial vs paralelo

Usa schedule(static) para distribuição de carga

Q4: Medição de Tempo por Thread
Mede tempo individual de cada thread

Analisa balanceamento de carga

Mostra número total de threads utilizadas

Q5: Análise de Escalonamento
Compara schedule(static) vs schedule(dynamic)

Testa com 2, 4 e 8 threads

Fornece recomendações de uso para cada política

Conceitos Abordados
Diretivas OpenMP: parallel, parallel for, single

Controle de threads: configuração e identificação

Reduction: operações seguras em variáveis compartilhadas

Escalonamento: políticas static e dynamic

Medição de tempo: análise de desempenho

Balanceamento de carga: entre threads

📈 Aplicações Práticas
Processamento de sinais e imagens

Cálculos científicos e matemáticos

Operações em machine learning

Análise de dados em larga escala

Os exercícios fornecem uma base sólida para programação paralela, desde conceitos básicos até técnicas avançadas de otimização com OpenMP.

