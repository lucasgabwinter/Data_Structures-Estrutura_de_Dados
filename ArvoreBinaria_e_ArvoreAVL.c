#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

/*
Algortimo para organizar palavras em ordem alfabética e comparar o desempenho das árvres binária e AVL
esque algoritmo requer um arquivo .txt como entrada
*/


//ambas terao o mesmo TDA
typedef struct NoArvore* PtrNoArvore;
typedef struct NoArvore{
PtrNoArvore direita, esquerda;
char palav[50];
//contador que vai contar o numero de repeticoes de cada palavra
int count;
//altura e utilizada somente para as arvores AVL
int altura; 
} NoArvore;
//variaveis globais que vao indicar o numero de comparacoes
int compBinaria = 0;
int compAVL = 0;

//inicio  (igual tanto para arvore binaria como avl)
//-----------------------------------------------------------------------
void iniciaArvore(PtrNoArvore *r){
	(*r) = NULL;
}


//arvore binaria
//-----------------------------------------------------------------------
bool insereArvoreBinaria(PtrNoArvore *No, char *palavra){
	//o contador de comparacoes conta a cada comparacao se o no eh nulo, e a cada comparacao se a chave eh igual (palavra)
	//compara se o no eh nulo
	compBinaria ++;
	if((*No)== NULL){
		(*No) = malloc(sizeof(NoArvore));
		strcpy((*No)->palav, palavra);
		(*No)->count=1;
		(*No)->direita = NULL;
		(*No)->esquerda = NULL;
		return true;
	}
	//caso a chave seja igual o contador eh incrementado
	compBinaria ++;
	if(strcmp((*No)->palav, palavra) == 0){
		(*No)->count++;
		return true;
	}
	else if(strcmp((*No)->palav, palavra)<0){
		return(insereArvoreBinaria((&(*No)->direita), palavra));
	}
	else{
		return(insereArvoreBinaria((&(*No)->esquerda), palavra));
	}
}


//avl
//-----------------------------------------------------------------------
//essa funcao eh utilizada para checar a altura do no
int alturaArvoreAVL(PtrNoArvore *no) {
	if ((*no) == NULL) return 0;
	else return (*no)->altura;
}

//atualiza a altura do no
int atualizaAltura(PtrNoArvore *esquerda, PtrNoArvore *direita) {
	int ae, ad, ret;
	ae = alturaArvoreAVL(&(*esquerda));
	ad = alturaArvoreAVL(&(*direita));
	if(ae >= ad) {
		ret = ae + 1;
	} else {
		ret = ad + 1;
	}
	return (ret);
}

//rotacao simples para a direita
void rotacaoSimplesDireita(PtrNoArvore *p) {
	PtrNoArvore v = (*p)->esquerda;
	(*p)->esquerda = v->direita;
	v->direita = (*p);
	(*p)->altura = atualizaAltura(&(*p)->esquerda, &(*p)->direita);
	v->altura = atualizaAltura(&(v->esquerda), &(v->direita));
	(*p) = v;
}

//rotacao simples para a esquerda
void rotacaoSimplesEsquerda(PtrNoArvore *p) {
	PtrNoArvore v = (*p)->direita;
	(*p)->direita = v->esquerda;
	v->esquerda = (*p);
	(*p)->altura = atualizaAltura(&(*p)->esquerda, &(*p)->direita);
	v->altura = atualizaAltura(&(v->esquerda), &(v->direita));
	(*p) = v;
}

//rotacao dupla para a direita
void rotacaoDuplaDireita(PtrNoArvore *p) {
	PtrNoArvore u = (*p)->esquerda;
	PtrNoArvore v = u->direita;
	u->direita = v->esquerda;
	(*p)->esquerda = v->direita;
	v->esquerda = u;
	v->direita = (*p);
	(*p)->altura = atualizaAltura(&(*p)->esquerda, &(*p)->direita);
	v->altura = atualizaAltura(&(v->esquerda), &(v->direita));
	u->altura = atualizaAltura(&(u->esquerda), &(u->direita));
	(*p) = v;
}

