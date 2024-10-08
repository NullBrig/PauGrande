

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Dom_DGJM_Controller.h"
#include "DOM_DGJM_View.cpp"


void jogo() //Responsavel pelo loop do jogo
{
	int opMenuInicial, opMenuJogador, cpu;
	int retornofim = 0;
	iniciarPecas();
	inicializarMesa();
	
	opMenuInicial = menuInicial();
	if((opMenuInicial == 1) || (opMenuInicial == 2))
	{
		if(opMenuInicial == 2)
			cpu = 1;
			
		system("cls");
		embaralharPecas();
		distribuirPecas();
		primeiroLance();
		turnos();
		//loop do jogo	
		do
		{
			if((cpu == 1) && (jvez == '2'))
				jogarCPU();
				
			//Menu do jogador			
			opMenuJogador = menujogador();
			switch(opMenuJogador)
			{
				case 1: //Jogar
					jogarPeca();
					retornofim = fim();
					break;
				case 2: //Comprar uma peca
					comprarPeca();
					break;
				case 3: //Passar					
					passar();
					retornofim = fim();
					break;
				case 4: //Salva o Jogo
					gravaCadastro();
					menujogador();
					break;
				case 5: //Saida para o menu principal
					system("cls");
					jogo();												
					break;
				default:
					system("cls");
            		apresentaMensagem("Opcao Invalida\n");
            		break;
			}										
		}while(retornofim == 0);
	}
}

void embaralharPecas() //Embaralha a ordem das pecas
{
	srand(time(NULL));  //Garante que o embaralhamento nao seja sempre o mesmo
    for (int i = 0; i < 28; i++)
	{
        int sorteio = rand() % 28;  // Sorteia um indice aleatorio
        
        pecaaux = peca[i];
        peca[i] = peca[sorteio];
        peca[sorteio] = pecaaux;
    }
}

void distribuirPecas() //Atribui as pecas para os jogadores e para o deposito de compra
{
	int i;
	
	for(i = 0; i < 7; i++) //Atribui as 7 primeiras pecas ao jogador 1
	{
		peca[i].status = '1'; 
	} 
	
	for(i = 7; i < 14; i++) //Atribui as pecas 7 a 13 ao jogador 2
	{
		peca[i].status = '2';
	} 
	
	for(i = 14; i < 28; i++) //Atribui as pecas 14 a 27 como disponiveis para comprar
	{
		peca[i].status = 'D'; //D = Disponivel para comprar
	} 
}

void primeiroLance() //Descobre e carrega a primeira peca na mesa
{
	int i, pj, dupla;
	pj = -1; //posicao da peca encontrada
	dupla = -1;
	
	//pesquisa primeiramente entre as pecas com lado1 = lado2
	for(i = 0; i < 14; i++)
	{
		if(peca[i].lado1 == peca[i].lado2)
		{
			if(peca[i].lado1 > dupla)
			{
				dupla = peca[i].lado1;
				pj = i;
			}
		}
	}
	//se nao encontrou, escolhe a peao com a maior soma
	if (pj == -1)
	{
		dupla = 0;
		for(i = 0; i < 14; i++)
		{	
			if(peca[i].lado1 + peca[i].lado2 > dupla)
	 		{
				dupla = peca[i].lado1 + peca[i].lado2;
				pj = i;
	 		}
 		}

 	}
	//descobre qual o jogador que jogou essa primeira peca
	
	jvez = peca[pj].status; //jvez deve ser uma variavel global tipo char
	//carrega a mesa com a primeira peca na posicao 0
	mesa[0].ladoE = peca[pj].lado1;
	mesa[0].ladoD = peca[pj].lado2;
	peca[pj].status = 'M'; //muda o status da peca
	mesa[0].status = 'E';
	mensagemJogada();
}

void comprarPeca() //Compra uma peca caso possivel
{
	int i;
	
	if(pecascompra > 0)
	{
		for (i = 14; i < 28; i++) //procura por uma peca disponivel
		{ 
    		if (peca[i].status == 'D') 
 	    	{
            peca[i].status = jvez;  // muda status da peca para o respectivo jogador
            pecascompra = pecascompra - 1;
            system("cls");
            apresentaMensagem("Compra efetuada com sucesso!\n");
            return;
			}
		}	
	}
	else
	{
		system("cls");
        apresentaMensagem("Nao exitem pecas disponiveis para compra!\n");
        return;
	}
	
}

void turnos() //Atualiza os turnos
{
	if(jvez == '1')
	{
		jvez = '2';
	}
	else
	{
		jvez = '1';
	}
}

