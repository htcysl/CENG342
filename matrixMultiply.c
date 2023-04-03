#include <stdio.h>
#include <matrixMultiply.h>
#include <stdlib.h>
#include <mpi.h>

// Hatice Uysal

void matrixMultiply(int row,int col,char *name){

   FILE *fileName ;
   int *A = (int*)malloc(row*col*sizeof(int)) ; // square matrix 
   int *B = (int*)malloc(col*sizeof(int)) ; // vector 
   int *C = (int*)malloc(col*sizeof(int)) ;  /* for out of io time */
  
   long  seed = 20050111076 ;
   int lower = 1, upper = 100 ;
   int range = upper-lower+1   ;

   srand(seed)  ;
   // generated random matrix by rowxcol

    for (int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
             *(A +i*col +j) = rand()%range ;
//             printf("%d ",*(A+i*col+j)) ;
         }
  //      printf("\n") ;
     }
     // generated random vertor b y size of col
   //  printf("-------------------------------\n") ;
     for(int i=0;i<col;i++) {
         *(B+i)  = rand()%range ;
    //     printf("%d ",*(B+i)) ;
     }
      
  //  printf("\n----------------------------------\n") ;


    MPI_Init(NULL,NULL) ; 

    int rank,size,local_i,sum,upper_limit;
    double start,end,global_time,elapsed ;

    MPI_Comm_size(MPI_COMM_WORLD,&size) ; 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank) ;

   int index = 0 ;
    if(rank== 0) {
     /*process 0 is doing own multiplication */
   
    start = MPI_Wtime() ;   
    for(int i=0;i<row/size;i++){
        sum =0 ;
        for(int j=0;j<col;j++){
           sum += *(A+col*i+j)*(*(B+j)) ;
        }
       *(C+index) = sum ;
       index++;
    }
  end = MPI_Wtime() ;

  elapsed = end-start ; 

  printf("elapse time:%lf for rank 0 \n",elapsed) ;

//  MPI_Reduce(&elapsed,&global_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD) ; 
  
 /*reciving data from other process  */
    for(int proc=1;proc<size;proc++) {
       for(int j=proc*row/size;j<(proc+1)*row/size;j++) {
           int recv ;
           MPI_Recv(&recv,1,MPI_INT,proc,999,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           *(C+index) = recv ;
           index++;
  //         printf("proc:%d, recv:%d\n",proc,recv) ;
       }
     }

 } else {
   
     /*upper_limit variables is used for data is not divided equally by processes, the remaining data is processed by the last process.
      according to this send and recv operation are arranged */

     /*Other processes multiplicaton */
    start = MPI_Wtime() ;
    for(int i=rank*row/size;i<(rank+1)*row/size;i++)  {
      int sum = 0 ; 
      for(int j=0;j<col;j++) {
          sum += *(A+i*row+j)*(*(B+j)); 
      }
      MPI_Send(&sum,1,MPI_INT,0,999,MPI_COMM_WORLD);
//      printf("rank:%d, sum:%d\n",rank,sum);
    }
    end = MPI_Wtime() ;
   elapsed = end-start ;
  
   printf("elapsed time:%lf from rank:%d\n",elapsed,rank) ;
//   MPI_Reduce(&elapsed,&global_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD) ;
  
}
  MPI_Finalize() ;

  free(A);
  free(B) ;
 
  if(rank == 0 ) { 
   printf("Maximumu time %lf \n",global_time) ;
/* writing result matrix to output.txt file */
        fileName = fopen(name,"w") ;
  
        if(fileName != NULL) {
  
           for(int i=0;i<row;i++) 
               fprintf(fileName,"%d\n",*(C+i));
         }
         fclose(fileName) ;
   }
 
   free(C);
   return ;

}

