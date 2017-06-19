
#include <stdio.h>
#include <stdlib.h>



struct elemento{			//Estrutura de um BUCKET: que � uma LISTA DIN�MICA ENCADEADA
	int dados;				//O que o bucket guarda
	struct elemento *prox;	//ponteiro para o pr�ximo elemento da lista. Armazena o endere�o do pr�ximo elemento, da pr�xima chave.
};

typedef struct elemento* Lista;	//Apelido da cabe�a. � um ponteiro para ponteiro.	
typedef struct elemento Elem;	//Apelido de um elemento qualquer do bucket.
Lista* cria_bucket();			//prot�tipos das fun��es
void libera_bucket(Lista* li);
int tamanho_lista(Lista* li);
int remove_bucket_comeco(Lista* li);
int remove_bucket_final(Lista* li);
int Remover_um_elemento_de_qualquer_posicao_do_Bucket(Lista* li, int n);
void imprimirTabelaPos(Lista* li, int n);




struct hash{			//Estrutura da TABELA HASH
	int qtd;			//qtd � a quantidade de elementos que a tabela tem atualmente.
	int tam;			//tam � o tamanho da tabela.
	int posBuck;		//posi��o de um bucket. Basicamente � uma posi��o da tabela hash extend�vel.
	Lista *itens;		//ponteiro para ponteiro de int. Cada posi��o do array eu guardo os endere�os dos elementos. Um ponteiro aponta pro vetor e outro ponteiro serve para guardar o endere�o.
};

typedef struct hash Hash;		//Apelidando struct hash de Hash
int decimalToBinary(int n);		//prot�tipo das fun��es auxuliares
int ultimoDigito(int n);
int penultimoDigito(int n);
int insereTabelaPos(Hash* ha, Lista* li1, Lista* li2, int pos, int chave);
int inserirHashExtendivelPOS(Hash* ha, Lista* li, int n);
void imprimirTabelaHashExtendivel(Hash* ha, Lista* li1, Lista* li2, Lista* li3, Lista* li4, Lista* li5, Lista* li6, Lista* li7, Lista* li8);
int buscarNumBucket(Hash* ha, Lista* li1, Lista* li2, int chave);


	
	
	
					//		-----	Fun��es Da Tabela Hash	-----	//

//Criando a tabela hash
Hash* criaHash(int tam){
	Hash* ha = (Hash*) malloc(sizeof(Hash));			//Aloca mem�ria para a struct hash
	if(ha != NULL){										//se a aloca��o deu certo
		int i;											//vari�vel auxiliar
		ha->tam = tam;									//tamanho da tabela = o par�metro que eu passei
		ha->itens = (Lista*) malloc(tam*sizeof(Lista));	//inicializa o ponteiro para ponteiro itens com int**
														//cria um VETOR com tamanho int** vezes o tamanho da tabela. Agora ha possui um vetor chamado itens: ha->itens.
		if(ha->itens == NULL){							//se n�o deu certo
			free(ha);									//libera o primeiro ponteiro
			return NULL;								//n�o cria nada.
		}
		ha->qtd = 0;									//quantidade de elementos atuais = 0
		for(i=0; i<ha->tam; i++)						//percorre de 0 at� tam-1, inicializando todo mundo do vetor itens com NULL.
			ha->itens[i] = NULL;
		}
	return ha;
}


//Destruindo a tabela Hash
void liberaHash(Hash* ha){
	if(ha != NULL){										//se pelo menos a tabela existe.
		int i;
		for(i=0; i<ha->tam; i++){						//percorre todo o array. Se tiver elemento desaloca mem�ria.
			if(ha->itens[i] != NULL) {					//ser diferente de null significa que um elemento foi inserido nessa posi��o da tabela.
				free(ha->itens[i]);						//libero as posi��es que cont�m elemento
			}
		}
		free(ha->itens);								//libera o vetor.
		free(ha);										//libera o struct hash que foi usado para criar inicialmente a tabela hash.
	}
}


//Fun��o Hash prim�ria, no qual tam � o tamanho da tabela. Essa opera��o � equivalente a fazer "N mod Tam"
int FHashPrimaria(int chave, int tam){
	return(chave & 0x7FFFFFFF) % tam;		//O operador bit a bit & junto com essa numera��o elimina o sinal de um n�mero. Isso evita resultados negativos.
}


//Fun��o Hash secund�ria, no qual n � o n�mero resultado da fun��o de hashing prim�ria. Ela retorna um vetor, da� ela ter um * no int e um *v.
int* FHashSecundaria(int n, int *v){
	int n2 = decimalToBinary(n);
	int nU = ultimoDigito(n2);
	int nPU = penultimoDigito(n2);
	
	v[0] = nPU;
	v[1] = nU;
	
	return v;
}




					//		-----	Fun��es Auxiliares	-----	//
					
	//Sobre as chaves e  a tabela Hash

