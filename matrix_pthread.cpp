#include <iostream>
#include <vector>
#include <chrono>
#include <pthread.h>
#include <fstream>

using namespace std;
using namespace std::chrono;

//to store
struct ThreadData {
    const vector<vector<int>>* A;
    const vector<vector<int>>* B;
    vector<vector<int>>* C;
    int n;
    int t_id;
    int n_threads;
};

void* matrixMultiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->n;
    int start_row = data->t_id * n / data->n_threads;
    int end_row = (data->t_id + 1) * n / data->n_threads;

    for (int i = start_row; i < end_row; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            (*data->C)[i][j] = 0;
            for (int k = 0; k < n; ++k) 
            {
                (*data->C)[i][j] += (*data->A)[i][k] * (*data->B)[k][j];
            }
        }
    }

    pthread_exit(nullptr);
}

int main() {
    int n = 100;
    int n_threads = 8;

    vector<vector<int>> A(n, vector<int>(n, rand() % 100));
    vector<vector<int>> B(n, vector<int>(n, rand() % 100));
    //C will strore the result of A*B. Therefore intialize it as null vector
    vector<vector<int>> C(n, vector<int>(n, 0)); 

    pthread_t threads[n_threads];
    ThreadData thread_data[n_threads];

    auto start = high_resolution_clock::now();//sart timer

    for (int i = 0; i < n_threads; ++i) 
    {
        thread_data[i] = {&A, &B, &C, n, i, n_threads};
        pthread_create(&threads[i], nullptr, matrixMultiply, (void*)&thread_data[i]);
    }

    for (int i = 0; i < n_threads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    auto stop = high_resolution_clock::now();//stop timer
    auto duration = duration_cast<milliseconds>(stop - start);//calculate duration

    //output the results
    cout << "Duration of pthread matrix multiplication: " << duration.count() << " milliseconds" << endl;

    //output the results
    ofstream output("output_pthread.txt");
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            output << C[i][j] << " ";
        }
        output << endl;
    }
    output.close();

    return 0;
}
