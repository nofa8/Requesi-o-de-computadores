//Include ...
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define Algo ...

//Structures for storing the information!
typedef struct data{
    //Basic Structure for storing the DAY of something happening!
    int dy;
    char mnth[15];
    int yer;
}data; 

typedef struct /*something*/{



}/*something*/;

//Functions!!
int menu(void);
void limpbuff(void);




//Main function
int main(void){
    //Variables:


    //
    menu();



    
       
}



void limpbuff(void){
    char lix;
    do{
        lix = getchar();
    }while(lix!='\n' && lix != EOF);
}

int menu(void){
    int i, rn;
    do{
        printf("\t\t__Requesição de computadores__\n\t()");


        i = scanf("%i",&rn);
    }while(i<=0 || i>/*número*/);
}


