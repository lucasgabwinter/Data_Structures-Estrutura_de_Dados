#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
	//struct com todos os dados necessários pelo programa
	int cod;
	char nome[30];
	char sexo;
	int idade;
	float peso;
	float altura;
	char telefone[20];
	//dois ponteiros do mesmo tipo dessa struct, um para o proximo node, outro para o node anterior
	struct node *next;
	struct node *prev;
}NODE;
	//NOD da sentinela como variável global
	NODE *sentinela = NULL;
	

void iniciar(){
	//alocação de memória para a sentinela
	sentinela = (NODE*)malloc(sizeof(NODE));
	//esse código não será acessado pelo programa, é apenas representativo
	sentinela->cod=-1;
	//os ponteiros da sentinela são setados, inicialmente, como nulos
	sentinela->next=NULL;
	sentinela->prev=NULL;
}


void adicionar(NODE *dados){
	//a cada nova linha é criado novo NODE e alocado de memória para ele
	NODE *p;
	p = (NODE*)malloc(sizeof(NODE));
	//atribuição das características lidas no arquivo para o NODE criado
	p->cod = dados->cod;
	p->sexo = dados->sexo;
	p->idade = dados->idade;
	strcpy(p->nome, dados->nome);
	p->peso = dados->peso;
	p->altura = dados->altura;
	strcpy(p->telefone, dados->telefone);
	//a cada NODE criado os ponteiros são setados para NULL, por padrão
	p->next=NULL;
	p->prev=NULL;
	//nesse caso será a primeira criação de NODE, ele e a sentinela irão se apontar
	if(sentinela->next==NULL){
		sentinela->next = p;
		sentinela->prev = p;
		p->next = sentinela;
		p->prev = sentinela;
	}
	//checa se o código do NODE é menor que o próximo da sentinela, e faz as atribuições de ponteiros
	else if(p->cod <= sentinela->next->cod){
		sentinela->next->prev = p;
		p->next = sentinela->next;
		p->prev = sentinela;
		sentinela->next = p;
	}
	//checa se o código do NODE é maior que o anterior da sentinela, e faz as atribuições de ponteiros
	else if(p->cod >= sentinela->prev->cod){
		p->prev = sentinela->prev;
		sentinela->prev->next = p;
		p->next = sentinela;
		sentinela->prev = p;
	}
	//nesse caso é criado um ponteiro auxiliar para percorrer a lista até achar o código maior ou igual ao cód. do NODE
	//após encontrar, faz as atribuições de ponteiros
	else{
		NODE *paux = sentinela;
		while(paux->cod <= p->cod){
			paux = paux->next;
		}
		p->prev = paux->prev;
		paux->prev->next = p;
		p->next = paux;
		paux->prev = p;
		
	}
}


void terminaPrograma(FILE* entrada, FILE* saida){
	//fecha os arquivos de entrada e saída
	fclose(entrada);	
	fclose(saida);
	//caso só exista o NODE sentinela, é desalocado memória para este
	if(sentinela->next == NULL){
		free(sentinela);
	}
	//caso existem mais NODES, é desalocado memória para todos
	else{
		//é criado dois ponteiros auxiliares que percorres a lista, desalocando a memória dos NODES
		NODE *p;
		p = sentinela->next;
		while(p != sentinela){
			NODE *q = p;
			p = p->next;
			free(q);
		}
		//desaloca memória da sentinela	
		free(sentinela);
	}
	//termina o programa
	exit(0);
}


void escreveCrescente(FILE* entrada, FILE* saida){
	NODE *p;
	//é criado um ponteiro auxiliar que percorre toda a lista para impressão
	p = sentinela->next;
	//enquanto o ponteiro auxiliar não retornar até a sentinela as informações serão impressas no arquivo
	while(p != sentinela){
		fprintf(saida,"{%d,%s,%c,%d,%g,%.2f,%s}\n", p->cod, p->nome, p->sexo,
		p->idade, p->peso, p->altura, p->telefone);
		//atualização do ponteiro auxiliar
		p = p->next;
	}
	//chama a função para desalocar memória e fechar os arquivos
	terminaPrograma(entrada, saida);
}


void escreveDecrescente(FILE* entrada, FILE* saida){
	//é criado um ponteiro auxiliar que percorre toda a lista para impressão, em sentido reverso
	NODE *p;
	p = sentinela->prev;
	//enquanto o ponteiro auxiliar não retornar até a sentinela as informações serão impressas no arquivo
	while(p != sentinela){
		fprintf(saida,"{%d,%s,%c,%d,%g,%.2f,%s}\n", p->cod, p->nome, p->sexo,
		p->idade, p->peso, p->altura, p->telefone);
		//atualização do ponteiro auxiliar
		p = p->prev;
	}
	//chama a função para desalocar memória e fechar os arquivos
	terminaPrograma(entrada, saida);
}


int escreveArqInvalido(FILE* entrada, FILE* saida){
	char fraseinv[99] = "Arquivo inválido!";
	//escreve arquivo inválido e checa pelo sucesso
	int retorno = fputs(fraseinv, saida);
	if (retorno == EOF){
		printf("Erro ao escrever arquivo.\n");
		return 0;
	}
	//chama a função para desalocar memória e fechar os arquivos
	terminaPrograma(entrada, saida);
}


int escreveElementoNEncontrado(FILE* entrada, FILE* saida){
	char fraseinv[99] = "Elemento não encontrado!";
	int retorno = fputs(fraseinv, saida);
	//escreve elemento não encontrado e checa pelo sucesso
	if (retorno == EOF){
		printf("Erro ao escrever arquivo.\n");
		return 0;
	}
	//chama a função para desalocar memória e fechar os arquivos 
	terminaPrograma(entrada, saida);
}


