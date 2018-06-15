#define _CRT_SECURE_NO_DEPRECATE
#define ERRO INT_MIN
#define TOLERANCIA 0.00001

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <math.h>

//i: linha, j: coluna

struct matriz
{
	int i;
	int j;
	float data;
	struct matriz *prox;
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

//------------------------------------------MATRIZ------------------------------------------//
//Inicializa a matriz
void criar_matriz(MATRIZ_PTR *matriz, CABECALHO_PTR *cabecalho);

//Pergunta ao usuario um numero e posicao, e coloca na matriz
void atribuir_valor_pos(MATRIZ_PTR *matriz, CABECALHO_PTR cabecalho);

//Pergunta uma posicao e mostra o valor dela
void consultar_valor_pos(MATRIZ_PTR ListaElementos, CABECALHO_PTR cabecalho);

//pergunta ao usuario o numero de uma linha, e mostra a soma dela
void consultar_soma_linha(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho);

//Pergunta ao usuarioo numero de uma coluna, e mostra a soma dela
void consultar_soma_coluna(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho);

//Dada a lista e a posicao de um elemento, retorna o valor dele (0 se nao existir na fila)
int BuscaValor(MATRIZ_PTR ListaMatriz, int i, int j);

//Dada a lista e a posicao de um elemento, retorna o endereco de memoria da struct desse elemento
MATRIZ_PTR BuscaElemento(MATRIZ_PTR ListaMatriz, int i, int j);

void InsereElemento(MATRIZ_PTR *ListaMatriz, MATRIZ_PTR NovoElemento);



//---------------------------------------DETERMINANTE---------------------------------------//
float Determinante(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho, int passo_a_passo);

void TrocaLinha(MATRIZ_PTR *ListaMatriz, int Linha_1, int Linha_2);

void multiplicaLinha(MATRIZ_PTR PrimeiroElemento, double fator);

void SomaLinhas(MATRIZ_PTR *ListaMatriz, MATRIZ_PTR Linha, MATRIZ_PTR Inicio, double *Multiplicador);

//Vai pegando todos os valores da diagonal principal, e retorna o resultado da multiplicacao entre eles
double Multiplicacao_Diagonal(MATRIZ_PTR ListaMatriz, int N_Linhas);

MATRIZ_PTR Elemento_diagonal_gauss(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho, int linha_atual, double* Multiplicador, int passo_a_passo);

float metodoGauss(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho, int linha_atual, double Multiplicador, int passo_a_passo);



//------------------------------------------SYSTEM------------------------------------------//
//Pega a entrada do usuario, limitando ele a numero especifico de digitos
int EntradaLimitadaInt(int min, int max);

//Pega a entrada do usuario, limitando ele a numero especifico de digitos
double EntradaLimitadaDouble(double min, double max);

bool SaoIguais(double N1, double N2);

//Le um int do Stdin
//Retorna false quando nao foi possivel ler nenhum numero do buffer, e retorna true quando leu
int ReadInt(int *numero);

//Le um float do Stdin
//Retorna false quando nao foi possivel ler nenhum numero do buffer, e retorna true quando leu
int ReadDouble(double *numero);



//------------------------------------------INTERFACE------------------------------------------//
//Informa ao usuario a descricao do programa e criadores
void MenuSobre();

//Espera o usuario pressionar ENTER para continuar o programa
void WaitENTER();

//Semelhante a funcao superior, porem nao informa que vai voltar ao menu principal
void WaitProsseguir();

//Imprime /n suficientes para "limpar" a tela
void Limpa_tela();

int menu_principal();

//Tela de apresentacao
void splash_screen();

void Imprime(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho);



//------------------------------------------MAIN------------------------------------------//
int main()
{
	MATRIZ_PTR ListaMatriz = NULL;
	CABECALHO_PTR cabecalho = (CABECALHO_PTR)malloc(sizeof(CABECALHO));
	cabecalho->N_Linhas = 0;
	cabecalho->N_Colunas = 0;

	splash_screen();
	WaitProsseguir();

	Limpa_tela();
	printf("                             AVISO!\n");
	printf("\n\nO seu programa nao possui matrizes. Sera criada uma matriz inicial.\n\n");
	printf("               Pressione ENTER para prosseguir.\n");
	char c = getchar();
	while (c != '\n')
		c = getchar();

	criar_matriz(&ListaMatriz, &cabecalho);
	Limpa_tela();
	//printf("Matriz Original: \n");
	//Imprime(ListaMatriz, cabecalho);
	//printf("%lf", Determinante(&ListaMatriz, cabecalho));
	WaitProsseguir();
	int acao;
	while (true && !false)
	{
		acao = menu_principal();
		//Imprime(ListaMatriz, cabecalho);
		switch (acao)
		{
		case 1:
			criar_matriz(&ListaMatriz, &cabecalho);
			break;

		case 2:
			consultar_valor_pos(ListaMatriz, cabecalho);
			break;

		case 3:
			consultar_soma_linha(ListaMatriz, cabecalho);
			break;

		case 4:
			consultar_soma_coluna(ListaMatriz, cabecalho);
			break;

		case 5:
			atribuir_valor_pos(&ListaMatriz, cabecalho);
			break;

		case 6:
			MenuSobre();
			break;

		case 7:
			printf("Voce escolheu a opcao de calcular o determinante.\n");
			printf("Caso sua matriz seja quadrada e esteja entre 3x3 e 13x13, sera possivel acompanhar o passo a passo.\n");
			printf("Deseja acompanhar o passo a passo do metodo? 1 - SIM   0 - NAO\n");
			int passo_a_passo = EntradaLimitadaInt(0, 1);
			if (passo_a_passo == 1 && cabecalho->N_Linhas > 13 && cabecalho->N_Colunas>13){
                printf("A sua matriz e muito grande para ser impressa na tela. Nao sera possivel observar o passo a passo.\n");
                WaitProsseguir();
                passo_a_passo = 0;
			}
			if (passo_a_passo == 1 && cabecalho->N_Linhas <= 2 && cabecalho->N_Colunas<=2){
                printf("Em matrizes 1x1 e 2x2 nao se utiliza o metodo de Gauss, portanto nao ha passo a passo para ser exibido.\n");
                WaitProsseguir();
                passo_a_passo = 0;
			}

            if (passo_a_passo == 1){
                printf("Matriz original\n");
                Imprime(ListaMatriz, cabecalho);
                WaitProsseguir();
            }
			double det = Determinante(&ListaMatriz, cabecalho, passo_a_passo);
			if (det == ERRO) break;

			printf("O determinante da sua matriz e: %lf\n", det);
			WaitENTER();
			break;

		case 8:
			return 0;
			break;

		default:
			printf("Valor invalido.\n");
			WaitENTER();
		}
	}
}

//------------------------------------------MATRIZ------------------------------------------//
void Exclui_Matriz(MATRIZ_PTR *ListaMatriz){
	MATRIZ_PTR atual = *ListaMatriz;
	MATRIZ_PTR prev = NULL;
	while (atual != NULL){
		prev = atual;
		atual = atual->prox;
		free(prev);
	}
	(*ListaMatriz) = NULL;
}

//cria uma struct de matriz e coloca na Lista de matrizes
void criar_matriz(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR *cabecalho){
	Limpa_tela();
	int linhas, colunas;

	//Libera da memoria todos os elementos antigos
	Exclui_Matriz(ListaMatriz);

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

int BuscaValor(MATRIZ_PTR ListaMatriz, int i, int j){
	while (ListaMatriz != NULL && (ListaMatriz->i != i || ListaMatriz->j != j))
		ListaMatriz = ListaMatriz->prox;

	if (ListaMatriz == NULL)
		return 0;
	else
		return ListaMatriz->data;
}

MATRIZ_PTR BuscaElemento(MATRIZ_PTR ListaMatriz, int i, int j){
	while (ListaMatriz != NULL && (ListaMatriz->i != i || ListaMatriz->j != j))
		ListaMatriz = ListaMatriz->prox;

	return ListaMatriz;
}

void InsereElemento(MATRIZ_PTR *ListaMatriz, MATRIZ_PTR NovoElemento){
	int i = NovoElemento->i;
	int j = NovoElemento->j;

	MATRIZ_PTR atual = *ListaMatriz;
	MATRIZ_PTR prev = NULL;

	while (atual != NULL && (atual->i < i || (atual->i == i && atual->j < j))){
		prev = atual;
		atual = atual->prox;
	}

	if (prev == NULL)
		*ListaMatriz = NovoElemento;
	else
		prev->prox = NovoElemento;

	NovoElemento->prox = atual;
}

void atribuir_valor_pos(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho){
	if (cabecalho->N_Colunas == 0){
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int i, j;
	double data;
	int leitura;
	MATRIZ_PTR NovoElemento = NULL;

	while (1){
		printf("Digite a linha da posicao: ");
		i = EntradaLimitadaInt(0, cabecalho->N_Linhas - 1);

		printf("Digite a coluna da posicao: ");
		j = EntradaLimitadaInt(0, cabecalho->N_Colunas - 1);

		printf("Digite o valor que deseja atribuir a posicao: ");
		data = EntradaLimitadaDouble((double)INT_MIN, (double)INT_MAX);

		NovoElemento = BuscaElemento(*ListaMatriz, i, j);
		if (NovoElemento != NULL){
			printf("Elemento na posicao (%d,%d) ja cadastrado\n", i, j);
			printf("Deseja cancelar a operacao (-1), tentar novamente (0) ou sobreescrever o elemento (1)");
			leitura = EntradaLimitadaInt(-1, 1);
			if (leitura == 0)
				continue;
			if (leitura == -1)
				return;
		}

		//verifica se a posicao ja esta sendo usada
		if (NovoElemento == NULL){
			NovoElemento = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
			NovoElemento->i = i;
			NovoElemento->j = j;
			NovoElemento->prox = NULL;
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
void consultar_valor_pos(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho){
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0){
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int i = 0, j = 0;
	printf("Digite o valor da linha que deseja consultar: ");
	i = EntradaLimitadaInt(0, cabecalho->N_Linhas - 1);

	printf("Digite o valor da coluna que deseja consultar: ");
	j = EntradaLimitadaInt(0, cabecalho->N_Colunas - 1);

	//busca o valor na matriz
	MATRIZ_PTR Elemento = BuscaElemento(ListaMatriz, i, j);
	if (Elemento == NULL)
		printf("O valor da posicao (%d,%d) e: 0\n", i, j);
	else
		printf("O valor da posicao (%d,%d) ss e: %.4lf\n", i, j, Elemento->data);

	WaitENTER();
	return;
}

void consultar_soma_linha(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho){
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0){
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int linha;
	double soma = 0;

	printf("Digite a linha que deseja consultar: ");
	linha = EntradaLimitadaInt(0, cabecalho->N_Linhas - 1);
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

void consultar_soma_coluna(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho){
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0){
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return;
	}

	int col;
	double soma = 0;

	printf("Digite a coluna que deseja consultar: ");
	col = EntradaLimitadaInt(0, cabecalho->N_Colunas - 1);
	MATRIZ_PTR Elemento = ListaMatriz;

	while (Elemento != NULL){
		if (Elemento->j == col)
			soma += Elemento->data;

		Elemento = Elemento->prox;
	}

	printf("A soma da coluna %d e: %.4lf\n", col, soma);
	WaitENTER();
	return;
}



//---------------------------------------DETERMINANTE---------------------------------------//
void multiplicaLinha(MATRIZ_PTR PrimeiroElemento, double fator){
	int linha = PrimeiroElemento->i;
	MATRIZ_PTR atual = PrimeiroElemento;
	while(atual != NULL && atual->i == linha){
		atual->data *= fator;
		atual = atual->prox;
	}
}

void SomaLinhas(MATRIZ_PTR *ListaMatriz, MATRIZ_PTR Linha, MATRIZ_PTR Inicio, double *Multiplicador){
	int i = Inicio->i;
	MATRIZ_PTR Novo = NULL;
	MATRIZ_PTR atual = Linha;
	double fator = (Linha->data/Inicio->data) * (-1);

	bool DivisaoPor1000 = false;
	//Soma a 1º linha na 2º linha
	//A cada elemento da 1º linha, pega o correspondente (msm coluna) da 2º linha e faz a soma
	while(Inicio != NULL && Inicio->i == i){
		//Enquanto a coluna do elemento da 2º linha estiver antes da coluna do elemento da 1º, vai pegando o proximo valor da 2º
		while(atual != NULL && atual->j < Inicio->j && atual->i == Linha->i)
			atual = atual->prox;

		//Se por acaso achar na 2º linha um elemento com a mesma coluna da 1º q está sendo analisada, soma os valores
		if(atual != NULL && atual->j == Inicio->j && atual->i == Linha->i)
			atual->data += fator*Inicio->data;

		//Se a 2º nao tem um elemento na coluna do elemento da 1º linha, cria um novo elemento na segunda linha com o valor da soma
		else{
			Novo = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
			Novo->data = fator*Inicio->data;
			Novo->i = Linha->i;
			Novo->j = Inicio->j;
			Novo->prox = NULL;
			InsereElemento(ListaMatriz, Novo);
		}

		if((atual != NULL && atual->data  > 10000) || (atual == NULL && Novo->data > 10000))
			DivisaoPor1000 = true;

		Inicio = Inicio->prox;
	}

	if(DivisaoPor1000){
		(*Multiplicador) *= 0.01;
		multiplicaLinha(Linha, 0.01);
	}
}

//Vai pegando todos os valores da diagonal principal, e retorna o resultado da multiplicacao entre eles
double Multiplicacao_Diagonal(MATRIZ_PTR ListaMatriz, int N_Linhas){
	int i;
	double Resul = 1;
	MATRIZ_PTR atual = ListaMatriz;
	for(i = 0; i < N_Linhas; i++){
		atual = BuscaElemento(atual, i, i);
		//Se o elemento procurado é 0, entao o resultado da multiplicacao é 0
		if(atual == NULL)
			return 0;
		
		Resul *= atual->data;
	}
	return Resul;
}

MATRIZ_PTR Elemento_diagonal_gauss(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho, int linha_atual, double* Multiplicador, int passo_a_passo){
	int cont;
	MATRIZ_PTR Inicio;
	int coluna_atual = linha_atual;
	Inicio = BuscaElemento(*ListaMatriz, linha_atual, coluna_atual);
	if(Inicio != NULL && !SaoIguais(Inicio->data, 0))
		return Inicio;
	
	Inicio = NULL;
	for(cont = linha_atual + 1; cont < cabecalho->N_Colunas && (Inicio == NULL || SaoIguais(Inicio->data, 0)); cont++)
		Inicio = BuscaElemento(*ListaMatriz, cont, coluna_atual);
		
	if(Inicio == NULL)
		return NULL;
	
	(*Multiplicador) *= -1;
	//PASSO A PASSO
    if (passo_a_passo == 1){
        printf("Trocando linha %d com a linha %d\n", linha_atual, Inicio->i);
        TrocaLinha(ListaMatriz, linha_atual, Inicio->i);
        Imprime(*ListaMatriz, cabecalho);
        printf("\n\n");
        WaitProsseguir();
    } else
        TrocaLinha(ListaMatriz, linha_atual, Inicio->i);
	
	Imprime(*ListaMatriz, cabecalho);
	printf("\n\n");
	Inicio = BuscaElemento(*ListaMatriz, linha_atual, linha_atual);

	return Inicio;
}

float metodoGauss(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho, int linha_atual, double Multiplicador, int passo_a_passo){
	//Se a matriz estiver fazia, entao a determinante é 0 (necessario aqui?)
	if (ListaMatriz == NULL)
		return 0;

	MATRIZ_PTR temp = *ListaMatriz;

	MATRIZ_PTR Inicio;
	int coluna_atual = linha_atual;
	Inicio = Elemento_diagonal_gauss(ListaMatriz, cabecalho, linha_atual, &Multiplicador, passo_a_passo);
	if(Inicio == NULL){
		printf("Todos os elementos abaixo da diagonal na coluna %d (incluindo o elemento da diagonal) sao zero\n", linha_atual);
		Imprime(*ListaMatriz, cabecalho);
		printf("Por definição, a determinante será zero\n");
		return 0;
	}

	temp = Inicio->prox;

	double resto;
	while(temp != NULL){
		if(temp->j == coluna_atual && !SaoIguais(temp->data, 0)){
			resto = fmod(temp->data, Inicio->data);
			if(!SaoIguais(resto, 0)){
				multiplicaLinha(temp, Inicio->data);
				Multiplicador *= Inicio->data;
				
                //PASSO A PASSO
				if (passo_a_passo == 1){
                    printf("Multiplicando a linha %d, por %.2lf\n", temp->i, Inicio->data);
                    Imprime(*ListaMatriz, cabecalho);
                    printf("\n\n");
                    WaitProsseguir();
                }
			}

            //PASSO A PASSO
			if (passo_a_passo == 1){
                printf("Somando na linha %d, a linha %d multiplicada por %.2lf\n", temp->i, Inicio->i, -temp->data/Inicio->data);
                SomaLinhas(ListaMatriz, temp,  Inicio, &Multiplicador);
                Imprime(*ListaMatriz, cabecalho);
                printf("\n\n");
                WaitProsseguir();
			} else {
                SomaLinhas(ListaMatriz, temp,  Inicio,  &Multiplicador);
			}
		}
		temp = temp->prox;
	}
	
	if(linha_atual < cabecalho->N_Linhas - 2)
		return metodoGauss(ListaMatriz, cabecalho, linha_atual+1, Multiplicador, passo_a_passo);
		
	double Multiplicacao = Multiplicacao_Diagonal(*ListaMatriz, cabecalho->N_Linhas);
	return Multiplicacao/Multiplicador;
}

void CopiaMatriz(MATRIZ_PTR Input, MATRIZ_PTR *Output){
	*Output = NULL;
	MATRIZ_PTR novo = NULL;
	MATRIZ_PTR prev = NULL;
	while(Input != NULL){
		novo = (MATRIZ_PTR)malloc(sizeof(MATRIZ));
		novo->i = Input->i;
		novo->j = Input->j;
		novo->prox = NULL;
		novo->data = Input->data;

		if(prev != NULL)
			prev->prox = novo;
		if(*Output == NULL)
			*Output = novo;

		prev = novo;
		Input = Input->prox;
	}
}

float Determinante(MATRIZ_PTR *ListaMatriz, CABECALHO_PTR cabecalho, int passo_a_passo){
	if (cabecalho->N_Colunas == 0 || cabecalho->N_Linhas == 0){
		printf("Essa matriz esta vazia.\n");
		WaitENTER();
		return ERRO;
	}

	if (cabecalho->N_Colunas != cabecalho->N_Linhas){
		printf("Essa matriz nao é quadrada, não existe determinante.\n");
		WaitENTER();
		return ERRO;
	}

	double valor;
	if (cabecalho->N_Linhas == 1)
		return BuscaValor(*ListaMatriz, 0, 0);
	
	if (cabecalho->N_Linhas == 2){
		valor =  BuscaValor(*ListaMatriz, 0, 0) * BuscaValor(*ListaMatriz, 1, 1);
		valor -= BuscaValor(*ListaMatriz, 0, 1) * BuscaValor(*ListaMatriz, 1, 0);
		return valor;
	}

	double Resultado;
	MATRIZ_PTR Copia;
	CopiaMatriz(*ListaMatriz, &Copia);
	Resultado =  metodoGauss(&Copia, cabecalho, 0, 1, passo_a_passo);
	Exclui_Matriz(&Copia);

	if (passo_a_passo == 1){
        printf("Pode-se observar que aqui possuimos uma matriz triangular, em que os elementos abaixo da diagonal principal tem valor 0\n");
        printf("Assim, o valor do determinante e o produto dos elementos da diagonal principal\n\n\n");
	}
	return Resultado;
}




//------------------------------------------INTERFACE------------------------------------------//
//Informa ao usuario a descricao do programa e criadores
void MenuSobre(){
	Limpa_tela();
	printf("                    Gerenciador de notas\n");
	printf("                       Sobre o projeto       \n\n\n\n\n\n");
	printf("        Programa para gerenciamento de matrizes esparsas\n\n");
	printf("     As posicões vazias sao tomadas como contendo o valor 0\n\n");
	printf(" Projeto da disciplina de Introducao a Ciencia da Computacao I\n\n");
	printf("                 Universidade de Sao Paulo\n\n\n");
	printf("\n\nPressione ENTER para seguir para as informacoes dos autores\n\n");
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

void WaitProsseguir(){
	printf("\n\n        Pressione ENTER para prosseguir\n\n");
	char c = getchar();
	while (c != '\n')
		c = getchar();
}

void WaitENTER(){
	printf("\n\n        Pressione ENTER para voltar ao menu principal\n\n");
	char c = getchar();
	while (c != '\n')
		c = getchar();
}

void Limpa_tela(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	return;
}

int menu_principal(){
	Limpa_tela();
	printf("                             Matriz Esparsa\n");
	printf("\n\n\n\n\n");
	printf("1 - Criar matriz                              2 - Consultar valor de uma posicao\n");
	printf("3 - Consultar valor soma de linha             4 - Consultar valor de soma de coluna\n");
	printf("5 - Atribuir valor a uma posicao              6 - Sobre\n");
	printf("7 - Calcular o determinante                   8 - Sair\n\n\n\n\n\n");
	printf("Digite a opcao desejada: ");
	return EntradaLimitadaInt(1, 7);
}

void splash_screen(){
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


//------------------------------------------SYSTEM------------------------------------------//
int EntradaLimitadaInt(int min, int max){
	int c;
	while (true && !false){
		while(!ReadInt(&c))
			printf("Entrada invalida. Digite novamente: ");
			
		if(c < min || c > max)
			printf("Valor invalido. Digite algo entre %d e %d. \nDigite novamente: ", min, max);
		else
			break;
	}

	return c;
}

double EntradaLimitadaDouble(double min, double max){
	double c;
	while (true && !false){
		while(!ReadDouble(&c))
			printf("Entrada invalida. Digite novamente: ");

		if(c < (min+TOLERANCIA) || c > (max-TOLERANCIA))
			printf("Valor invalido. Digite algo entre %.2lf e %.2lf. \nDigite novamente: ", min, max);
		else
			break;
	}

	return c;
}

bool SaoIguais(double N1, double N2){
	if(N1 > N2-TOLERANCIA && N1 < N2+TOLERANCIA)
		return true;
	else
		return false;
}


//Le um inteiro do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadInt(int *numero){
	bool negativo = false;

	//Limpa o buffer inicial at� encontrar um numero ou ate o buffer acabar
	char c = getchar();
	if (c == '\n' || c == '\0')
		c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9')){
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
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9'){
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Certifica que o buffer continua limpo depois da leitura
	while (c != '\n' && c != '\0')
		c = getchar();

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
int ReadDouble(double *numero){
	int i;
	bool negativo = false;

	//Limpa o buffer inicial at� encontrar um numero ou ate o buffer acabar
	char c = getchar();
	if (c == '\n' || c == '\0')
		c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9'))	{
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
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9'){
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Caso o usuario digitou um '.' ou uma ',', le os proximos digitos ate acabar
	if (c == '.' || c == ','){
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
		c = getchar();

	//Se o usuario digitou um '-' antes de digitar o numero, deixa o numero negativo
	if (negativo)
		*numero *= -1;

	//retorna sucesso
	return 1;
}



void Imprime(MATRIZ_PTR ListaMatriz, CABECALHO_PTR cabecalho){ 
	int Last_i = 0, Last_j = 0;
	int i, j;
	while(ListaMatriz != NULL){		
		while(Last_i != ListaMatriz->i){
			for(j = Last_j; j < cabecalho->N_Colunas; j++)
				printf(" 000.0  ");
			Last_j = 0;
			Last_i++;
			printf("\n");
		}
		
		for(j = Last_j; j < ListaMatriz->j; j++){
			printf(" 000.0  ");
			Last_j++;
		}

		if(SaoIguais(ListaMatriz->data, 0))
			printf(" 000.0  ");
		else if (ListaMatriz->data < 0)
			printf("%06.1f  ", ListaMatriz->data);
		else
			printf(" %05.1f  ", ListaMatriz->data);
		Last_i = ListaMatriz->i;
		Last_j = ListaMatriz->j;
		Last_j++;
		ListaMatriz = ListaMatriz->prox;
	}


	for (j = Last_j; j < cabecalho->N_Colunas; j++)
		printf(" 000.0  ");

	for(i = Last_i; i < cabecalho->N_Linhas - 1; i++){
		printf("\n");
		for(j = 0; j < cabecalho->N_Colunas; j++)
			printf(" 000.0  ");
	}
	printf("\n\n");
}

//Refazer, muito ilegivel (mas funciona)
void TrocaLinha(MATRIZ_PTR *ListaMatriz, int Linha_1, int Linha_2){
	if(Linha_1 >= Linha_2)
		return;

	MATRIZ_PTR temp = *ListaMatriz;
	MATRIZ_PTR Fim1 = NULL,    Fim2 = NULL;
	MATRIZ_PTR Inicio1 = NULL, Inicio2 = NULL;
	bool ExisteL1 = false, ExisteL2 = false;
	bool Elementos_Antes_L1 = false, Elementos_Entre_L1eL2 = false;

	while(temp != NULL && temp->i < Linha_1){
		Inicio1 = temp;
		temp = temp->prox;
	}
	if(Inicio1 != NULL)
		Elementos_Antes_L1 = true;

	while(temp != NULL && temp->i == Linha_1){
		Fim1 = temp;
		temp->i = Linha_2;
		temp = temp->prox;	
	}
	if(Fim1 != NULL)
		ExisteL1 = true;

	while(temp != NULL && temp->i < Linha_2){
		Inicio2 = temp;
		temp = temp->prox;
	}
	if(Inicio2 != NULL)
		Elementos_Entre_L1eL2 = true;

	while(temp != NULL && temp->i == Linha_2){
		Fim2 = temp;
		temp->i = Linha_1;
		temp = temp->prox;	
	}
	if(Fim2 != NULL)
		ExisteL2 = true;


	if(!ExisteL1 && !ExisteL2)
		return;
	if(!Elementos_Entre_L1eL2 && (!ExisteL1 || !ExisteL2))
		return;
	
	MATRIZ_PTR Pos_Fim1 = NULL,    Pos_Fim2 = NULL;
	MATRIZ_PTR Pos_Inicio1 = NULL, Pos_Inicio2 = NULL;

	if(Elementos_Antes_L1)
		Pos_Inicio1 = Inicio1->prox;
	else{
		Pos_Inicio1 = *ListaMatriz;
		if(!ExisteL1)
			Pos_Fim1 = *ListaMatriz;
	}

	if(Elementos_Entre_L1eL2)
		Pos_Inicio2 = Inicio2->prox;
	else{
		Pos_Inicio2 = Fim1->prox;;
		if(Elementos_Antes_L1)
			Inicio1->prox = Pos_Inicio2;
		else
			*ListaMatriz = Pos_Inicio2;
		
		temp = Fim2->prox;
		Fim2->prox = Pos_Inicio1;
		Fim1->prox = temp;
		return;
	}

	if(ExisteL2)
		Pos_Fim2 = Fim2->prox;
	else
		Pos_Fim2 = Pos_Inicio2;


	if(ExisteL1){
		Pos_Fim1 = Fim1->prox;
		Fim1->prox = Pos_Fim2;
		Inicio2->prox = Pos_Inicio1;
	}
	else if (Elementos_Antes_L1){
		Pos_Fim1 = Pos_Inicio1;
		Inicio2->prox = Pos_Fim2;
	}

	
	if(ExisteL2){
		Fim2->prox = Pos_Fim1;
		if(Elementos_Antes_L1)
			Inicio1->prox = Pos_Inicio2;
		else
			*ListaMatriz = Pos_Inicio2;
	} 
	else{
		if(Elementos_Antes_L1)
			Inicio1->prox = Pos_Fim1;
		else
			*ListaMatriz = Pos_Fim1;
	}
}