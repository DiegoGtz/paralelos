#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <math.h>
#include <algorithm>
using namespace std;


typedef vector<vector<int>> matrix;
typedef vector<int> _list;

//Pagina 22 Libro 
/* First pair of loops */
	
void PrintM (matrix m){
  for(int i = 0; i < m.size(); i ++){
    for(int j = 0; j < m[0].size(); j++){
      cout<<m[i][j]<<"  ";
    }
    cout<<endl;
  }
  cout<<endl;
}
matrix inicializar(int MAX){
  matrix A = matrix(MAX, _list(MAX,0));
  int num ;
  for(int i = 0; i < MAX; i++){
    for(int j = 0; j < MAX; j++){
    	num=1+rand()%(1001-1);
      A[i][j] = num;
    }
  }
  return A;
}
_list inicializarL(int MAX){
	_list x(MAX,0);
	int num;
	for(int i=0;i<MAX;i++){

		num=1+rand()%(1001-1);
		x[i]=num;
	}
	return x;	
}

void First(matrix A , _list x,  _list y ){
	int i ,j ;
	int MAX1 =  A.size();
	int MAX2 = A[0].size();
	for( i = 0 ; i < MAX1; i++){
		for (j = 0; j < MAX2; j++)
		{
			y[i] += A[i][j]*x[j]; 
		}
	}
	//PrintM(A);
}
/* Second pair of loops */
void Second(matrix A , _list x,  _list y ){
	int i ,j ;
	int MAX1 =  A.size();
	int MAX2 = A[0].size();

	for( j = 0 ; j < MAX2; j++){
		for (i = 0; i < MAX1; i++)
		{
			y[i] += A[i][j]*x[j]; 
		}
	}
	
}	

int main()
{
	clock_t Time_First, Time_Second;


	int tam = 5000; 
	_list x = inicializarL(tam);
	_list y = inicializarL(tam);
	matrix A = inicializar(tam);

	cout<< "Tamanio: "<< tam<<endl;

	Time_First = clock();
	First(A,x,y);
	Time_First = clock() - Time_First;

	Time_Second = clock();
	Second(A,x,y);
	Time_Second = clock() - Time_Second;



	cout<<"First: "<<float(Time_First)/CLOCKS_PER_SEC<<endl;


	cout<<"Second: "<<float(Time_Second)/CLOCKS_PER_SEC<<endl;

	return 0;
}

