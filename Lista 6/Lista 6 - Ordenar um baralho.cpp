#include <stdio.h>
#include <stdlib.h>
#define ace 1

//Elias Cícero Moreira Guedes

/*Ordenar as cartas de um baralho:
- Usaremos a seguinte estratégia: converter um caractere ou uma string para seu valor inteiro e comparar se é menor. Se sim, então a palavra vem antes, de acordo com a ordem alfabética.
- Mas no C não precisamos fazer o cast(conversão), pois ele automaticamente já faz por você.
- São exemplos de expressões com valores verdade 1:
	if('a' < 'b');
	if("abacate" < "boi");
- Mas é melhor fazer essa comparação com letras, char únicos. Não dá muito certo com strings.
*/

struct carta{
	char naipe;
	int numero;
};

struct lista{
	int qtd;
	struct carta baralho[52];
};

typedef struct carta Carta;
typedef struct lista Lista;

		//Métodos
void imprimeLista(Lista* li){
	int i;
	printf("Lista:\n");
	for(i=0; i<li->qtd; i++){
		printf("carta %d: ", (i+1));
		if (2<= li->baralho[i].numero && li->baralho[i].numero <= 10){
			printf("%d de ", (li->baralho[i].numero));
		}
		if (li->baralho[i].numero == 11){
			printf("V de ");
		}
		if (li->baralho[i].numero == 12){
			printf("D de ");
		}
		if (li->baralho[i].numero == 13){
			printf("R de ");
		}
		if (li->baralho[i].numero == ace){
			printf("AS de ");
		}
		if (li->baralho[i].naipe == 'e'){
			printf("espadas\n");
		}
		if (li->baralho[i].naipe == 'c'){
			printf("copas\n");
		}
		if (li->baralho[i].naipe == 'p'){
			printf("paus\n");
		}
		if (li->baralho[i].naipe == 'o'){
			printf("ouros\n");
		}
	}
}

int lista_cheia(Lista* li){
	if(li == NULL)
		return -1;
	else
		return (li->qtd == 52);
}

int inserirFinal(Lista* li, Carta c){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}
	li->baralho[li->qtd] = c;
	li->qtd++;
	return 1;
}

int ordenarBaralho(Lista* li){
	Carta copas[13];
	Carta espadas[13];
	Carta ouros[13];
	Carta paus[13];
	int posCopas = 0, posEspadas = 0, posOuros = 0, posPaus = 0;
	int i, k, l, m, n, p, q, r, s;
	Carta auxC, auxE, auxO, auxP;
	int orgC, orgE, orgO, orgP;
	int orgES = 0;
	int orgOU = 0;
	int orgPA = 0;
	
	//Separa a lista em 4 vetores, cada um de naipe diferente.
	for (i=0; i<li->qtd; i++){
		if(li->baralho[i].naipe == 'c'){
			copas[posCopas] = li->baralho[i];
			posCopas++;
		}
		if(li->baralho[i].naipe == 'e'){
			espadas[posEspadas] = li->baralho[i];
			posEspadas++;
		}
		if(li->baralho[i].naipe == 'o'){
			ouros[posOuros] = li->baralho[i];
			posOuros++;
		}
		if(li->baralho[i].naipe == 'p'){
			paus[posPaus] = li->baralho[i];
			posPaus++;
		}	
	}
	
	//Organiza o vetor de copas
	for(k=0; k<13; k++){
		for(l=0; l<13; l++){
			if(copas[k].numero < copas[l].numero){
				auxC = copas[k];
				copas[k] = copas[l];
				copas[l] = auxC;
			}
		}
	}

	//Organiza o vetor de espadas
	for(m=0; m<13; m++){
		for(n=0; n<13; n++){
			if(espadas[m].numero < espadas[n].numero){
				auxE = espadas[m];
				espadas[m] = espadas[n];
				espadas[n] = auxE;
			}
		}
	}

	//organiza o vetor de ouros
	for(p=0; p<13; p++){
		for(q=0; q<13; q++){
			if(ouros[p].numero < ouros[q].numero){
				auxO = ouros[p];
				ouros[p] = ouros[q];
				ouros[q] = auxO;
			}
		}
	}

	//organiza o vetor de paus
	//Elias
	for(r=0; r<13; r++){
		for(s=0; s<13; s++){
			if(paus[r].numero < paus[s].numero){
				auxP = paus[r];
				paus[r] = paus[s];
				paus[s] = auxP;
			}
		}
	}

	//Insere de forma organizada na lista sobrepondo as Cartas desorganizadas
	for(orgC=0; orgC<13; orgC++){
		li->baralho[orgC] = copas[orgC];
	}
	for(orgE=13; orgE<26; orgE++){
		li->baralho[orgE] = espadas[orgES];
		orgES++;
	}
	for(orgO=26; orgO<39; orgO++){
		li->baralho[orgO] = ouros[orgOU];
		orgOU++;
	}
	for(orgP=39; orgP<52; orgP++){
		li->baralho[orgP] = paus[orgPA];
		orgPA++;
	}
}


Lista* CriarLista(){
	Lista *li;
	li = (Lista*) malloc(sizeof(struct lista));
	if (li!= NULL){
		li->qtd = 0;
	}
	return li;
}

void DeletarLista(Lista* li){
	free(li);
}

