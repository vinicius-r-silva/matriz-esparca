#define _CRT_SECURE_NO_DEPRECATE
#define ERRO INT_MIN

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
//#include <locale.h>

/**
------TO DO LIST------
- Criar uma struct que informa a qtd_linhas e qtd_colunas da matriz e tirá-la da struct
- Após isso modificar as funções passando essa nova struct como parâmetro
- Colocar as funções para receber somente números e impedir o usuario de colocar letras ou numeros inválidos
**/
//i: linha, j: coluna

struct matriz
{
	int i;
	int j;
	bool Usado;
	float data;
	struct matriz *direita;
	struct matriz *baixo;
};

struct cabecalho
{
	int N_Linhas;
	int N_Colunas;
};

typedef struct matriz MATRIZ;
typedef MATRIZ *MATRIZ_PTR;

typedef struct cabecalho CABECALHO;
typedef CABECALHO *CABECALHO_PTR;

//------------------------------------------SYSTEM------------------------------------------//
//Pega a entrada do usuario, limitando ele a numero especifico de digitos
int EntradaLimitadaInt(int min, int max);

//Pega a entrada do usuario, limitando ele a numero especifico de digitos
double EntradaLimitadaDouble(double min, double max);

//Pergunta ao usuario um numero e posicao, e coloca na matriz
void atribuir_valor_pos(MATRIZ_PTR *matriz, CABECALHO_PTR cabecalho);

//Inicializa a matriz
void criar_matriz(MATRIZ_PTR *matriz, CABECALHO_PTR *cabecalho);

//Pergunta uma posicao e mostra o valor dela
void consultar_valor_pos(MATRIZ_PTR ListaElementos, CABECALHO_PTR cabecalho);

double BuscaValor(MATRIZ_PTR ListaMatriz, int i, int j);

MATRIZ_PTR BuscaElemento(MATRIZ_PTR ListaMatriz, int i, int j);

//pergunta ao usuario o numero de uma linha, e mostra a soma dela
void consultar_soma_linha(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho);

//Pergunta ao usuarioo numero de uma coluna, e mostra a soma dela
void consultar_soma_coluna(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho);

//------------------------------------------INTERFACE------------------------------------------//
//Informa ao usuario a descricao do programa e criadores
void MenuSobre();

//Espera o usuario pressionar ENTER para continuar o programa
void WaitENTER();

//Imprime /n suficientes para "limpar" a tela
void Limpa_tela();

int menu_principal();

//Tela de apresentacao
void splash_screen();

//Le um int do Stdin
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
int ReadInt(int *numero);

//Le um float do Stdin
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
int ReadDouble(double *numero);

//------------------------------------------MAIN------------------------------------------//
int main()
{
	//setlocale(LC_ALL, "Portuguese");
	MATRIZ_PTR ListaMatriz = NULL;
	CABECALHO_PTR cabecalho = (CABECALHO_PTR)malloc(sizeof(CABECALHO));
	cabecalho->N_Linhas = 0;
	cabecalho->N_Colunas = 0;

	splash_screen();
	WaitENTER();

	Limpa_tela();
	printf("                             AVISO!\n");
	printf("\n\nO seu programa nao possui matrizes. Sera criada uma matriz inicial.\n\n");
	printf("               Pressione ENTER para prosseguir.\n");
	char c = getchar();
	while (c != '\n')
		c = getchar();

	criar_matriz(&ListaMatriz, &cabecalho);
	Limpa_tela();
	WaitENTER();
	int acao;
	while (1)
	{
		acao = menu_principal();
		switch (acao)
		{
		case 1:
			criar_matriz(&ListaMatriz, &cabecalho);
			break;

		case 2:
			consultar_valor_pos(ListaMatriz, cabecalho);
			break;

		case 3:
			//consultar_soma_linha(ListaMatriz);
			break;

		case 4:
			//consultar_soma_coluna(ListaMatriz);
			break;

		case 5:
			atribuir_valor_pos(&ListaMatriz, cabecalho);
			break;

		case 6:
			MenuSobre();
			break;

		case 7:
			return 0;
			break;

		default:
			printf("Valor invalido.\n");
			WaitENTER();
		}
	}
}

//------------------------------------------SYSTEM------------------------------------------//
int EntradaLimitadaInt(int min, int max)
{
	int c;
	while (!ReadInt(&c) && (c < min || c > max))
		printf("Valor invalido. Digite algo entre %d e %d. \nDigite novamente: ", min, max);

	return c;
}

