#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

double f(double x){return x*x;}


double Trap(double left_endpt, double right_endpt ,int trap_count, double base_len) 
{

	double  estimate, X;
	int i ;

	estimate = (f(left_endpt) + f(right_endpt))/2.0;

	for (i = 1; i <= trap_count -1 ; i++)
	{
		X = left_endpt + i*base_len;
		estimate += f(X);
	}
	estimate = estimate*base_len;

	return estimate;


}


int main(void)
{
	int my_rank, comm_sz, n = 1024 , local_n;

	double a = 0.0,  b = 3.0, h, local_a, local_b;

	double local_init, total_int;

	int source;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	h = (b-a)/n;  //h  es la misma para todos los procesos 

	local_n = n/comm_sz; // numero de trapezoides 

	local_a = a + my_rank*local_n*h;

	local_b = local_a + local_n*h;

	local_init = Trap(local_a,local_b,local_n,h);

	printf("%f\n", local_init);

	if (my_rank != 0){

		MPI_Send(&local_init, 1, MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	else{

		total_int = local_init;

		for (source  = 1; source <comm_sz; source++)
		{
			MPI_Recv(&local_init, 1, MPI_DOUBLE, source, 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

			total_int += local_init;
		}
	}

	if (my_rank == 0 ){

		printf("With n = %d trapezoids, our estimate \n", n );
		printf("of the integrak from %f to % f = %.15e\n",a,b,total_int );
	}

	MPI_Finalize();
	return 0;

}