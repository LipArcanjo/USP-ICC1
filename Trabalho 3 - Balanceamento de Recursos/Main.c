/*	 Trabalho III de Icc
	Autor: Luan Icaro Pinto Arcanjo
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Funcao que cria matriz dinamica como feita em sala
int **criaMatriz(int linhas,int colunas){
	int **posRec;
	


	posRec = (int **)malloc(sizeof(int *) * linhas);//Nesta linha cria o vetor de vetores, mas ainda nao se sabe o tamanho de cada vetor


	for (int i = 0; i < linhas; i++){
	  *(posRec+i) = (int *)malloc (sizeof(int) * colunas);//Da o tamanho de cada vetor atraves do for
	}

	return posRec; 
}

//esta funcao vai receber a matriz posRec e de acordo com o nRec vai preencher a matriz atraves do scanf
void PreenchePosRec(int nRec,int **posRec){
	int aux;
	for (int i = 0; i < nRec; i++){
		for (int j = 0; j < 2; j++){
			
			scanf("%d",&aux);
			posRec[i][j] = aux;
		}
	}
		
	
}

//adaptacao da funcao floodFill apresentada na descricao do trab
int FloodFill(int l,int c,int *lRec,int *cRec, int **map,int *v){


	//se a celula requerida estiver fora do mapa ou seu valor for diferente de 0 retorna
	if(l < 0 || l > 8 || c < 0 || c > 8 || map[l][c] != 0) {
		return 0;
	}
	//soma um ao contador
	*v = *v + 1;
	map[l][c] = 2;//esta "pintando" a celula de 2

	//verifica se ehh ja chegou no recurso, se sim retorna 1, se nao retorna continua o flood
	if(l != *lRec || c != *cRec){
		//o if serve pra ver se a floodFill mais interna que a atual retornou 1, serve para parar o floodfill quando achar o recurso. 
		if(FloodFill((l + 1),c,lRec,cRec,map,v) == 1){
			return 1;
		}
		if(FloodFill((l - 1),c,lRec,cRec,map,v) == 1){
			return 1;
		}
		if(FloodFill(l,(c - 1),lRec,cRec,map,v) == 1){
			return 1;
		}
		if(FloodFill(l,(c + 1),lRec,cRec,map,v) == 1){
			return 1;
		}

		return 0;

	}else{
		return 1;
	}
	
	
}
//essa funcao faz com que todas as celulas que foram "pintadas" de 2 retorne pra 0
void MapaValorPadrao(int **map){
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; j++)
		{
			if(map[i][j] == 2)
				map[i][j] = 0;
		}
	}
}

//calcula o E de um jogador
double CalculaE(int nRec, int *posJogador,int **posRec,int **map,int P){
	//v ehh uma especie de contador
	int v = 0;
	double E = 0;
	//vai fazer floodFill para cada recurdo
	for (int i = 0; i < nRec; i++)
	{
		//faz o flood fill
		FloodFill(posJogador[0],posJogador[1],&posRec[i][0],&posRec[i][1], map,&v);
		//retorna o mapa ao valor padrao
		MapaValorPadrao(map);
		//faz a somatoria da formula E-->j / P
		E += (double)v / (double)P;
		//retorna o contador ao valor padra
		v = 0;
	}
	//por fim divide por nrec que vai ser o N -1 da formula
	E = E / nRec;

	
	return E;


}



int main(int argc, char const *argv[])
{
	
	//Inicializa o map e faz a leitura
	int map[9][9] ={0};

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	//Recebe a posicao dos jogadores
	int pos1[2],pos2[2];
	scanf("%d",&pos1[0]);
	scanf("%d",&pos1[1]);
	scanf("%d",&pos2[0]);
	scanf("%d",&pos2[1]);

	//Entrada do numero e das Posicoes dos recursos;
	int nRec = 0;
	scanf("%d",&nRec);

	int **posRec;

	posRec = criaMatriz(nRec,2);
	PreenchePosRec(nRec,posRec);

	//Calcula o numero de celulas transponiveis
	int P = 0;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; j++)
		{
			if(map[i][j] == 0){
				P++;
			}
		}
	}

	//cria uma copia do mapa em alocacao dinamica
	int **mapDinamico;
	mapDinamico = criaMatriz(9,9);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mapDinamico[i][j] = map[i][j];
		}
	}
	//faz os valores de E1,E2
	double E1,E2;

	E1 = CalculaE(nRec, pos1,posRec,mapDinamico,P);

	E2 = CalculaE(nRec, pos2,posRec,mapDinamico,P);


	//Parte De Saida
	printf("%lf\n", E1);
	printf("%lf\n", E2);
	//fabs ehh funcao de diferenca absoluta do math.h
	if(fabs(E1 - E2) >= 0.01f){
		if(E1 > E2){
			printf("O jogador 2 possui vantagem\n");
		}else{
			printf("O jogador 1 possui vantagem\n");
		}
	}else{
		printf("O mapa eh balanceado \n");
	}


	//Libera a memoria
	for (int i = 0; i < 9; i++)
	 	free (mapDinamico[i]);
	free(mapDinamico);
	
	for (int i = 0; i < nRec; i++)
	 	free (posRec[i]);
	free(posRec);
	return 0;
}