//Fun��o auxiliar: transformar um n�mero decimal em bin�rio
int decimalToBinary(int n) {
	int remainder; 
	int binary = 0;
	int i = 1;
  
	while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}


//Fun��o Auxiliar: pega o �ltimo digito de um numero
int ultimoDigito(int n){
	int dig1 = n%10;		//Pega o resto da divisao por 10, i.e, o ultimo digito.
	return dig1;
}


//Fun��o Auxiliar: pega o pe�ltimo d�gito de um n�mero
int penultimoDigito(int n){
	int aux1 = n%100;	//pega os dois ultimos digitos do numero
	float aux2 = aux1;	//armazena o resto da divisao por 100 em um inteiro
	int dig2 = aux2/10;	//pega so a parte inteira da divisao por 10, i.e, o penultimo digito.	
	return dig2;
}


//Fun��o Auxiliar: Inserir na posi��o ??? da tabela Hash Extens�vel
int inserirHashExtendivelPOS(Hash* ha, Lista* li, int n){
	if(tamanho_lista(li) == 4){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));				//Aloca mem�ria para o novo n� criado
	if(no == NULL) {										//Se deu errado retorna 0
		return 0;
	}
	no->dados = n;
	if((*li) == NULL){										//se a lista est� vazia ent�o n�o h� necessidade de ordenar. Logo � s� fazer como inserir no in�cio.
		no->prox = NULL;									//o novo elemento aponta para NULL
		*li = no;											//a cabe�a aponta para o novo n�
		ha->qtd++;											//incrementa a quantidade de elementos atual da lista
		return 1;
	}else{													//se ela j� tem alguma coisa, ent�o eu devo procurar aonde inserir.
		Elem *ant, *atual = *li;							//cria auxiliares para eu ter conhecimento sobre o conteudo do no atual e do no anterior. Fa�o eles receberem a o que a cabe�a esta apontando.
		while(atual != NULL && atual->dados < n){			//Se o meu no atual nao aponta para null e a matricula do aluno do no atual e menor do que a matricula do aluno que eu quero inserir eu fa�o:
			ant = atual;									//fa�o uma ordenada.
			atual = atual->prox;											
		}
		if(atual == *li){									//insere no inicio
			no->prox = (*li);
			*li = no;
		}else {												//fazemos uma inser��o ordenada
			no->prox = atual;
			ant->prox = no;
		}
	ha->qtd++;											//incrementa a quantidade de elementos atual da lista	
	return 1;
	}
}

//Fun��o Auxiliar: selecionar a inser��o em um determinado bucket 
int insereTabelaPos(Hash* ha, Lista* li1, Lista* li2, int pos, int n){
	int pos2 = pos+ 4;
	int chave = n;
	if(ha->itens[pos] == NULL){
		ha->itens[pos] = *li1;
	}
	if(tamanho_lista(li1) != 4){
		inserirHashExtendivelPOS(ha, li1, chave);
		return 1;
	}
	if(tamanho_lista(li1) == 4){
		if(ha->itens[pos2] == NULL){	
			ha->itens[pos2] = *li2;
		}
		if(tamanho_lista(li2) != 4){
			inserirHashExtendivelPOS(ha, li2, chave);
			return 1;			
		}	
	}
	return 0;
}

//Fun��o Auxiliar: fun��o de busca
int buscarNumBucket(Hash* ha, Lista* li1, Lista* li2, int chave){
	if(li1 == NULL && li2 == NULL){
		return -1;
	}
	Elem *no = *li1;
	int cont = 0;
	while(no != NULL && no->dados != chave){						//no != NULL e no->prox != NULL tem quase o mesmo significado.
		cont++;
		no = no->prox;
	}
	if(no->dados == chave){
		return cont;
	}
	if(no == NULL){
		Elem *no2 = *li2;
		int cont2 = 0;
		while(no2 != NULL && no2->dados != chave){						//no != NULL e no->prox != NULL tem quase o mesmo significado.
			cont2++;
			no2 = no2->prox;
		}
		if (no == NULL){
			return -1;
		}else{
			return cont2;
		}
	}
}


