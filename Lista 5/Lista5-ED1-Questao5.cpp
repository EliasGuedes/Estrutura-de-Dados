#include <stdio.h>
#include <stdlib.h>

//Elias Cícero Moreira Guedes


struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct newNode *ant;
	struct cliente dados;
	struct newNode *prox;
};
typedef struct newNode* Lista;		//Apelido da cabeça.
typedef struct  newNode Elem;		//Apelido a um nó qualquer ou de uma "cabeça auxiliar".




			//Métodos auxiliares
//Informa o tamanho da lista
int tamanho_lista(Lista* li){
	if(li == NULL){
		return 0;
	}
	int cont = 0;
	Elem*no = *li;
	while(no != NULL){
		cont++;
		no = no->prox;
	}
	return cont;
}

//Verifica se a lista está vazia
int lista_vazia(Lista *li){
	if(li == NULL){
		return 1;
	}
	if(*li == NULL){
		return 1;
	}
	return 0;
}
			
//Insere no inicio da lista duplamente encadeada
int insere_lista_inicio(Lista *li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = (*li);
	no->ant = NULL;
	if(*li != NULL){
		(*li)->ant = no;
	}
	*li = no;
	return 1;
}


//Insere no final da lista duplamente encadeada
int insere_lista_final(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = NULL;
	if((*li) == NULL){				//lista vazia: insere no inicio
		no->ant = NULL;
		*li = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != NULL){	//percorre até o final da lista(que será o ex-final)
			aux = aux->prox;
		}
		aux->prox = no;
		no->ant = aux;
	}
	return 1;
}
		
//Insere no meio da lista
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
		no->ant = NULL;
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
	no->ant = auxAnt;
	no->prox = auxPost;
	auxPost->ant = no;
	}
	return 1;
}	
			
			
			
			
			//Métodos da lista de exercícios
//Cria uma lista duplamente encadeada.
Lista*	Criar_lista_vazia(){
	Lista* li = (Lista*) malloc (sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Insere um cliente em ma posição qualquer da lista.
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

//Remove um elemento de qualquer posição da lista duplamente encadeada
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista* li, int cpf){
	if(li == NULL){
		return 0;
	}
	Elem *ant = *li;
	Elem *no = *li;
	while(no != NULL && no->dados.cpf != cpf){					//While que percorre até achar o cpf do cliente e deixar em "no".
		ant = no;
		no = no->prox;
	}
	if(no == NULL){												//Caso a lista estivesse vazia ou não tivesse o cliente na lista.
		return 0;
	}
	if(no == *li){												//caso seja uma lista Elias com 1 elemento
		*li = no->prox;
	}else{
		ant->prox = no->prox;
		if(no->prox != NULL){
			no->prox->ant = ant;
		}
	}
	int cpfRemovido = no->dados.cpf;
	free(no);
	return cpfRemovido;
}



//Retorna a posição de um elemento na lista duplamente encadeada.
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




//Imprime todos os elementos da lista
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

//Deleta uma lista duplamente encadeada
void Deletar_lista(Lista *li){
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
