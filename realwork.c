#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXX 30
#define UM 1
#define RAM 32
#define I3 "i3"
#define I7 "i7"
#define I5 "i5"
#define MAX_NOME 80
#define ZERO 0
#define MENOR_ANO 2014
#define MAIOR_ANO 2021
#define MAX_DESIG 20
#define MAXIMUS 9999
#define STAT_REQ "requisitado"
#define STAT_DISP "disponivel"
#define STAT_AVA "avariado"


//Structures for storing the information!
typedef struct{
    //Basic Structure for storing the DAY of something happening!
    int dy;
    char mnth[15];
    int yer;
}DATa;


typedef struct{
    char requiscode[15];
    DATa requis;
    int numpraz;     //prazo days
    DATa praz;      // prazo requisicao
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
    char nomedoutente[MAX_NOME];
}REQUi;


typedef struct{
    REQUi *requisition;
    int portId;
    char desig[MAX_DESIG];
    char process[3];
    int  memoria;
    char stat[13];
    int quantAvarias;
    int quantReq;
    char local[15];
    DATa aquis;
    float valuequi;
}PORTATIl;

typedef struct{
    int portatexist;        // Portateis existentes
    int portatedisp;        //Portateis disponiveis
    int totalderequisefet;  // Total de requisiçoes feitas
    int requisativas;       // Requisiçoes ativas
} CONTADOREs;
















void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
float lerFloat(float min, float max);


char menu(CONTADOREs *cont);
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX]);
void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX]);
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX]);
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX]);

int lerID(PORTATIl port[MAXX], CONTADOREs *cont);
int lerDesignacao(PORTATIl port[MAXX], CONTADOREs *cont, int pos);


int main()
{
    PORTATIl portateis[30];
    CONTADOREs oscontadores;
    char escolha;
    //portateis->requisition = malloc(10*sizeof(REQUi));
    oscontadores.portatexist = 0;
    oscontadores.portatedisp = 0;
    oscontadores.requisativas = 0;
    oscontadores.totalderequisefet = 0;

    do{
        escolha = menu(&oscontadores);
        switch(escolha){
            case 'A':

                break;
            case 'I':
                insertPCs(&oscontadores, portateis);
                break;
            case 'M':

                break;
            case 'G':
//                gravaFicheiroTexto(vEstudantes,quantInscritos);
//                gravaFicheiroBinario(vEstudantes, quantInscritos);
                break;
            case 'L':
                subListar(&oscontadores, portateis);
                break;
            case 'S':
                printf("\nA sair ...\n");
            break;
        }
    }while(escolha != 'S');



    return 0;
}



char menu(CONTADOREs *cont){
    char opcao;
    printf("\n\n==========================Menu Principal==========================\n\n");
    printf("\tQuantidade de portateis: %d", cont->portatexist);
    printf("\t\tQuantidade de portateis disponiveis: %d \n\tTotal de requisicoes efetuadas: %d\tQuantidade de requisicoes ativas: %d\n", cont->portatedisp, cont->totalderequisefet, cont->requisativas);

    printf("\nI - Inserir Portateis\n");
    printf("L - Listar Informacao\n\n");      //adicionar dados de requisicoes

    printf("R - Registar Requisicao\n");
    printf("V - Registar Avaria / Reparacao\n");
    printf("D - Registar Devolucao \n\n");

    printf("A - Alteracao da Localizacao de um portatil\n");
    printf("Y - Renovar requisicao\n");
    printf("M - Mostrar dados de Requisicoes\n\n");

    printf("G - Gravar dados nos Ficheiros\n");
    printf("E - Extrair dados dos Ficheiros\n\n");
    printf("Z - Apresentacao de dados estatisticos\n");
    printf("\tS - Sair\n\t\t\tOpcao --> ");

    do{
        opcao = getchar();
        limpaBufferStdin();
        opcao = toupper(opcao);
        if(opcao != 'M'&& opcao != 'Y'&& opcao != 'Z'&& opcao != 'A'&& opcao != 'D'&& opcao != 'V'&& opcao != 'I'&& opcao != 'L' && opcao != 'G' && opcao != 'E' && opcao != 'R' && opcao != 'S'){
            printf("Opcao invalida!\n\n");
        }
    }while(opcao != 'M'&& opcao != 'Y'&& opcao != 'Z'&& opcao != 'A'&& opcao != 'D'&& opcao != 'V'&& opcao != 'I'&& opcao != 'L' && opcao != 'G' && opcao != 'E' && opcao != 'R' && opcao != 'S');



    return opcao;
}
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX]){     //passar quantPortateis nos ()
    int i;
    char opcao1;

    printf("\n\n\n\n\n\n\n\n==========================Listar Informacao==========================\n\n");
    printf("\tP - Informacao de Portateis\n\n");
    printf("\tT - Listar dados de Todas Requisicoes\n\n");
    printf("\tR - Apresentar informacao de uma requisicao\n\n");
    printf("\tA - Apresentar listagem de todas as avarias ocorridas\n\n");
    printf("\tS - Sair\n");
    printf("\t\tOpcao: ");
    do{
        opcao1 = getchar();
        limpaBufferStdin();
        opcao1 = toupper(opcao1);
        if(opcao1 != 'P'&& opcao1 != 'T'&& opcao1 != 'R'&& opcao1 != 'A' && opcao1 != 'S'){
            printf("\nOpcao invalida!\nInsira Novamente: ");
        }
    }while(opcao1 != 'P'&& opcao1 != 'T'&& opcao1 != 'R'&& opcao1 != 'A' && opcao1 != 'S');

    switch(opcao1){
    case 'P':
        lePortate(cont,port1);
        break;
    case 'T':
        //listaReq(cont,port1);
        break;
    case 'R':
        break;
    case 'A':
        break;
    case 'S':
        printf("\n\t.\n");
        break;
    }
 }

