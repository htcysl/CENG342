#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>

int main( ){
    
     
     long  seed = 20050111076 ;
     int lower = 1, upper = 100 ;
     int range = upper-lower+1   ;   
    
     srand(seed) ;   
        
     // generated random number between ? 
     for(int i=0;i<10 ;i++) {
       printf("%5d\n",rand()%range)  ;    
 }   

    //calling a function from header file
    myPrintHelloMake();
     


    return 0 ;
}
