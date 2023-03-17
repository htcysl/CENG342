#include <stdio.h>
#include <matrixMultiply.h>
#include <stdlib.h>

void matrixMultiply(int row,int col,char *name){

     FILE *fileName ;
     int *A = (int*)malloc(row*col*sizeof(int)) ;
     int *B = (int*)malloc(col*sizeof(int)) ;

     long  seed = 20050111076 ;
     int lower = 1, upper = 100 ;
     int range = upper-lower+1   ;

     srand(seed)  ;
     // generated random matrix by rowxcol    

     for (int i=0;i<row;i++) {
         for(int j=0;j<col;j++) {
              *(A +i*col +j) = rand()%range ; 
          }
     }
     // generated random vertor b y size of col 
       for(int i=0;i<col;i++) {
           *(B+i)  = rand()%range ;
       }

       fileName = fopen(name,"w") ;
       
       if(fileName == NULL) {
         printf("File cannot opened!");
       }
       else {
      // matrix and vertor maltiplication
      printf("file is opened...\n") ;
      for(int i=0;i<row;i++) {
         int sum = 0 ;
         for(int j=0;j<col;j++){
            // printf("%d ", *(A +i*col +j)) ;
            // printf("%d ",*(B+j)) ;
             sum +=  *(A+i*row+j) * (*(B+j))  ; 
          }
       //  printf(" =  %d\n ",sum) ;
         fprintf(fileName,"%d\n",sum);
         }
        }
       fclose(fileName) ;
     printf("file is closed.\n") ;
 
   return ;

}

