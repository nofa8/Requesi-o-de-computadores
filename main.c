#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXIMUS 9999
#define MAXX 30
#define NMAXX 15
#define UM 1
#define ZERO 0

#define RAM 32

#define I3 "i3"
#define I5 "i5"
#define I7 "i7"

#define STAT_DISP "disponivel"
#define STAT_REQ "requisitado"
#define STAT_AVA "avariado"

#define STAT_ATIV "ativo"
#define STAT_CONC "concluido"

#define MAX_DESIG 20
#define MAX_NOME 80
#define MENOR_ANO 2010
#define MAIOR_ANO 2023

#define CAMPUS1 "campus1"
#define CAMPUS2 "campus2"
#define CAMPUS5 "campus5"
#define RESID "residencias"

#define TIPO_ESTUD "estudante"
#define TIPO_DOCE  "docente"
#define TIPO_ADM  "tecnico administrativo"

 //Structures for storing the information!
typedef struct{
    //Basic Structure for storing the DAY of something happening!
    int dia;
    int mes;
    int ano;
}DATa;


typedef struct{
    char requiscode[NMAXX];
    DATa requis;
    int numpraz;     //prazo days
    DATa praz;      // prazo requisicao
    //state of a pc?
    //estado de requesição
    char statreq[NMAXX];

    //Devolução
    DATa devol;
    char local[NMAXX];
    float finee;
    int prazreal;

    //UTENTE STUFF
    char typeut[25];
    int numutent;
    char nomedoutente[MAX_NOME];
}REQUi;


typedef struct{
    REQUi *requisition;
    int portId;
    char desig[MAX_DESIG];
    char process[3];
    int  memoria;
    char stat[NMAXX];
    int quantAvarias;
    int indicereq;
    int quantReq;
    char local[NMAXX];
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
DATa lerData(void);
int subtrairDatas(DATa d1, DATa d2);

char menu(CONTADOREs *cont,PORTATIl port[MAXX]);
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX]);

void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX]);
void regRq(CONTADOREs *cont, PORTATIl port[MAXX]);
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX]);
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX]);

int lerID(CONTADOREs *cont, PORTATIl port[MAXX]);
int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX]);
int lerDesignacao( CONTADOREs *cont, PORTATIl port[MAXX], int pos);

void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX]);
void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX]);


int main()
{
    PORTATIl portateis[30];
    CONTADOREs oscontadores;
    char escolha;
    int i = 0;
    oscontadores.portatexist = 0;
    oscontadores.portatedisp = 0;
    oscontadores.requisativas = 0;
    oscontadores.totalderequisefet = 0;
    for(i = 0;i<MAXX;i++){
        portateis[i].requisition = malloc(20*sizeof(REQUi));
    }
    
    do{
        escolha = menu(&oscontadores,portateis);
        switch(escolha){
            case 'I':
                insertPCs(&oscontadores, portateis);
                break;
            case 'L':
                subListar(&oscontadores, portateis);
                break;
            case 'R':
                regRq(&oscontadores, portateis);
                break;
            case 'V':

                break;
            case 'D':

                break;
            case 'A':

                break;
            case 'Y':

                break;
            case 'M':

                break;
            case 'G':
                gravarFicheiroBinario(oscontadores, portateis);
                //gravarFicheiroTexto(oscontadores,portateis);

                break;
            case 'E':
                lerFicheiroBinario(&oscontadores, portateis);
                break;
            case 'Z':

                break;
            
            case 'S':
                printf("\nA sair ...\n");
                
        }
    }while(escolha != 'S');



    return 0;
}



char menu(CONTADOREs *cont,PORTATIl port[MAXX]){
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
            printf("Opcao invalida!\n\nInsira Novamente: ");
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
        listaReq(cont,port1);
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
    int i, u;
    if(cont->portatexist!=0){
        for(i=0; i < cont->portatexist; i++){
            printf("\nId: %d\n", port2[i].portId);
            printf("Portatil %s: \n", port2[i].desig);
            printf("\t\tProcessador: %s", port2[i].process);
            printf("\t\t\tEstado: %s\n", port2[i].stat);
            printf("\t\tLocalizacao: %s", port2[i].local);
            printf("\t\tData de aquisicao: %d / %d / %d\n", port2[i].aquis.dia,port2[i].aquis.mes,port2[i].aquis.ano);
            printf("\t\tValor do equipamento: %.2f", port2[i].valuequi);
            printf("\tQuantidade de avarias: %d\n", port2[i].quantAvarias);
            printf("\t\tQuantidade de requisicoes: %d\n", port2[i].quantReq);
            if(port2[i].quantReq == 0){
                printf("\t\tTipo de utente: ----\tPrazo de requisicao: ---- dias");
            }
            else{
                printf("\t\tTipo de utente: %15s\tPrazo de requisicao: %d dias", port2[i].requisition[port2[i].indicereq].typeut,port2[i].requisition[port2[i].indicereq].numpraz);
            }
        }

    }
    else{
        printf("\nNao ha computadores!\n");
    }
}