//rotacao dupla para a esquerda
void rotacaoDuplaEsquerda(PtrNoArvore *p){
	PtrNoArvore u = (*p)->direita;
	PtrNoArvore v = u->esquerda;
	u->esquerda = v->direita;
	(*p)->direita = v->esquerda;
	v->esquerda = (*p);
	v->direita = u;
	(*p)->altura = atualizaAltura(&(*p)->esquerda, &(*p)->direita);
	v->altura = atualizaAltura(&(v->esquerda), &(v->direita));
	u->altura = atualizaAltura(&(u->esquerda), &(u->direita));
	(*p) = v;
}


void aplicarRotacoes(PtrNoArvore *no) { // se entrou, o fator de balanceamento do *no eh -2, ou 2
	int ae, ad, fatorBalanceamento;
	ae = alturaArvoreAVL(&(*no)->esquerda);
	ad = alturaArvoreAVL(&(*no)->direita);
	fatorBalanceamento = ad - ae;
	PtrNoArvore u;
	int aUdireita, aUesquerda;
	if(fatorBalanceamento == -2) {
		u = (*no)->esquerda;
		aUdireita = alturaArvoreAVL(&u->direita);
		aUesquerda = alturaArvoreAVL(&u->esquerda);
		if(aUesquerda >= aUdireita) {
			rotacaoSimplesDireita(&(*no));
		} else {
			rotacaoDuplaDireita(&(*no));
		}
	} 
	else { // == +2
		u = (*no)->direita;
		aUdireita = alturaArvoreAVL(&u->direita);
		aUesquerda = alturaArvoreAVL(&u->esquerda);
		if(aUdireita >= aUesquerda) {
			rotacaoSimplesEsquerda(&(*no));
		} 
		else {
			rotacaoDuplaEsquerda(&(*no));
		}
	}
}


bool insereArvoreAVL(PtrNoArvore *No, char *palavra) {
	//o contador de comparacoes conta a cada comparacao se o no eh nulo, e a cada comparacao se a chave eh igual (palavra)
	compAVL++;
	if((*No) == NULL) {
		(*No) = malloc(sizeof(NoArvore));
		(*No)->count=1;
		(*No)->esquerda = NULL;
		(*No)->direita = NULL;
		strcpy((*No)->palav, palavra);
		(*No)->altura = 1;
		return true;
	}
	//caso a palavra ja exista, o contador eh incrementado (count)
	compAVL++;
	if(strcmp((*No)->palav, palavra) == 0){
		(*No)->count++;
		return true;
	}
	//esse booleano eh utilizado para verificar se teve insercao de novo elemento
	bool ret;
	if(strcmp((*No)->palav, palavra)<0) {
		ret = insereArvoreAVL(&(*No)->direita, palavra);
	} 
	else {
		ret = insereArvoreAVL(&(*No)->esquerda, palavra);
	}
	// se nao inseriu elemento, nao desbalanceou
	if(!ret) return false;
	// PODE ter desbalanceamento (*no)
	int ad, ae, fatorBalanceamento;
	ad = alturaArvoreAVL(&(*No)->direita);
	ae = alturaArvoreAVL(&(*No)->esquerda);
	fatorBalanceamento = ad - ae;
	// valores aceitaveis = {-1, 0, 1}
	// valor desbalanceamento = {-2, +2}
	if(fatorBalanceamento == 2 || fatorBalanceamento == -2) {
		aplicarRotacoes(&(*No));
	}
	//atualizar a altura do no atual (*no)
	(*No)->altura = atualizaAltura(&(*No)->esquerda, &(*No)->direita);
	return true;
}
//-----------------------------------------------------------------------


//impressao e desalocador de memoria
//-----------------------------------------------------------------------
void EmOrdemArvore(PtrNoArvore *no) {
if((*no) == NULL) return; //clausula base
	EmOrdemArvore(&(*no)->esquerda);
	printf("	%s: %d\n", (*no)->palav, (*no)->count);
	EmOrdemArvore(&(*no)->direita);
}


