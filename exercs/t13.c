#include <stdio.h>
#include <stdlib.h>

int buscaValor( int*, int, int);
int buscaBinariaR( int*, int, int, int);
int buscaBinariaI( int*, int, int);
int alimentaVETAleatorio (int*, int);

int main (int argc, char *argv[]) /* Exemplo de uso */
{
	int *vetor;

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

	srand(time(NULL));

	alimentaVETAleatorio (vetor, tam);

	int retorno;
	int existe = rand() % tam;
	existe = vetor[existe];
	int inexistenteMenorUltimo = vetor[tam - 1] - 1;
	int inexistenteMaiorUltimo = vetor[tam - 1] + 1;

	printf("Testes de busca sequencial\n");

	//chamar tempo
	retorno = buscaValor( vetor, tam, existe);
	if (retorno != -1) printf("%d encontrado na posicao %d\n", existe, retorno);
	//pausar tempo
	//chamar tempo
	retorno = buscaValor( vetor, tam, inexistenteMenorUltimo);
	if (retorno == -1) printf("%d nao encontrado\n", inexistenteMenorUltimo);
	//pausar tempo
	//chamar tempo
	retorno = buscaValor( vetor, tam, inexistenteMaiorUltimo);
	if (retorno == -1) printf("%d nao encontrado\n", inexistenteMaiorUltimo);
	//pausar tempo

	printf("\nTestes busca binaria recursiva\n");

	//chamar tempo
	retorno = buscaBinariaR( vetor, 0, tam - 1, existe);
	if (retorno != -1) printf("%d encontrado na posicao %d\n", existe, retorno);
	//pausar tempo
	//chamar tempo
	retorno = buscaBinariaR( vetor, 0, tam - 1, inexistenteMenorUltimo);
	if (retorno == -1) printf("%d nao encontrado\n", inexistenteMenorUltimo);
	//pausar tempo
	//chamar tempo
	retorno = buscaBinariaR( vetor, 0, tam - 1, inexistenteMaiorUltimo);
	if (retorno == -1) printf("%d nao encontrado\n", inexistenteMaiorUltimo);
	//pausar tempo


	printf("\nTestes busca binaria iterativa\n");

	//chamar tempo
	retorno = buscaBinariaI( vetor, existe, tam);
	if (retorno != -1) printf("%d encontrado na posicao %d\n", existe, retorno);
	//pausar tempo
	//chamar tempo
	retorno = buscaBinariaI( vetor, inexistenteMenorUltimo, tam);
	if (retorno == -1) printf("%d nao encontrado\n", inexistenteMenorUltimo);
	//pausar tempo
	//chamar tempo
	retorno = buscaBinariaI( vetor, inexistenteMaiorUltimo, tam);
	if (retorno == -1) printf("%d nao encontrado\n", inexistenteMaiorUltimo);
	//pausar tempo


	free(vetor);
}

int buscaValor( int* v, int tam, int n) {
	int i;
	for (i = 0; i < tam; i++) {
		if (v[i] == n) return i;
		if (v[i] > n) return -1;
	}
	return -1;
}

int buscaBinariaR( int* arr, int e, int d, int x)
{
   if (d >= e)
   {
        int meio = e + (d - e)/2;
        if (arr[meio] == x) {
        	return meio;
		}
        if (arr[meio] > x) {
        	return buscaBinariaR(arr, e, meio-1, x);
		}
        return buscaBinariaR(arr, meio+1, d, x);
   }
   return -1;
}

int buscaBinariaI( int* arr, int x, int tam)
{
	int e = 0, d = tam - 1, meio;
	while(d >= e)
	{
		meio = e + (d - e)/2;
		if (arr[meio] == x) return meio;
		if (arr[meio] > x) d = meio - 1;
		if (arr[meio] < x) e = meio + 1;
	}
	return -1;
}

int alimentaVETAleatorio (int *v, int t)
{
	int i;
	for (i = 0; i < t; i++) {
		if (i % 2 == 0) v[i] = i * 4 + 7;
		else v[i] = i * 4 + 5;
	}
	return(i);
}