void regRq(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i= 0,l=0,h = 0,u = 0,idTemporario = 0, indice=-1, numutente = 0, date = 0;
    if((*cont).portatedisp >0){
            printf("\nInsira o numero de identificacao do portatil: ");
            idTemporario = lerInteiro(UM,MAXIMUS);
            for (l=0;i<(*cont).portatexist;l++){
                if(port[l].portId == idTemporario){
                    indice = l;
                    if(strcmp(port[indice].stat,STAT_DISP)==0){

                        //Codigo de Requisicao
                        printf("\nCodigo de requisicao: ");
                        do{
                            lerString(port[indice].requisition[port[indice].quantReq].requiscode,NMAXX);
                            for(i = 0; i <(*cont).portatexist;i++){
                                    if(strcmp(port[indice].requisition[port[indice].quantReq].requiscode,port[i].requisition[port[i].quantReq].requiscode)==0){
                                        //"Podiamos deixar ai um comentario para depois falar à professora", Gonçalo 21/12/2022
                                        if(strcmp(port[i].requisition[port[i].quantReq].statreq,STAT_ATIV)==0){
                                            printf("\nCodigo de requisicao indisponivel.\n");
                                            u = -1;
                                            i = cont->portatexist;
                                        }  
                                    }
                            }
                        }while(u == -1);
                        //Data Requisição
                        printf("\nData de Requisicao: ");
                        port[indice].requisition[port[indice].quantReq].requis = lerData();
                        //PRazo e cenas...
                        printf("\nPrazo de Devolucao: ");
                        do{
                            port[indice].requisition[port[indice].quantReq].praz = lerData();
                            if(!((port[indice].requisition[port[indice].quantReq].praz.ano > port[indice].requisition[port[indice].quantReq].requis.ano) || (port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes > port[indice].requisition[port[indice].quantReq].requis.mes) || ( port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes == port[indice].requisition[port[indice].quantReq].requis.mes&&port[indice].requisition[port[indice].quantReq].praz.dia > port[indice].requisition[port[indice].quantReq].requis.dia))){
                                printf("\n\tData invalida.\n");
                            }
                            port[indice].requisition[port[indice].quantReq].numpraz = subtrairDatas(port[indice].requisition[port[indice].quantReq].requis,port[indice].requisition[port[indice].quantReq].praz);
                            if(port[indice].requisition[port[indice].quantReq].numpraz >30){
                                    date = -1;
                                    printf("\nErro. O prazo maximo sao 30 dias.");
                            }
                        }while( (date == -1)||(!((port[indice].requisition[port[indice].quantReq].praz.ano > port[indice].requisition[port[indice].quantReq].requis.ano) || (port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes > port[indice].requisition[port[indice].quantReq].requis.mes) || ( port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes == port[indice].requisition[port[indice].quantReq].requis.mes&&port[indice].requisition[port[indice].quantReq].praz.dia > port[indice].requisition[port[indice].quantReq].requis.dia))));
                        //Prazo de devolução tem de ser superior ao dia de requisição
                        
                        
                        //Nome Utente
                        printf("\nNome do utente: ");
                        lerString(port[indice].requisition[port[indice].quantReq].nomedoutente, MAX_NOME);
                        
                        //Typo Utente
                        printf("\nTipo de utente: ");
                        do{
                            lerString(port[indice].requisition[port[indice].quantReq].typeut, 25);
                            for(h = 0; h < strlen(port[indice].requisition[port[indice].quantReq].typeut);h++){
                                port[indice].requisition[port[indice].quantReq].typeut[h] = tolower(port[indice].requisition[port[indice].quantReq].typeut[h]);
                            }
                            if(strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ESTUD)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_DOCE)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ADM)!= 0){
                                printf("\nErro tipo de utente invalido (estudante, docente, tecnico administrativo).Insira novamente: ");
                            }
                        }while(strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ESTUD)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_DOCE)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ADM)!= 0);
                        
                        // Numero de utente
                        printf("\nNumero do utente: ");
                        do{
                            numutente = lerUtente(cont, port);
                        }while(numutente == -1);
                        if(numutente == -2){
                            printf("\n\t\t\t\tRegisto cancelado!\n");
                        }
                        else{       
                            port[indice].requisition[port[indice].quantReq].numutent = numutente;
                            (port[indice].quantReq)++;
                            (port[indice].indicereq)++;
                            ((*cont).requisativas)++;
                            (cont->totalderequisefet)++;
                            (cont->portatedisp)--;
                            strcpy(port[indice].requisition[port[indice].indicereq].statreq, STAT_ATIV);
                            strcpy(port[indice].stat, STAT_REQ);
                        }
                    }
                    else{
                        printf("\nPortatil indisponivel\n");
                    }
                    i = (*cont).portatexist;
                }

            }
            if(indice == -1){
                printf("\nId nao existe\n");
            }

    }
    else{
        printf("\nNao ha computadores disponiveis!\n");
    }
}
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i=0,u=0,o=0;
    for(i=0; i<cont->portatexist;i++){
        printf("\nComputador: %s",port[i].desig);
        for(u=0; u< port[i].quantReq;u++){      // requi e um vetor, logo temos de fazer outro for
            printf("\n\tData requisicao: %d/%d/%d",port[i].requisition[u].requis.dia,port[i].requisition[u].requis.mes,port[i].requisition[u].requis.ano);
            printf("\n\tEstado da requisicao: %s",port[i].requisition[u].statreq);
            if(strcmp(port[i].requisition[u].statreq, STAT_ATIV)==0){
                printf("\n\tDia maximo de Devolucao: %d/%d/%d",port[i].requisition[u].praz.dia,port[i].requisition[u].praz.mes,port[i].requisition[u].praz.ano);
                printf("\n\tDuracao maxima da requisicao: %d",port[i].requisition[u].numpraz);
                printf("\n\tLocal: ---\n\tMulta: ---\n");
            }
            else{
                printf("\n\tDevolucao: %d/%d/%d",port[i].requisition[u].devol.dia,port[i].requisition[u].devol.mes,port[i].requisition[u].devol.ano);
                printf("\n\tDuracao da  requisicao: %d",port[i].requisition[u].prazreal);
                printf("\n\tLocal: %s\n\tMulta: %d\n",port[i].requisition[u].local,port[i].requisition[u].finee);
            }
        }
    }
}


