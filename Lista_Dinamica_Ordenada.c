#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}NODE;
	NODE *primeiro = NULL;


void adicionar(int x){
	if(primeiro == NULL){
		primeiro = (NODE*)malloc(sizeof(NODE));
		primeiro->data = x;
		primeiro->next = NULL;	
	}
	else{
		NODE *t;
		t = (NODE*)malloc(sizeof(NODE));
		t->data = x;
		t->next = NULL;
		if(x <= primeiro->data){
			t->next = primeiro;
			primeiro = t;
		}
		else{
			NODE *r;
			r = primeiro;
			while(r->next && r->next->data <= x){
				r = r->next;
			}
			t->next = r->next;
			r->next = t;	
		}
	}
}


void remover(){
	int x;
	printf("Digite o indice do elemento que sera removido da lista\n");
	scanf("%d", &x);
	NODE *p;
	p = primeiro;
	if(x == 0){
		p = primeiro;
		primeiro = primeiro->next;
		free(p);
		printf("Elemento de indice 0 deletado\n");
	}
	else{
		NODE *q = NULL;
		int i;
		for(i=1 ; i<=x ; i++){
			q= p;
			p = p->next;
			if(p==NULL){
				printf("A lista nao possui o indice digitado\n");
				system("pause");
				return;
			}
		}
		q->next = p->next;
		free(p);
		printf("Elemento de indice %d deletado\n", i);
	}
}


void display(){
	NODE *p;
	p = primeiro;
	int i =0;
	while(p != NULL){
		printf("\n---Imprimindo o elemento %d no indice %d---\n", p->data, i);
		i++;
		p = p->next;
	}
}


void contar(NODE *primeiro){
	NODE *p;
	p = primeiro;
	int count = 0;
	while(p != NULL){
		count++;
		p = p->next;
	}
	printf("A lista tem um total de %d elementos\n", count);
}


void estaVazia(NODE *primeiro){
	if(primeiro == NULL){
		printf("A lista esta vazia\n");
	}
	else{
		printf("A lista nao esta vazia\n");
	}
}


void maior(){
	NODE *p;
	p = primeiro;
	int x = -9999, i=0;
	int aux = 0;
	while(p != NULL){
		if(p->data >= x){
			x = p->data;
			aux=i;
		}
		p = p->next;
		i++;
	}
	printf("O maior elemento da lista e o %d que esta no indice %d\n", x, aux);
}


void menor(){
	NODE *p;
	p = primeiro;
	int x = 9999, i=0;
	int aux = 0;
	while(p != NULL){
		if(p->data <= x){
			x = p->data;
			aux=i;
		}
		p = p->next;
		i++;
	}
	printf("O menor elemento da lista e o %d que esta no indice %d\n", x, aux);
}


int main(void){
	while(1){
		int opcao;
		system("pause");
		printf("\n---------------------------------\n");
		printf("\nLista ordenada crescente por Lucas Gabriel Winter\n");
		printf("\nEscolha uma opcao\n");
		printf("1 - Insere elemento na lista\n");
		printf("2 - Remove elemento da lista\n");
		printf("3 - Imprime os elementos da lista\n");
		printf("4 - Mostra o tamanho da lista\n");
		printf("5 - Mostra o menor elemento da lista\n");
		printf("6 - Mostra o maior elemento da lista\n");
		printf("7 - Verifica se a lista esta vazia\n");
		printf("8 - Encerra o programa\n");
		printf("\n---------------------------------\n");
		scanf("%d", &opcao);
		switch(opcao){
			int num;
			case 1:
				printf("Digite o inteiro a ser inserido na lista\n");
				scanf("%d", &num);
				adicionar(num);
				display();
				break;
			case 2:
				remover();
				display();
				break;
			case 3:
				display();
				break;
			case 4:
				contar(primeiro);
			case 5:
				menor();
				break;
			case 6:
				maior();
				break;
			case 7:
				estaVazia(primeiro);
				break;
			case 8:
				return 0;
				break;
			default:
				printf("Valor digitado invalido\n");
				break;
		}
	}
}
