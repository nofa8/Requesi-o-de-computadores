#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constantes.h"
#include "leituraemais.h"
#include "avarias.h"
#include "requi.h"
void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava){
    FILE *fc,*fp,*fa;
    //ficheiro contadores, ficheiro portateis
    int confirmacao = 1;
    char continuar;
    if(cont.portatexist == 0){
        printf("\nNão há registo(gravar nada), pretende continuar?(S/N) ");
        do{
            continuar = getchar();
            continuar = toupper(continuar);
        }while(continuar != 'S' && continuar != 'N');
        switch (continuar){

        case 'S':
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
        }
        fclose(fc);

        fp = fopen("portateis.dat", "wb");
        if(fp == NULL){
            printf("\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(port,sizeof(PORTATIl),cont.portatexist,fp);
            fwrite(req,sizeof(REQUi),cont.totalderequisefet,fp);
        }
        fclose(fp);

        fa = fopen("avarias.dat","wb");
        if(fa == NULL){
            printf("\n\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(ava,sizeof(AVARIAs),cont.totaldeavarias,fa);
        }
        fclose(fa);
    }
}

void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req, AVARIAs *ava){
    FILE *fc,*fp,*fa;
    int confirm;
    char problem = 'K';
    fc = fopen("contadores.dat", "rb");
    if (fc==NULL){
        printf("\nErro ao abrir o ficheiro!\n");
        problem = 'O';
    }
    else{
        fread(&(*cont),sizeof(CONTADOREs),1,fc);
    }
    fclose(fc);

    fp = fopen("portateis.dat", "rb");
    if (fp==NULL){
        printf("\nErro ao abrir o ficheiro!\n");
    }
    else{
        if(problem == 'O'){
            printf("\n\tNao e possivel retirar do ficheiro a informacao.\n");
        }
        else{
            req = aumentarReq(cont,req,&confirm);
            if(-1 == confirm){
                //.....
                problem = 'N';
            }
            else{
                ava = aumentarava(cont,ava,&confirm);
                if(confirm == -1){
                    //....
                    problem = 'N';
                }
                else{
                    if(problem == 'N'){
                        printf("\n\tNao e possivel erro memoria.\n");
                    }
                    else{
                        fread(port,sizeof(PORTATIl),cont->portatexist,fp);
                        fread(req,sizeof(REQUi),cont->totalderequisefet,fp);

                    }
                }
            }
        }

    }
    fclose(fp);
    if(problem != 'O'&& problem != 'N'){
        fa = fopen("avarias.dat","wb");
        if(fa == NULL){
            printf("\n\nErro ao abrir o ficheiro!\n");
        }
        else{
            fread(ava,sizeof(AVARIAs),cont->totaldeavarias,fa);
        }
        fclose(fa);
    }
}







void limpaBufferStdin(void){
    char lixo;
    do
    {
        lixo=getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}

int lerID(CONTADOREs *cont, PORTATIl port[MAXX], int idtemp){
    int i, id=-1;
    for (i=0; i<(*cont).portatexist; i++){
        if( idtemp == port[i].portId){
            id = i;
            i = (*cont).portatexist;
        }
    }
    return id;
}

int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i, ut=0,u=0;
    char conf, confdoconf;
    ut = lerInteiro(UM,MAXIMUS);
    for (i=0; i<(*cont).totalderequisefet; i++){
            if( ut == req[i].numutent && strcmp(req[i].statreq,STAT_ATIV)==0){
                printf("\nO utente com o numero %d, ja tem uma requisicao ativa!",req[i].numutent);

                i = (*cont).totalderequisefet;
                printf("\n\tDeseja continuar com o registo com este numero?(S/N)");
                do{
                    conf = getchar();
                    conf = toupper(conf);
                }while(conf != 'S'&& conf != 'N');
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

int procurarReq(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i, cod = -1, u;
    char code[NMAXX];
    lerString(code, NMAXX);
    for (i=0; i < (*cont).totalderequisefet; i++){
        if(strcmp(req[i].requiscode, code)==0){
            cod = i;
            i = (*cont).totalderequisefet;
        }
    }

    return cod; //devolve indice da requesicao
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
                numerodedias1 += d1.dia;
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
                numerodedias2 += d2.dia;
                numerodedias += (numerodedias2 - numerodedias1);
            }

        }

    }
    else{
        numerodedias = -1;
    }
    return numerodedias;
}

DATa sumD(DATa d1, int d){
    int aux,aux1,aux2,aux3;
    DATa data;
    switch(d1.mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            aux = d1.dia+7;
            aux1 = aux -31;
            if(aux1>0){
                data.mes = d1.mes +1;
                data.dia = aux1;
                data.ano = d1.ano;
            }
            else{
                data.mes = d1.mes;
                data.dia = aux,
                data.ano = d1.ano;
            }
            break;
        case 12:
            aux = d1.dia+7;
            aux1 = aux -31;
            if(aux1 > 0){
                data.mes = 1;
                data.dia = aux1;
                data.ano = d1.ano++;
            }
            else{
                data.dia = aux;
                data.mes = d1.mes;
                data.ano = d1.ano;
            }
            break;
        case 2:
            if((d1.ano%400==0) || (d1.ano%4==0 && d1.ano%100!=0)){
                aux =d1.dia+7 ;
                aux1 = aux -29;
                if(aux1 >0){
                    data.mes = d1.mes++;
                    data.dia = aux1;
                    data.ano =d1.ano;
                }
                else{
                    data.mes = d1.mes;
                    data.dia = aux;
                    data.ano = d1.ano;
                }
            }
            else{
                aux = d1.dia + 7;
                aux1 = aux -28;
                if(aux1 > 0){
                    data.mes = d1.mes++;
                    data.dia = aux1;
                    data.ano = d1.ano;
                }
                else{
                    data.mes = d1.mes;
                    data.dia = aux;
                    data.ano = d1.ano;
                }
            }
            break;


        default:
            aux = d1.dia+7;
            aux1 = aux -30;
            if(aux1>0){
                data.mes = d1.mes +1;
                data.dia = aux1;
                data.ano = d1.ano;
            }
            else{
                data.mes = d1.mes;
                data.dia = aux,
                data.ano = d1.ano;
            }
    }
    return data;
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