void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i,u,desig=0, aux = 0;
    printf("\nQuantos pcs deseja inserir: ");
    u = lerInteiro(0,MAXX);
    u += cont->portatexist;
    if(u>30){
        u -= 30;
        printf("Nao e possivel adicionar mais computadores.\n%d a mais do numero limite.\n",u);
    }
    else{
        for(i = (*cont).portatexist; i<u; i++){
            
            do{    
                printf("\nId: ");
                port[i].portId = lerID(cont,port);
            }while(port[i].portId == -1);
            
            
            do{   
                printf("\nDesignacao do portatil: ");
                desig = lerDesignacao(cont,port,i);
            }while(desig == -1);

            printf("\n\tProcessador: ");
            do{
                lerString(port[i].process, 3);
                if(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0){
                    printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
                }
            }while(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0);
            
            printf("\n\tEstado: ");
            do{
               lerString(port[i].stat,NMAXX);
                for(aux = 0; aux < strlen(port[i].stat); aux++){
                    port[i].stat[aux] = tolower(port[i].stat[aux]);
                }
                if(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0){
                    printf("\nEstado invalido (avariado, requisitado, disponivel). Insira novamente: ");
                    
                }
            }while(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0);
        
            printf("\n\tQuantidade de avarias: ");
            do{
                port[i].quantAvarias  =   lerInteiro(0,MAXIMUS);
                if(strcmp(STAT_AVA, port[i].stat)==0 && port[i].quantAvarias==0){
                    printf("\nErro nao pode ter 0 avarias e estar avariado.Tente de novo: ");
                }
            }while(strcmp(STAT_AVA, port[i].stat)==0 && port[i].quantAvarias==0);
            printf("\n\tLocalizacao: ");
            
            do{
                lerString(port[i].local,NMAXX);
                for(aux = 0; aux < strlen(port[i].local); aux++){
                    port[i].local[aux] = tolower(port[i].local[aux]);
                }
                if(strcmp(CAMPUS1 , port[i].local)!=0 && strcmp(CAMPUS2, port[i].local)!=0 && strcmp(CAMPUS5, port[i].local)!=0 && strcmp(RESID, port[i].local)!=0 ){
                    printf("\nLocalizacao invalida (Campus1, Campus2, Campus5 ou Residencias). Insira novamente: ");
                }
            }while(strcmp(CAMPUS1 , port[i].local)!=0 && strcmp(CAMPUS2, port[i].local)!=0 && strcmp(CAMPUS5, port[i].local)!=0 && strcmp(RESID, port[i].local)!=0);
            
            printf("\n\tData de aquisicao: ");
            port[i].aquis = lerData();
            
            printf("\n\tValor do equipamento: ");
            port[i].valuequi = lerFloat(MAXX,MAXIMUS);
            
            port[i].quantReq = 0;
            port[i].indicereq = -1;
            (*cont).portatexist = i ;

        }
        (*cont).portatexist = i ;
        (*cont).portatedisp = 0;
        for(i = 0; i< (*cont).portatexist;i++){
            if(strcmp(port[i].stat,STAT_DISP)==0){
                (*cont).portatedisp++;
            }
        }
    }
    
}

