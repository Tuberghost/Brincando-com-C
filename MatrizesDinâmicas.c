// Programa feito no linux mint compilado usando gcc com argumento -lm no final



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void vermelho();
void verde();
void amarelo();
void resetcolor();

void delay(int segundos);
void jogo(int D);
int** matriz(int N); /* Entra o lado e sai a matriz */
void mostrar(int** matriz, int L, int C, int** marcador); /* Exibe uma matriz */
int** preenchimento(int** matriz, int N); /* Preenche uma matriz quadrada de lado par */



int main()
{
	system("clear");

	printf("→ Bem vindo(a) ao jogo da memória, selecione uma dificuldade:\n   Fácil   - [1]\n   Médio   - [2]\n   Difícil - [3]\n\n   ");

	int dificuldade = 0, lado;

	scanf("%i", &dificuldade);
	fflush(stdin);
	printf("\n");

	while((dificuldade < 1) || (dificuldade > 3))
	{
		system("clear");

		printf("→ Bem vindo(a) ao jogo da memória, selecione uma dificuldade:\n   Fácil   - [1]\n   Médio   - [2]      Selecione uma dificuldade válida!\n   Difícil - [3]\n\n   ");

		scanf("%i", &dificuldade);
		printf("\n");
	}

	lado = 2*(1 + dificuldade);
 	
 	system("clear");

 	printf("→ Bem vindo(a) ao jogo da memória, selecione uma dificuldade:\n   Fácil   - [1]\n   Médio   - [2]\n   Difícil - [3]\n\n");

	printf("   Dificuldade escolhida: [%i] → Tabuleiro: [%i×%i]\n\n   Pressione ENTER para continuar...\n", dificuldade, lado, lado);

	char buffer = getchar();

	while(getchar() != buffer);

	system("clear");





	jogo(dificuldade);





	/*system("clear");*/

	return 0;
}



void jogo(int D)
{
	int lado = 2*(1 + D);

	int** tabuleiro;
	tabuleiro = preenchimento(matriz(lado), lado);

	int** revelador;
	revelador = matriz(lado);

	int** marcador;
	marcador = matriz(lado);

	mostrar(tabuleiro, lado, lado, marcador);

	printf("\n\n   Pressione ENTER quando estiver pronto");
	getchar();

	system("clear");

	mostrar(revelador, lado, lado, marcador);

	int acertos = 0, gap = 0, combo = 0;
	float pontos = 0, ganho = 0;

	while(acertos < pow(lado, 2)/2)
	{
		int l1 = 0, c1 = 0, l2 = 0, c2 = 0;

		while((l1 < 1) || (l1 > lado) || (c1 < 1) || (c1 > lado) || (l2 < 1) || (l2 > lado) || (c2 < 1) || (c2 > lado) || ((l1 == l2) && (c1 == c2)))
		{
			system("clear");

			mostrar(revelador, lado, lado, marcador);

			printf("\n\n                                     Pontuação: %.2f", pontos);
			printf("\n\n   Digite um par de coordenadas\n\n");
			scanf("%i %i %i %i", &l1, &c1, &l2, &c2);

		}

		l1--;
		c1--;
		l2--;
		c2--;

		revelador[l1][c1] = tabuleiro[l1][c1];
		revelador[l2][c2] = tabuleiro[l2][c2];

		system("clear");

		if((marcador[l1][c1] == -1) || (marcador[l2][c2] == -1))
		{
			amarelo();
			printf("\n   Você já escolheu uma dessas cartas! Pontuação: %.2f\n", pontos);
			resetcolor();

			if(marcador[l1][c1] != -1)
				revelador[l1][c1] = 88;
			if(marcador[l2][c2] != -1)
				revelador[l2][c2] = 88;
		}
		else
		{
			if(tabuleiro[l1][c1] == tabuleiro[l2][c2])
			{
				marcador[l1][c1] = -1;
				marcador[l2][c2] = -1;

				mostrar(revelador, lado, lado, marcador);

				printf("\n   Voce escolheu (%i, %i) e (%i, %i)\n", l1 + 1, c1 + 1, l2 + 1, c2 + 1);


				acertos++;

				ganho = (float) 100/(gap + 1) + 5*pow(combo, 1.5);

				pontos = pontos + ganho;

				verde();
				printf("\n   Você acertou e ganhou %.2fpts + combo[%.2fpts]. Pontuação: %.2f\n", (float) 100/(gap + 1), (float) 5*pow(combo, 1.5), pontos);
				resetcolor();

				gap = 0;

				combo++;

			}
			else
			{

				marcador[l1][c1] = -1;
				marcador[l2][c2] = -1;

				mostrar(revelador, lado, lado, marcador);

				marcador[l1][c1] = 88;
				marcador[l2][c2] = 88;

				revelador[l1][c1] = 88;
				revelador[l2][c2] = 88;

				printf("\n   Voce escolheu (%i, %i) e (%i, %i)\n", l1 + 1, c1 + 1, l2 + 1, c2 + 1);

				vermelho();
				printf("\n   Você errou! Pontuação: %.2f\n", pontos);
				resetcolor();

				gap++;

				combo = 0;



			}

		}

		printf("\n   Pressione ENTER para continuar...\n");

		char buffer = getchar();

		while(getchar() != buffer);

	}

	system("clear");

	verde();

	printf("Você venceu!\nPontuação final: %f", pontos);

	resetcolor();

}




