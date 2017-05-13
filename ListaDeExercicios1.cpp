#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct cliente{
	char nome[20];
	int cpf;
}; 

struct lista{
	int qtd;
	struct cliente clientes[MAX];
};

struct pilha{
	int qtd;
	struct cliente clientesp[MAX];
};

struct fila{
	int inicio,final,qtd;
	struct cliente clientesf[MAX];
};

typedef struct cliente Cliente;
typedef struct lista Lista;
typedef struct pilha Pilha;
typedef struct fila Fila;


 										//	Métodos Auxiliares
											
//Verifica se a lista li está com seu vetor de clientes cheio.
int lista_cheia(Lista* li){
	if(li == NULL)
		return -1;
	else
		return (li->qtd == MAX);
}

//Verifica se a lista li está com seu vetor de clientes vazia.
int lista_vazia(Lista* li){
	if(li == NULL)
		return -1;
	else
		return (li->qtd == 0);
}

//Insere um cliente no começo da lista e afasta os clientes a direita uma posição para frente.
int inserir_comeco(Lista* li, Cliente c){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}
	int i;
	for(i=(li->qtd-1); i>=0; i--){
		li->clientes[i+1] = li->clientes[i];
	}
	li->clientes[0] = c;
	li->qtd++;
	return 1;
}

//Insere um cliente no final da lista.
int inserir_final(Lista* li, Cliente c){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}
	li->clientes[li->qtd] = c;
	li->qtd++;
	return 1;
}

//Insere um cliente no meio da lista.
int inserir_meio(Lista* li, Cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}
	int i;
	for(i=(li->qtd-1); i>=pos; i--){
		li->clientes[i+1] = li->clientes[i];
	}
	li->clientes[pos] = c;
	li->qtd++;
	return 1;
}

//Verifica se a pilha pi está com seu vetor de clientes cheio.
int pilha_cheia(Pilha* pi){
	if(pi == NULL)
		return -1;
	else
		return (pi->qtd == MAX);
}

//Verifica se a pilha pi está com seu vetor de clientes vazia.
int pilha_vazia(Pilha* pi){
	if(pi == NULL)
		return -1;
	else
		return (pi->qtd == 0);
}

//Verifica se a fila está cheia
int fila_cheia(Fila* fi){
	if(fi == NULL){
		return -1;
	}
	else
		return (fi->qtd == MAX);

}

//verifica se a fila está vazia
int fila_vazia(Fila* fi){
	if(fi == NULL){
		return -1;
	}
	else
		return (fi->qtd == 0);
}

//imprime uma lista
void imprime_lista(Lista* li){
	int i;
	for(i=0; i<li->qtd; i++){
		printf("Lista: cliente %d : %s\n", (i+1), li->clientes[i].nome);
	}
}

//imprime uma pilha
void imprime_pilha(Pilha* pi){
	int i;
	for(i=0; i<pi->qtd; i++){
		printf("Pilha: cliente %d : %s\n", (i+1), pi->clientesp[i].nome);
	}
}

//imprime uma fila
void imprime_fila(Fila* fi){
	int i;
	for(i=0; i<fi->qtd; i++){
		printf("Fila: cliente %d : %s\n", (i+1), fi->clientesf[i].nome);
	}
}



									//Implementação dos métodos da Lista de Exercícios 1 -> LISTAS
//Criar lista vazia.
Lista* Criar_lista_vazia(){
	Lista *li;
	li = (Lista*) malloc(sizeof(struct lista));
	if (li!= NULL){
		li->qtd = 0;
	}
	return li;
}

//nserir um elemento em qualquer posição da lista.
int Inserir_um_elemento_em_qualquer_posicao_da_lista(Lista* li, Cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}
	if(lista_vazia(li)){
		li->clientes[0] = c;
		li->qtd++;
		return 1;
	}	
	if(pos==0){
		inserir_comeco(li, c);
	}
	if(0<pos && pos<MAX){
		inserir_meio(li, c, pos);
	}
	if(pos==MAX){
		inserir_final(li, c);
	}
}

//string Remover_um_elemento_de_qualquer_posição_da_lista(Lista* li, int pos);
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista* li, int pos){
	if(li == NULL){
		return 0;
	}
	if(lista_vazia(li)){
		return 0;
	}	
	int i = pos;
	int cpfRemovido = li->clientes[pos].cpf;
	for(i=pos; i<(li->qtd-1); i++){
		li->clientes[i] = li->clientes[i+1];
	}
	li->qtd--;
	return cpfRemovido;
}
	
//busca o índice de um elemento da lista
int Buscar_o_indice_de_um_elemento_na_lista(Lista* li, Cliente c){
	if(li == NULL){
		return 0;
	}
	if(lista_vazia(li)){
		return 0;
	}
	int i = 0;
	for(i=0; i<li->qtd-1; i++){
		if(c.cpf == li->clientes[i].cpf){
			return i;
		}
		else
			return 0;
	}
}

//Deletar lista.
void Deletar_lista(Lista* li){
	free(li);
}



									//Implementação dos métodos da Lista de Exercícios 1 -> PILHAS
