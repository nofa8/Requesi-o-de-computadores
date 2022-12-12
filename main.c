//Include ...
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//Gloabal Constants 
#define MAXX 30
#define UM 1
#define RAM 32
//Structures for storing the information!
typedef struct{
    //Basic Structure for storing the DAY of something happening!
    int dy;
    char mnth[15];
    int yer;
}DATa; 

typedef struct{
    int portId;
    char desig[25];
    char process[12];
    int  memoria;
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
char menu(CONTADOREs *quantidadesInicial, PORTATIl pcs[MAXX], REQUi req[MAXX]);
void limpaBufferStdin(void);
int lerInteiro(int min, int max);
float lerFloat(float min, float max);
void lerString(char vetor[], int max);
char lerChar(void);
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
    REQUi requisicoes[MAXX];
    PORTATIl portatil1[MAXX];
    CONTADOREs contador;
    FILE *fp, *fp1, *fp2;
    int *numerodeportateis, iniciacao = 1;
    char opcao, inicicontad;
    //
    contador.portatedisp = 0;
    contador.portatexist = 0;
    contador.totalderequisefet = 0;
    contador.requisativas = 0;
    fp1 = fopen("contadore.dat","rb");
    if(fp1 != NULL){
        fread(&contador, sizeof(CONTADOREs), 4, fp);
    }else{

    }
    fp = fopen("requisicao.dat","rb");
    if(fp!=NULL){
        fread(requisicoes, sizeof(REQUi),30, fp);
    }
    else{
        printf("Nao se encontra nenhum ficheiro, recomenda-se listar computadores.\nSe ja existir ficheiro houve um erro ao abrir.\n");
    }
    fclose(fp);


    opcao = menu(&contador,portatil1, requisicoes);




}

//Ficheiros______________________________________________________________________________________


//Buffer Cleaner_________________________________________________________________________________
void limpaBufferStdin(void){
    char lix;
    do{
        lix = getchar();
    }while(lix!='\n' && lix != EOF);
}

//Menu and stuff_________________________________________________________________________________
char menu(CONTADOREs *quantidadesInicial, PORTATIl pcs[MAXX], REQUi req[MAXX]){
    char opc, opcasec;
    int m,e;
    for(m = 0;m<30;m++){
        printf("========");
    }
    printf("\n=\t\t\t\tGestao de Computadores\n\t\t\t\tMeter aqui cenas\n=\n=\n=\n=");
    printf("\n=\t\t\t(I)nserir informacao\n");
    printf("=\t\t\t(L)istar informacao\n");
    printf("=\t\t\t(A)lteracao em relacao a computadores\n");
    printf("=\t\t\t(R)equisicao / Devolucao de computadores\n");
    printf("=\t\t\t(S)air");
    for(e =0;e<30;e++){
        printf("========");
    }
    printf("\n=\t\tInsira a sua opcao: ");
    do{
        limpaBufferStdin();
        opc = lerChar();
        if(opc != 'I' && opc != 'L' && opc != 'A' && opc!= 'R' && opc!= 'S'){
            printf("\nOpcao invalida, insira novamente: ");
        }
    
    }while( opc != 'I' && opc != 'L' && opc != 'A' && opc!= 'R' && opc!= 'S');
    
    switch(opc){
        case 'I':
            int n, i;
            for(m = 0;m<30;m++){
                printf("========");
            }
            printf("\n=\t\t\t\tGestao de Computadores\n=\n=\n=\n=");
            printf("\n=\t\t\tInserir:          \n");
            printf("=\t\t->(C)omputadores            \n");
            printf("=\t\t->(A)varias     \n");
            printf("=\t\t->       \n");
            printf("=\t\t\t(S)air");
            for(e =0;e<30;e++){
                printf("========");
            }   
            printf("\n=\t\tInsira a sua opçao: ");
            do{
                limpaBufferStdin();
                opcasec = lerChar();
                if(opcasec != 'A' && opcasec!= 'C' && opcasec!= 'S'){
                    printf("\nOpcao invalida, insira novamente: ");
                }
            
            }while(opcasec != 'A' && opcasec!= 'C' && opcasec!= 'S');    


            // MAXX - pcs ja registados = num max de pcs para registar
            
            /*printf("Indique quantos computadores pretende registar: ");
            n = lerInteiro(1, 5);
            for(i=0; i<n; i++){
                printf("Introduza o numero de identificacao: ");

                printf("Introduza a desginacao: ");

                printf("Processador: ");
                do{
                    lerString(pcs[i].process , 2);
                    if(strcmp('i3', pcs[i].process) != 0 && strcmp('i5', pcs[i].process) != 0 && strcmp('i7', pcs[i].process) != 0){
                        printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
                    }
                }while(strcmp('i3', pcs[i].process) != 0 && strcmp('i5', pcs[i].process) != 0 && strcmp('i7', pcs[i].process) != 0);               // repete se nao inserir processador valido 

                printf("Memoria RAM (GB): ");
                pcs[i].memoria = lerInteiro(UM,RAM);
            }*/
            break;
        case 'L':
            //Function
            break;
        case 'A':
            //Function
            break;
        case 'R':
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
        if(numero<min || numero>max || controlo==0){
            printf("Valor invalido. Insira novamente: ");
        }
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
char lerChar(void){
    char c;
    scanf(" %c", &c);
    c = toupper(c);
    return c;

}
