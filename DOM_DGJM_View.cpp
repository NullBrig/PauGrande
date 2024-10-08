

#include <stdio.h>
#include "Dom_DGJM_View.h"



int menuInicial()
{
	int op;
	printf("Menu: \n");
	printf("(1) Iniciar jogo para dois jogadores\n(2) Iniciar jogo para um jogador\n(3) Regras do jogo\n(4) Sair\n(5) Retomar Jogo em Andamento\n(6) Carregar Jogo Salvo\n");
	printf("Digite o numero da sua escolha\n");
	scanf("%d", &op);
	
	switch(op)
	{
		case 1: //Jogar com 2 jogadores
			return op; 
			break;
		case 2: //Jogar com 1 jogador
			return op;
			break;
		case 3: //Regras
			system ("cls");
			regrasJogo();	
			break;
		case 4: //Sair
			return 0;
			break;
		case 5: //Retomar o jogo
			if(jvez == '0')
				{
				 system("cls");
					printf("Nao existe nenhum jogo em andamento para ser retomado!\n\n");
				}
			else
			{
				system("cls");
				menujogador();
				break;
			}
		case 6: //Carregar jogo salvo
		{	
			fRecuperaCadastro();
			menujogador();
			break;
		}	
	}
}
			
int menujogador()
{
	int escolha;
	if(jvez == '1') //Menu do jogador 1
	{
		//Exibir as pecas		
		apresentaMesa();
		apresentaPecasJ1();
		
		//Exibir as escolhas				
		printf("Menu do Jogador 1: \n");
		printf("(1) Jogar\n(2) Comprar\n(3) Passar\n(4) Gravar Jogo\n(5) Sair para o Menu Inicial\n");
		printf("Digite o numero da sua escolha: \n");
		scanf("%d", &escolha);
		return escolha;
		
	}
	else if((jvez == '2') && (cpu == 0)) //Menu do jogador 2
	{
		//Exibir as pecas		
		apresentaMesa();
		apresentaPecasJ2();
		
		//Exibir as escolhas				
		printf("Menu do Jogador 2: \n");
		printf("(1) Jogar\n(2) Comprar\n(3) Passar\n(4) Gravar Jogo\n(5) Sair para o Menu Inicial\n");
		printf("Digite o numero da sua escolha: \n");
		scanf("%d", &escolha);
		return escolha;
	}

}

int menuJogada()
{
	int EscolhaPeca;
	
	printf("Digite a peca escolhida:\n");
	scanf("%d", &EscolhaPeca);
	/*if(jvez == '1')
	{
		if(peca[Escolha])
	}*/
	return EscolhaPeca;
}

void apresentaMesa() //Exibe as pecas da mesa
{
	int indice = 0;
	
	printf("Pecas na mesa: ");
	
	for(int y = 0; y < 28; y++)
	{
		if(mesa[y].status == 'E')
		{
			printf("   [%d|%d]   ", mesa[y].ladoE, mesa[y].ladoD);
		}
	}
	printf("\n\n");
}

void apresentaPecasJ1() //Exibe as pecas do jogador 1
{
	int indice = 1;
	printf("Pecas do Jogador 1:");
	
	for(int y = 0; y < 28; y++) 
	{
		if(peca[y].status == '1')
		{
			printf(" %d  [%d|%d]   ",y , peca[y].lado1, peca[y].lado2);
			indice++;
		}
	}
	printf("\n\n");
}

void apresentaPecasJ2() //Exibe as pecas do jogador 2
{
	int indice = 1;
	printf("Pecas do Jogador 2:");
	
	for(int y = 0; y < 28; y++) 
	{
		if(peca[y].status == '2')
		{
			printf(" %d  [%d|%d]   ",y ,peca[y].lado1, peca[y].lado2);
			indice++;
		}
	}
	printf("\n\n");
}


void apresentaMensagem(const char mens[100]) //Funcao para exibir mensagens quaisquer
{
	printf("%s\n", mens);
}

void mensagemJogada() //Nao consegui usar %c na funcao "apresentaMensagem" entao criei essa
{
	printf("O jogador %c fez a primeira jogada!\n\n", jvez);
}

void regrasJogo()
{
	system("cls");
	printf("\n");
	printf("===============Regras do Jogo===============");
	printf("\n");
	
	printf("Adotaremos as regras mais simples do jogo:\n");
    printf("\n");

    printf("1. Cada jogador inicia com sete pecas obtidas aleatoriamente.\n");
    printf("\n");

    printf("2. Os jogadores podem \"comprar\" quantas vezes for necessario sempre que precisar de uma peca para jogar ou se quiser \"blefar\".\n");
    printf("\n");

    printf("3. O jogo inicia-se com o jogador que tiver a peca \"seis-seis\".\n");
    printf("\n");

    printf("4. Caso ninguem tenha essa peca, o jogo inicia-se com o jogador que tiver a peca com os numeros repetidos mais altos, como \"cinco-cinco\", \"quatro-quatro\", e assim sucessivamente.\n");
    printf("\n");

    printf("5. O jogo acontece no sentido anti-horario.\n");
    printf("\n");

    printf("6. Os jogadores devem colocar pecas que tenham os mesmos numeros das pecas nas extremidades da mesa.\n");
    printf("\n");

    printf("7. O jogador que comeca a partida leva vantagem.\n");
    printf("\n");

    printf("8. Antes de cada jogada, o jogador pode \"comprar\" quantas pecas quiser do deposito ainda disponivel.\n");
    printf("\n");

    printf("9. Perde a partida aquele que, no final, tiver maior quantidade de pecas.\n");
    printf("\n");

    printf("10. Cada jogador, no seu turno, deve colocar uma de suas pecas em uma das extremidades abertas na mesa.\n");
    printf("\n");

    printf("11. Os pontos de um lado da peca devem coincidir com os pontos da extremidade onde esta sendo colocada.\n");
    printf("\n");

    printf("12. As pecas dobradas sao colocadas transversalmente (este detalhe nao sera levado em conta no texto).\n");
    printf("\n");

    printf("13. Quando o jogador coloca sua peca, seu turno acaba e passa-se ao proximo jogador.\n");
    printf("\n");

    printf("14. Se um jogador nao puder jogar, devera \"comprar\" do monte tantas pecas quanto necessarias.\n");
    printf("\n");

    printf("15. Se nao houver mais pecas, passara o turno ao seguinte jogador.\n");
    printf("\n");

    printf("16. Portanto, o jogador so podera passar a jogada se nao possuir peca possivel de ser colocada e se nao houver mais pecas livres.\n");
    printf("\n");

    printf("17. A partida continua ate que o estoque de pecas disponiveis a comprar esteja vazio e se apresente alguma das seguintes situacoes:\n");
    printf("\n");

    printf("17.1. Quando um jogador coloca sua ultima pedra na mesa, essa acao e chamada de bater e ele se torna o vencedor do jogo.\n");
    printf("\n");

    printf("17.2. Quando nenhum jogador pode continuar a partida e o deposito esta vazio (numero das extremidades ja saiu 7 vezes), a partida esta fechada.\n");
    printf("\n");

    printf("18. Vence quem tiver menos pecas.\n");
    printf("\n");

    printf("19. Em caso de empate, vence o jogador com menos pontos nas pecas restantes.\n");
    printf("\n");

    printf("20. Portanto, vence o jogador que tiver a menor quantidade de pecas ou, se houver empate, a menor contagem total de pontos.\n");
    printf("\n");
    
    printf("=================================");
    printf("\n");
    
    menuInicial();
}
