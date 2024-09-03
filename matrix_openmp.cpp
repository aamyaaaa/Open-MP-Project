#include <iostream>
#include <vector>
#include <chrono>
#include "/opt/homebrew/opt/libomp/include/omp.h"
#include <fstream>
using namespace std;
using namespace std::chrono;

int main() { 
    int n = 100;
    vector<vector<int>> A(n, vector<int>(n, rand() % 100));
    vector<vector<int>> B(n, vector<int>(n, rand() % 100));
    //C will strore the result of A*B. Therefore intialize it as null vector
    vector<vector<int>> C(n, vector<int>(n, 0)); 

    auto start = high_resolution_clock::now();//start timer

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            for (int k = 0; k < n; ++k) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto stop = high_resolution_clock::now();//stop timer
    auto duration = duration_cast<milliseconds>(stop - start);//calculate duration

    cout << "Duration by OpenMP matrix multiplication: " << duration.count() << " milliseconds" << endl;

    ofstream output("output_openmp.txt");
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