void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX]){
    int i;
    if(cont->portatexist!=0){
        for(i=0; i < cont->portatexist; i++){
            printf("\nId: %d\n", port2[i].portId);
            printf("Portatil %s: \n", port2[i].desig);
            printf("\tProcessador: %s", port2[i].process);
            printf("\tEstado: %s\n", port2[i].stat);
            printf("\tLocalizacao: %s", port2[i].local);
            printf("\tData de aquisicao: %d / %d / %d\n", port2[i].aquis.dy,port2[i].aquis.mnth,port2[i].aquis.yer);
            printf("\tValor do equipamento: %f", port2[i].valuequi);
            printf("\tQuantidade de avarias: %d\n", port2[i].quantAvarias);
            printf("\tQuantidade de requisicoes: %d\n", port2[i].quantReq);
            printf("\tTipo de utente: %15c\tPrazo de requisicao: %d dias", port2[i].requisition->typeut,port2[i].requisition->numpraz);
        }
    }
    else{
        printf("\nNao ha computadores!\n");
    }
}

void listaReq(CONTADOREs *cont, PORTATIl port[MAXX]){





}


void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i, u, desig = 0, aux = 0;
    printf("\nQuantos pcs deseja inserir: ");
    u = lerInteiro(1,MAXX);
    u += cont->portatexist;     // se for + q 30 nao deixar inserir
    if(u>30){
        u -= 30;
        printf("Nao e possivel adicionar mais computadores.\n%d a mais que o limite", u);
    }
    else{
        for(i = (*cont).portatexist; i<u; i++){
            do{
                printf("\nId: ");
                port[i].portId = lerID(port, cont);
            }while (port[i].portId == -1);
            do{
                printf("\nDesignacao do portatil: ");
                desig = lerDesignacao(port, cont, i);
            }while(desig == -1);

            printf("\n\tProcessador: ");
            do{
                lerString(port[i].process , 3);
                if(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0){
                    printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
                }
            }while(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0);

            printf("\n\tEstado: ");
            do{
               lerString(port[i].stat, 13);
                for(aux = 0; aux < strlen(port[i].stat); aux++){
                    port[i].stat[aux] = tolower(port[i].stat[aux]);
                }
                if(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0){
                    printf("\nEstado invalido (Avariado, Requisitado, Disponivel). Insira novamente: ");
                }
            }while(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0);
            printf("\n\tLocalizacao: ");
            printf("\n\tData de aquisicao: ");
            printf("\n\tValor do equipamento: ");
            (*cont).portatexist ++;

        }
    }


}



/*_________________________________________________________________________________________________*/

void limpaBufferStdin(void){
    char lixo;
    do
    {
        lixo=getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}


int lerInteiro(int min, int max){
    int numero, controlo;
    do
    {
        controlo = scanf("%d", &numero);// scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin(); /* elimina caracteres que ficaram no buffer stdin */
        if (numero<min || numero>max || controlo==0){
            printf("Valor invalido! \nInsira novamente: ");
        }
    }
    while (numero<min || numero>max || controlo==0);
    return numero;
}

float lerFloat(float min, float max)
{
    float numero;
    int controlo;
    do{
        controlo = scanf("%f", &numero); // scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin(); /* elimina caracteres que ficaram no buffer stdin */
    }while (numero<min || numero>max || controlo==0);
    return numero;
}

void lerString(char vetor[], int max)
{
    int tamanhoString;
    do  /*Repete leitura caso sejam introduzidas strings apenas com o \n (tamanhoString == 1) */
    {
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }
    while(tamanhoString == 1);
    if (vetor[tamanhoString-1] != '\n'){
        /* armazenados no vetor todos os caracteres */
        limpaBufferStdin(); /* elimina caracteres que ficaram no buffer stdin */
    }
    else {
        vetor[tamanhoString-1] ='\0'; /*substitui \n da string armazenada em vetor por \0 */
    }
}

int lerID(PORTATIl port[MAXX], CONTADOREs *cont){         //funcao para verificar se id ja foi inserido
    int i, id = 0;
    id = lerInteiro(UM, MAXIMUS);
    for (i=0; i < (*cont).portatexist; i++){
        if(id == port[i].portId){
            id = -1;
            i = (*cont).portatexist;          //para nao procurar mais pq ja encontrou
            printf("\nId ja existente.\n");
        }
    }
    return id;
}

int lerDesignacao(PORTATIl port[MAXX], CONTADOREs *cont, int pos){
    int i, des = 0;
    char design[MAX_DESIG];
    lerString(design, MAX_DESIG);
    for (i=0; i < (*cont).portatexist; i++){
        if (strcmp(design, port[i].desig)==0){  //encontrou o codigo no vetor
            des = -1;
            i = (*cont).portatexist;
            printf("\nErro. Designacao ja existente.\n");
        }
    }
    if(des != -1){      // se designacao ainda nao existir
        strcpy(port[pos].desig, design);
    }
    return des;
}