//Fun��o Auxliar: imprimir todos os buckets
void imprimirTabelaHashExtendivel(Hash* ha, Lista* li1, Lista* li2, Lista* li3, Lista* li4, Lista* li5, Lista* li6, Lista* li7, Lista* li8){
	imprimirTabelaPos(li1, 1);
	imprimirTabelaPos(li2, 2);
	imprimirTabelaPos(li3, 3);
	imprimirTabelaPos(li4, 4);
	imprimirTabelaPos(li5, 5);
	imprimirTabelaPos(li6, 6);
	imprimirTabelaPos(li7, 7);
	imprimirTabelaPos(li8, 8);
}

	//Sobre os Buckets
	
//Fun��o Auxiliar: Cria um bucket
Lista* cria_bucket(){
	Lista* li = (Lista*) malloc(sizeof(Lista));		//alocando um espa�o de mem�ria para um struct elemento.
	if(li != NULL)									//Se a cria��o deu certo
		*li = NULL;									//a li aponta para nulo: o que significa que ainda n�o temos nenhum n� na lista.
	return li;
}


//Fun��o Auxiliar: Libera um bucket
void libera_bucket(Lista* li){						//Passo a lista que quero liberar. Devo liberar os n�s um a um do primeiro pro final e por �ltimo a cabe�a.
	if(li != NULL){
		Elem* no;									//Eu manipulo as coisas com a cabe�a da lista. S� que se eu mexer a cabe�a da lista de verade eu vou perder o in�cio da lista. Ent�o eu crio uma "cabe�a auxiliar" chamada n�.
		while((*li) != NULL){						//Enquanto o in�cio for diferente de NULL (isto �, enquanto ainda existir um pr�ximo elemento depois dele)
			no = *li;								//N� recebe o in�cio da lista.
			*li = (*li)-> prox;						//o in�cio passa a ser o pr�ximo elemento.
			free(no);								//libero essa ex-posi��o de mem�ria do li.
		}
		free(li);									//quando s� sobrou a cabe�a, libera ela.
	}
}	


//Fun��o Auxiliar: Tamanho do bucket
int tamanho_lista(Lista* li){						//Recebe a lista que eu quero saber o tamanho e retorna um inteiro: o tamanho dela.
	if(li == NULL){									
	//Se a lista n�o deu certo o tamanho dela � 0...
		return 0;
	}					
	int cont = 0;									//crio uma vari�vel auxiliar contadora.
	Elem* no = *li;									//crio uma cabe�a auxiliar: ela vai percorrer elemento por elemento da lista. Cada vez que ela percorre 1, meu contador imcrementa.
	while(no != NULL){								//Enquanto minha cabe�a auxiliar n�o estiver no final da lista (que significa apontar para nulo) eu fa�o:
		cont++;										//incremento o contador.
		no = no->prox;								//passo a cabe�a auxiliar para o pr�ximo elemento.
	}
	return cont;
}