void EmOrdemPrincipal(PtrNoArvore *no) {
	printf("frequencia das palavras:\n\n");
	EmOrdemArvore(&(*no));
}


void desalocaMemoria(PtrNoArvore *no) {
if((*no) == NULL) return; //clausula base
	desalocaMemoria(&(*no)->esquerda);
	desalocaMemoria(&(*no)->direita);
	free((*no));
}


void imprimeBinaria(double tempo, int compBinaria){
	printf("arvore binaria:\n\n");
	printf("	%d comparacoes\n", compBinaria);
	printf("	%f segundos\n\n", tempo);
}


void imprimeAVL(double tempo, int compAVL){
	printf("arvore avl:\n\n");
	printf("	%d comparacoes\n", compAVL);
	printf("	%f segundos\n\n", tempo);
}


//varredura do arquivo (leitura) e insercao das palavras nas arvores
//-----------------------------------------------------------------------
void ImplementaArvoreBinaria(PtrNoArvore *raizBinaria, FILE* arq){
	int i, j=0;
	char palavra[50];
	char ch, ch2;
	while ((ch = fgetc(arq)) != EOF){
		//caso o caracter seja diferente dessas pontuacoees, o caractere nao e inserido na palavra
		if(ch !=',' && ch !='.' && ch !=' ' && ch !='\n' && ch !=';' && ch !=':'){
			palavra[j] = tolower(ch);
			palavra[j+1] = '\0';
			j++;
		}
		//se for uma das pontuacoes, significa uma quebra de palavra, e parte para insercao na arvore
		else{
			//esse if tem o intuito de verificar problemas como duas virgulas seguidas
			//ou entao dois espacos seguidos
			if(palavra[0]!=',' && palavra[0] !='.' && palavra[0] !=' ' 
			&& palavra[0] !='\n' && palavra[0] !=';' && palavra[0] !=':'){
				insereArvoreBinaria(raizBinaria, palavra);
			}
			j=0;
			palavra[0] = ':';
		}
	}
	//ultima insercao
	//esse if tem o intuito de verificar se a ultima palavra inserida terminou com pontuacao ou 
	//simplementes sem ponto. Caso ela terminou sem ponto, a ultima palavra nao eh inserida nesse if
	if(ch == -1 && palavra[0] != ':'){
		insereArvoreBinaria(raizBinaria, palavra);	
	}
}


void ImplementaArvoreAVL(PtrNoArvore *raizAVL, FILE *arq){
	int i, j=0;
	char palavra[50];
	char ch, ch2;
	while ((ch = fgetc(arq)) != EOF){
		//caso o caracter seja diferente dessas pontuacoees, o caractere nao e inserido na palavra
		if(ch !=',' && ch !='.' && ch !=' ' && ch !='\n' && ch !=';' && ch !=':'){
			palavra[j] = tolower(ch);
			palavra[j+1] = '\0';
			j++;
		}
		//se for uma das pontuacoes, significa uma quebra de palavra, e parte para insercao na arvore
		else{
			//esse if tem o intuito de verificar problemas como duas virgulas seguidas
			//ou entao dois espacos seguidos
			if(palavra[0]!=',' && palavra[0] !='.' && palavra[0] !=' ' 
			&& palavra[0] !='\n' && palavra[0] !=';' && palavra[0] !=':'){
				insereArvoreAVL(raizAVL, palavra);
			}
			j=0;
			palavra[0] = ':';
		}
	}
	//ultima insercao
	//esse if tem o intuito de verificar se a ultima palavra inserida terminou com pontuacao ou 
	//simplementes sem ponto. Caso ela terminou sem ponto, a ultima palavra nao eh inserida nesse if
	if(ch == -1 && palavra[0] != ':'){
		insereArvoreAVL(raizAVL, palavra);	
	}
}


