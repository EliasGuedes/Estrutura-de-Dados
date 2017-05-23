#include <stdio.h>
#include <stdlib.h>

//Elias Cícero Moreira Guedes


struct cliente{
	char nome[30];
	int cpf;
};

struct fila{						//Duas cabeças.
	struct newNode* inicio;
	struct newNode* final;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};

typedef struct fila Fila;			//Apelido das duas cabeças.
typedef struct  newNode Elem;		//Apelido a um nó qualquer ou de uma "cabeça auxiliar".



			//Métodos auxiliares
//Informa o tamanho da Fila
int tamanho_fila(Fila* fi){
	if(fi == NULL){
		return 0;
	}
	int cont = 0;
	Elem* no = fi->inicio;			//ão precisa ser ponteiro. Ponteiro é o conteudo da cabeça, e fi->inicio é também um dos conteúdos da cabeça.
	while(no != NULL){				//Enquanto a cabeça inicial auxiliar ainda não é o último elemento da fila faça:
		cont++;
		no = no->prox;
	}
	return cont;
}


//verificar se a fila está vazia
int fila_vazia(Fila* fi){
	if(fi == NULL){
		return 1;
	}
	if(fi->inicio == NULL){
		return 1;
	}
	return 0;
}


//imprimi a fila
void Imprimir_fila(fila* fi){
	if(fi == NULL){
		return;
	}
	Elem* aux = fi->inicio;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}			
	
	
			
			//Métodos da lista de exercícios
//Cria uma Fila vazia
Fila* Criar_fila_vazia(){
	Fila* fi = (Fila*) malloc(sizeof(Fila));			//Aloca espaço para um as cabeças.
	if(fi != NULL){
		fi->final = NULL;
		fi->inicio = NULL;
	}
	return fi;
}

//Insere um elemento no final da fila (FIFO = first in, first out)
int Inserir_um_elemento_em_qualquer_na_fila(Fila* fi, struct cliente c){
	if(fi == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = NULL;									//Caracterizando ser o último elemento.
	if(fi->final == NULL){								//Caracterizando uma lista vazia. Já que o fi->final aponta para o último elemento
		fi->inicio = no;								//inicio aponta para o no, porque ele é o primeiro e ultimo.
	} else{
		fi->final->prox = no;							//o próximo do último aponta para nulo.
	}
	fi->final = no;										//a cabaçe final ponta para o último elemento(no).
	return 1;
}

//Remove um elemento de uma pilha (FIFO = first in, first out)
//Elias
int Remover_um_elemento_da_fila(Fila* fi){
	if(fi == NULL){
		return 0;
	}
	if(fi->inicio == NULL){								//indicador de fila vazia.
		return 0;
	}
	Elem *no = fi->inicio;
	fi->inicio = fi->inicio->prox;
	int cpfRemovido = no->dados.cpf;
	if(fi->inicio == NULL){								//se a lista ficou vazia
		fi->final = NULL;
	}
	free(no);
	return cpfRemovido;
}

//Delata uma Fila
void Deletar_fila(Fila* fi){
	if(fi != NULL){
		Elem* no;
		while(fi->inicio != NULL){						//Basta criar uma cabeça inicial auxiliar e percorrer, deletando um a um. Depois deleta as duas cabeças.
			no = fi->inicio;
			fi->inicio = fi->inicio->prox;
			free(no);
		}
		free(fi);
	}
}
			
			
			//Main
int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};
	struct cliente isa = {"isa", 102};
	struct cliente lar = {"lar", 103};
	struct cliente Elias = {"Eli", 104};
	
	
	Fila *fi = Criar_fila_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi, ana);
	Imprimir_fila(fi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi, bia);
	Imprimir_fila(fi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi, isa);
	Imprimir_fila(fi);	
	printf("-----------------------------------------\n");
	printf("-----	-----	Remover	-----	-----\n");
	int x = Remover_um_elemento_da_fila(fi);
	printf("Cpf Removido: %d\n", x);
	Imprimir_fila(fi);		
	
}

