//Gean de Mello Dias

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define N 9 // tamanho do vetor de fatores máximo


int EscolheNr(int array[], int tamanhoArray){
	int valorAleatorio = 0;
	int TAMANHOVETOR = tamanhoArray;
	int contador;

	while(valorAleatorio <= 2){
		time_t t;
		srand((unsigned) time(&t)); //inicializa o random
		valorAleatorio = (rand() % 10); //escolhe um número aleatorio    

	if(valorAleatorio >= 2){
		for (contador = 0; contador <= TAMANHOVETOR; contador++){
			if (array[contador] != 0){
				if (valorAleatorio % array[contador] == 0){
                        valorAleatorio = 0;
				}
                }
		}
	}
	}
    //printf("\nPrimeira Chave Pública %d", valorAleatorio);
    return valorAleatorio;
}

int NrNaoExistenoArray(int valor, int divisao[], int tamanhoArray){
	int TAMANHOVETOR = tamanhoArray;
	int retorno = 1;
	int contador;
    
	for(contador = 0; contador <= TAMANHOVETOR; contador++){
		if(valor == divisao[contador]){
            retorno = 0;
		}
	}
return retorno;
}

void Fatoracao(int valor, int divisao[], int tamanhoArray){
	int indicevalor = 0; //posicoes do vetor
	int valordivisor = 2; //este valor vai sendo incrementado 
	int TAMANHOVETOR = tamanhoArray;
	int contador;

	while (valor != 1){
		if((valor % valordivisor) == 0){ //calcula se a divisao vai ser perfeita, sem restos
			valor = valor / valordivisor; //realiza a divisao
			if(NrNaoExistenoArray(valordivisor, divisao, 9)){ //add valordivisor no array caso n existe
				divisao[indicevalor] = valordivisor;
				indicevalor++;
			}
		}else valordivisor++;
	}

	printf("Fatoração\n"); //impressão para conferir
	for(contador = 0; contador <= TAMANHOVETOR; contador++){
		if(divisao[contador] != 0){
            
            printf("%d ", divisao[contador]);
            
		}
 	}
}

int EncontraNumeroDecodificar(int chavePublica1, int produtoMenor){
	int valorEncontrado = 0;
	int nr = 0;

	while(valorEncontrado == 0){
		if((chavePublica1 * nr) % produtoMenor == 1){
			
			printf("\nNr para decodificar  %d \n", nr);
			valorEncontrado = nr;
		}
        nr++;
	}
return valorEncontrado;
}

int verificaSeEprimo(int primo){
	int x;

	for(x = 2; x <= primo - 1; x++){
		if(primo % x == 0)
			return 0;
    }
return 1;
}

int main(){

	FILE *numcripto; //arquivo
	FILE *numdescripto; //arquivo
    
	numcripto = fopen("numcripto.txt", "w"); //criar o arquivo texto
	numdescripto = fopen("numdescripto.txt", "w"); //criar o arquivo texto

	if(numcripto == NULL){ 
		printf("Erro abrindo arquivo numcripto!");
		exit(1);
	}

	if(numdescripto == NULL){
		printf("Erro abrindo arquivo numdescripto!");
		exit(1);
	}

	int nrPrimoDigitado1; 
	int nrPrimoDigitado2;

	printf("Entre com o primeiro número primo: ");
	scanf("%d", &nrPrimoDigitado1); //recebe o primeiro nr primo

	printf("Entre com o segundo número primo: ");
	scanf("%d", &nrPrimoDigitado2); //recebe o segundo nr primo

    //nrPrimoDigitado1 = 13; //número de teste
    //nrPrimoDigitado2 = 17; //número de teste

	if(verificaSeEprimo(nrPrimoDigitado1) && verificaSeEprimo(nrPrimoDigitado2)){ //verifica se o primo

	int produtoMaior = nrPrimoDigitado1 * nrPrimoDigitado2; // produto maior exemplo com nrs 13 e 17 fica 221
	int produtoMenor = (nrPrimoDigitado1 - 1) * (nrPrimoDigitado2 - 1); // produto menor exemplo com n0s 13 e 17 fica 192

        
	int valoresdivisao[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //armazenar os valores de números primos encontrados na fatoração
	Fatoracao(produtoMenor, valoresdivisao, N); //Fatorar 

	int ChavePublica1 = EscolheNr(valoresdivisao, N); //escolhe um número que não pertence ao vetor de fatores primos encontrados na fatoração.
        
	int ChavePublica2 = produtoMaior;

	int nrDecodifica = EncontraNumeroDecodificar(ChavePublica1, produtoMenor); //encontrar a chave privada 

	fprintf(numcripto, "%d", ChavePublica1); //cria chave pública nr1
	fprintf(numcripto, "\n%d", ChavePublica2); //cria chave pública nr2
	fclose(numcripto); //fecha o arquivo

	fprintf(numdescripto, "%d", nrDecodifica); //cria chave privada n01
	fprintf(numdescripto, "\n%d", produtoMaior); //cria chave prívada n02
	fclose(numdescripto);
	}else{
        printf("Números digitados não são primos !!");
    }

return 0;
}
