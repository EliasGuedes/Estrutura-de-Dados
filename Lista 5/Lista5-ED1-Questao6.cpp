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

typedef struct newNode* Lista;		//Apelido da cabeça.
typedef struct  newNode Elem;		//Apelido a um nó qualquer ou de uma "cabeça auxiliar".



			//Métodos auxiliares
//Informa o tamanho da lista circular
int tamanho_lista(Lista* li){
	if(li == NULL || (*li) == NULL){
		return 0;
	}
	int cont = 0;
	Elem* no = *li;
	do{								//Eu percorro pelo primeiro elemento. Se ele não é o último então eu repito até que eu chege no último.
		cont++;
		no = no->prox;
	} while(no != (*li));
	return cont;
}	

//Insere na lista circular			
int lista_vazia(Lista* li){
	if(li == NULL && (*li) == NULL){
		return 1;
	}
	else {
		return 0;
	}
}	

//insere no inicio da lista circular: aloca espaço para uma nova célula e faz ela apontar para ela mesma, caso a lista esteja vazia.	
int insere_lista_inicio(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;	
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	if((*li) == NULL){				//se a lista está vazia.
		*li = no;
		no->prox = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != (*li)){		//Na lista circular, ser o último significa apontar para o primeiro elemento(o mesmo elemento que a cabeça aponta)
			aux = aux->prox;
		}
		aux->prox = no;
		no->prox = *li;					//o que a lista estava apontando
		*li = no;						//cabeça aponta para o início.
	}
	return 1;
}
			
//insere no final da lista circular
int insere_lista_final(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;	
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}	
	no->dados = c;
	if((*li) == NULL){					//Lista vazia. Insere no inicio.
		*li = no;
		no->prox = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != (*li)){		//percorre a lista até chegar no final
			aux = aux->prox;
		}
		aux->prox = no;
		no->prox = *li;
	}
	return 1;
}

//Insere no meio da lista.
int insere_lista_meio(Lista* li, struct cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	//Elias
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	if(lista_vazia(li)){
		*li = no;
		no->prox = no;
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

//remove no inicio da lista duplamente encadeada.
int remove_lista_inicio(Lista *li){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	if((*li) == (*li)->prox){							//Lista com um único elemento
		free(*li);
		*li = NULL;
		return 1;
	}
	Elem *atual = *li;
	while(atual->prox != (*li)){						//percorre até o último
		atual = atual->prox;
	}
	Elem *no = *li;
	int cpfRemovido = no->dados.cpf;
	atual->prox = no->prox;
	*li = no->prox;
	free(no);
	return cpfRemovido;
}




			
			//Métodos da lista de exercícios
//Cria uma lista vazia
Lista* Criar_lista_vazia(){
	Lista* li = (Lista*) malloc(sizeof(Lista));						//Aloca um espaço para a alma da lista, cabeça.
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Insere um elemento em qualquer posição da lista circular
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

//Remove um elemento em qualquer posição da lista.
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista*li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	Elem* no = *li;
	int cpfRemovido = no->dados.cpf;
	if(no->dados.cpf == c.cpf){										//Remove do inicio
		remove_lista_inicio(li);
	}
	Elem *ant = no;
	no = no->prox;
	while(no != (*li) && no->dados.cpf != c.cpf){					//enquanto não chegou no final e não encontrou
		ant = no;
		no = no->prox;
	}
	if(no == *li){													//se não encontrou
		return 0;
	}
	ant->prox = no->prox;
	free(no);
	return cpfRemovido;
}

//Faz uma busca na lista retornando a posição do cliente, caso exista na lista.
int Buscar_a_posicao_de_um_elemento_na_lista(Lista* li, struct cliente c){
	if(li == NULL){
		return -1;
	}
	Elem *no = *li;
	int cont = 0;
	while(no->prox != (*li) && no->dados.cpf != c.cpf){						//no != NULL e no->prox != NULL tem quase o mesmo significado.
		cont++;
		no = no->prox;
	}
	if(no == NULL){
		return -1;
	}else{
		return cont;
	}
}

//Imprime todos os elementos da lista duplamente encadeada Elias.
void Imprimir_todos_os_elementos_da_lista(Lista* li){
	if(li == NULL || (*li) == NULL){
		return;
	}
	Elem* aux = *li;
	int i = 0;
	do{
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	} while(aux != (*li));
}

//Deleta uma lista circular encadeada.	
void Deletar_lista(Lista* li){
	if(li != NULL && (*li) != NULL){
		Elem *aux, *no = *li;							//Cria duas cabeças auxiliares.
		while((*li) != no->prox){						//Enquanto não der a volta!
			aux = no;									//aux vem e no vai. Elimina aux e repete o ciclo.
			no = no->prox;
			free(aux);
		}
		free(no);
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
	int y = Remover_um_elemento_de_qualquer_posicao_da_lista(li, lar);
	printf("cpf removido: %d\n", y);		
	Imprimir_todos_os_elementos_da_lista(li);
	Deletar_lista(li);	
}
