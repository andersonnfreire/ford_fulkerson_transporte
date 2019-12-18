#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
int V = 0;//quantidade registros transporte
int T = 0;//quantidade registros de veiculo
int qtd = 0;//total de registros transporte
int totalCarroAlocado = 0;
int totalNaoAlocado = 0;
int capacidadeMenor = 0;
int totalSobrando = 0;
bool inseriu = true;
float soma = 0.0;

typedef struct Transporte
{
	float fluxo;
	float distancia;
}TTransporte;
typedef struct Carro
{
	int indice;
	char placa[100];
	char nome[200];
	float capacidade;
}TCarro;
//==========================================================================
// FILA 
//==========================================================================
//Estrutura do tipo Elemento
typedef struct TipoElemento{
	int valor;
	struct TipoElemento *prox;
	struct TipoElemento *ant;
}TEle;// Fila

//Estrutura do tipo Pilha
typedef struct TipoFila{
	TEle *inicio;
	TEle *fim;
	int quant;
}TFila;

TFila fila;

float fordFulkerson(TTransporte graph[V][V], int s, int t,TCarro vetorCarro[]);



void iniciarFila(TFila *fila){
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->quant = 0;
}
//----------------------------------------------------------------------------------------------------------------------------------
int filaVazia(TFila *fila){
	if(fila->inicio == NULL){
		return 1;
	}
	else{
		return 0;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
int VerificarnaFila(int valor, TFila *fila){
	TEle *aux = fila->inicio;
	
	while(aux != NULL){
		if(aux->valor == valor){
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------
void excluirdaFila(TFila *fila){
	TEle *retirado;
	retirado = NULL;
	// Verifica se a fila está vazia
	if(!filaVazia(fila)){
		retirado = fila->inicio;
		fila->inicio = fila->inicio->prox;

		if(fila->inicio == NULL){
			fila->fim = NULL;
		}

		else{
			fila->inicio->ant = NULL;
		}
		retirado->prox = NULL;
		fila->quant = fila->quant - 1;
	}
}
//--------------------------------------------------------------------------------------------
void inserirFila(TFila *fila, int valor){
	//printf("- Valor: %d   Distancia: %d\n", nome, distancia);
	TEle *novo = (TEle*)malloc(sizeof(TEle));
	novo->valor = valor;

	novo->ant = NULL;
	novo->prox = NULL;
	
	// Verifica se a fila esta vazia para inserir como o primeiro elemento
	if(filaVazia(fila)){
		fila->inicio = novo;
		fila->fim = novo;
	}
	// insere na lista que ja tem um elemento
	else{
		fila->fim->prox = novo;
		novo->ant = fila->fim;
		fila->fim = novo;
	}
	fila->quant++;
	
}


/**=============================== CONVERTE STRING PARA FLOAT ===========================================OK**/
float convertStringToFloat(char *token)
{
	char numF[10];
	int i, k = 0, tam, achou = 0;

	/**Procura virgula*/
	tam = strlen(token);
	while(i < tam)
	{

		if(token[i] == ',')
		{
			numF[k] = '.';
			achou = 1;
		}
		else numF[k] = token[i];
		k++;
		i++;
	}

	if(achou != 1) return atof(token);
	else return atof(numF);
}

void carregarDados(char *nome)
{
	FILE *fp;

	char string[1000];
	char cidades[1000];
	int i;

	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}
	i = -1;

	while (!feof(fp))
	{
		if(fgets(string, 2000, fp))
		{
			if(i == -1)
			{
				strcpy(cidades, string);
				i++;
			}
			if(inseriu)
			{
				V++;
			}	
		}
	}
	if(inseriu)
	{
		V -= 1;
		qtd = pow(V,2);
		inseriu = false;
	}
	fclose(fp);
}
void carregarDadosVeiculo(char *nome)
{
	FILE *fp;

	char string[1000];

	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		if(fgets(string, 2000, fp))
		{
			T++;	
		}
	}
	fclose(fp);
}
TTransporte * inserirDados(TTransporte vetorA[],char * nome)
{
	FILE *fp;

	char string[1000];
	char *substring = (char*)malloc(5000 * sizeof(char));
	char cidades[1000];
	float custo;
	int i, j, v, y, f;

	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}
	i = -1;
	j = 0;
	v = 0;

	int numMatriz, tot = 0;;

	while (!feof(fp))
	{
		if(fgets(string, 2000, fp))
		{
			if(i == -1)
			{
				strcpy(cidades, string);
				
			}
			if(i > -1)
			{
				substring = strtok(string, ";\n");

				while(substring != NULL)
				{

					if (j == 0)
					{
						strcpy(cidades, substring);
						//strcpy(array[v].nome, substring);
						j++;
					}
					else
					{
				
						vetorA[v].fluxo = convertStringToFloat(substring);
						v++;
					}
					substring = strtok(NULL, ";\n");
				}
				j = 0;
				y++;
				substring = strtok(NULL, ";\n");
				
			}
			i++;
		}
	}
	fclose(fp);
	
	return vetorA;
}
TTransporte * inserirDados2(TTransporte vetorA[],char * nome)
{
	FILE *fp;

	char string[1000];
	char *substring = (char*)malloc(5000 * sizeof(char));
	char cidades[1000];
	float custo;
	int i, j, v, y, f;

	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}
	i = -1;
	j = 0;
	v = 0;

	int numMatriz, tot = 0;;

	while (!feof(fp))
	{
		if(fgets(string, 2000, fp))
		{
			if(i == -1)
			{
				strcpy(cidades, string);
				
			}
			if(i > -1)
			{
				substring = strtok(string, ";\n");

				while(substring != NULL)
				{

					if (j == 0)
					{
						strcpy(cidades, substring);
						//strcpy(array[v].nome, substring);
						j++;
					}
					else
					{
				
						vetorA[v].distancia = convertStringToFloat(substring);
						v++;
					}
					substring = strtok(NULL, ";\n");
				}
				j = 0;
				y++;
				substring = strtok(NULL, ";\n");
				
			}
			i++;
		}
	}
	fclose(fp);
	
	return vetorA;
}
TCarro * inserirDadosVeiculo(TCarro vetorA[],char * nome)
{
	FILE *fp;
	
	char string[128];
	char *substring = (char*)malloc(sizeof(char));
	char nomes[200];
	int i;
	
	if ((fp = fopen(nome, "r")) == NULL)
	{
		printf("\nO arquivo nao pode ser aberto.\n");
		exit(1);
	}
	int j = 0;
	while (!feof(fp))
	{
		if(fgets(string, 128, fp))
		{
			i = 0;
			substring = strtok(string, ";\n");
			strcpy(nomes, substring);
			while(substring != NULL)
			{

				if (i == 0)
				{
					strcpy(vetorA[j].placa,substring);
					substring = strtok(NULL, ";\n");
				}
				if(i == 1)
				{
					strcpy(vetorA[j].nome,substring);
					substring = strtok(NULL, ";\n");
				}
				if (i == 2)
				{
					vetorA[j].capacidade = atof(substring);
					substring = strtok(NULL, ";\n");
					j++;
				}
				else
				{
					putchar('\n');
				}
				i++;
			}
				
		}
	}
	fclose(fp);
	return vetorA;
}

void inicializarVetorTransporte(TTransporte vetor[], TTransporte vetorB[])
{
	int i;
	for(i = 0; i < qtd; i++)
	{
		vetor[i].fluxo = -1;
		vetorB[i].distancia = -1;
	}
}
void inicializarVetorVeiculo(TCarro car[])
{
	int i;
	for(i = 0; i < T; i++)
	{
		car[i].indice = i;
		strcpy(car[i].placa," ");
		strcpy(car[i].nome," ");
		car[i].capacidade = 0.0;
		
	}
}

void inserirFluxo(TTransporte mtrx[V][V],TTransporte vetorF[], TTransporte vetorD[])
{
	int i,j,v=0;

	for(i = 0; i < V; i++)
	{
		
		for(j = 0; j < V;j++)
		{
			
		    mtrx[i][j].fluxo = vetorF[v].fluxo;
		    mtrx[i][j].distancia = vetorD[v].distancia;
			v++;	
		}
		  
	}
}
void imprimirMatriz(TTransporte mtrx[V][V])
{
	int i,j;
	printf(" ======= TRANSPORTE =============\n\n");
	for(i = 0; i < V; i++)
	{
		for(j = 0; j < V;j++)
		{
			
		    printf("Fluxo - %lf | Distancia: %lf\n",mtrx[i][j].fluxo,mtrx[i][j].distancia);
		}
		printf("\n");
	}
}
void imprimirVetor(TCarro vet[])
{
	int i,j;
	printf(" ======= CARROS =============\n\n");
	for(i = 0; i < T; i++)
	{
		printf("INDICE: %d \n\n",i);
		printf("PLACA: %s \n",vet[i].placa);
		printf("NOME: %s  \n",vet[i].nome);
		printf("CAPACIDADE: %.2f  \n",vet[i].capacidade);
		printf("\n");
	}
}

int verificarCarro(int fluxo,TCarro vetorCarro[], int carroUtilizado[], int vetorCarroNaoAlocado[])
{
	int i,j;
	for(i = 0; i < T; i++)
	{
		if(fluxo <= vetorCarro[i].capacidade)
		{
			if(carroUtilizado[i] == -1)
			{
				carroUtilizado[i] = i;
				return i;
			}
		}		
	}
	return -1;
}
int imprimirCapacidade(int aux[V][V], int fluxo,TTransporte graph[V][V], TCarro vetorCarro[], int carroUtilizado[], int vetorCarroNaoAlocado[])
{
	int i=0, j=0, cont = 0;
	TCarro nome[T];
	bool conferir;
	int carroAlocado = verificarCarro(fluxo,vetorCarro,carroUtilizado, vetorCarroNaoAlocado);
	
	//printf("\n\n\n INDICE CARRO: %d ",carroAlocado);
	
	
	if(carroAlocado != -1)
	{		
		printf("CARRO %s : %d - ALOCADO COM SUCESSO !!! \n", vetorCarro[carroAlocado].nome, carroAlocado);
		
		strcpy(vetorCarro[carroAlocado].nome,"");
		vetorCarro[carroAlocado].capacidade = 0;
		strcpy(vetorCarro[carroAlocado].placa,"");
	    totalCarroAlocado++;
	}
	else
	{
		totalNaoAlocado++;
	
	}
	return carroAlocado;
}
/* Returns true if there is a path from source 's' to sink 't' in 
  residual graph. Also fills parent[] to store the path */
bool bfs(float rGraph[V][V], int s, int t, int parent[]) 
{ 
   	int v, u;
    // Crie um vetor para armazenar os pontos visitados, inicialmente coloquei todos os vértices como não visitados = 0
    int visitados[V]; 
    memset(visitados, 0, sizeof(visitados)); 

    inserirFila(&fila, s);
    visitados[s] = 1;// marcando como visitado 
    parent[s] = -1; 
    
    // Loop que verifica as conexoes do grafo
    while (!filaVazia(&fila)){ //quando chega no destino a fila estará vazia
        u = fila.inicio->valor; // recebe o inicio da fila
        
        excluirdaFila(&fila);
  
        for(v = 0; v < V; v++) { // percorre as conexões de uma linha do grafico
            if ((visitados[v] == 0) && (rGraph[u][v] > 0)) { // se não foi visitado e tiver um fluxo de capacidade ainda
            	inserirFila(&fila, v);// insere a coluna
                parent[v] = u; // guarda as linhas visitadas da matriz
                visitados[v] = 1; // marca como visitado
            } 
        } 
    } 
      // If we reached sink in BFS starting from source, then return 
    // true, else false 
    return (visitados[t] == 1); // se o valor do destino foi visitado, ou seja, se chegou no destino
} 
int imprimirVeiculosNaoAlocados(TCarro vetCarro[],int vetor[])
{
	int i = 0;
	bool condicao;
	for(i = 0; i < T;i++ )
	{	
		if(vetor[i] != i &&  !(strcmp(vetCarro[i].nome, vetCarro[vetor[i]].nome)==0))
		{

		   printf("\n\n\t INDICE: %d CARRO: %s NAO ALOCADO\n",i,vetCarro[i].nome);
		}
	}	
}
// Returns the maximum flow from s to t in the given graph 
int fordFulkersonOriginal(float graph[V][V], int s, int t, int parent[]) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    float rGraph[V][V]; // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             rGraph[u][v] = graph[u][v]; 
  
    float max_flow = 0;  // There is no flow initially 
  
    // Augment the flow while tere is path from source to sink 
    while (bfs(rGraph, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = __min(path_flow, rGraph[u][v]); 
        } 
  
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
  
    // Return the overall flow 
    return max_flow; 
} 
float verificarMaiorValor(float graph[V][V])
{
	int i,j;
	int maior= graph[0][0];
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
           if(graph[i][j]>maior){
            maior=graph[i][j];
           }
        }
    }
    return maior;
}
void verificarVerticeNulo(float rGraph[V][V], TTransporte graph[V][V], int s, int t)
{
	int i, j, k, l, v, u;
	int maior = verificarMaiorValor(rGraph);
	float fluxoMaior = 0;
	int pais[V];
	float fluxoAnt = 0;
	for(i = 0; i < V; i++)
	{
		for(j = 0; j < V; j++)
		{
			if(rGraph[i][j] == 0 && graph[i][j].fluxo != 0 && i != j)
			{
				for(k = 0; k < maior; k++)
				{
					rGraph[i][j]++;
					fluxoMaior = fordFulkersonOriginal(rGraph, s, t, pais);
					if((fluxoMaior - fluxoAnt) == 1)
					{
						fluxoAnt = fluxoMaior;
					}
					else
					{
						break;
					}

				}

				if(fluxoMaior > 0)
				{
					printf("\n-CAMINHO-\n");
					for(v = t; v != s; v = pais[v])   // for que procura o fluxo minimo
					{
						u = pais[v];
						printf("%d- %d :", v, u);
					}
					printf("\nVertice NULO: ");
					printf("\n %d -> %d : %.2f", i,j,fluxoMaior);
					printf("\n");
					printf("\n");
				}

				rGraph[i][j] = 0;
				fluxoAnt = 0;
			}
		}
	}
}

