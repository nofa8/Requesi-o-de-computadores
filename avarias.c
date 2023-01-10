#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constantes.h"
#include "leituraemais.h"
#include "avarias.h"


void regRep(CONTADOREs *cont, PORTATIl port[MAXX], int indice, AVARIAs *ava){     //confirmar valor do indice
    int i=0;
    for(i= (cont->totaldeavarias-1); i >=0;i--){
        if(ava[i].indiceport == indice){
            indice = i;
            i = 0;
            printf("%d",indice);
        }
    }
    if(strcmp(ava[indice].tipoavaria,STAT_PERM)==0){
        printf("\n\tTipo de avaria permanente.\n");
    }
    else{
        do{
            ava[indice].fimavaria = lerData();
            if(ava[indice].fimavaria.ano <  ava[indice].dataavaria.ano || (ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes <  ava[indice].dataavaria.mes)||(ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes ==  ava[indice].dataavaria.mes && ava[indice].fimavaria.dia <  ava[indice].dataavaria.dia)){
                printf("\nData invalida.Data: ");
            }
        }while(ava[indice].fimavaria.ano <  ava[indice].dataavaria.ano || (ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes <  ava[indice].dataavaria.mes)||(ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes ==  ava[indice].dataavaria.mes && ava[indice].fimavaria.dia <  ava[indice].dataavaria.dia));
        ava[indice].duracaoavaria = subtrairDatas(ava[indice].dataavaria, ava[indice].fimavaria);
        strcpy(ava[indice].statavaria, STAT_CONC);      //avaria reparada
    }

}

AVARIAs *aumentarava(CONTADOREs *cont,AVARIAs *ava,int *confirm){
    int aaumentar = cont->totaldeavarias+1;
    AVARIAs *a;
    a = ava;

    ava = realloc(ava, sizeof(AVARIAs)*aaumentar);
    if(ava == NULL){
        printf("\n\tErro ao alocar memoria!\n");
        ava = a;
        *confirm = -1;
    }
    else{
        *confirm = 1;
    }
    return ava;
}

//falta so ver o comentario
void regAva(CONTADOREs *cont, PORTATIl port[MAXX],int ind, AVARIAs *ava){     //confirmar valor de indice
    int i=0,u=0,indice = -1,reallocar,confirm;
    //AVARIAs *a;
    //a = ava;
    ava = aumentarava(cont,ava,&confirm);
    if(confirm ==-1){
        //...
    }
    else{
        indice = cont->totaldeavarias;
        ava[indice].indiceport = ind;
        ava[indice].portid = port[ind].portId;

        printf("\n\tTipo de avaria: ");
        do{
            lerString(ava[indice].tipoavaria, NMAXX);
            for(i = 0; i < strlen(ava[indice].tipoavaria); i++){
                ava[indice].tipoavaria[i] = tolower(ava[indice].tipoavaria[i]);
            }
            if(strcmp(ava[indice].tipoavaria, STAT_TEMP)!= 0 && strcmp(ava[indice].tipoavaria, STAT_PERM)!= 0){
                printf("\nErro tipo de avaria invalido (temporaria ou permanente).Insira novamente: ");
            }
        }while(strcmp(ava[indice].tipoavaria, STAT_TEMP)!= 0 && strcmp(ava[indice].tipoavaria, STAT_PERM)!= 0);

        printf("\n\tData de avaria: ");
        do{
            ava[indice].dataavaria = lerData();
            if(ava[indice].dataavaria.ano < port[ava[indice].indiceport].aquis.ano ||(ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes < port[ava[indice].indiceport].aquis.mes)||ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes == port[ava[indice].indiceport].aquis.mes && ava[indice].dataavaria.dia < port[ava[indice].indiceport].aquis.dia){
                printf("\n\tErro, dia de avaria nao pode ser inferior ao dia de aquisicao.\n\t\tData:");
            }
        }while((ava[indice].dataavaria.ano < port[ava[indice].indiceport].aquis.ano ||(ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes < port[ava[indice].indiceport].aquis.mes)||ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes == port[ava[indice].indiceport].aquis.mes && ava[indice].dataavaria.dia < port[ava[indice].indiceport].aquis.dia));
        strcpy(ava[indice].statavaria, STAT_ATIV);      //avaria nao esta reparada
        port[indice].quantAvarias++;
        (cont->totaldeavarias)++;
    }
}
