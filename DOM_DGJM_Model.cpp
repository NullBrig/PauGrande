
#include <stdio.h>
#include "Dom_DGJM_Model.h"

char jvez = '0'; //Turno
int pecascompra = 14; //Pecas disponiveis para compra
int QtdPecasMesa = 0; //Quantidade de pecas na mesa
int pecasj1 = 0; //Quantidade de pecas que o Jogador 1 pode jogar
int pecasj2 = 0; //Quantidade de pecas que o Jogador 2 pode jogar
int cpu = 0; //Verifica se o 
typedef struct stpeca 
	{
	int lado1;
	int lado2;
	char status;
	} tipoPeca;
	
	tipoPeca peca[28]; 
	tipoPeca pecaaux; 

typedef struct stmesa 
	{
	int ladoE;
	int ladoD;
	char status;
	} tipomesa;
	
	tipomesa mesa[28];



void iniciarPecas()
{
	int indice = 0;
	
	for(int i=0; i<=6; i++)
	{
	
		for(int x=i; x<=6; x++)
		{
			peca[indice].lado1 = i;
			peca[indice].lado2 = x;
			peca[indice].status = NULL;
			indice++;
		}
	}
}

void inicializarMesa()
{
    for(int i = 0; i < 28; i++) 
	{
        mesa[i].ladoE = 0;
        mesa[i].ladoD = 0;
        mesa[i].status = 'A'; 
    }
}





