#include <matrixMultiply.h>
#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// 20050111076 hatice uysal
int main(int argc,char *argv[]){

  // homework 2 -> 3
     matrixMultiply(atoi(argv[1]),atoi(argv[2]),argv[3])  ;


  // homework1
   //calling a function from header file
//   myPrintHelloMake();
     


    return 0 ;
}
