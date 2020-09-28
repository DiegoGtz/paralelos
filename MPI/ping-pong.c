#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>


int main(int argc, char  *argv[])
{


	MPI_Init(NULL,NULL);
	

	int  myId;
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
	int numP;
	MPI_Comm_size(MPI_COMM_WORLD, &numP);

	if(numP != 2 ){
		printf(" El tamaño tiene que ser %s\n",argv[0]);
		MPI_Abort(MPI_COMM_WORLD,1);
	}

	int num_ping_pong 	= atoi(argv[1]);
	int ping_pong_count = 0;
	int partner_rank = (myId + 1) % 2;
	//int partner_rank ;
	/*bool odd = myId%2;
	if (odd)
	{
		partner_rank = myId - 1 ;
	}else{
		partner_rank = myId + 1 ;
	}*/


	while(ping_pong_count < num_ping_pong){
	

		if(myId == ping_pong_count%2){
			
			ping_pong_count++;
			MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
			printf("Env : Proceso %d >>>> [%d] >>>> Proceso %d\n", myId, ping_pong_count,partner_rank );		
			
		}
		else{

			MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Rec : Proceso %d >>>> [%d] >>>> Proceso %d\n", myId, ping_pong_count,partner_rank );
		}
	}



	MPI_Finalize();
	return 0;
} 