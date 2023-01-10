#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constantes.h"
#include "leituraemais.h"
#include "menus.h"
#include "requi.h"



// looks good !!!
void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX],REQUi *req){
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
                for(u = 0; u < cont->totalderequisefet; u++){
                    if(req[u].portid == port2[i].portId){
                        if(strcmp(req[u].statreq,STAT_CONC)){
                            printf("\t\tTipo de utente: %15s\tPrazo de requisicao: %d/%d/%d\n", req[u].typeut, req[u].praz.dia,req[u].praz.mes,req[u].praz.ano);
                        }
                        else{
                            printf("\t\tTipo de utente: %15s\tDia da devolucao: %d/%d/%d\n", req[u].typeut, req[u].devol.dia,req[u].devol.mes,req[u].devol.ano);
                        }
                    }
                }
            }
        }

    }
    else{
        printf("\nNao ha computadores!\n");
    }
}


//Tá bom! ! !
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava){
    int i,u,desig=0, aux = 0,prob = -1, tempid = -1;
    printf("\nQuantos pcs deseja inserir: ");
    u = lerInteiro(0,MAXX);
    u += cont->portatexist;
    if(u>30){
        u -= 30;
        printf("Nao e possivel adicionar mais computadores.\n%d a mais do numero limite.\n",u);
    }
    else{
        for(i = (*cont).portatexist; i<u; i++){
            port[i].quantAvarias = 0;
            port[i].quantDev = 0;
            port[i].quantDiasReq=0;
            printf("\n\n\tId: ");
            do{
                tempid = lerInteiro(UM,MAXIMUS);
                prob = lerID(cont,port,tempid);
                if(prob != -1){
                    printf("\nID invalido, ja existe!\n");
                }
            }while(prob != -1);
            port[i].portId = tempid;

            do{
                printf("\nDesignacao do portatil: ");
                desig = lerDesignacao(cont,port,i);
            }while(desig == -1);

            printf("\n\tProcessador: ");
            do{
                lerString(port[i].process, 4);
                if(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0){
                    printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
                }
            }while(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0);


            printf("\n\tQuantidade de memoria: ");

            port[i].memoria = lerInteiro(UM,MAXIMUS);

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

            //estado
            strcpy(port[i].stat,STAT_DISP);
            /*
            do{
                lerString(port[i].stat,NMAXX);
                for(aux = 0; aux < strlen(port[i].stat); aux++){
                    port[i].stat[aux] = tolower(port[i].stat[aux]);
                }
                if(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0){
                    printf("\nEstado invalido (avariado, requisitado, disponivel). Insira novamente: ");

                }
            }while(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0);
            if(strcmp(STAT_AVA, port[i].stat)==0){

                regAva(cont, port,i,ava);  // adicionar indice
            }
            */

            printf("\n\tValor do equipamento: ");
            port[i].valuequi = lerFloat(MAXX,MAXIMUS);

            port[i].quantReq = 0;
            (*cont).portatexist = i + 1 ;

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
// por alterar
void dadosEstatisticos(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req){      //funcao so e acionada se houverem pcs
    int opcao, quant = 0, i,aux1,aux3;
    int numerodeMultas=0, auxdata=0,referencia = -1,*indicereqderef,*confindice,numdemin=0,u=-1;
    int quantEst = 0, quantDoce = 0, quantTec = 0;
    float atalmedia,totalMultas=0,percentagem;
    char processador[3];
    DATa base;
    base.dia = 1;
    base.mes = 1;
    base.ano = 2010;
    indicereqderef=NULL;
    confindice = indicereqderef;

    printf("\n\t1 - %% de portateis com um processador\n\t2 - Custo medio de cada multa\n\t3 - Tipo(s) de utente(s) com a menor quantidade de requisicoes efetuadas\n\t4 - Devolucao(coes) mais recente(s)\n\t0 - Sair\n");
    printf("\t\tOpcao -> ");
    opcao = lerInteiro(0, 4);
    switch(opcao){

    case 1:
        printf("\nIndique o processador: ");
        do{
            lerString(processador, 3);
            if(strcmp(I3, processador) != 0 && strcmp(I5, processador) != 0 && strcmp(I7, processador) != 0){
                printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
            }
        }while(strcmp(I3, processador) != 0 && strcmp(I5, processador) != 0 && strcmp(I7, processador) != 0);
        for(i=0; i < (*cont).portatexist; i++){
            if(strcmp(processador, port[i].process)==0){
                quant++;
            }
        }
        percentagem = 100 * quant / ((*cont).portatexist);
        printf("A percentagem de processadores %s e %.1f%%.\n", processador, percentagem);
        break;
    case 2:
        for(aux1 = 0; aux1 < (*cont).totalderequisefet; aux1++){
                if(req[aux1].finee > 0){
                    totalMultas += req[aux1].finee;
                    numerodeMultas++;
                }
        }
        atalmedia = (float)totalMultas/numerodeMultas;
        printf("\n\tO custo media de cada multa e %f.",atalmedia);
        break;
    case 3:                                     // ainda nao terminado!!!! /////
        if( (cont->totalderequisefet) == 0){
            printf("\nAinda nao foram realizadas requisicoes.\n");
        }
        else{

            for(i=0; i < (cont->totalderequisefet); i++){

                    if(strcmp(TIPO_ESTUD, req[i].typeut) == 0){
                        quantEst ++;
                    }
                    if(strcmp(TIPO_DOCE, req[i].typeut) == 0){
                        quantDoce ++;
                    }
                    if(strcmp(TIPO_ADM, req[i].typeut) == 0){
                        quantTec ++;
                    }

            }
            if(quantEst < quantDoce){
                if(quantEst < quantTec){
                    printf("\n\tO tipo de utente em minoria e o estudante: %d requisicao(coes).",quantEst);
                }
                else{
                    if(quantEst > quantTec){
                        printf("\n\tO tipo de utente em minoria e o tecnico administrativo: %d requisicao(coes).",quantTec);
                    }
                    else{
                        printf("\n\tOs tipos de utente em minoria sao neste caso o tecnico administrativo e o estudante: %d requisicao(coes).",quantTec);
                    }
                }
            }
            else{
                if(quantDoce == quantEst){
                    if(quantEst < quantTec){
                    printf("\n\tOs tipos de utente em minoria sao o estudante e o docente: %d requisicao(coes).",quantEst);
                    }
                    else{
                        if(quantEst == quantTec){
                            printf("\n\tOs utentes estudante, docente e tecnico administrativo tem a mesma quantidade de requisicoes : %d requisicao(coes).",quantTec);
                        }
                        else{
                            printf("\n\tO tipo de utente em minoria e o tecnico administrativo: %d requisicao(coes).",quantTec);
                        }
                    }
                }
                else{
                    if(quantDoce < quantTec){
                        printf("\n\tO tipo de utente em minoria e o docente: %d requisicao(coes).",quantDoce);
                    }
                    else{
                        if(quantDoce == quantTec){
                            printf("\n\tOs tipos de utente em minoria sao o tecnico administrativo e docente: %d requisicao(coes).",quantTec);
                        }
                        else{
                            printf("\n\tO tipo de utente em minoria e o tecnico administrativo: %d requisicao(coes).",quantTec);
                        }
                    }
                }
            }
        }
        break;
    case 4:
        if(cont->totalderequisefet!=0){      //ids possui ids de pcs já  registados e devolvidos
            for(aux3 = 0;aux3<cont->totalderequisefet;aux3++){
                if(strcmp(req[aux3].statreq,STAT_CONC)){
                    auxdata = subtrairDatas(base,req[aux3].devol);
                    if(auxdata > referencia){
                        referencia = auxdata;
                    }
                }
            }
            for(aux3 = 0;aux3<cont->totalderequisefet;aux3++){
                if(strcmp(req[aux3].statreq,STAT_CONC)){
                    auxdata = subtrairDatas(base,req[aux3].devol);
                    if(auxdata == referencia){
                        numdemin ++;
                        u++;
                        indicereqderef = realloc(indicereqderef,(numdemin)*sizeof(int));
                        if(indicereqderef == NULL){
                            printf("\nErro de memoria!\n");
                        }
                        else{
                            indicereqderef[u]=aux3;
                        }

                    }
                }
            }
            printf("\nA(s) ultima(s) requisicao(coes) é(sao):");
            for(aux3 = u; aux3 >=0;aux3--){
                printf("\nId:%d\n\t\tDia de devolucao: %d - %d - %d",req[indicereqderef[aux3]].portid,req[indicereqderef[aux3]].devol.dia,req[indicereqderef[aux3]].devol.mes,req[indicereqderef[aux3]].devol.ano);
            }
        }
        break;
    default:
        printf("\n\n\n\n");
    }

}

//________________________________________________________________________________________________________________________________________________________________


REQUi *aumentarReq(CONTADOREs *cont,REQUi *req,int *confirm){
    int aaumentar = cont->totalderequisefet+1;
    REQUi *r;
    r = req;

    req = realloc(req, sizeof(REQUi)*aaumentar);
    if(req == NULL){
        printf("\n\tErro ao alocar memoria!\n");
        req = r;
        *confirm = -1;
    }
    else{
        *confirm = 1;
    }
    return req;
}

//parece que sim
void regRq(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i= 0,l=0,h = 0,u = 0,idTemporario = 0, indice=-1, numutente = 0, date = 0,confirm;
    //REQUi *r;
    //r = req;
    if(cont->totalderequisefet != 0){

            if((*cont).portatedisp >0){
                printf("\nInsira o numero de identificacao do portatil: ");
                idTemporario = lerInteiro(UM,MAXIMUS);
                for (l=0;l<(*cont).portatexist;l++){
                    if(port[l].portId == idTemporario){
                        indice = l;

                        if(strcmp(port[indice].stat,STAT_DISP)==0){
                            printf("\n\t%d",cont->totalderequisefet+1);
                            req = aumentarReq(cont,req,&confirm);
                            if(confirm == -1){
                                //....
                            }
                            else{
                                //Codigo de Requisicao

                                printf("\nCodigo de requisicao: ");
                                do{
                                    lerString(req[(*cont).totalderequisefet].requiscode,NMAXX);
                                    for(i = 0; i <(*cont).totalderequisefet;i++){
                                            if(strcmp(req[(*cont).totalderequisefet].requiscode,req[i].requiscode)==0){
                                                    printf("\nCodigo de requisicao indisponivel.\n");
                                                    u = -1;
                                                    i = cont->portatexist;
                                            }
                                    }
                                }while(u == -1);
                                //Data Requisição
                                if(port[indice].quantReq == 0){
                                printf("\n\tData de Requisicao: ");
                                do{
                                    req[cont->totalderequisefet].requis = lerData();
                                    if(port[indice].quantReq != 0){
                                        if((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia)){
                                            printf("\n\tErro data invalida nao pode ser inferior ao dia de aquisicao.");
                                        }
                                    }
                                }while((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia));

                                }
                                else{
                                    printf("\nData de Requisicao: ");
                                    do{
                                        req[cont->totalderequisefet].requis = lerData();
                                        if(port[indice].quantReq != 0){
                                            if((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia)){
                                                printf("\n\tErro data invalida nao pode ser inferior ao dia de aquisicao.");
                                            }
                                        }
                                        else{
                                            if((port[indice].ultimadev.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes == req[cont->totalderequisefet].requis.mes && port[indice].ultimadev.dia > req[cont->totalderequisefet].requis.dia)){
                                                printf("\n\tErro data invalida nao pode ser inferior ao dia da ultima devolucao. Insira Novamente: ");
                                            }
                                        }

                                    }while((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia) || (port[indice].ultimadev.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes == req[cont->totalderequisefet].requis.mes && port[indice].ultimadev.dia > req[cont->totalderequisefet].requis.dia));
                                    //PRazo e cenas...
                                }
                                printf("\nPrazo de Devolucao: ");
                                do{
                                    date = 0;
                                    req[cont->totalderequisefet].praz = lerData();
                                    if(((req[cont->totalderequisefet].praz.ano < req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes < req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia < req[cont->totalderequisefet].requis.dia))){
                                        printf("\n\tData invalida.\n");
                                    }
                                    req[cont->totalderequisefet].numpraz = subtrairDatas(req[cont->totalderequisefet].requis,req[cont->totalderequisefet].praz);
                                    if(req[cont->totalderequisefet].numpraz >30 ){
                                            date = -1;
                                            printf("\nErro. O prazo maximo sao 30 dias.");
                                    }
                                }while((date == -1)||((req[cont->totalderequisefet].praz.ano < req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes < req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia < req[cont->totalderequisefet].requis.dia)));
                                //Prazo de devolução tem de ser superior ao dia de requisição


                                //Nome Utente
                                printf("\nNome do utente: ");
                                lerString(req[cont->totalderequisefet].nomedoutente, MAX_NOME);

                                //Typo Utente
                                printf("\nTipo de utente: ");
                                do{
                                    lerString(req[cont->totalderequisefet].typeut, 25);
                                    for(h = 0; h < strlen(req[cont->totalderequisefet].typeut);h++){
                                        req[cont->totalderequisefet].typeut[h] = tolower(req[cont->totalderequisefet].typeut[h]);
                                    }
                                    if( strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0){
                                        printf("\nErro tipo de utente invalido (estudante, docente, tecnico administrativo).Insira novamente: ");
                                    }
                                }while(strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0);

                                // Numero de utente
                                printf("\nNumero do utente: ");
                                do{
                                    numutente = lerUtente(cont, port,req);
                                }while(numutente == -1);
                                if(numutente == -2){
                                    printf("\n\t\t\t\tRegisto cancelado!\n");
                                }
                                else{
                                    req[cont->totalderequisefet].numutent = numutente;
                                    (port[indice].quantReq)++;
                                    strcpy(req[cont->totalderequisefet].statreq, STAT_ATIV);
                                    req[cont->totalderequisefet].portid = port[indice].portId;
                                    req[cont->totalderequisefet].indiceport = indice;
                                    ((*cont).requisativas)++;
                                    (cont->totalderequisefet)++;
                                    (cont->portatedisp)--;
                                    strcpy(port[indice].stat, STAT_REQ);

                                }
                            }
                        }
                        else{
                            printf("\nPortatil indisponivel\n");
                        }
                        l = (*cont).portatexist;
                        //fim do ciclo
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
    else{
        if((*cont).portatedisp >0){
                printf("\nInsira o numero de identificacao do portatil: ");
                idTemporario = lerInteiro(UM,MAXIMUS);
                for (l=0;l<(*cont).portatexist;l++){
                    if(port[l].portId == idTemporario){
                        indice = l;

                        if(strcmp(port[indice].stat,STAT_DISP)==0){

                            req = realloc(req,((*cont).totalderequisefet+1)*sizeof(REQUi));
                            //adiciona espaço
                            //Codigo de Requisicao

                            printf("\nCodigo de requisicao: ");
                            do{
                                lerString(req[(*cont).totalderequisefet].requiscode,NMAXX);
                                for(i = 0; i <(*cont).totalderequisefet;i++){
                                        if(strcmp(req[(*cont).totalderequisefet].requiscode,req[i].requiscode)==0){
                                                printf("\nCodigo de requisicao indisponivel.\n");
                                                u = -1;
                                                i = cont->portatexist;
                                        }
                                }
                            }while(u == -1);
                            //Data Requisição
                            printf("\nData de Requisicao: ");
                            do{
                                req[cont->totalderequisefet].requis = lerData();
                                if(port[indice].quantReq != 0){
                                    if((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia)){
                                        printf("\n\tErro data invalida nao pode ser inferior ao dia de aquisicao.");
                                    }
                                }
                            }while((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia));
                            //PRazo e cenas...
                            printf("\nPrazo de Devolucao: ");
                            do{
                                req[cont->totalderequisefet].praz = lerData();
                                if(((req[cont->totalderequisefet].praz.ano < req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes < req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia <= req[cont->totalderequisefet].requis.dia))){
                                    printf("\n\tData invalida.\n");
                                }
                                req[cont->totalderequisefet].numpraz = subtrairDatas(req[cont->totalderequisefet].requis,req[cont->totalderequisefet].praz);
                                if(req[cont->totalderequisefet].numpraz >30 ){
                                        date = -1;
                                        printf("\nErro. O prazo maximo sao 30 dias.");
                                }
                            }while( (date == -1)||((req[cont->totalderequisefet].praz.ano < req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes < req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia <= req[cont->totalderequisefet].requis.dia)));
                            //Prazo de devolução tem de ser superior ao dia de requisição


                            //Nome Utente
                            printf("\nNome do utente: ");
                            lerString(req[cont->totalderequisefet].nomedoutente, MAX_NOME);

                            //Typo Utente
                            printf("\nTipo de utente: ");
                            do{
                                lerString(req[cont->totalderequisefet].typeut, 25);
                                for(h = 0; h < strlen(req[cont->totalderequisefet].typeut);h++){
                                    req[cont->totalderequisefet].typeut[h] = tolower(req[cont->totalderequisefet].typeut[h]);
                                }
                                if( strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0){
                                    printf("\nErro tipo de utente invalido (estudante, docente, tecnico administrativo).Insira novamente: ");
                                }
                            }while(strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0);

                            // Numero de utente
                            printf("\nNumero do utente: ");
                            do{
                                numutente = lerUtente(cont, port,req);
                            }while(numutente == -1);
                            if(numutente == -2){
                                printf("\n\t\t\t\tRegisto cancelado!\n");
                            }
                            else{
                                req[cont->totalderequisefet].numutent = numutente;
                                (port[indice].quantReq)++;
                                strcpy(req[cont->totalderequisefet].statreq, STAT_ATIV);
                                req[cont->totalderequisefet].portid = port[indice].portId;
                                req[cont->totalderequisefet].indiceport = indice;
                                ((*cont).requisativas)++;
                                (cont->totalderequisefet)++;
                                (cont->portatedisp)--;
                                strcpy(port[indice].stat, STAT_REQ);

                            }
                        }
                        else{
                            printf("\nPortatil indisponivel\n");
                        }
                        l = (*cont).portatexist;
                        //fim do ciclo
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
}
//parece que sim
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i=0,u=0,o=0;
    if(cont->totalderequisefet != 0){
        for(i=0; i<cont->totalderequisefet;i++){
            printf("\nComputador: %s",port[req[i].indiceport].desig);
                  // requi e um vetor, logo temos de fazer outro for
                printf("\n\tData requisicao: %d/%d/%d",req[i].requis.dia,req[i].requis.mes,req[i].requis.ano);
                printf("\n\tEstado da requisicao: %s",req[i].statreq);
                if(strcmp(req[i].statreq, STAT_ATIV)==0){
                    printf("\n\tDia maximo de Devolucao: %d/%d/%d",req[i].praz.dia,req[i].praz.mes,req[i].praz.ano);
                    printf("\n\tDuracao maxima da requisicao: %d",req[i].numpraz);
                    printf("\n\tLocal: ---\n\tMulta: ---\n");
                }
                else{
                    printf("\n\tDevolucao: %d/%d/%d",req[i].devol.dia,req[i].devol.mes,req[i].devol.ano);
                    printf("\n\tDuracao da  requisicao: %d",req[i].prazreal);
                    printf("\n\tLocal: %s\n\tMulta: %f\n",req[i].local,req[i].finee);
                }

        }
    }
}
