/*
Autor: Luan Icaro Pinto Arcanjo
Numero Usp: 10799230
Trab 4 de ICC
Universidade De Sao Paulo
*/

#include <stdio.h>
#include <stdlib.h>
//A Struct de numero real na forma num / den
typedef struct{
	int num;
	int den;
}Real;

//cria Uma Matriz alocada na heap do tipo Real
Real **criaMat(int lin, int col){
	Real **mat;

	mat = (Real **)malloc(sizeof(Real *) * lin);

	for (int i = 0; i < lin; ++i){
	  *(mat+i) = (Real *)malloc (sizeof(Real) * col);  

	}

	return mat;
}


void LePlano(Real **mat,int* numLinOcupadas, int col){
	//Le 2 * col numeros.
	//é inserido na linha do numLinOcupadas
	for(int i = 0; i < col; i++){
		scanf("%d %d", &mat[*numLinOcupadas][i].num, &mat[*numLinOcupadas][i].den);
	}
	//adiciona um na linha ocupada
	*numLinOcupadas = *numLinOcupadas + 1;
}

//1 Eq Reta == 2 Eq Plano
void LeReta(Real **mat,int* numLinOcupadas, int col){
	LePlano(mat , numLinOcupadas, col);
	LePlano(mat , numLinOcupadas, col);	
}

//troca duas linhas da matrix
void TrocaLinhas(Real **mat, int l1, int l2,int col){
	Real aux;
	//Faz a troca um por um atraves do for usando a variavel aux
	for(int i = 0; i < col; i++){

		aux = mat[l1][i];
		mat[l1][i] = mat[l2][i];
		mat[l2][i] = aux;
	}
}

int EscalonamentoRecursivo(Real **mat,int pivoCoe,int lin, int col){
	
	//Este bloco troca linhas quando o pivo for 0
	int existePivo = 1;	//variavel que informa se existe pivo possivel ou nao
	
	if( mat[pivoCoe][pivoCoe].num == 0){	//verifica se o pivo da linha por padrao ehh 0

		existePivo = 0;
		//verifica todas as eqs procurando por um pivo != 0
		for(int i = pivoCoe + 1; i < lin; i++){
			//Se o candidato a pivo desta linha for diferente de 0
			if((mat[i][pivoCoe].num / mat[i][pivoCoe].den) != 0){
				existePivo = 1;
				TrocaLinhas(mat,pivoCoe,i,col);
				break;
			}
		}
	}


	if(existePivo == 1){
		//Faz o escalonamento para eliminar o coe de pivoCoe
		for(int i = (pivoCoe + 1);i < lin; i++){
			//calcula o Xi1/P da formula
			//Se lembre que a/b / c/d == a * d / c * b
			Real xi1P;
			xi1P.num = mat[i][pivoCoe].num * mat[pivoCoe][pivoCoe].den;
			xi1P.den = mat[i][pivoCoe].den * mat[pivoCoe][pivoCoe].num;
			//Calcula a linha do pivo * xi1/p
			Real linhaXfator[col - pivoCoe];
			for(int j = pivoCoe; j < col; j++){
				linhaXfator[j].num = mat[pivoCoe][j].num * xi1P.num;
				linhaXfator[j].den = mat[pivoCoe][j].den * xi1P.den;
				
			}


			//Faz a alteracao na linha i em si
			
			for(int j = pivoCoe; j < col; j++){
				if(mat[i][j].den % linhaXfator[j].den == 0){
					mat[i][j].num = mat[i][j].num - (linhaXfator[j].num * mat[i][j].den  / linhaXfator[j].den);
				}else if(linhaXfator[j].den % mat[i][j].den == 0){
					mat[i][j].num = (linhaXfator[j].den * mat[i][j].num  / mat[i][j].den) - linhaXfator[j].num;
					mat[i][j].den = linhaXfator[j].den;
				}else{
					//lembre-se que a/b - c/d == (a * d - b* d) / b * d 
					mat[i][j].num = (mat[i][j].num * linhaXfator[j].den) -  (mat[i][j].den * linhaXfator[j].num);
					mat[i][j].den = mat[i][j].den * linhaXfator[j].den;
				}


				
			}
			
		}
	}
	//Este bloco realiza a funcao de verificar se ha absurdo
	for(int i = 0; i < lin; i++){

		int verif = 0;	//bool
		//verifica se todos os coeficientes menos o ultimo eeh 0
		for(int j = 0;j < (col - 1); j++){

			if(mat[i][j].num != 0){
				verif = 1;
				break;
			}
		}
		//verifica o absurdo
		//a primeira condicao nao sera 0 se um dos coeficientes menos o ultimo for diferente de zero
		//A segunda é se o ultimo coeficiente é 0
		if(verif == 0 && mat[i][col - 1].num != 0){	
			return 1;
		}
		

	}
	//A primeira condicao ehh para a da primeira coluna ser o coeficiente c e a segunda ehh para se a matriz virou uma matriz linha
	if(pivoCoe == 2 || pivoCoe + 2 == lin){		
		return 0;
	}else{
			
		return EscalonamentoRecursivo(mat,pivoCoe + 1,lin,col);
	}
}


int main(){
	//Entrada e Leitura de dados

	int numEqs, numCoeficientes;
	scanf("%d %d", &numEqs, &numCoeficientes);

	Real **mat;
	mat = criaMat(numEqs,numCoeficientes);


	int numLinOcupadas = 0;	//serve para controlar em qual linha guardar a proxima equacao que sera lida
	char obj1;
	scanf(" %c ",&obj1);

	if(obj1 == 'r'){
		LeReta(mat, &numLinOcupadas, numCoeficientes);
	}
	else{
		LePlano(mat, &numLinOcupadas, numCoeficientes);
	}

	char obj2;
	scanf(" %c ",&obj2);
	//se ler r le uma reta, se nao le um plano
	if(obj2 == 'r'){
		LeReta(mat, &numLinOcupadas, numCoeficientes);
	}
	else{
		LePlano(mat, &numLinOcupadas, numCoeficientes);
	}

	//Fim Entrada e Leitura de dados

	//chama a funcao recursiva
	int temColisao = EscalonamentoRecursivo(mat,0,numEqs, numCoeficientes);
	if(temColisao == 1){
		printf("nao\n");
	}else{
		printf("sim\n");
	}

	
	//Faz a impressao da matriz
	for (int i = 0; i < numEqs; ++i)
	{
		for (int j = 0; j < numCoeficientes; j++)
		{
			//Se o o modulo da divisao do numerador pelo denominador for igual a 0(numero inteiro)
			if(mat[i][j].num % mat[i][j].den == 0){
				mat[i][j].num = mat[i][j].num / mat[i][j].den;	//numerador vira o numerador dividido pelo denominador
				mat[i][j].den = 1;	//denominador vira 1
			}

			printf("%d",mat[i][j].num);
			if(mat[i][j].num != 0 && mat[i][j].den != 1){	//se o numero nao for 0 e o denominador for diferente de 1
				printf("/%d",mat[i][j].den);
			}
			printf("\t");
		}
		printf("\n");
	}


	//liberacao de memoria
	for (int i = 0; i < numEqs; ++i)
	 	free (mat[i]); 
	free(mat);

	return 0;


}