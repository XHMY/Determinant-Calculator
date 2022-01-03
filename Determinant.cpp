#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>
#include <fstream>
#define size 20 // Modify to fit your matrix
using namespace std;

int det[size];
int mat[size][size];

// declaring variable for storing my_thread id
pthread_t my_thread[size];

// function for finding determinant
int determinant(vector<vector<int> > mat2, int s)
{
    if (s == 2)
    {
        // if size of matrix is 2X2 then returning the determinant
        return mat2[0][0] * mat2[1][1] - mat2[0][1] * mat2[1][0];
    }
    else
    {
        // else dividing the matrix in smaller part.
        vector<vector<vector<int> > > submatrix(s);
        int res = 0, row, i, col_d ,col_s;
        for (i = 0; i < s; i++)
        {
            submatrix[i] = vector<vector<int> >(s - 1);
            for(row = 0; row < s - 1; row++)
                submatrix[i][row] = vector<int>(s - 1);
        }
        for(i = 0; i < s; i++)
            for(row = 1; row < s; row++)
                for(col_d = 0, col_s = 0; col_d < s - 1;)
                {
                    if(col_s == i)
                    {
                        col_s++;
                        continue;
                    } 
                    submatrix[i][row - 1][col_d] = mat2[row][col_s]; 
                    col_d++; col_s++;
                }
        for(i = 0; i < s; i++)
        {
            if (i % 2 == 0)
                res += mat2[0][i] * determinant(submatrix[i], s - 1);
            else
                res -= mat2[0][i] * determinant(submatrix[i], s - 1);
        } 
        return res;
    }
}

// function for finding determinant using first row
// with each element of row a my_thread is associated.
void *createTd(void *arg)
{
    int *ar = (int *)arg, i, j, k;
    vector<vector<int> > mat2(size - 1);

    for (i = 0; i < size - 1; i++)
        mat2[i] = vector<int>(size - 1);

    // extracting the matrix smaller by size one.
    // for finding the determinant.
    for (i = 1; i < size; i++)
    {
        k = 0;
        for (j = 0; j < size; j++)
        {
            if (j != (*ar))
            {
                mat2[i - 1][k] = mat[i][j];
                k++;
            }
        }
    }

    // calling determinant function
    det[*ar] = det[*ar] * determinant(mat2, size - 1);
}

// driver function
int main()
{
    int i, j, detfin = 0;
    int p[size];
    
    ifstream infile; 
    infile.open("data.in"); 
    for(i = 0; i < size; i++)
        for(j = 0; j < size; j++)
            infile >> mat[i][j]; 
    infile.close();
    cout<<"Calculate determinant for "<< size <<"×"<< size <<" matrix:"<<endl;
    auto start = chrono::system_clock::now();

    // storing the first row in a array for later multipying with the determinant of smaller matrix
    for (i = 0; i < size; i++)
        det[i] = mat[0][i];

    // creating my_thread
    for (i = 0; i < size; i++)
    {
        p[i] = i;
        pthread_create(&my_thread[i], NULL, &createTd, (void *)&p[i]);
    }

    // waiting for all the threads to join
    for(i=0;i<size;i++)
        pthread_join(my_thread[i], NULL);
    
    for (i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            detfin += det[i];
        else
            detfin -= det[i];
    }
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time Spend: " << elapsed.count() / 1000.0 << " s" << '\n';
    cout << "The result is " << detfin << endl;

    return 0;
}