//------------------------------------------------------------------------------------------------------
int main(int argc, const char * argv[]){
	setlocale(LC_ALL, "Portuguese_Brazil");
	// usando o argc
	printf("Trabalho de Estrutura de Dados.\n");
	printf("Luca Aguiar Costa Carvalho e Lucas Gabriel Winter.\n");
	printf("Profa. Maria Adelina Silva Brito.\n");
	printf("Numero de parametros fornecidos: %d\n", argc);
	//checa se a quantidade de parâmetros informada é válida
	//consideramos a possibilidade de uma entrada a mais no caso de usar o Dev-C++
	if(argc!= 2 && argc!= 3) {
		printf("Quantidade de parametros invalida\n");
		printf("Favor usar o terminal para informar os arquivos de entrada e o metodo!\n");
		printf("Escolha informando o arquivo de entrada e digitando arvore-binaria ou arvore-avl!\n");
		return 0;
	}  
	//imprime os parametros informados
	int k = 0;
	for(k = 0; k < argc; k++) {
		printf("argv[%d] = %s\n", k, argv[k]);
	}
	//essa chave vai verificar qual arvore foi chamada pelo terminal
	int chave = 0;
	if(strcmp(argv[2], "arvore-binaria") == 0 || strcmp(argv[1], "arvore-binaria") == 0){
		chave = 1;
	}
	else if(strcmp(argv[2], "arvore-avl") == 0 || strcmp(argv[1], "arvore-avl") == 0){
		chave = 2;
	}
	else{
		printf("Metodo digitado invalido! Execute informando o arquivo de entrada e "
		"digitando 'arvore-binaria' ou 'arvore-avl'!");
		return 0;
	}
	//iniciando as arvores e abrindo o arquivo
	PtrNoArvore raizBinaria, raizAVL;
	iniciaArvore(&raizBinaria);
	iniciaArvore(&raizAVL);
	FILE *arq = fopen("entrada2.txt", "r");
	//caso tenha algum problema o arquivo eh encerrado
	if (arq == NULL){
		printf("Erro ao abrir arquivo.\n");
		exit(1);
	}
	//esse trecho de codigo acusa quando o arquivo esta em branco
	if (arq != NULL) {
		fseek (arq, 0, SEEK_END);
		int size = ftell(arq);
		if (size == 0) {
			printf("Arquivo em branco!\n");
			return 0;
		}
	}
	rewind(arq);
	//implementando as arvores binaria e avl
    //contando o tempo para a implementacao da binaria
    clock_t start_tb, end_tb;
	start_tb = clock();
    double total_tb;
	ImplementaArvoreBinaria(&raizBinaria, arq);
	end_tb = clock();
    total_tb = (double)(end_tb - start_tb) / CLOCKS_PER_SEC;
    //rebobinando o arquivo
    rewind(arq);
    //contando o tempo para a implementacao da avl
	clock_t start_tavl, end_tavl;
	start_tavl = clock();
    double total_tavl;
	ImplementaArvoreAVL(&raizAVL, arq);
	end_tavl = clock();
    total_tavl = (double)(end_tavl - start_tavl) / CLOCKS_PER_SEC;
    //comparando os tempos para ver qual arvore sera impressa primeiro
	if(total_tb <= total_tavl){
		imprimeBinaria(total_tb, compBinaria);
		imprimeAVL(total_tavl, compAVL);
	}
	else{
		imprimeAVL(total_tavl, compAVL);
		imprimeBinaria(total_tb, compBinaria);
	}
	//imprime as informacoes dos nos conforme a chamada do terminal (frequencia das palavras)
	if(chave == 1){
		EmOrdemPrincipal(&raizBinaria);		
	}
	else if(chave == 2){
			EmOrdemPrincipal(&raizAVL);		
	}
	//fecha o arquivo e desaloca memoria para os nos da arvore binaria e avl
	fclose(arq);
	desalocaMemoria(&raizBinaria);
	desalocaMemoria(&raizAVL);
	return 0;
}
