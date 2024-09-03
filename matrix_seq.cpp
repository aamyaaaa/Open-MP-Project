#include <iostream>
#include <vector>
#include <chrono>//to measure time 
#include <fstream>

using namespace std;
using namespace std::chrono;

void matrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n)//we are using reference ie pointers to make the process faster
{
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 100;
    vector<vector<int>> A(n, vector<int>(n, rand() % 100));
    vector<vector<int>> B(n, vector<int>(n, rand() % 100));
    //C will strore the result of A*B. Therefore intialize it as null vector
    vector<vector<int>> C(n, vector<int>(n, 0)); 

    auto start = high_resolution_clock::now();//sart timer
    
    matrixMultiplication(A, B, C, n);

    auto stop = high_resolution_clock::now();//stop timer
    auto duration = duration_cast<milliseconds>(stop - start);//calculate duration

    //output the results
    cout << "Duration of sequential matrix multiplication: " << duration.count() << " milliseconds" << endl;

    //to check the actual output matrix
    ofstream output("output.txt");
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            output << A[i][j] << " ";
        }
        for (int j = 0; j < n; ++j) 
        {
            output << B[i][j] << " ";
        }
        for (int j = 0; j < n; ++j) 
        {
            output << C[i][j] << " ";
        }
        output << endl;
    }
    output.close();

    return 0;
}