// Returns the maximum flow from s to t in the given graph 
float fordFulkerson(TTransporte graph[V][V], int s, int t,TCarro vetorCarro[]) 
{ 
    int u, v, k = 0; 
    int indice=0;
    float rGraph[V][V]; 
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++){ 
             rGraph[u][v] = graph[u][v].fluxo;
		}
		printf("\n");
	}		  
    int aux[V][V];
    int parent[V];  // This array is filled by BFS and to store path 
  
    float max_flow = 0;  // There is no flow initially 
    memset(parent, 0, sizeof(parent));// limpando o vetor
    
	int carroUtilizado[T]; 
    memset(carroUtilizado, -1, sizeof(carroUtilizado)); 
    
    int teste[T]; 
    memset(teste, -1, sizeof(teste)); 
    
    int a=0;
    float sum=0.0;
    int vetorCarroNaoAlocado[T]; 
    memset(vetorCarroNaoAlocado, -1, sizeof(vetorCarroNaoAlocado));
    // Augment the flow while tere is path from source to sink
	printf("\n");
	printf("\n ============= CAMINHO PERCORRIDO, CARRO ALOCADO E DISTANCIA   =================\n");
	
    while (bfs(rGraph, s, t, parent)) 
    { 
    	if(totalCarroAlocado == T)
    	{
    		printf("\n ============= VERIFICANDO SE EXISTE CARROS SUFICIENTE =====================\n");
    		printf("\n\n\t NAO EXISTE VEICULOS DISPONIVEIS SUFICIENTES\n\n");
    	    break;	
		}
		
	    // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        float path_flow = 1000000000; 
 		for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = __min(path_flow, rGraph[u][v]);
			sum += graph[u][v].distancia; 
        } 

        	
	    	for (v=t; v != s; v=parent[v]) 
	        { 
	           
				u = parent[v];
				 
	            rGraph[u][v] -= path_flow; 
	    		printf("CAMINHO: %d -> %d \n\n",u,v);	            
	            aux[u][v] = u;
	            aux[v][u] = v;   
	        }
	        
	        indice = imprimirCapacidade(aux,path_flow,graph,vetorCarro,carroUtilizado,vetorCarroNaoAlocado);
	        printf("DISTANCIA PERCORRIDA: %.2f\n\n",sum);
	        sum = 0.0;
	        if(indice != -1)
	        {
			   teste[k] = indice;   	
			}	
	        k++;
	        max_flow += path_flow;
    }
    
	printf("\n");
	printf("\n ============= VERIFICANDO CARROS NAO UTILIZADOS =================\n");
	imprimirVeiculosNaoAlocados(vetorCarro, teste);
	printf("\n");
	
	
	int g,z;
	printf("\n");
	printf("\n ============= VERIFICANDO CARGA PENDENTE =================\n");
	
	for(g = 0; g < V; g++)
	{
		for(z = 0; z < V; z++)
		{
			if(rGraph[g][z] > 0)
			{
				printf("\n\n %d - %d : %.2f \n", g,z,rGraph[g][z]);
			}
		}	
	}
	
	printf("\n");
	printf("\n ============= VERIFICANDO CAMINHO NO QUAL APENAS UMA ARESTA ESTA NULA =================\n");
	
	
    verificarVerticeNulo(rGraph,graph,s,t);	

    return max_flow; 
} 