double EntradaLimitadaDouble(double min, double max)
{
	double c;
	while (!ReadDouble(&c) && (c < min || c > max))
		printf("Valor invalido. Digite algo entre %.4lf e %.4lf. \nDigite novamente: ", min, max);

	return c;
}
/*
int Determinante(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho)
{
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0)
	{
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return ERRO;
	}

	if (cabecalho->N_Colunas != cabecalho->N_Linhas)
	{
		printf("Essa matriz não é quadrada, não existe determinante.\n");
		WaitENTER();
		return ERRO;
	}

	int i;
	double valor;
	MATRIZ_PTR Elemento = NULL;
	if (cabecalho->N_Linhas == 1)
		return BuscaValor(ListaMatriz, 1, 1);
	
	if (cabecalho->N_Linhas == 2)
	{
		valor = BuscaValor(ListaMatriz, 1, 1) * BuscaValor(ListaMatriz, 2, 2);
		valor -= BuscaValor(ListaMatriz, 1, 2) * BuscaValor(ListaMatriz, 2, 1);
		return valor;
	}

	return 0;
}
*/

//cria uma struct de matriz e coloca na Lista de matrizes
void criar_matriz(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR *cabecalho)
{
	Limpa_tela();
	int linhas, colunas;

	MATRIZ_PTR prev = NULL;
	MATRIZ_PTR linha = NULL;
	MATRIZ_PTR coluna = *ListaMatriz;
	while (coluna != NULL)
	{
		linha = coluna->direita;
		while (linha != NULL)
		{
			prev = linha;
			linha = linha->direita;
			free(prev);
		}
		prev = coluna;
		coluna = coluna->baixo;
		free(prev);
	}
	(*ListaMatriz) = NULL;

	printf("Digite a quantidade de linhas da matriz: ");
	linhas = EntradaLimitadaInt(1, INT_MAX);

	printf("Digite a quantidade de colunas da matriz: ");
	colunas = EntradaLimitadaInt(1, INT_MAX);

	(*cabecalho)->N_Linhas = linhas;
	(*cabecalho)->N_Colunas = colunas;

	printf("Matriz criada com sucesso!\n");
	printf("Deseja atribuir algum valor a uma posicao? 1 - SIM   0 - NAO\n");
	int num = EntradaLimitadaInt(0, 1);
	if (num == 1)
		atribuir_valor_pos(ListaMatriz, *cabecalho);
}

double BuscaValor(MATRIZ_PTR ListaMatriz, int i, int j)
{
	MATRIZ_PTR matriz = BuscaElemento(ListaMatriz, i, j);
	if (matriz == NULL)
		return 0;
	else
		return matriz->data;
}

MATRIZ_PTR BuscaElemento(MATRIZ_PTR ListaMatriz, int i, int j)
{
	MATRIZ_PTR linha = NULL;
	MATRIZ_PTR coluna = ListaMatriz;
	while (coluna != NULL && coluna->j < j)
		coluna = coluna->baixo;

	if (coluna == NULL || coluna->j > j)
		return NULL;

	linha = coluna;
	while (linha != NULL && linha->i < i)
		linha = linha->direita;

	if (linha == NULL || linha->i > i)
		return NULL;
	else
		return linha;
}