//Fun��o Auxiliar: Remover do inicio
int remove_bucket_comeco(Lista* li){
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


//Fun��o Auxiliar: Remover do final
int remove_bucket_final(Lista* li){
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


//Fun��o Auxuliar: Remover de qualquer posi��o do bucket:
int Remover_um_elemento_de_qualquer_posicao_do_Bucket(Lista* li, int n){
	if(li == NULL){
		return 0;
	}
	Elem *ant = *li;
	Elem *no = *li;
	while(no != NULL && no->dados != n){					//While que percorre at� achar o cpf do cliente e deixar em "no".
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
	int numeroRemovido = no->dados;
	free(no);
	return numeroRemovido;
}

//Fun��o Auxiliar: Imprimir um bucket
void imprimirTabelaPos(Lista* li, int n){
	if(li == NULL){
		printf("Sem Bucket na posicao %d\n", n);
		printf("%d");
		return;
	}
	Elem* aux = *li;
	int i = 0;
	while(aux != NULL){
		printf("No Bucket %d posicao %d: %s\n", n, (i+1), aux->dados);
		i++;
		aux = aux->prox;
	}
}



					//		-----	Main	-----	//

int main(){
	Hash* ha = criaHash(11);
	
	Lista *li1;	li1 == cria_bucket();
	Lista *li2;	li2 == cria_bucket();
	Lista *li3;	li3 == cria_bucket();
	Lista *li4;	li4 == cria_bucket();
	Lista *li5;	li5 == cria_bucket();
	Lista *li6;	li6 == cria_bucket();
	Lista *li7;	li7 == cria_bucket();
	Lista *li8;	li8 == cria_bucket();
	
	int tamanho = 2;

	
	int a; 

do{
		printf("  ============================================ \n ");	
		printf(" ============= Trabalho de Hash ============= \n ");
		printf(" ============================================ \n ");
			
		printf(" ===(1) Adicionar novo valor	            == \n ");
		printf(" ===(2) Remover um valor                   == \n ");
		printf(" ===(3) Buscar um valor                    == \n ");
		printf(" ===(4) Imprimir todos os valores          == \n ");
		printf(" ===(5) Sair                               == \n  ");
		printf("============================================ \n ");
		printf("\n");
		printf("  ===Opcao: ");
		scanf ("%d",&a);
				
		if(a<1 || a>5){
			while((a<1) || (a>5)){
				printf("\n");
				printf("  ===Digite a opcao novamente: ");
				scanf("%d",&a);
				printf("\n");
			}
		}	

	switch(a){
		case 1: 
			printf("\n");
			int chave;
			printf("Digite um numero inteiro: \n");
			scanf("%d", &chave);
		
			int chave8, chave7;
			int *vetor;
			
			vetor = (int*) calloc(2, sizeof(int));
			vetor = FHashSecundaria(chave, vetor);
			chave8 = vetor[1];
			chave7 = vetor[0];
			
			
			int tranca = 0;
		
			if(chave7 == 0 && chave8 == 0){
				insereTabelaPos(ha, li1, li5, tranca, chave);
			}
				
			if(chave7 == 0 && chave8 == 1){
				insereTabelaPos(ha, li2, li6, 1, chave);		
			}
			
			if(chave7 == 1 && chave8 == 0){
				insereTabelaPos(ha, li3, li7, 2, chave);			
			}
			
			if(chave7 == 1 && chave8 == 1){
				insereTabelaPos(ha, li4, li8, 3, chave);	
			}
			printf("\n");
			break;
		//	
		//
		//	
		case 2: 
			printf("\n");
			int chave2;
			printf("Digite um numero inteiro: \n");
			scanf("%d\n", &chave2);
		
			int chave82, chave72;
			int *vetor2;

			
			vetor = (int*) calloc(2, sizeof(int));
			vetor = FHashSecundaria(chave2, vetor2);
			chave82 = vetor2[1];
			chave72 = vetor2[0];
			
			
			if(chave72 == 0 && chave82 == 0){
			int aux1 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li1, chave2);
				if (aux1 == 0){
					int aux2 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li5, chave2);		
					if(aux2 == 0){
						printf("O elemento nao se encontra na tabela\n");
					}
				}
			}
			
			if(chave72 == 0 && chave82 == 1){
			int aux3 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li2, chave2);
				if (aux3 == 0){
					int aux4 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li6, chave2);		
					if(aux4 == 0){
						printf("O elemento nao se encontra na tabela\n");
					}
				}
			}
			
			if(chave72 == 1 && chave82 == 0){
			int aux5 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li3, chave2);
				if (aux5 == 0){
					int aux6 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li7, chave2);		
					if(aux6 == 0){
						printf("O elemento nao se encontra na tabela\n");
					}
				}
			}
			
			if(chave72 == 1 && chave82 == 1){
			int aux7 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li4, chave2);
				if (aux7 == 0){
					int aux8 = Remover_um_elemento_de_qualquer_posicao_do_Bucket(li8, chave2);		
					if(aux8 == 0){
						printf("O elemento nao se encontra na tabela\n");
					}
				}
			}
			printf("\n");
			break;
		//
		//
		//	
		case 3: 
			if(ha == NULL){
				return -1;
			}
			
			int chave3;
			printf("Digite um numero inteiro: \n");
			scanf("%d\n", &chave3);
		
			int chave83, chave73;
			int *vetor3;

			
			vetor = (int*) calloc(2, sizeof(int));
			vetor = FHashSecundaria(chave3, vetor3);
			chave83 = vetor3[1];
			chave73 = vetor3[0];
			
		
			if(chave73 == 0 && chave83 == 0){
				buscarNumBucket(ha, li1, li5, chave3);
			}
		
			if(chave73 == 0 && chave83 == 1){
				buscarNumBucket(ha, li2, li6, chave3);
			}
		
			if(chave73 == 1 && chave83 == 0){
				buscarNumBucket(ha, li3, li7, chave2);
			}
			
			if(chave73 == 1 && chave83 == 1){
				buscarNumBucket(ha, li4, li8, chave3);
			}
			printf("\n");
			break;
		//
		//
		//					
		case 4: 
			printf("\n");
			imprimirTabelaHashExtendivel(ha, li1, li2, li3, li4, li5, li6, li7, li8);
			printf("\n");
			break;	
		//	
		//
		//						
		case 5: 
			printf("  ===Voce optou por sair do progama. \n");
			printf("  ===Fim de progama. ");
			printf("\n");
			break;							
	}
		
	}while(a!=5);
	
	return 0;
}