void passar() //Passa a vez do jogador
{
	verificarPecasJogador();
	
	if(jvez == '1')
	{
		if((pecasj1 == 0) && (pecascompra == 0)) //O jogador nao tem pecas que possam ser jogadas e nao existem pecas para comprar
		{
			turnos();
			system("cls");
			apresentaMensagem("O jogador 1 passou o turno para o jogador 2\n\n");
		}
		else
		{
			system("cls");
			apresentaMensagem("Um jogador so pode passar o turno quando nao houver pecas que possam ser jogadar e\nnao houver pecas disponiveis para compra!\n\n");
		}
	}
	else
	{
		if((pecasj2 == 0) && (pecascompra == 0))
		{
			turnos();
			system("cls");
			apresentaMensagem("O jogador 2 passou o turno para o jogador 1\n\n");
			
		}
		else
		{
			system("cls");
			apresentaMensagem("Um jogador so pode passar o turno quando nao houver pecas que possam ser jogadar e\nnao houver pecas disponiveis para compra!\n\n");	
		}
	}
}

void verificarPecasJogador() //Verifica se o jogador da vez tem pecas que possam ser jogadas
{
	int i;
	
	pecasj1 = 0;
	pecasj2 = 0;
	
	for (i = 0; i < 28; i++)
	{
		if(peca[i].status == '1')
		{
			if((peca[i].lado1 == mesa[0].ladoE) || (peca[i].lado2 == mesa[0].ladoE) || (peca[i].lado1 == mesa[QtdPecasMesa - 1].ladoD) || (peca[i].lado2 == mesa[QtdPecasMesa - 1].ladoD))
			{
				pecasj1++;
			}
		}
		if(peca[i].status == '2')
		{
			if((peca[i].lado1 == mesa[0].ladoE) || (peca[i].lado2 == mesa[0].ladoE) || (peca[i].lado1 == mesa[QtdPecasMesa - 1].ladoD) || (peca[i].lado2 == mesa[QtdPecasMesa - 1].ladoD))
			{
				pecasj2++;
			}
		}		
	}
}

void jogarE() //"Empurra" as pecas para o lado direito
{
	int i;
	
    for (i = QtdPecasMesa; i > 0; i--)
	{
        mesa[i] = mesa[i - 1];
    }
}

void jogarPeca() //Joga a peca na mesa
 {
	int escolha, retorno, pos, count, i;
	contarPecasMesa();		
	escolha = menuJogada();
	
	if(peca[escolha].status != jvez) 
	{
		system("cls");
        apresentaMensagem("Essa peca nao pertence a voce!\n");
        return;
	}
	
	//Lado direito da mesa
	if((peca[escolha].lado1 == mesa[QtdPecasMesa - 1].ladoD) || (peca[escolha].lado2 == mesa[QtdPecasMesa - 1].ladoD))
	{
		// Verifica se precisa inverter a peca
		if ((peca[escolha].lado2) == (mesa[QtdPecasMesa - 1].ladoD))
		{
			int temp = peca[escolha].lado1;
            peca[escolha].lado1 = peca[escolha].lado2;
            peca[escolha].lado2 = temp;
		}

		mesa[QtdPecasMesa].ladoE = peca[escolha].lado1;
        mesa[QtdPecasMesa].ladoD = peca[escolha].lado2;
        mesa[QtdPecasMesa].status = 'E';
        peca[escolha].status = 'M';
        turnos();
        system("cls");
		apresentaMensagem("Um jogador jogou uma peca!\n\n");
		
	}
	
	//Verifica o lado esquerdo
	else if((peca[escolha].lado1 == mesa[0].ladoE) || (peca[escolha].lado2 == mesa[0].ladoE))	
	{
		// Verifica se precisa inverter a peca	
		if((peca[escolha].lado1) == (mesa[0].ladoE))
		{
			int temp = peca[escolha].lado1;
			peca[escolha].lado1 = peca[escolha].lado2;
			peca[escolha].lado2 = temp;
		}

		jogarE();
		
		//jogar a peca
		mesa[0].ladoE = peca[escolha].lado1;
		mesa[0].ladoD = peca[escolha].lado2;
		mesa[0].status = 'E';
		peca[escolha].status = 'M';
		turnos();	
		system("cls");
		apresentaMensagem("Um jogador jogou uma peca!\n\n");
	}
	else
	{
		system("cls");
		apresentaMensagem("Essa peca nao pode ser jogada!\n\n");
		return;
	}
}

void contarPecasMesa() //Verifica a quantidade de pecas na mesa
{
	QtdPecasMesa = 0;
	
	for(int i = 0; i < 28; i++) 
	{
		if(mesa[i].status == 'E')
			QtdPecasMesa++;
	}
}

