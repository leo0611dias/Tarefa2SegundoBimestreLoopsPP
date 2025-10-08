#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    //4 threads
    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        cout << "Thread " << thread_id << " de " << total_threads << ": Hello World!" << endl;
    }
    
    return 0;
}