void InsereElemento(MATRIZ_PTR *ListaMatriz, MATRIZ_PTR NovoElemento)
{
	int i = NovoElemento->i;
	int j = NovoElemento->j;

	MATRIZ_PTR atual = *ListaMatriz;
	MATRIZ_PTR prev = NULL;

	MATRIZ_PTR linha = NULL;
	MATRIZ_PTR coluna = *ListaMatriz;
	if (coluna == NULL){
		*ListaMatriz = NovoElemento;
		return;
	} else if (coluna->j > j){
		NovoElemento->baixo = *ListaMatriz;
		*ListaMatriz = NovoElemento;
	} else if (coluna->j == j && coluna->i > i){
		
		*ListaMatriz = NovoElemento;
	}

	while (atual != NULL && (atual->i > i || atual->j > j))
	{
		prev = atual;
		atual = atual->prox;
	}

	if (prev == NULL)
		*ListaMatriz = NovoElemento;
	else
		prev->prox = NovoElemento;

	NovoElemento->prox = atual;
}
/*
void atribuir_valor_pos(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho)
{
	if (cabecalho->N_Colunas == 0)
	{
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int i, j;
	double data;
	int leitura;
	MATRIZ_PTR NovoElemento = NULL;

	while (1)
	{
		printf("Digite a linha da posicao: ");
		i = EntradaLimitadaInt(1, cabecalho->N_Linhas);

		printf("Digite a coluna da posicao: ");
		j = EntradaLimitadaInt(1, cabecalho->N_Colunas);

		printf("Digite o valor que deseja atribuir a posicao: ");
		data = EntradaLimitadaDouble(FLT_MIN, FLT_MAX);

		NovoElemento = BuscaElemento(*ListaMatriz, i, j);
		if (NovoElemento != NULL)
		{
			printf("Elemento na posicao (%d,%d) ja cadastrado\n", i, j);
			printf("Deseja cancelar a operacao (-1), tentar novamente (0) ou sobreescrever o elemento (1)");
			leitura = EntradaLimitadaInt(0, 1);
			if (leitura == 0)
				continue;
			if (leitura == -1)
				return;
		}

		//verifica se a posicao ja esta sendo usada
		if (NovoElemento == NULL)
		{
			NovoElemento = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
			NovoElemento->i = i;
			NovoElemento->j = j;
			NovoElemento->prox = NULL;
			NovoElemento->Usado = false;
			InsereElemento(ListaMatriz, NovoElemento);
		}

		NovoElemento->data = data;

		printf("Deseja adicionar mais valores?  1 - SIM     0 - NAO.\n");
		leitura = EntradaLimitadaInt(0, 1);
		Limpa_tela();
		if (leitura == 0)
			return;
	}
}

//
void consultar_valor_pos(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho)
{
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0)
	{
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int i = 0, j = 0;
	double data;
	printf("Digite o valor da linha que deseja consultar: ");
	i = EntradaLimitadaInt(1, cabecalho->N_Linhas);

	printf("Digite o valor da coluna que deseja consultar: ");
	j = EntradaLimitadaInt(1, cabecalho->N_Colunas);

	//busca o valor na matriz
	MATRIZ_PTR Elemento = BuscaElemento(ListaMatriz, i, j);
	if (Elemento == NULL)
		printf("O valor da posicao (%d,%d) e: 0\n", i, j);
	else
		printf("O valor da posicao (%d,%d) ss e: %.4lf\n", i, j, Elemento->data);

	WaitENTER();
	return;
}

void consultar_soma_linha(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho)
{
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0)
	{
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int linha;
	double soma = 0;

	printf("Digite a linha que deseja consultar: ");
	linha = EntradaLimitadaInt(1, cabecalho->N_Linhas);
	MATRIZ_PTR Elemento = ListaMatriz;

	while (Elemento != NULL && Elemento->i < linha)
		Elemento = Elemento->prox;

	while (Elemento != NULL && Elemento->i == linha)
	{
		soma += Elemento->data;
		Elemento = Elemento->prox;
	}

	printf("A soma da linha %d e: %.4lf\n", linha, soma);
	WaitENTER();
	return;
}

void consultar_soma_coluna(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho)
{
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0)
	{
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int col;
	double soma = 0;

	printf("Digite a coluna que deseja consultar: ");
	col = EntradaLimitadaInt(1, cabecalho->N_Linhas);
	MATRIZ_PTR Elemento = ListaMatriz;

	while (Elemento != NULL)
	{
		if (Elemento->j == col)
			soma += Elemento->data;

		Elemento = Elemento->prox;
	}

	printf("A soma da coluna %d e: %.4lf\n", col, soma);
	WaitENTER();
	return;
}*/

//------------------------------------------INTERFACE------------------------------------------//
//Informa ao usuario a descricao do programa e criadores
void MenuSobre()
{
	Limpa_tela();
	printf("                    Gerenciador de notas\n");
	printf("                       Sobre o projeto       \n\n\n\n\n\n");
	printf("        Programa para gerenciamento de matrizes esparsas\n\n");
	printf("             As posicões vazias sao tomadas como contendo o valor 0\n\n");
	printf(" Projeto da disciplina de Introducao a Ciencia da Computacao I\n\n");
	printf("                 Universidade de Sao Paulo\n\n\n");
	printf("\n\n   Pressione ENTER para seguir para as informacões dos autores\n\n");
	char c = getchar();
	while (c != '\n')
		c = getchar();

	Limpa_tela();
	printf("                         Criado por:\n");
	printf("                       Vinicius Ribeiro\n");
	printf("                       vinicius.r@usp.br\n");
	printf("                 github.com/vinicius-r-silva\n\n");
	printf("                             e\n\n");
	printf("                  Gabriel Santos Nicolau:\n");
	printf("                gabriel.nicolau97@hotmail.com\n");
	printf("                     github.com/7Nic\n\n");
	WaitENTER();
}

