#ifndef FUNCOES_LEITURA_E_MAIS_INCLUDED
#define FUNCOES_LEITURA_E_MAIS_INCLUDED

#include "constantes.h"


void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava);
void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava);
void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
float lerFloat(float min, float max);
DATa lerData(void);
int subtrairDatas(DATa d1, DATa d2);
DATa sumD(DATa d1, int d);
int lerID(CONTADOREs *cont, PORTATIl port[MAXX], int idtemp);
int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
int lerDesignacao( CONTADOREs *cont, PORTATIl port[MAXX], int pos);



#endif