void consulta(int n, FILE* entrada, FILE* saida){
	NODE *p;
	//cria um ponteiro auxiliar que percorre a lista até encontrar o código informado
	p = sentinela->next;
	while(p != sentinela){
		if(p->cod == n){
			//se encontrar o código, o programa imprime as informações no arquivo de saída e chama a função terminaPrograma
			fprintf(saida,"{%d,%s,%c,%d,%g,%.2f,%s}\n", p->cod, p->nome, p->sexo,
			p->idade, p->peso, p->altura, p->telefone);
			terminaPrograma(entrada, saida);
		}
		//atualização do ponteiro auxiliar
		p = p->next;
	}
	//caso não encontre o código, é impresso elemento não encontrado
	char fraseinv[99] = "Elemento não encontrado!";
	int retorno = fputs(fraseinv, saida);
	if (retorno == EOF){
		printf("Erro ao escrever arquivo.\n");
	}
	//chama a função para desalocar memória e fechar os arquivos 
	terminaPrograma(entrada, saida);
}


int main(int argc, const char * argv[]){
	// usando o argc 
	printf("Numero de parametros fornecidos: %d\n", argc);
	//checa se a quantidade de parâmetros informada é válida
	if(argc!= 3 && argc!= 4) {
		printf("Quantidade de parametros invalida\n");
		printf("Favor usar o terminal para informar os arquivos de entrada e saida\n");
		return 0;
	}  
	//imprime os parâmetros informados
	int j = 0;
	for(j = 0; j < argc; j++) {
		printf("argv[%d] = %s\n", j, argv[j]);
	}
	//abre dois arquivos, um de entrada, outro de saída
	FILE* entrada = fopen(argv[1], "r");
	FILE* saida   = fopen(argv[2], "w");
	// checa erros de abertura dos arquivos
	if(entrada == NULL || saida == NULL) {
		printf("Erro: algum dos arquivos nao pode ser criado corretamente\n");
		return 0;
	}
	//chama a função para iniciar a sentinela
	iniciar();
	//essa chave visa checar se o usuário inseriu um número para consulta de código, mas não inseriu o código "3"
	int keyconsulta=0;
	char frase[100];
	//percorre todo o arquivo até o final
	while(fscanf(entrada,"%[^\n]%*c",frase) !=EOF){
		//analisa o tamanho da string para verificar erros em linhas com poucos parâmetros
		if(strlen(frase) > 1 && strlen(frase)<30 && keyconsulta==0){
			escreveArqInvalido(entrada, saida);
		}
		//caso exista algum dos números abaixo, o programa imprime elemento não encontrado
		else if(strlen(frase)==1){
			if(frase[0]=='0' || frase[0]=='4' || frase[0]=='5'|| frase[0]=='6'|| frase[0]=='7'
			|| frase[0]=='8'|| frase[0]=='9'){
				escreveElementoNEncontrado(entrada, saida);
			}
			//se o código 3 estiver no arquivo, o programa altera a chave de consulta
			else if(frase[0]=='3'){
					keyconsulta=1;
			}
			//esse  trecho de código acusa erros de quando existe caracteres isolados estranhos no arquivo, como letras
			else if(frase[0]!='1' && frase[0]!='2' && frase[0]!='3'){
				escreveArqInvalido(entrada, saida);
			}
		}
	}
	//esse trecho de código acusa quando o arquivo está em branco e imprime arquivo inválido
	if (entrada != NULL) {
		fseek (entrada, 0, SEEK_END);
		int size = ftell(entrada);
		if (size == 0) {
			escreveArqInvalido(entrada, saida);
		}
	}
	//checados as possíveis falhas, o arquivo é rebobinado para leitura dos parâmetros
	rewind(entrada);
	//esse ponteiro será responsável por enviar os dados lidos do arquivo para a função "adicionar"
	NODE *pstruct;
	pstruct = (NODE*)malloc(sizeof(NODE));
	//enquanto existirem 7 parâmetros(código, nome, sexo, etc) o arquivo é lido e cada nova linha é enviada
	//para a função adicionar
	while(fscanf(entrada," %*c %d,%29[^,],%c,%d,%f,%f,%19[^}] %*c", &pstruct->cod, pstruct->nome, &pstruct->sexo,
	&pstruct->idade, &pstruct->peso, &pstruct->altura, pstruct->telefone)==7){
		adicionar(pstruct);
	}
	//desaloca memória do ponteiro que levou os dados para a função "adicionar"
	free(pstruct);
	//após a leitura dos parâmetros, o arquivo é rebobinado para verificar os códigos das tarefas
	rewind(entrada);
	//variável para armazenar e checar os códigos das tarefas
	char frase2[100];
	//essa variável é utilizada no caso da consulta, (código de tarefa 3)
	int nconsulta;
	//le as linhas até o final do arquivo
	while(fscanf(entrada,"%[^\n]%*c",frase2) !=EOF){
		//checa se o tamanho da string é "1"
	 	if(strlen(frase2)==1){
	 		//quando o código de operação for "1", chama a função para imprimir em ordem crescente
			if(frase2[0]=='1'){
				escreveCrescente(entrada, saida);
			}
			//quando o código de operação for "2", chama a função para imprimir em ordem decrescente
			else if(frase2[0]=='2'){
			escreveDecrescente(entrada, saida);
			}
		}
		//checa se o tamanho da string é "2", pois esse será o código a ser consultado
		else if(strlen(frase2)==2){
			//converte o código a ser consultado para um inteiro
			nconsulta = atoi(frase2);
			//chama a função para consultar
			consulta(nconsulta, entrada, saida);
		}
	}
	//chama a função para desalocar memória da lista e fechar os arquivos
	terminaPrograma(entrada, saida);
	return 0;
}
