//Gean de Mello Dias

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>



// cálcula a base, expoente e módulo, utilizando bits
// a forma tradicional de cálculo utilizando números decimais irá ocasionar
// o estouro do limite das variáveis, até do long

int calcula_modulo(int base, int expoente, int modulo){ 
	int result = 1;
	while(expoente > 0){
		if(expoente % 2 == 1)
			result = (result * base) % modulo;
		expoente = expoente >> 1; 
		base = (base * base) % modulo;
    }
return result;
}

int Codifica(int nr, char caracter, int produtoMaior){ //recebe as chaves públicas e o caracter para criptografar
	int codigoAsc = caracter;
	int x;

	unsigned long long int resultado = 1; //tem que ser long pq inteiro estoura o
	for (x = 1; x <= nr; x++){
		resultado = resultado * codigoAsc;
	}

	int retorno = resultado % produtoMaior;
return retorno;
}

int *retornaChavesPublicas(){ //abertura do arquivo numcripto.
	int chavePublica1 = 0;
	int chavePublica2 = 0;
	char line1[32];
	char line2[32];
	FILE *f = fopen("numcripto.txt", "r");

	if (!f){
		printf("Erro abrindo arquivo numcripto.txt");
	}else{
		fscanf(f, "%5[^\n]\n%5[^\n] ", line1, line2);//se refere ao número de caracteres por linha
		chavePublica1 = atoi(line1); //converter string para inteiro
		chavePublica2 = atoi(line2); //converter string para inteiro
		fclose(f); //fecha o arquivo
    }

	static int r[1];
	r[0] = chavePublica1;
	r[1] = chavePublica2;
return r;
}

int *retornaChavesPrivada(){ //abertura do arquivo para descriptografar
	int chavePrivada1 = 0;
	int chavePrivada2 = 0;
	char line1[32];
	char line2[32];
	FILE *f = fopen("numdescripto.txt", "r");

    if(!f){
	printf("Erro abrindo arquivo numdescripto.txt");
    }else{
		fscanf(f, "%5[^\n]\n%5[^\n] ", line1, line2); //se refere ao número de caracteres por linha
		chavePrivada1 = atoi(line1); //converte o valor da linha para inteiro
		chavePrivada2 = atoi(line2); //converte o valor da linha para inteiro
		fclose(f);
    }

	static int r[1];
	r[0] = chavePrivada1;
	r[1] = chavePrivada2;
    return r;
}

int main(int argc, char *argv[]) {
	if (argc == 4) { //quantidade de vetores de entrada
		char *argumento = argv[1]; //capturar o valor dos parâmetros se será c ou d

        //criptografar
		if (*argumento == 'c') {//criptografando arquivo passado como parâmetro para arquivo de saída
			FILE *arquivoparacriptografar = fopen(argv[2], "r"); //ler o arquivo 
			FILE *arquivocriptografado = fopen(argv[3], "w"); //abrir em modo de escrita arquivo

            //verifica se arquivo existe no diretório em que estão as funções mains 
			if(arquivoparacriptografar == NULL){
				printf("Erro abrindo arquivo %s.\n", argv[2]); 
			return -1;
			}

            	if(arquivocriptografado == NULL) {
				printf("Erro abrindo arquivo %s.\n", argv[3]);
			return -1;
			}

		int *p = retornaChavesPublicas(); //abertura, leitura e fechamento do arquivo numcripto.
		int chavePublica1 = *(p + 0); //aponta para primeira posição
		int chavePublica2 = *(p + 1); //aponta para segunda posição

		char caracterParaCriptografar; 
		while((caracterParaCriptografar = getc(arquivoparacriptografar)) != EOF){ //função que lê caracter por caracter até o fim do arquivo
			int caracterCodificado = Codifica(chavePublica1, caracterParaCriptografar, chavePublica2); //recebe as chaves públicas e o caracter para criptografar
			fprintf(arquivocriptografado, "%d\n", caracterCodificado); // \n -> armazena cada caracter criptografado numa linha
		}

			fclose(arquivoparacriptografar); //fecha o arquivo que fez a leitura
			fclose(arquivocriptografado);//fecha o arquivo que foi feito a leitura
        }

		if(*argumento == 'd'){ //descriptografa
			FILE *arquivoCriptografado = fopen(argv[2], "r"); //abri o arquivo descriptografado
			FILE *arquivoDecriptografado = fopen(argv[3], "w"); //abri arquivo para escrita

           //verifica se arquivo existe no diretório em que estão as funções mains 
			if(arquivoCriptografado == NULL){
				printf("Erro abrindo arquivo %s.\n", argv[2]);
                return -1;
            }

			if(arquivoDecriptografado == NULL) {
				printf("Erro abrindo arquivo %s.\n", argv[3]);
			return -1;
            }

		int *p = retornaChavesPrivada(); //abertura do arquivo para descriptografar
		int nrDecodifica = *(p + 0); //aponta para primeira posição
		int produtoMaior = *(p + 1); //aponta para segunda posição

		int i = 0;
		fscanf(arquivoCriptografado, "%d", &i); //lê o primeiro caracter do arquivo para inicializar while
		while(!feof(arquivoCriptografado)){ //le até o fim do arquivo criptografado
			int caracterDecodificado = calcula_modulo(i, nrDecodifica, produtoMaior);
			fprintf(arquivoDecriptografado, "%c", caracterDecodificado); //caracter decodificado
			fscanf(arquivoCriptografado, "%d", &i); //permanecer dentro do while lendo linha por linha
		}

		fclose(arquivoCriptografado);
		fclose(arquivoDecriptografado);
        }

    }else{
        printf("3 parâmetros devem ser passados, c ou d, arquivo de entrada, arquivo de saída.");
    }
    return 0;
}
