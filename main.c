//Include ...
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define Algo ...

//Structures for storing the information!
typedef struct DATa{
    //Basic Structure for storing the DAY of something happening!
    int dy;
    char mnth[15];
    int yer;
}DATa; 



/*
typedef struct something{



}something;
*/

//Functions!!
int menu(void);
void limpaBufferStdin(void);
int lerInteiro(int min, int max);
float lerFloat(float min, float max);
void lerString(char vetor[], int max);
//Insert and list information on every computer, quantidade de avarias, requezições, prazo de requesição, tipo de utente...
//List data of every requisition, duration of the requisition, campus where it was returned and bill(ef)...

//INFORMATION ABOUT THE COMPUTERS AND REQUISTIONS IN A BINARY FILE, stored and read...

//Update information on the location of a computer and the aquisition of the same...
//Register devolution of a computer, previously 'borrowed', processer,ram/mem,(log)...
//Register overall problems and maintenance of the computer...

//Renew aquisitions 

//Present the information of a requisition, selected by the user, designation, status, overall quantity of days 'borrowed'...
//Present statistic data of computers with every kind of processer, overall cost of fine, type of requesters with less quantity of requesitions, recent devolutions...
//Present list of every problems/hazards in a computer, tipo of problem (temporary, permanent), data of the problem, duration of the problem...
   

//Main function
int main(void){
    //Variables:


    //
    menu();



    
       
}



void limpaBufferStdin(void){
    char lix;
    do{
        lix = getchar();
    }while(lix!='\n' && lix != EOF);
}

int menu(void){
    int i, rn;
    do{
        printf("\t\t__Requesiçao de computadores__\n\t()");


        i = scanf("%i",&rn);
    }while(i<=0 );  //|| i>numero);
}

int lerInteiro(int min, int max){
    int numero, controlo;
    do{
        controlo = scanf("%d", &numero);
        limpaBufferStdin();
    }while (numero<min || numero>max || controlo==0);
    return numero;
}

float lerFloat(float min, float max){
    float numero;
    int controlo;
    do{
        controlo = scanf("%f", &numero);
        limpaBufferStdin();
    }while (numero<min || numero>max || controlo==0);
    return numero;
}

void lerString(char vetor[], int max){
    int tamanhoString;
    do{
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }while(tamanhoString == 1);
    if (vetor[tamanhoString-1] != '\n'){
            limpaBufferStdin();
    }
    else{
        vetor[tamanhoString-1] ='\0';
    }
}
