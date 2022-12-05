//Include ...
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Gloabal Constants 
#define maxx 30
//Structures for storing the information!
typedef struct{
    //Basic Structure for storing the DAY of something happening!
    int dy;
    char mnth[15];
    int yer;
}DATa; 

typedef struct{
    int portId;
    char desing[25];
    char process[12];
    int  memora;
    char stat[20];
    char local[15];
    DATa aquis;
    float valuequi;
}PORTATIl;

typedef struct{
    PORTATIl portat;
    char requiscode[15];
    DATa requis;
    int numpraz;
    DATa praz;
    //state of a pc?
    //estado de requesição
    char statreq[16];

    //Devolução
    DATa devol;
    char local[15];
    float finee;
    
    //UTENTE STUFF
    char typeut[16];
    int numutent;
    char nomedoutente[40];
}REQUi;

typedef struct{
    int portatexist;
    // Portateis existentes
    int portatedisp;
    //Portateis disponiveis
    int totalderequisefet;
    // Total de requisiçoes feitas
    int requisativas;
    // Requisiçoes ativas
} CONTADOREs;

//Functions!!
int menu(REQUi requisicoes1[maxx], CONTADOREs *contador1);
void limpaBufferStdin(void);
int lerInteiro(int min, int max);
float lerFloat(float min, float max);
void lerString(char vetor[], int max);
void lePortate(REQUi requisicoes2[maxx], CONTADOREs *contador2);
void nextt(int decisor, REQUi requisicoes3[maxx], CONTADOREs *contador3);
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
    //Variables
    REQUi requisicoes[maxx];
    CONTADOREs *contador;
    FILE *fp;
    int *numerodeportateis, iniciacao;
    //
    printf("\t\t\t\tGestao de Portateis\n");
    fp = fopen("iniciacao.dat","rb");
    fread(&iniciacao,sizeof(int),1,fp);
    fclose(fp);
    if(iniciacao!=1){
        iniciacao = 1;
        fp = fopen("iniciacao.dat","wb");
        fwrite(&iniciacao,sizeof(int),1,fp);
        fclose(fp);
        printf("\t\tPor favor digite quantos computadores deseja registar: ");
        *numerodeportateis = lerInteiro(1,30);

    }
    while(1){
    menu(requisicoes,&contador);



            
    }

}

//Ficheiros______________________________________________________________________________________
void lePortate(REQUi requisicoes2[maxx], CONTADOREs *contador2){
    FILE *fp1;
    fp1 = fopen("portatrequis.dat","rb");
    if(fp1 !=NULL){
        fread(requisicoes2,sizeof(PORTATIl),30,fp1);
    }
    else{
        printf("\nErro ao abrir o ficheiro por favor renicie o programa.\n");
    }
} //Testar


//Buffer Cleaner_________________________________________________________________________________
void limpaBufferStdin(void){
    char lix;
    do{
        lix = getchar();
    }while(lix!='\n' && lix != EOF);
}

//Menu and stuff_________________________________________________________________________________
int menu(REQUi requisicoes1[maxx], CONTADOREs *contador1){
    int i, rn;
    lePortate(requisicoes1, &contador1);
    
    printf("\t\t(1)---");
    do{
        i = scanf("%i",&rn);
    }while(i!=0 && rn<0 || rn>5);
    nextt(rn, requisicoes1, &contador1);
}

void nextt(int decisor,REQUi requisicoes3[maxx], CONTADOREs *contador3){
    switch(decisor){
        case 1:
            //Function
            break;
        case 2:
            //Function
            break;
        case 3:
            //Function
            break;
        case 4:
            //Function
            break;
        case 5:
            //Function
            break;
        default:printf("Ocorreu um erro!");
    }
}




//Reading_______________________________________________________________________________________
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