int** matriz(int N)
{
	int** ponteiro; 
	ponteiro = (int**) malloc(N * sizeof(int*));
	/* Poderia ser diretamente "int** ponteiro = (int**) malloc(N * sizeof(int*))"; */

	for(int i = 0; i < N; i++)
		ponteiro[i] = (int*) malloc(N * sizeof(int));

	for(int l = 0; l < N; l++)
		for(int c = 0; c < N; c++)
			ponteiro[l][c] = 88;

	return ponteiro;
}



void mostrar(int** matriz, int L, int C, int** marcador)
{
	for(int l = 0; l < L; l++)
		for(int c = 0; c < C; c++)
		{
			if(marcador[l][c] == -1)
				amarelo();
			if(c == 0)
				printf("\t         ");

			if(matriz[l][c] < 10)
				printf("\t0");

			printf("\t%i ", matriz[l][c]); /* Ajustar distância horizontal */


			if(c == (C - 1))
				printf("\n"); /* Ajustar distância vertical */

			resetcolor();
		}

}



int** preenchimento(int** matriz, int N)
{
	int k = pow(N, 2)/2;

	int** contador;
	contador = (int**) malloc(2 * sizeof(int*));

	for(int i = 0; i < 2; i++)
		contador[i] = (int*) malloc(k * sizeof(int));


	for(int i = 0; i < k; i++)
	{
		contador[0][i] = i;
		contador[1][i] = 2; /* Pois usamos duas vezes cada símbolo */
	}


	int Sorteio;
	srand(time(NULL)); // Semente aleatória com base no horário
	for(int l = 0; l < N; l++) 
		for(int c = 0; c < N; c++)
			{
				do
					Sorteio = rand() % k; /* Recebe algum valor aleatório do conjunto {0, 1, 2, ..., k - 1} */
				while (contador[1][Sorteio] == 0);

				matriz[l][c] = contador[0][Sorteio];

				contador[1][Sorteio]--;
				
			}	


	return matriz;

}



void vermelho()
{
	printf("\033[0;31m");
}



void verde()
{
	printf("\033[0;32m");
}



void amarelo()
{
	printf("\033[0;33m");
}



void resetcolor()
{
	printf("\033[0m");
}















/*void delay(int segundos) // Reloginho
{
  
    long int tempo_inicial = time(NULL);
  
    while (time(NULL) < (tempo_inicial + (long int)segundos))
    {
    }

}*/