void swap(TCarro *xp, TCarro *yp)  
{  
    TCarro temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
// A function to implement bubble sort  
void bubbleSort(TCarro arr[])  
{  
    int i, j;  
    for (i = 0; i < T-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < T-i-1; j++)  
        if (arr[j].capacidade > arr[j+1].capacidade)  
            swap(&arr[j], &arr[j+1]);  
}
int main(){
	
	/*char nome[100];
	printf("Informe o nome do arquivo:");
	gets(nome);*/
	int origem, destino;
	carregarDados("fluxo.txt");
	carregarDados("distancia.txt");
	carregarDadosVeiculo("veiculos.txt");
	
	TTransporte vetorFluxo[qtd];
	TTransporte vetorDistancia[qtd];
	TCarro vetorCarro[T];
	
	TTransporte graph[V][V];
	
	inicializarVetorTransporte(vetorFluxo, vetorDistancia);
	inicializarVetorVeiculo(vetorCarro);
	
	inserirDados(vetorFluxo,"fluxo.txt");
	inserirDados2(vetorDistancia,"distancia.txt");
	inserirDadosVeiculo(vetorCarro,"veiculos.txt");
	
	inserirFluxo(graph,vetorFluxo,vetorDistancia);
	
	bubbleSort(vetorCarro);
	

	imprimirVetor(vetorCarro);
	printf("\nInforme a origem: ");
	scanf("%d",&origem);
	printf("\nInforme o destino: ");
	scanf("%d", &destino);
	
	fordFulkerson(graph, origem, destino,vetorCarro);
	
	return 0;
	
}
