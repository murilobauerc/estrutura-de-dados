#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

int buscaValor( int* v, int tam, int n) {
	int i;
	for (i = 0; i < tam; i++) {
		if (v[i] == n) return i;
		if (v[i] > n) return -1;
	}
	return -1;
}

// DEVE TER FICADO UM BUBBLE SORT(ja conheciamos a implementa��o), MAS FIZEMOS NO BRA�O
void ordena( int* v, int tam) {
	int i, aux, flag = true;
	while (flag) {
		flag = false;
		for (i = 0; i < (tam - 1); i++) {
			if (v[i] > v[i + 1]) {
				flag = true;
				aux = v[i + 1];
				v[i + 1] = v[i];
				v[i] = aux;
			}
		}	
	}
}

int alimentaVETAleatorio (int *v, int t)
{
/* preeche o vetor v com valores aleat�rios entre
  -MAX a MAX (dica: para procurar um valor inexistente
  procure um valor fora deste range)
*/

	int i;
	int MAX=20000000; // seria de -20000000 a 20000000
	
	for (i = 0; i < t; i++) {
		v[i] = (rand() % MAX);
	}
	return(i);
}

int main (int argc, char *argv[]) /* Exemplo de uso */
{
/* Este main � um main m�nimo apenas com um exemplo de uso.
   O aluno ter� que altera-lo muito para realizar os testes.
   A seu crit�rio...
*/
	int *vetor;
	/* Para muitos elementos, jamais use aloca��o est�tica, pois haver�
	estouro de pilha. Malloc � o recomendado. Fa�a testes para ver at� qual
	quantidade de elementos tua mem�ria aceita. */
	
	int tam;
	
	if (argc!=2){
		fprintf(stderr, "Erro. Precisa passar o tamanho do vetor\n");
		return(1);
	}
	tam = atoi(argv[1]);
	
	vetor = (int *) malloc(tam * sizeof(int));
	if (vetor == NULL) {
		fprintf(stderr, "ERRO ao tentar alocar %d inteiros\n", tam);
		return(2);
	}

// inicio da semente de n�meros aleat�rios
	srand(time(NULL));

	alimentaVETAleatorio (vetor, tam);
	
	int val;
	printf("Digite um numero para buscar no vetor: ");
	scanf("%d", &val);
	fflush(stdin);
	
	/*printf("Vetor antes de ordenar\n");
	int i;
	for (i = 0; i < tam; i++) {
		printf("%d\t", vetor[i]);
	}*/
	
	printf("Pressione qualquer tecla para ordenar\n");
	getchar();
	ordena(vetor, tam);
	printf("Fim do ordenamento - Pressione qualquer tecla para continuar\n");
	getchar();
	
	/*printf("Vetor depois de ordenar\n");
	for (i = 0; i < tam; i++) {
		printf("%d\t", vetor[i]);
	}*/
	
	int resul = buscaValor(vetor, tam, val);
	if (resul == -1) {
		printf("Valor nao encontrado");	
	}
	else {
		printf("Valor %d encontrado na posicao %d\n", val, resul);
	}
	

/* Tua parte aqui.
- codigo para ler um valor de busca
- uma pausa para acertar o relogio teu :-D
- (dentro da medi��o de tempo) ordenar
- pausa: ver quanto tempo levou para ordenar
- usar um valor de busca que n�o existe e ver quanto tempo levou
*/

	free(vetor);
}