int fim() // Verifica as condicoes para o fim do jogo e determina o vencedor
{
	int i;
	int qtdPecasj1 = 0; //Quantidade de pecas do jogador 1
	int qtdPecasj2 = 0; // Quantidade de pecas do jogador 2
	int somaj1 = 0; // Soma dos pontos (lado1 + lado2) das pecas do jogador 2	
	int somaj2 = 0; // Soma dos pontos (lado1 + lado2) das pecas do jogador 2

	//Contagem de pecas dos jogadores e pontos 
	for(i = 0; i < 28; i++)
	{
		if(peca[i].status == '1')
		{
			qtdPecasj1++;
			somaj1 = somaj1 + peca[i].lado1 + peca[i].lado2;
		}
		
		if(peca[i].status == '2')
		{
			qtdPecasj2++;
			somaj2 =  somaj2 + peca[i].lado1 + peca[i].lado2;
		}
	}
	
	//Jogador 1 "Bateu"
	if(qtdPecasj1 == 0)
	{
		system("cls");
		apresentaMensagem("\n Jogador 1 Bateu!\n Vitoria do Jogador 1\n");
		return 1;
	}
	
	//Jogador 2 "Bateu"
	if(qtdPecasj2 == 0)
	{
		system("cls");
		apresentaMensagem("\n Jogador 2 Bateu!\n Vitoria do Jogador 2\n");
		return 1;
	}	

	//Casos de Empate
	verificarPecasJogador();
	
	if((pecasj1 == 0) && (pecasj2 == 0) && (pecascompra == 0)) //Nenhum jogador tem pecas que possam ser jogadas e nao existem pecas disponiveis para compra
	{
		//Jogador 1 tem mais pontos
		if(somaj1 > somaj2)
		
		{
			system("cls");
			apresentaMensagem("\nNenhum dos jogadores possuem pecas que possam ser jogadas\n");
			apresentaMensagem("\nO jogador 1 tem mais pontos que o jogador 2");
			apresentaMensagem("\nVitoria do Jogador 1\n");	
			return 1;
		}
		
		//Jogador 2 tem mais pontos
		else if(somaj1 < somaj2)
		{
			system("cls");
			apresentaMensagem("\nNenhum dos jogadores possuem pecas que possam ser jogadas\n");
			apresentaMensagem("\nO jogador 2 tem mais pontos que o jogador 1");
			apresentaMensagem("\nVitoria do Jogador 2\n");	
			return 1;
		}	
		else //Os jogadores tem a mesma quantidade de pecas e pontos
		{
			system("cls");
			apresentaMensagem("\n Nenhum dos jogadores possuem pecas que possam ser jogadas\n");
			apresentaMensagem("\nEmpate\n");
			return 1;	
		}
	}
	return 0; // O jogo continua
}

void gravaCadastro() 
{
    FILE *fp; //pecas
    FILE *fpm; //mesa
    FILE *fps; //situacao
 
 	//CAD_DOMINO
	if((fp = fopen("CAD_DOMINO.txt", "w")) == NULL) 
	{
		apresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto para gravacao!\n");
		return; 
	}
	
	for(int i = 0; i < 28; i++)
	{
		if (fwrite(&peca[i], sizeof(tipoPeca), 1, fp) != 1)
		{
			apresentaMensagem("Erro na gravacao do arquivo CAD_DOMINO\n");
			return;
		}
	}
	
	fclose(fp);
	
	//CAD-MESA
	if((fpm = fopen("CAD-MESA.txt", "w")) == NULL) 
	{
		apresentaMensagem("O arquivo CAD-MESA nao pode ser aberto para gravacao!\n");
		return; 
	}
	
	for(int i = 0; i < 28; i++)
	{
		if (fwrite(&mesa[i], sizeof(tipomesa), 1, fpm) != 1)
		{
			apresentaMensagem("Erro na gravacao do arquivo CAD-MESA\n");
			return;
		}
	}
	
	fclose(fpm);
	
	//CAD_JOGO
	if( (fps = fopen("CAD_JOGO.txt", "w")) == NULL) 
	{
		apresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto para gravacao!\n");
		return; 
	}
	
	if (fwrite(&jvez, sizeof(char), 1, fps) != 1 ||
        fwrite(&pecascompra, sizeof(int), 1, fps) != 1 ||
        fwrite(&QtdPecasMesa, sizeof(int), 1, fps) != 1 ||
        fwrite(&pecasj1, sizeof(int), 1, fps) != 1 ||
        fwrite(&pecasj2, sizeof(int), 1, fps) != 1)
    {
    	apresentaMensagem("Erro na gravacao do arquivo CAD_JOGO\n");
		return;
	}
	
	fclose(fps);
	//
	apresentaMensagem("Jogo Salvo com Sucesso\n");
}

