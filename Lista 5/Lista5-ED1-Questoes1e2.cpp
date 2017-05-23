#include <stdio.h>
#include <stdlib.h>

//Elias C�cero Moreira Guedes


struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};
typedef struct newNode* Lista;		//Apelido da cabe�a.
typedef struct  newNode Elem;		//Apelido a um n� qualquer ou de uma "cabe�a auxiliar".


		//M�todos auxiliares
//Verifica se a lista est� vazia.
int lista_vazia(Lista* li){
	if(li == NULL){
		return 1;
	}
	if(*li == NULL){
		return 1;
	}
	return 0;
}

//retorna o tamanho de uma lista din�mica.
int tamanho_lista(Lista* li){
	if(li == NULL){
		return 0;
	}
	int cont = 0;
	Elem* aux = *li;
	while(aux != NULL){
		cont++;
		aux = aux->prox;
	}
	return cont;
}

//Aloca espa�o de mem�ria para um novo n� e o insere no come�o da lista, fazendo as altera��es necess�rias.
int insere_lista_inicio(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	no->prox = (*li);
	*li = no;
	return 1;
}

//Insere no meio da lista.
int insere_lista_meio(Lista* li, struct cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	if(lista_vazia(li)){
		no->prox = (*li);												//se a lista est� vazia ent�o n�o h� necessidade de ordenar. Logo � s� fazer como inserir no in�cio.
		*li = no;
		return 1;
	}else{
	int cont1 = 0;
	int cont2 = 0;
	Elem* auxAnt = *li;
	Elem* auxPost = *li;	
	while(cont1 != (pos-1)){
		auxAnt = auxAnt->prox;
		cont1++;
	}
	while(cont2 != (pos)){
		auxPost	= auxPost->prox;
		cont2++;
	}
	auxAnt->prox = no;
	no->prox = auxPost;	
	}
	return 1;
}

//Insere no final da lista.
int insere_lista_final(Lista* li, struct  cliente c){
	if(li == NULL){
		return 0;						//Elias
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados= c;
	no->prox = NULL;
	if (lista_vazia(li)){
		*li = no;
	} else{
		Elem *aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
	}
	return 1;
}

//Remove no come�o da lista. Uma "cabe�a Elias auxiliar" fica com o elemento para remover, a cabe�a original aponta pro segundo elemento e faz um free na cabe�a auxiliar.
int remove_lista_comeco(Lista* li){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){									//Lista vazia
		return 0;
	}
	Elem *no = *li;
	*li = no->prox;
	free(no);
	return 1;
}
	
//Remove um elemento do final da lista
//Mexer com algum n� da lista implica criar uma cabe�a auxiliar para ir at� esse n� e poder mexer comele
//A cabe�a principal � a alma da lista.
int remove_lista_final(Lista* li){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}	
	Elem *ant, *no = *li;								//Duas cabe�as auxiliares para manipular dois n�s
	while(no->prox != NULL){							//While para fazer o "ant" ser o pen�ltimo n� e "no" ser o �ltimo n�.
		ant = no;
		no = no->prox;
	}
	if(no == (*li)){									//Se a lista possui somente 1 elemento
		*li = no->prox;
	}else{
		ant->prox = no->prox;
	}
	free(no);
	return 1;
}




			//M�todos da lista de exerc�cios
//Cria a cabe�a de uma lista e faz ela apontar para nulo.
Lista* Criar_lista_vazia(){
	Lista* li = (Lista*) malloc(sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}


//Insere um elemento em qualquer posi��o da lista
int Inserir_um_elemento_em_qualquer_posicao_da_lista(Lista* li, struct cliente c, int pos){
	int x = tamanho_lista(li);
	if (pos == 0 || pos > x){
		insere_lista_inicio(li,c);
	}
	if (0 < pos && pos < x){
		insere_lista_meio(li,c,pos);
	}
	if (pos == x){
		insere_lista_final(li,c);
	}
}


//Remove um elemento qualquer da lista: desaloca uma mem�ria e muda o prox necess�rios.
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista* li, int cpf){
	if(li == NULL){
		return 0;
	}
	Elem *ant = *li;
	Elem *no = *li;
	while(no != NULL && no->dados.cpf != cpf){					//While que percorre at� achar o cpf do cliente e deixar em "no".
		ant = no;
		no = no->prox;
	}
	if(no == NULL){												//Caso a lista estivesse vazia ou n�o tivesse o cliente na lista.
		return 0;
	}
	if(no == *li){												//caso seja uma lista com 1 elemento
		*li = no->prox;
	}else{
		ant->prox = no->prox;
	}
	int cpfRemovido = no->dados.cpf;
	free(no);
	return cpfRemovido;
}


//Faz uma busca na lista retornando a posi��o do cliente, caso exista na lista.
int Buscar_a_posicao_de_um_elemento_na_lista(Lista* li, struct cliente c){
	if(li == NULL){
		return -1;
	}
	Elem *no = *li;
	int cont = 0;
	while(no != NULL && no->dados.cpf != c.cpf){						//no != NULL e no->prox != NULL tem quase o mesmo significado.
		cont++;
		no = no->prox;
	}
	if(no == NULL){
		return -1;
	}else{
		return cont;
	}
}


//Imprime todos os elementos da lista Din�mica
void Imprimir_todos_os_elementos_da_lista(Lista* li){
	if(li == NULL){
		return;
	}
	Elem* aux = *li;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}


//Desaloca a mem�ria de cada no que essa lista possui, um por um.
void Deletar_lista(Lista* li){
	if(li != NULL){
		Elem* no;
		while((*li) != NULL){
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}




		//Main
int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};
	struct cliente isa = {"isa", 102};
	struct cliente lar = {"lar", 103};
	struct cliente Elias = {"Eli", 104};
	
	Lista* li = Criar_lista_vazia();	
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere ana	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, ana, 3);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere bia	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, bia, 1);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere isa no inicio-----\n");			
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, isa, 0);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere lar na pos 1-----\n");		
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, lar, 1);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Busca pos da ana    -----\n");
	int x = Buscar_a_posicao_de_um_elemento_na_lista(li, ana);
	printf("Posicao: %d\n", x);
	printf("-----------------------------------------\n");
	printf("-----	-----	Remove lar da lista -----\n");
	int y = Remover_um_elemento_de_qualquer_posicao_da_lista(li, 103);
	printf("cpf removido: %d\n", y);		
	Imprimir_todos_os_elementos_da_lista(li);
	Deletar_lista(li);		
		
}
	
	
	/*
	Lista* Criar_lista_vazia()
	int Inserir_um_elemento_em_qualquer_posicao_da_lista(Lista* li, struct cliente c, int pos)
	int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista* li, int cpf)
	int Buscar_a_posi��o_de_um_elemento_na_lista(Lista* li, struct cliente c)
	void Imprimir_todos_os_elementos_da_lista(Lista* li)
	void Deletar_lista(Lista* li)
	
	*/