int main(){
	//Elias.
	Carta c1;	c1.naipe = 'e';		c1.numero = ace;
	Carta c2;	c2.naipe = 'e';		c2.numero = 2;
	Carta c3;	c3.naipe = 'e';		c3.numero = 3;
	Carta c4;	c4.naipe = 'e';		c4.numero = 4;
	Carta c5;	c5.naipe = 'e';		c5.numero = 5;
	Carta c6;	c6.naipe = 'e';		c6.numero = 6;
	Carta c7;	c7.naipe = 'e';		c7.numero = 7;
	Carta c8;	c8.naipe = 'e';		c8.numero = 8;
	Carta c9;	c9.naipe = 'e';		c9.numero = 9;
	Carta c10;	c10.naipe = 'e';	c10.numero = 10;
	Carta c11;	c11.naipe = 'e';	c11.numero = 11;
	Carta c12;	c12.naipe = 'e';	c12.numero = 12;
	Carta c13;	c13.naipe = 'e';	c13.numero = 13;
	
	Carta c14;	c14.naipe = 'c';	c14.numero = ace;
	Carta c15;	c15.naipe = 'c';	c15.numero = 2;
	Carta c16;	c16.naipe = 'c';	c16.numero = 3;
	Carta c17;	c17.naipe = 'c';	c17.numero = 4;
	Carta c18;	c18.naipe = 'c';	c18.numero = 5;
	Carta c19;	c19.naipe = 'c';	c19.numero = 6;
	Carta c20;	c20.naipe = 'c';	c20.numero = 7;
	Carta c21;	c21.naipe = 'c';	c21.numero = 8;
	Carta c22;	c22.naipe = 'c';	c22.numero = 9;
	Carta c23;	c23.naipe = 'c';	c23.numero = 10;
	Carta c24;	c24.naipe = 'c';	c24.numero = 11;
	Carta c25;	c25.naipe = 'c';	c25.numero = 12;
	Carta c26;	c26.naipe = 'c';	c26.numero = 13;
	
	Carta c27;	c27.naipe = 'o';	c27.numero = ace;
	Carta c28;	c28.naipe = 'o';	c28.numero = 2;
	Carta c29;	c29.naipe = 'o';	c29.numero = 3;
	Carta c30;	c30.naipe = 'o';	c30.numero = 4;
	Carta c31;	c31.naipe = 'o';	c31.numero = 5;
	Carta c32;	c32.naipe = 'o';	c32.numero = 6;
	Carta c33;	c33.naipe = 'o';	c33.numero = 7;
	Carta c34;	c34.naipe = 'o';	c34.numero = 8;
	Carta c35;	c35.naipe = 'o';	c35.numero = 9;
	Carta c36;	c36.naipe = 'o';	c36.numero = 10;
	Carta c37;	c37.naipe = 'o';	c37.numero = 11;
	Carta c38;	c38.naipe = 'o';	c38.numero = 12;
	Carta c39;	c39.naipe = 'o';	c39.numero = 13;
	
	Carta c40;	c40.naipe = 'p';	c40.numero = ace;
	Carta c41;	c41.naipe = 'p';	c41.numero = 2;
	Carta c42;	c42.naipe = 'p';	c42.numero = 3;
	Carta c43;	c43.naipe = 'p';	c43.numero = 4;
	Carta c44;	c44.naipe = 'p';	c44.numero = 5;
	Carta c45;	c45.naipe = 'p';	c45.numero = 6;
	Carta c46;	c46.naipe = 'p';	c46.numero = 7;
	Carta c47;	c47.naipe = 'p';	c47.numero = 8;
	Carta c48;	c48.naipe = 'p';	c48.numero = 9;
	Carta c49;	c49.naipe = 'p';	c49.numero = 10;
	Carta c50;	c50.naipe = 'p';	c50.numero = 11;
	Carta c51;	c51.naipe = 'p';	c51.numero = 12;
	Carta c52;	c52.naipe = 'p';	c52.numero = 13;
	
	Lista* li = CriarLista();
	inserirFinal(li,c5);	inserirFinal(li,c48);	inserirFinal(li,c42);	inserirFinal(li,c23);
	inserirFinal(li,c29);	inserirFinal(li,c12);	inserirFinal(li,c44);	inserirFinal(li,c4);
	inserirFinal(li,c47);	inserirFinal(li,c14);	inserirFinal(li,c18);	inserirFinal(li,c52);
	inserirFinal(li,c11);	inserirFinal(li,c6);	inserirFinal(li,c3);	inserirFinal(li,c43);
	inserirFinal(li,c28);	inserirFinal(li,c17);	inserirFinal(li,c34);	inserirFinal(li,c22);
	inserirFinal(li,c49);	inserirFinal(li,c50);	inserirFinal(li,c7);	inserirFinal(li,c36);
	inserirFinal(li,c39);	inserirFinal(li,c2);	inserirFinal(li,c19);	inserirFinal(li,c38);
	inserirFinal(li,c40);	inserirFinal(li,c10);	inserirFinal(li,c21);	inserirFinal(li,c37);
	inserirFinal(li,c41);	inserirFinal(li,c16);	inserirFinal(li,c31);	inserirFinal(li,c24);
	inserirFinal(li,c1);	inserirFinal(li,c51);	inserirFinal(li,c32);	inserirFinal(li,c26);
	inserirFinal(li,c27);	inserirFinal(li,c13);	inserirFinal(li,c20);	inserirFinal(li,c8);
	inserirFinal(li,c46);	inserirFinal(li,c30);	inserirFinal(li,c45);	inserirFinal(li,c25);
	inserirFinal(li,c33);	inserirFinal(li,c15);	inserirFinal(li,c9);	inserirFinal(li,c35);
	
	imprimeLista(li);
	
	printf("\n-----	-----	Depois de ordenado	-----	-----	-----\n");
	ordenarBaralho(li);
	imprimeLista(li);
	DeletarLista(li);
	

	system("pause");
	return 0;	
}