void WaitENTER()
{
	printf("\n\n        Pressione ENTER para voltar ao menu principal\n\n");
	char c = getchar();
	while (c != '\n')
		c = getchar();
}

void Limpa_tela()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	return;
}

int menu_principal()
{
	Limpa_tela();
	printf("                             Matriz Esparsa\n");
	printf("\n\n\n\n\n");
	printf("1 - Criar matriz                              2 - Consultar valor de uma posicao\n");
	printf("3 - Consultar valor soma de linha             4 - Consultar valor de soma de coluna\n");
	printf("5 - Atribuir valor a uma posicao              6 - Sobre\n");
	printf("7 - Sair\n\n\n\n\n\n");
	printf("Digite a opcao desejada: ");
	return EntradaLimitadaInt(1, 7);
}

void splash_screen()
{
	printf("        .___  ___.      ___   .___________..______       __   ________ \n");
	printf("        |   \\/   |     /   \\  |           ||   _  \\     |  | |       / \n");
	printf("        |  \\  /  |    /  ^  \\ `---|  |----`|  |_)  |    |  | `---/  /  \n");
	printf("        |  |\\/|  |   /  /_\\  \\    |  |     |      /     |  |    /  /   \n");
	printf("        |  |  |  |  /  _____  \\   |  |     |  |\\  \\----.|  |   /  /----. \n");
	printf("        |__|  |__| /__/     \\__\\  |__|     | _| `._____||__|  /________| \n");
	printf("\n");
	printf(" _______     _______..______      ___      .______          _______.     ___ \n");
	printf("|   ____|   /       ||   _  \\    /   \\     |   _  \\        /       |    /   \\ \n");
	printf("|  |__     |   (----`|  |_)  |  /  ^  \\    |  |_)  |      |   (----`   /  ^  \\ \n");
	printf("|   __|     \\   \\    |   ___/  /  /_\\  \\   |      /        \\   \\      /  /_\\  \\ \n");
	printf("|  |____.----)   |   |  |     /  _____  \\  |  |\\  \\----.----)   |    /  _____  \\ \n");
	printf("|_______|_______/    | _|    /__/     \\__\\ | _| `._____|_______/    /__/     \\__\\ \n");
}

//Le um inteiro do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadInt(int *numero)
{
	bool negativo = false;

	//Limpa o buffer inicial at� encontrar um numero ou ate o buffer acabar
	char c = getchar();
	if (c == '\n' || c == '\0')
		c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9'))
	{
		//Se o usuario digitou o sinal de menos, salva para no final multiplar por -1
		if (c == '-')
			negativo = true;

		c = getchar();
	}

	//Se o buffer de entrada acabou, entao nao tem nenhum numero para ler
	if (c == '\n' || c == '\0')
		return 0;

	//Caso o usuario digitou algum digito, le os digitos ate acabar
	*numero = c - '0';
	c = getchar();
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9')
	{
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Certifica que o buffer continua limpo depois da leitura
	while (c != '\n' && c != '\0')
	{
		c = getchar();
	}

	//Se o usuario digitou um '-' antes de digitar o numero, deixa o numero negativo
	if (negativo)
		*numero *= -1;

	//retorna sucesso
	return 1;
}

//Le um float do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadDouble(double *numero)
{
	int i;
	bool negativo = false;

	//Limpa o buffer inicial at� encontrar um numero ou ate o buffer acabar
	char c = getchar();
	if (c == '\n' || c == '\0')
		c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9'))
	{
		if (c == '-')
			negativo = true;

		c = getchar();
	}

	//Se o buffer de entrada acabou, entao nao tem nenhum numero para ler
	if (c == '\n' || c == '\0')
		return 0;

	//Caso o usuario digitou algum digito, le os digitos ate acabar
	*numero = (double)(c - '0');
	c = getchar();
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9')
	{
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Caso o usuario digitou um '.' ou uma ',', le os proximos digitos ate acabar
	if (c == '.' || c == ',')
	{
		i = 10;
		c = getchar();
		while (c != '\n' && c != '\0' && c >= '0' && c <= '9')
		{
			*numero = (*numero) + ((double)(c - '0') / i);
			c = getchar();
			i *= 10;
		}
	}

	//Certifica que o buffer continua limpo depois da leitura
	while (c != '\n' && c != '\0')
	{
		c = getchar();
	}

	//Se o usuario digitou um '-' antes de digitar o numero, deixa o numero negativo
	if (negativo)
		*numero *= -1;

	//retorna sucesso
	return 1;
}