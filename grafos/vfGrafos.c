#include<stdio.h>
#include<malloc.h>
// MURILO BAUER CARDOSO DA ROSA
struct adjacente{
	struct adjacente *prox;
	int a;
};

struct vertice{
	struct vertice *proxv;
	int v;
	struct adjacente *proxa;
};

struct vertice *aloca_vertice(int v){
	struct vertice *novo;
	novo=(struct vertice *)malloc(sizeof(struct vertice));
	novo->v=v;
	novo->proxv=NULL;
	novo->proxa=NULL;
 return (novo); //retorna um endereço de memória
}

//Aloca um nodo do tipo adjacente
struct adjacente *aloca_adjacente(int a){
	struct adjacente *novo;
	novo=(struct adjacente *)malloc(sizeof(struct adjacente));
	novo->a=a;
	novo->prox=NULL;
 return (novo); //retorna um endereço de memória
}

int conecta(struct vertice **g, int v, int a){
	struct vertice *auxG = *g, *novo_v = NULL;
	struct adjacente *auxA = NULL, *auxB = NULL, *novo_a = NULL;
	for(; auxG; auxG = auxG -> proxv) {
        if (auxG -> v == v) {
            if (!(auxG -> proxa)) {
                novo_a = aloca_adjacente(a); // alocou o adjacente
				auxG -> proxa = novo_a; // conecta com o vertice
            }else{
                auxA = auxG -> proxa;
                novo_a = aloca_adjacente(a);
                for(; auxA; auxA = auxA -> prox){
                    if(a < auxA->a){ // ADJ. menor
                        auxB = auxG -> proxa;
                        while(auxB -> prox != auxA) {
                            if (auxB == auxA){
                                novo_a -> prox = auxA;
                                auxG -> proxa = novo_a;
                                return 1;
                        }
                        auxB = auxB -> prox;
                    }
                    if(!(auxB -> prox)) return 1;
                        auxB -> prox = novo_a;
                        novo_a -> prox = auxA;
                        return 1;
                    }if(a == auxA -> a) return 1; // ADJ. igual
            }
            auxA = auxG -> proxa;
            for(; auxA; auxA = auxA -> prox){
					if(!(auxA -> prox)){
						auxA -> prox = novo_a;
						return 1;
					}
				}
			}
			break;
        }if(!(auxG -> proxv)){
		 	novo_v = aloca_vertice(v);
		 	novo_a = aloca_adjacente(a);
			novo_v -> proxa = novo_a;
			auxG -> proxv = novo_v;
		 	return 1;
        }
        if(v < auxG -> v){
		 	novo_v = aloca_vertice(v);
		 	novo_v -> proxv = auxG;
		 	*g = novo_v;
		 	novo_a = aloca_adjacente(a);
			(*g) -> proxa = novo_a;
		 	return 1;
        }
	 }
 }

int desconectaAdjacente(struct vertice **g, int v, int a) {
    struct vertice *auxG = *g;
    struct adjacente *auxA = NULL, *auxB = NULL, *del = NULL;
    for(; auxG; auxG = auxG -> proxv) {
        if(auxG -> v == v){
 			auxA = auxG -> proxa;
 			for(; auxA; auxA = auxA -> prox){
                if((auxA -> a == a) && (auxA == auxG -> proxa)){
                    del = auxA;
                    auxG -> proxa = auxA -> prox;
                    free(del);
                    return 1;
                }if(!(auxA -> prox)){
                    auxB = auxG -> proxa;
                    for(; auxB; auxB = auxB -> prox){
                        if(auxB -> prox == auxA){
                            del = auxA;
                            auxB -> prox = NULL;
                            free(del);
                            return 1;
                        }
                    }
                }else{
                    auxB = auxG -> proxa;
                    for(; auxB; auxB = auxB -> prox){
                        if(auxB -> prox == auxA){
                            del = auxA;
                            auxB -> prox = auxA -> prox;
                            free(del);
                            return 1;
                        }
                    }
                }
 			}
        }
    }
    return 0;
}

int pesquisaVerticeAdj (struct vertice **g, int v, int a) {
	struct vertice *auxG = *g;
	struct adjacente *auxA = NULL;
	int achou = 0;
	for(; auxG; auxG = auxG -> proxv){
        if(auxG -> v == v) {
            auxA = auxG -> proxa;
            for(; auxA; auxA = auxA -> prox) {
                if (auxA -> a == a) achou = 1;
            }
        }
    }
    return achou;
}

int imprimeGrafo(struct vertice **g){
	struct vertice *auxG = *g;
	struct adjacente *auxA = NULL;
	while(auxG != NULL) {
		printf("%d --> ", auxG -> v);
		auxA = auxG -> proxa;
		while(auxA != NULL){
			printf("%d -->", auxA -> a);
			auxA = auxA -> prox;
		}
		printf("\n");
		auxG = auxG -> proxv;
    }
}

int main() {
struct vertice *gr = NULL;
int v,a, achou;
do{
	printf("\nPara encerrar digite 0 para o vertice e o adjacente\n");
	printf("Digite o vertice: ");
	scanf("%d",&v);
	printf("Digite o adjacente: ");
	scanf("%d",&a);
	if((v!=0)&&(a!=0)){
	 	if(!(gr)){
	 		gr = aloca_vertice(v);
		 }
		conecta(&gr,v,a);
		imprimeGrafo(&gr);

	}
}while((v!=0)&&(a!=0));

 do{
    printf("\nInforme o vertice relativo ao adjacente que voce deseja desconectar: \n");
    printf("Digite o vertice: ");
	 scanf("%i",&v);
    printf("Informe qual do(s) adjacente(s) relativo ao vertice %d voce deseja desconectar: ", v);
	scanf("%d", &a);
    if((v!=0)&&(a!=0)){
        if(!(gr)) printf("Não é possivel desconectar um grafo inexistente.\n");

        if (!desconectaAdjacente(&gr,v,a)) printf("Nao existe o adjacente ou o vertice informado.\n");
		else printf("Desconectado com sucesso.\n");

		imprimeGrafo(&gr);

        printf("\n\nInforme um vertice e adjacente para pesquisar no grafo.\n");
        printf("Digite o vertice: ");
        scanf("%d",&v);
        printf("Digite o adjacente: ");
        scanf("%d",&a);
        achou = pesquisaVerticeAdj(&gr,v,a);
        if (achou) printf("Arco encontrado com sucesso.\n");
        else printf("Arco informado nao existente.\n");
        imprimeGrafo(&gr);
    }
}while((v!=0)&&(a!=0));

}