//Cria uma pilha de até 100 clientes, alocando um espaço de memória.
Pilha* Criar_pilha_vazia(){
	Pilha *pi;
	pi = (Pilha*) malloc(sizeof(struct pilha));
	if (pi!= NULL){
		pi->qtd = 0;
	}
	return pi;
}

//Insere um elemento na última posição vaga na pilha.
int Inserir_um_elemento_em_qualquer_na_pilha(Pilha* pi, Cliente c){
	if(pi == NULL){
		return 0;
	}
	if(pilha_cheia(pi)){
		return 0;
	}
	pi->clientesp[pi->qtd] = c;
	pi->qtd++;
	return 1;	
}

//Remove o último cliente da pilha e volta o cpf dele.
int Remover_um_elemento_da_pilha(Pilha* pi){
	if(pi == NULL){
		return 0;
	}
	if(pilha_cheia(pi)){
		return 0;
	}
	int cpfRemovido = pi->clientesp[pi->qtd-1].cpf;
	pi->qtd--;
	return cpfRemovido;
}
	
	
//Retira o espaço de memória alocado para a pilha pi.
void Deletar_pilha(Pilha* pi){
	free(pi);
}


	
									//Implementação dos métodos da Lista de Exercícios 1 -> FILAS
//Cria fila
Fila* Criar_fila_vazia(){
	Fila* fi = (Fila*) malloc(sizeof(struct fila));
	if(fi != NULL){
		fi->inicio = 0;
		fi->final = 0;
		fi->qtd = 0;
	}
	return fi;
}

int Inserir_um_elemento_em_qualquer_na_fila(Fila* fi, Cliente c){
	if(fi == NULL){
		return 0;
	}
	if(fila_cheia(fi)){
		return 0;
	}
	fi->clientesf[fi->qtd] = c;
//	fi->final = (fi->final+1)%MAX;
	fi->qtd++;
	return 1;
}

int Remover_um_elemento_da_fila(Fila* fi){
	if(fi == NULL){
		return 0;
	}
	if(fila_vazia(fi)){
		return 0;
	}
	int i;
	int cpfRemovido = fi->clientesf[0].cpf;
//	fi->inicio = (fi->inicio+1)%MAX;
	for(i=0; i<(fi->qtd-1); i++){
		fi->clientesf[i] = fi->clientesf[i+1];
	}
	fi->qtd--;
	return cpfRemovido;
}

//deleta fila
void Deletar_fila(Fila* fi){
	free(fi);	
}


		//	-----	Main	-----	//
int main(){
	Cliente ana = {"ana", 100};
	Cliente isa = {"isa", 101};
	Cliente bia = {"bia", 102};
	Cliente hi = {"hi", 103};

	
		//	-----	LISTAS	-----	//
	printf("~~~~	Manipulando LISTAS	~~~~~~ \n\n");
	Lista* li = Criar_lista_vazia();
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, ana, 0);
		imprime_lista(li);
		printf("	-----		-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, isa, 1);
		imprime_lista(li);
		printf("	-----		-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, bia, 2);
		imprime_lista(li);
		printf("	-----		-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, hi, 1);
		imprime_lista(li);
		printf("	-----		-----\n");
		
	Remover_um_elemento_de_qualquer_posicao_da_lista(li, 2);
		imprime_lista(li);
		printf("	-----		-----\n");
	
	int x =	Buscar_o_indice_de_um_elemento_na_lista(li, ana);
		printf("A ana esta no indice: %d\n", x);
		printf("	-----		-----\n\n");
	Deletar_lista(li);
	
	
				//	-----	PILHAS	-----	//
	printf("~~~~	Manipulando PILHAS	~~~~~~ \n\n");
	Pilha* pi = Criar_pilha_vazia();
	Inserir_um_elemento_em_qualquer_na_pilha(pi, ana);
		imprime_pilha(pi);
		printf("	-----			-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, isa);
		imprime_pilha(pi);
		printf("	-----			-----\n");
 	Inserir_um_elemento_em_qualquer_na_pilha(pi, bia);
		imprime_pilha(pi);
		printf("	-----			-----\n");
	Remover_um_elemento_da_pilha(pi);
		imprime_pilha(pi);
		printf("	-----			-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, hi);
		imprime_pilha(pi);
		printf("	-----			-----\n");
	Remover_um_elemento_da_pilha(pi);
		imprime_pilha(pi);
		printf("	-----			-----\n\n");
 	Deletar_pilha(pi);
	
	
				//	-----	FILAS	-----	//
	printf("~~~~	Manipulando FILAS	~~~~~~ \n\n"); 
	Fila* fi = Criar_fila_vazia();
	Inserir_um_elemento_em_qualquer_na_fila(fi,ana);
		imprime_fila(fi);
		printf("	-----		-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi,isa);
		imprime_fila(fi);
		printf("	-----		-----\n");
	Remover_um_elemento_da_fila(fi);
		imprime_fila(fi);
		printf("	-----		-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi,bia);
		imprime_fila(fi);
		printf("	-----		-----\n");
	Remover_um_elemento_da_fila(fi);	
		imprime_fila(fi);
		printf("	-----		-----\n");
		
	Deletar_fila(fi);
}
