/*Problema de Josephus

- Elias Cícero Moreira Guedes

- O problema de Josephus postula um grupo de soldados circundados por uma força inimiga esmagadora.
- Não há esperanças de vitória sem a chegada de reforços e existe somente um cavalo disponível para escapar.
- Os soldados entram em um acordo para determinar qual deles deverá escapar e trazer ajuda.
- Eles formam um círculo e um número N é sorteado em um chapéu. Um de seus nomes também é sorteado.
- Iniciando pelo soldado cujo nome foi sorteado, eles começam a contar ao longo do círculo e a contagem reinicia com o soldado seguinte.
- O processo continua de maneira que, toda vez que N é alcançado, outro soldado é retirado do círculo. 
- Todo soldado retirado do círculo não entra mais na contagem.
- O último soldado que restar deverá montar no cavalo e escapar. 
- Considerando a quantidade de soldados e o número N o problema é determinar a sequência na qual os soldados são eliminados do círculo e o soldado que escapará.

*/

#include <stdio.h>
#include <stdlib.h>

struct newNode{
	int dados;
	struct newNode *prox;
};

typedef struct newNode* Lista;		//Apelido da cabeça.
typedef struct  newNode Elem;		//Apelido a um nó qualquer ou de uma "cabeça auxiliar".

//remove no inicio da lista circular.
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
	atual->prox = no->prox;
	*li = no->prox;
	free(no);
	return 1;
}

//remove um elemento qualquer da lista circular
int RemoverElementoLista(Lista*li, int c){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	Elem* no = *li;
	if(no->dados == c){										//Remove do inicio
		remove_lista_inicio(li);
		return 1;
	}
	Elem *ant = no;
	no = no->prox;
	while(no != (*li) && no->dados != c){					//enquanto não chegou no final e não encontrou
		ant = no;
		no = no->prox;
	}
	if(no == *li){											//se não encontrou
		return 0;
	}
	ant->prox = no->prox;
	free(no);
	return 1;
}

//insere no final da lista circular
int InserirLista(Lista* li, int c){
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

//Cria uma lista vazia
//Elias.
Lista* Criar_lista_vazia(){
	Lista* li = (Lista*) malloc(sizeof(Lista));						//Aloca um espaço para a alma da lista, cabeça.
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Imprime os elementos de uma lista circular
void ImprimirLista(Lista* li){
	if(li == NULL || (*li) == NULL){
		return;
	}
	Elem* aux = *li;
	int i = 0;
	do{
		printf("Numero %d: %d\n", (i+1), aux->dados);
		i++;
		aux = aux->prox;
	} while(aux != (*li));
}

//Deleta lista circular.
void Deletar_lista(Lista* li){
	if(li != NULL && (*li) != NULL){
		Elem *aux, *no = *li;							//Cria duas cabeças auxiliares.
		while((*li) != no->prox){						//Enquanto não der a volta!
			aux = no;									//aux vem e no vai. Elimina aux e repete o ciclo.
			no = no->prox;								//Elias.
			free(aux);
		}
		free(no);
		free(li);
	}	
}

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



int main(){

	//Para facilitarmos o problema vou criar uma lista com 10 elementos, N = 3	e comecar a contagem do primeiro elemento.
	
	int cont = 0;
	int tam = 10;
	int numerosRestantes = tam;
	int i;
	int chave = 0;
	Lista* li = Criar_lista_vazia();

	printf("----------	    Inicio da lista		----------\n");
	InserirLista(li,1);
	InserirLista(li,2);
	InserirLista(li,3);
	InserirLista(li,4);
	InserirLista(li,5);
	InserirLista(li,6);
	InserirLista(li,7);
	InserirLista(li,8);
	InserirLista(li,9);
	InserirLista(li,10);
	ImprimirLista(li);
	
	Elem* aux = *li;
	Elem* auxAnt = *li;
	Elem* auxAntRecover = *li;
	cont++;
	
	while(chave != 1){							//Quando sobrar um elemento acaba o loop.
	for(i = 0; i<9; i++){						//repetir a té remover 9 vezes.
		while(cont != 3){						//de 3 em 3
			auxAnt = aux;
			aux = aux->prox;
			cont++;
		}
		if(cont == 3){
			auxAnt = aux;
			auxAntRecover = aux;
			aux = aux->prox;
			cont = 1;
			RemoverElementoLista(li, auxAnt->dados);
			Elem* auxAnt = auxAntRecover;
			numerosRestantes--;
			printf("----------	Retirada numero %d, tamanho da lista: %d	----------\n", (i+1), tamanho_lista(li));
			ImprimirLista(li);
		}
		if(numerosRestantes == 1){
			chave = 1;
		}
	}
}
	Elem* restou = *li;
	printf("Numero que restou: %d\n", restou->dados);
	
	
	Deletar_lista(li);
	
	system("pause");
	return 0;
}


