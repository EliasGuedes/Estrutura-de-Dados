#include <stdio.h>
#include <stdlib.h>

//Elias Cícero Moreira Guedes


struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};
typedef struct newNode* Pilha;		//Apelido da cabeça.
typedef struct  newNode Elem;		//Apelido a um nó qualquer ou de uma "cabeça auxiliar".



		// Métodos Auxiliares
//Nos informa o tamanho da pilha
int tamanho_pilha(Pilha* pi){
	if(pi == NULL){
		return 0;
	}
	int cont = 0;
	Elem* no = *pi;
	while (no != NULL){							//A cada vez que minha pilha auxiliar se move pelos nós eu incremento o contador. Paro quando chegar no final.
		cont ++;
		no = no->prox;
	}
	return cont;
}

//Verifica se a pilha está vazia.
int pilha_vazia(Pilha* pi){
	if(pi == NULL){								//Se a pilha está vazia
		return 1;
	}
	if(*pi = NULL){								//Se a cabeça aponta para o vazio.
		return 1;
	}
	return 0;
}

//Imprime a pilha
//Elias
void Imprimir_pilha(Pilha* pi){
	if(pi == NULL){
		return;
	}
	Elem* aux = *pi;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}


		
		
		
		
		//Métdos dos exercícios,
//Cria uma pilha apenas com a cabeça.
Pilha*	Criar_pilha_vazia(){
	Pilha *pi = (Pilha*) malloc(sizeof(Pilha));				//Aloca memória para a cabeça.
	if(pi != NULL)
		*pi = NULL;
	return pi;
}

//Insere um elemento no início da pilha. (como é por sua definição Lifo > last in, first out).
int Inserir_um_elemento_em_qualquer_na_pilha(Pilha* pi, struct cliente c){
	if(pi == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));				//Aloca espaço de memória para a nova célula
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = (*pi);										//Imagine os elementos empilhados, o mais debaixo é o último.
	*pi = no;

}

//Remove um elemento no início da pilha (como é por sua definição Lifo > last in, first out).
int Remover_um_elemento_da_pilha(Pilha* pi){
	if(pi == NULL){
		return 0;
	}
	if((*pi) == NULL){
		return 0;
	}
	Elem *no = *pi;
	int cpfRemovido = no->dados.cpf;
	*pi = no->prox;											//Faz a cabeça apontar pro próximo, que será o novo início.
	free(no);												//Libera o ex-início
	return cpfRemovido;
}

//Deleta um a um os nós da lista
//"Elias cíceros", Fabio viana.
void Deletar_pilha(Pilha*pi){
	if(pi != NULL){											//Se ela não ta vazia
		Elem* no;											//Criando a nossa cabeça auxiliar
		while((*pi) != NULL){								//Enquanto ainda haver elementos na pilha
			no = *pi;
			*pi = (*pi) ->prox;
			free(no);
		}
		free(pi);
	}
}




		//Main
int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};
	struct cliente isa = {"isa", 102};
	struct cliente lar = {"lar", 103};
	struct cliente Elias = {"Eli", 104};
	
	
	Pilha *pi = Criar_pilha_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, ana);
	Imprimir_pilha(pi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, bia);
	Imprimir_pilha(pi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, isa);
	Imprimir_pilha(pi);	
	printf("-----------------------------------------\n");
	printf("-----	-----	Remover	-----	-----\n");
	int x = Remover_um_elemento_da_pilha(pi);
	printf("Cpf Removido: %d\n", x);
	Imprimir_pilha(pi);	
}
		
		
