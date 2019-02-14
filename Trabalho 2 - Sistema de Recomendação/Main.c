#include <stdio.h>
#include <math.h>



//realiza o calculo do cosseno entre duas pessoas(linhas da matriz)
//'u' e 'v' sao as duas linhas da matriz, i eh o numero de filmes
float cosseno(int* u,int* v,int i){

	int prod_escalar = 0;
	float mod_u = 0,mod_v = 0,cos = 0;

	//Este bloco calcula o produto escalar de u e v, modulo de u e v ao quadrado 
	int a = 0;
	for (a = 0; a < i; a++)
	{
		prod_escalar += (u[a] * v[a]);	// produto escalar

		mod_u += u[a] * u[a];			// modulo de u ao quadrado

		mod_v += v[a] * v[a];			// modulo de v ao quadrado
	}

	//Faz a raiz quadrada para ter os proprios modulos
	mod_u = sqrt(mod_u);
	mod_v = sqrt(mod_v);

	//faz o cosseno atraves da formula passada
	cos = prod_escalar / (float)(mod_u * mod_v);
	return cos;	

}

//Calcula a media de notas de uma pessoa
float calcula_media(int  *u,int i){
;
	float media = 0;

	int b,cont = 0;
	for (b = 0; b < i;b++)
	{
		media += u[b];
		if(u[b] == 0){
			cont++;
		}
	}

	media = (float)media / (float)(i - cont);
	return media;
}

//Calcula a estimativa de uma nota nao dada
//notas,n ,i e t sao os valores padrao, l e c sao a localizacao da nota,media ehh o vetor com todas as medias
int calcula_nota(float *media,int n,int i,double t, int l,int c,int (*notas)[i]){

	float nota = media[l];
	float denominador = 0,numerador = 0,cos_aux = 0;

	int a;
	for (a = 0; a < n; a++)
	{
		if(a != l && notas[a][c] != 0){		//verifica se a pessoa 'a' nao ehh a msm que a pessoa ao qual estamos estipulando a nota

			cos_aux = cosseno(notas[a],notas[l],i);


			if(cos_aux >= t ){ // verifica se o cosseno entre as duas pessoas ehh maior que o liminar

				denominador += cos_aux; // monta o denominador

				/*notas[a][c] se refere a nota que a pessoa 'a' deu ao filme ao qual 
				queremos estimar a nota que a pessoa 'l' daria para ele*/
				numerador += cos_aux * (notas[a][c] - media[a]); 
			}
		}
	}

	nota += (numerador / denominador) ;

	if(denominador != 0 && nota != 0) {	//Se o denominador for igual a 0 nao da pra estimar a nota
		
		printf("%.2f ", nota);
	}else{
		printf("DI ");
	}

	return 0;
}

int main(){

	//Declaracao das variaveis de entrada
	int n,i;
	double t;

	scanf("%d %d %lf",&n,&i,&t);

	//declaracao da matriz de entrada
	int notas[n][i];

	//Este bloco faz a leitura da matriz e armazena em notas
	int a,b;
	for (a = 0; a < n; a++)
	{

		for (b = 0; b < i; b++)
		{
			scanf("%d",&notas[a][b]);
		}
	}

	//Calcula a media de todas as pessoas
	float media[n];
	for(a = 0; a < n; a++){
		media[a] = calcula_media(notas[a],i); // chama a funcao

	}

	int cont = 0;	//Controla quando tem que dar \n
	//Bloco principal
	for (a = 0; a < n; a++)
	{

		for (b = 0; b < i; b++)
		{
			if(notas[a][b] == 0){	// quando nao tiver nota
				cont++;
				calcula_nota(media,n,i,t, a,b,notas);

			}
		}

		if(cont != 0)
			printf("\n");

		cont = 0;
	}


	return 0;
}