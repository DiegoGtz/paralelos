#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <math.h>
#include <algorithm>
using namespace std;


typedef vector<vector<int>> matrix;
typedef vector<int> _list;

	
void PrintM (matrix m){
  for(int i = 0; i < m.size(); i ++){
    for(int j = 0; j < m[0].size(); j++){
      cout<<m[i][j]<<"  ";
    }
    cout<<endl;
  }
  cout<<endl;
}
matrix inicializarM(int MAX){
  matrix A = matrix(MAX, _list(MAX,0));
  int num ;
  for(int i = 0; i < MAX; i++){
    for(int j = 0; j < MAX; j++){
    	num=1+rand()%(101-1);
      	A[i][j] = num;
    }
  }
  return A;
}

void Version_por_bloques(matrix A, matrix B){
  int n = A.size();
  int b = 10;
  matrix C = matrix(n, _list (B[0].size(),0));
  for(int i0 = 0; i0 < n; i0+= b){
    for(int j0 = 0; j0 < n; j0+= b){
      for(int k0 = 0; k0 < n; k0+= b){
        for(int i = i0; i < min(i0 + b , n ); i++){
          for(int j = j0; j < min(j0 + b, n); j++){
            for(int k = k0; k < min(k0 + b, n); k++){
              C[i][j] += A[i][k] * B[k][j];
            }
          }
        }
      }
    }
  }
  //PrintM(C);


}



int main()
{
	clock_t Time_First, Time_Second;


	int tam = 1000; 

	cout<<"Tamanio : " << tam << endl;
	matrix A = inicializarM(tam);
	
	matrix B = inicializarM(tam);


	Time_Second = clock();
	Version_por_bloques(A,B);
	Time_Second = clock() - Time_Second;


	//cout<<"First: "<<float(Time_First)/CLOCKS_PER_SEC;
	cout<<"Version por Bloques Clasica : "<<float(Time_Second)/CLOCKS_PER_SEC;

	return 0;
}