void fRecuperaCadastro()
{
	FILE *fp; //pecas
    FILE *fpm; //mesa
    FILE *fps; //situacao
    
 	//CAD_DOMINO
	if((fp = fopen("CAD_DOMINO.txt", "r")) == NULL) 
	{
		apresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto para gravacao!\n");
		return; 
	}
	
	for(int i = 0; i < 28; i++)
	{
		if (fread(&peca[i], sizeof(tipoPeca), 1, fp) != 1)
		{
			apresentaMensagem("Erro na leitura do arquivo CAD_DOMINO\n");
			return;
		}
	}
	
	fclose(fp);
	
	//CAD-MESA
	if((fpm = fopen("CAD-MESA.txt", "r")) == NULL) 
	{
		apresentaMensagem("O arquivo CAD-MESA nao pode ser aberto para leitura!\n");
		return; 
	}
	
	for(int i = 0; i < 28; i++)
	{
		if (fread(&mesa[i], sizeof(tipomesa), 1, fpm) != 1)
		{
			apresentaMensagem("Erro na leitura do arquivo CAD-MESA\n");
			return;
		}
	}
	
	fclose(fpm);
	
	//CAD_JOGO
	if( (fps = fopen("CAD_JOGO.txt", "r")) == NULL) 
	{
		apresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto para leitura!\n");
		return; 
	}
	
	if (fread(&jvez, sizeof(char), 1, fps) != 1 ||
        fread(&pecascompra, sizeof(int), 1, fps) != 1 ||
        fread(&QtdPecasMesa, sizeof(int), 1, fps) != 1 ||
        fread(&pecasj1, sizeof(int), 1, fps) != 1 ||
        fread(&pecasj2, sizeof(int), 1, fps) != 1)
    {
    	apresentaMensagem("Erro na leitura do arquivo CAD_JOGO\n");
		return;
	}
	
	fclose(fps);
	//
	apresentaMensagem("Jogo Carregado com Sucesso\n");
}

int jogarCPU()
{
	do
	{
		verificarPecasJogador();
		
		//CPU precisa passar o turno	
		if((pecasj2 == 0) && (pecascompra == 0))
		{
			turnos();
			system("cls");
			apresentaMensagem("O jogador 2 passou o turno para o jogador 1\n\n");
		}
		
		//CPU precisa comprar uma peca
		if((pecasj2 == 0) && (pecascompra != 0))
		{
			comprarPeca();
		}
		
		//CPU vai jogar uma peca
		else if(pecasj2 > 0)
		{
			contarPecasMesa();
			for(int i = 0; i < 20; i++)
			{
				if(peca[i].status == '2')
				{
					//Verifica o lado direito da mesa
					if((peca[i].lado1 == mesa[QtdPecasMesa - 1].ladoD) || (peca[i].lado2 == mesa[QtdPecasMesa - 1].ladoD))
					{
						// Verifica se precisa inverter a peca
						if((peca[i].lado2) == (mesa[QtdPecasMesa - 1].ladoD))
						{
							int temp = peca[i].lado1;
							peca[i].lado1 = peca[i].lado2;
							peca[i].lado2 = temp;
						}
						
						//Joga a peca
						mesa[QtdPecasMesa].ladoE = peca[i].lado1;
						mesa[QtdPecasMesa].ladoD = peca[i].lado2;
						mesa[QtdPecasMesa].status = 'E';
						peca[i].status = 'M';
						turnos();
        				system("cls");
						apresentaMensagem("Um jogador jogou uma peca!\n\n");
						return 0;
					}	
					
					//Verifica o lado esquerdp da mesa
					else if((peca[i].lado1 == mesa[0].ladoE) || (peca[i].lado2 == mesa[0].ladoE))
					{
						// Verifica se precisa inverter a peca	
						if((peca[i].lado1) == (mesa[0].ladoE))
						{
							int temp = peca[i].lado1;
							peca[i].lado1 = peca[i].lado2;
							peca[i].lado2 = temp;
						}
						jogarE();
		
						//jogar a peca
						mesa[0].ladoE = peca[i].lado1;
						mesa[0].ladoD = peca[i].lado2;
						mesa[0].status = 'E';
						peca[i].status = 'M';
						turnos();	
						system("cls");
						apresentaMensagem("Um jogador jogou uma peca!\n\n");	
						return 0;
					}						
				}
			}	
		}
	}while(1);
}

//aguarda os segundos solicitados (de 1 a 59)
void ftempo(int seg)
{
 time_t lt1, lt2;
 lt1 = time(NULL);
 lt2 = lt1;
 while (difftime(lt2, lt1) < seg)
 lt2 = time(NULL);
}