//________________________________________________________________________________________________________________________________________________________________
void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX]){
    FILE *fc,*fp;
    //ficheiro contadores, ficheiro portateis
    int confirmacao = 1;
    char continuar;

    if(cont.portatexist == 0){
        printf("\nNão há registo(gravar nada), pretende continuar?(Y/N) ");
        do{
            continuar = getchar();
            continuar = toupper(continuar);
        }while(continuar != 'Y' && continuar != 'N');
        switch (continuar){

        case 'Y':
            confirmacao = 1 ;
            break;
        
        case 'N':
            confirmacao = 0 ;
            break;

        }
    }
    if(confirmacao == 0){
        printf("\nPor favor comece por registar computadores!");
    }
    else{
        fc = fopen("contadores.dat", "wb");
        if (fc==NULL){
            printf("\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(&cont,sizeof(CONTADOREs),1,fc);
            fclose(fc);
        }

        fp = fopen("portateis.dat", "wb");
        if(fp == NULL){
            printf("\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(port,sizeof(PORTATIl),cont.portatexist,fp);
            fclose(fp);
        }
    }
}

void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX]){
    FILE *fc,*fp;
    char problem = 'K';
    fc = fopen("contadores.dat", "rb");
    if (fc==NULL){
        printf("\nErro ao abrir o ficheiro!\n");
        problem = 'O';
    }
    else{
        fread(&(*cont),sizeof(CONTADOREs),1,fc);
        fclose(fc);
    }
    

    fp = fopen("portateis.dat", "rb");
    if (fp==NULL){
        printf("\nErro ao abrir o ficheiro!\n");
    }
    else{
        if(problem == 'O'){
            fread(port,sizeof(PORTATIl),30,fp);
        }
        else{
            fread(port,sizeof(PORTATIl),(*cont).portatexist,fp);
            fclose(fp);
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

int lerID(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i, id=0;
    id = lerInteiro(UM,MAXIMUS);
    for (i=0; i<(*cont).portatexist; i++){
        if( id == port[i].portId){
            id = -1;
            i = (*cont).portatexist;
            printf("\nID invalido, ja existe!\n");
        }
    }
    return id;
}

int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i, ut=0,u=0;
    char conf, confdoconf;
    ut = lerInteiro(UM,MAXIMUS);
    for (i=0; i<(*cont).portatexist; i++){
        for(u=0; u<port[i].quantReq; u++){
            if( ut == port[i].requisition[u].numutent && strcmp(port[i].requisition[u].statreq,STAT_ATIV)==0){
                printf("\nO utente com o numero %d, ja tem uma requisicao ativa!",port[i].requisition[u].numutent);
                u = port[i].quantReq;
                i = (*cont).portatexist;
                printf("\n\tDeseja continuar com o registo com este numero?(S/N)");
                do{
                    conf = getchar();
                    conf = toupper(conf);
                }while(conf != 'S'&& conf != 'N');
            }
        }
    }
    if(conf == 'N'){
        ut = -2;
    }
    if(conf == 'S'){
        printf("\n\t\tDeseja utilizar este numero mesmo com os avisos previamente alertados?(S/N)");
        do{
            confdoconf = getchar();
            confdoconf = toupper(confdoconf);
        }while(confdoconf != 'S' && confdoconf != 'N');
        if(confdoconf == 'S'){}
        else{
            ut = -1;
        }
    }
    return ut;
}

int lerDesignacao(CONTADOREs *cont, PORTATIl port[MAXX], int pos){
    int i, des = 0;
    char design[MAX_DESIG];
    lerString(design, MAX_DESIG);
    for (i=0; i < (*cont).portatexist; i++){
        if (strcmp(port[i].desig, design)==0){  
            des = -1;
            i = (*cont).portatexist;
            printf("\nErro, designacao existente.\n");
        }
    }
    if(des != -1){
        strcpy(port[pos].desig, design);
    }
    return des;
}
int subtrairDatas(DATa d1, DATa d2){
    int numerodedias=0,numerodedias1=0,numerodedias2 =0, numerodemeses =0, numerodeanos = 0, diffdias = 0;
    
    if((d2.ano > d1.ano )|| (d2.ano==d1.ano && d2.mes > d1.mes )|| (d2.ano==d1.ano && d2.mes==d1.mes && d2.dia >d1.dia)){
        if(d2.ano==d1.ano && d2.mes==d1.mes && d2.dia >d1.dia){
            numerodedias = d2.dia - d1.dia;
        }
        if(d2.ano==d1.ano && d2.mes > d1.mes){
            for(numerodemeses = d1.mes; numerodemeses<d2.mes; numerodemeses++){
                switch(numerodemeses){
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        numerodedias+=31;
                        break;
                    case 2:
                        if((d2.ano%400==0) || (d2.ano%4==0 && d2.ano%100!=0)){
                            numerodedias+= 29;
                        }       
                        else{
                            numerodedias+= 28;
                        }
                        break;
                    default:
                        numerodedias += 30;
                }
            }
            numerodedias += (d2.dia-d1.dia);
        }
        if(d2.ano > d1.ano ){
            for(numerodeanos = d1.ano; numerodeanos < d2.ano; numerodeanos++){
                if((numerodeanos%400==0) || (numerodeanos%4==0 && numerodeanos%100!=0)){
                    numerodedias += 366;
                }
                else{
                    numerodedias += 365;
                }
            }
            if(d2.mes > d1.mes){
                for(numerodemeses = d1.mes; numerodemeses<d2.mes; numerodemeses++){
                    switch(numerodemeses){
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                            numerodedias+=31;
                            break;
                        case 2:
                            if((d2.ano%400==0) || (d2.ano%4==0 && d2.ano%100!=0)){
                                numerodedias+= 29;
                            }       
                            else{
                                numerodedias+= 28;
                            }
                            break;
                        default:
                            numerodedias += 30;
                    }
                }
                numerodedias += (d2.dia-d1.dia);
            }
            else{
                for(numerodemeses = d1.mes; numerodemeses!=0; numerodemeses--){
                    switch(numerodemeses){
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                            numerodedias1+=31;
                            break;
                        case 2:
                            if((d1.ano%400==0) || (d1.ano%4==0 && d1.ano%100!=0)){
                                numerodedias1+= 29;
                            }       
                            else{
                                numerodedias1+= 28;
                            }
                            break;
                        default:
                            numerodedias1 += 30;
                    }
                }
                for(numerodemeses = d2.mes; numerodemeses!=0; numerodemeses--){
                    switch(numerodemeses){
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                            numerodedias2+=31;
                            break;
                        case 2:
                            if((d2.ano%400==0) || (d2.ano%4==0 && d2.ano%100!=0)){
                                numerodedias2+= 29;
                            }       
                            else{
                                numerodedias2+= 28;
                            }
                            break;
                        default:
                            numerodedias += 30;
                    }
                }
                numerodedias += (numerodedias2 - numerodedias1);
            }

        }
 
    }
    else{
        numerodedias = -1;
    }
    return numerodedias;
}

DATa lerData(void){
    DATa data;
    int maxDias=31;
    printf("-Indique a Data-\n");
    printf("Ano: ");
    data.ano = lerInteiro(MENOR_ANO, MAIOR_ANO);

    printf("Mes: ");
    data.mes = lerInteiro(UM,12);
    switch(data.mes){
    case 2:
        if((data.ano%400==0) || (data.ano%4==0 && data.ano%100!=0)){
            maxDias = 29;       //ano bissexto
        }
        else{
            maxDias = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDias = 30;
    }

    printf("Dia: ");
    data.dia = lerInteiro(UM, maxDias);

    return data;
}

int lerInteiro(int min, int max){
    int numero, controlo;
    do
    {
        controlo = scanf("%d", &numero);
        limpaBufferStdin(); 
        if (numero<min || numero>max || controlo==0){
            printf("\nValor invalido! Insira novamente: ");
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
        if(numero<min || numero>max || controlo==0){
            printf("\nValor invalido! Insira novamente: ");
        }
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

