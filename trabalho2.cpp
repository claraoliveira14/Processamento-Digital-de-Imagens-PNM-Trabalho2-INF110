// INF110 - Trabalho pratico 2
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
// Autores: Andre Gustavo dos Santos, Clara Rodrigues de Oliveira (matricula 117041)

#include <iostream>
#include <fstream>
#include <cstring>

const int MAXALTURA  = 1000;				
const int MAXLARGURA = 1000;

unsigned char imagem[MAXALTURA][MAXLARGURA];	//para tons de cinza
unsigned char imR[MAXALTURA][MAXLARGURA];		//para o vermelho
unsigned char imG[MAXALTURA][MAXLARGURA];		//para o verde
unsigned char imB[MAXALTURA][MAXLARGURA];		//para o azul
unsigned char aux[MAXALTURA][MAXLARGURA];		//matriz auxiliar
unsigned char auxR[MAXALTURA][MAXLARGURA];		//matriz auxiliar vermelha
unsigned char auxG[MAXALTURA][MAXLARGURA];		//matriz auxiliar verde
unsigned char auxB[MAXALTURA][MAXLARGURA];		//matriz auxiliar azul

using namespace std;

int main() {
	bool cor = false; 								//para controlar o tipo de imagem
	
	int largura, altura;						//dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;						//arquivo que contem a imagem original
	ofstream arqsaida;							//arquivo que contera a imagem modificada
	char comentario[200], c;				//auxiliares
	int i, j, valor;								//auxiliares

//*** LEITURA DA IMAGEM ***//

	char nome[100]; //variavel para guardar o nome da imagem
	
	//*** Abertura do arquivo ***//
	cout << "Digite o nome do arquivo da imagem (No formato .pnm)" << endl;
	cin >> nome;
	arqentrada.open(nome,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo imagem.pnm" << endl;
		return 0;
	}
//***************************//

//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
		cor = true;
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
													//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura > MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura > MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado, assumimos 255)
//****************************//

//*** ESCOLHA DE QUAL FUNCAO UTILIZAR ***//

	int num; //variavel para guardar a escolha da função
	
	//*** Escolha da funcao ***//
	cout << "Como gostaria de modificar a imagem?" << endl;
	cout << "1 - Escurecer\n";
	cout << "2 - Clarear\n";
	cout << "3 - Espelhar\n";
	cout << "4 - Negativo\n";
	cout << "5 - Tons de cinza\n";
	cout << "6 - Filtro de Sobel\n";
	cout << "7 - Pixelizacao\n";
	
	cin >> num;
	
	while (num<1 || num>7) {
	cout << "Escolha invalida, por favor tente novamente:" << endl;
	cin >> num;
}

//*** Leitura dos pixels da imagem ***//
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			//Se for colorida le 3 valores por pixel (RGB)
			if (cor==true) {
			arqentrada >> valor; imR[i][j] = (unsigned char)valor;
			arqentrada >> valor; imG[i][j] = (unsigned char)valor;
			arqentrada >> valor; imB[i][j] = (unsigned char)valor;
		}
			//Se for em tons de cinza le 1 valor por pixel
			else
			arqentrada >> valor;
			imagem[i][j] = (unsigned char)valor;	//guarda no formato unsigned char
		}
//************************************//

	arqentrada.close();  //Fecha arquivo apos a leitura
	
//*** FIM DA LEITURA DA IMAGEM ***//


//*** TRATAMENTO DA IMAGEM ***//

	int fator; //variavel para guardar mudanças nas imagens
	int valorR, valorG, valorB; //para mudar o valor das cores dos pixels
	
	//*** Escurece a imagem ***//
	if (num==1) {
	cout << "Qual a porcentagem de escurecimento (1-100)? ";
	cin >> fator;
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			if (cor==false) {					//pegando cada pixel e escurencendo em (fator)%
				valor = (int)imagem[i][j];			//pega o valor do pixel
				valor = valor - ( (fator*255) / 100 ) ;			//escurece o pixel em (fator)%
				if (valor < 0)									//se der negativo
					valor = 0;									//fica preto
				imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
			
			else {								//se for colorida, ha uma matriz para o vermelho, uma para o verde e outra para o azul
				valorR = (int)imR[i][j];			//implementado a mesma logica de quando a imagem apresenta tons cinzas mas nas tres matrizes
				valorR = valorR - ( (fator*255) / 100 ) ;			
				if (valorR < 0)									
					valorR = 0;									
				imR[i][j] = (unsigned char)valorR;	
			
				valorG = (int)imG[i][j];			
				valorG = valorG - ( (fator*255) / 100 ) ;			
				if (valorG < 0)									
					valorG = 0;									
				imG[i][j] = (unsigned char)valorG;	
			
				valorB = (int)imB[i][j];			
				valorB = valorB - ( (fator*255) / 100 ) ;			
				if (valorB < 0)									
					valorB = 0;									
				imB[i][j] = (unsigned char)valorB;		
		}
		}
	}
    //*************************//
    
     //*** Clarear a imagem ***//
    else if (num==2) {
    cout << "Qual a porcentagem de clareamento (1-100)? ";
	cin >> fator;
    for (i=0;i<altura;i++) 
		for (j=0;j<largura;j++) {
			if (cor==false) {					//pegando cada pixel e clareando em (fator)%
				valor = (int)imagem[i][j];
				valor = valor  + ( (fator*255) / 100 );			//clarea o pixel em (fator)%
				if (valor>255)										//se der acima de 255
					valor = 255;									//fica branco
				imagem[i][j] = (unsigned char)valor;				//modifica o pixel
		}
			else {								//para imagens coloridas
				valorR = (int)imR[i][j];		//pegando cada pixel da matriz vermelha e clareando em (fator)%	
				valorR = valorR + ( (fator*255) / 100 ) ;			
				if (valorR>255)							
					valorR = 255;									
				imR[i][j] = (unsigned char)valorR;	
			
			
				valorG = (int)imG[i][j];		//pegando cada pixel da matriz verde e clareando em (fator)%
				valorG = valorG + ( (fator*255) / 100 ) ;			
				if (valorG>255)							
					valorG = 255;									
				imG[i][j] = (unsigned char)valorG;	
				
			
				valorB = (int)imB[i][j];		//pegando cada pixel da matriz azul e clareando em (fator)%
				valorB = valorB + ( (fator*255) / 100 ) ;			
				if (valorB>255)								
					valorB = 255; 									
				imB[i][j] = (unsigned char)valorB;	
				
			}
		}
	}
	//*************************//
	
	//*** Espelhar a imagem ***//
	else if (num==3) {
		for (int i=0; i<altura ;i++)
			for (int j=0; j<largura/2 ; j++) {	//largura/2 para não destrocar os pixels
				if (cor==false) {	
					int aux = imagem[i][j];						//variavel temporária para guardar o lado esquerdo da imagem
					imagem[i][j] = imagem[i][largura - 1 - j];	//copia o pixel do lado direito para o esquerdo
					imagem[i][largura - 1 - j] = aux;			//copia o lado esquerdo que estava guardado na variavel para o lado direito
				}
				else {							//mesma logica para cada uma das matrizes RGB
					unsigned char auxR = imR[i][j];			//vermelho			
					imR[i][j] = imR[i][largura - 1 - j];	
					imR[i][largura - 1 - j] = auxR;	
					
					unsigned char auxG = imG[i][j];			//verde	
					imG[i][j] = imG[i][largura - 1 - j];	
					imG[i][largura - 1 - j] = auxG;
					
					unsigned char auxB = imB[i][j];			//azul		
					imB[i][j] = imB[i][largura - 1 - j];	
					imB[i][largura - 1 - j] = auxB;	
					}			
			}
		}
	//*************************//
	
	//*** Negativo da imagem ***//
	else if (num==4) {
		for (int i=0; i<altura ;i++)
			for (int j=0; j<largura ; j++) {
				if (cor==false) {
					valor = (int)imagem[i][j];				//pega o valor de cada pixel
					valor = 255 - valor;					//inverte o valor
					imagem[i][j] = (unsigned char)valor;	//atribui a cada pixel seu novo valor
				}
				else {										//mesma logica para cada matriz RGB
					valorR = (int)imR[i][j];			
					valorR = 255 - valorR;					//vermelho
					imR[i][j] = (unsigned char)valorR;
					
					valorG = (int)imG[i][j];			
					valorG = 255 - valorG;					//verde
					imG[i][j] = (unsigned char)valorG;
				
					valorB = (int)imB[i][j];			
					valorB = 255 - valorB;					//azul
					imB[i][j] = (unsigned char)valorB;
				}
		}
	}
	//*************************//
	 
	//*** Tons de Cinza ***//
	else if (num==5) {
		for (int i=0; i<altura ;i++)
			for (int j=0; j<largura ; j++) {
				if (cor==true) {							//utilizando a forma ponderada para criar o tom de cinza: 30% do vermelho, 59% do verde e 11% do azul
					int cinza =int (imR[i][j]*0.3 + imG[i][j]*0.59 + imB[i][j]*0.11);
					imagem[i][j] = (unsigned char)cinza;
				}
				else {										//caso a imagem já esteja em tons de cinza
					cout << "Essa imagem ja esta em tons de cinza!" << endl;
					return 0;
				}
		}
		if (cor==true)			//trocando o tipo de imagem, para o programa passar a reconhece-la como em tons de cinza
		cor = false;
		strcpy(tipo, "P2");
	}
	//*************************//
	
	//*** Filtro de Sobel ***//
	else if (num==6) {
		if (cor == false) {
		for (int i=1; i<altura-1 ;i++)  //ignorando a primeira e ultima linha e coluna
			for (int j=1; j<largura-1 ; j++) {
				aux[i][j] = imagem[i][j]; //matriz auxiliar para guardar os resultados
				//mapeando uma janela de 3x3 para verificar a mudança de cor dos pixels
				int primeirax = (-1*imagem[i-1][j-1] + 0*imagem[i-1][j] + 1*imagem[i-1][j+1]);   //conta com os pesos da matriz de sobel para o eixo x
				int segundax = (-2*imagem[i][j-1] + 0*imagem[i][j] + 2*imagem[i][j+1]);
				int terceirax = (-1*imagem[i+1][j-1] + 0*imagem[i+1][j] + 1*imagem[i+1][j+1]);
				int somax = primeirax + segundax + terceirax;
				
				int primeiray = (-1*imagem[i-1][j-1] + -2*imagem[i-1][j] + -1*imagem[i-1][j+1]); //conta com os pesos da matriz de sobel para o eixo y
				int segunday = (0*imagem[i][j-1] + 0*imagem[i][j] + 0*imagem[i][j+1]);
				int terceiray = (1*imagem[i+1][j-1] + 2*imagem[i+1][j] + 1*imagem[i+1][j+1]);
				int somay = primeiray + segunday + terceiray;
				
				int resultado = abs(somax) + abs(somay); // Soma os valores absolutos para não dar resultados negativos
				if (resultado > 255)					 //trava para não ultrapassar o 255
					resultado = 255;
				aux[i][j] = (unsigned char)resultado;
			}
		for (int i=0; i<altura ;i++)
			for (int j=0; j<largura ; j++)
				imagem[i][j] = aux[i][j]; 				//passando o valor da matriz auxiliar de volta para a matriz original da imagem
			}
		else {
			for (int i=1; i<altura-1 ;i++)  //ignorando a primeira e ultima linha e coluna
				for (int j=1; j<largura-1 ; j++) {
					auxR[i][j] = imR[i][j]; //matriz auxiliar para guardar os resultados
					//para a matriz vermelha
					int primeiraxR = (-1*imR[i-1][j-1] + 0*imR[i-1][j] + 1*imR[i-1][j+1]);   //conta com os pesos da matriz de sobel para o eixo x
					int segundaxR = (-2*imR[i][j-1] + 0*imR[i][j] + 2*imR[i][j+1]);
					int terceiraxR = (-1*imR[i+1][j-1] + 0*imR[i+1][j] + 1*imR[i+1][j+1]);
					int somaxR = primeiraxR + segundaxR + terceiraxR;
				
					int primeirayR = (-1*imR[i-1][j-1] + -2*imR[i-1][j] + -1*imR[i-1][j+1]); //conta com os pesos da matriz de sobel para o eixo y
					int segundayR = (0*imR[i][j-1] + 0*imR[i][j] + 0*imR[i][j+1]);
					int terceirayR = (1*imR[i+1][j-1] + 2*imR[i+1][j] + 1*imR[i+1][j+1]);
					int somayR = primeirayR + segundayR + terceirayR;
					
					int resultadoR = abs(somaxR) + abs(somayR); // Soma os valores absolutos para não dar resultados negativos
					if (resultadoR > 255)					 //trava para não ultrapassar o 255
						resultadoR = 255;
					//para a matriz verde
					auxG[i][j] = imG[i][j];
					int primeiraxG = (-1*imG[i-1][j-1] + 0*imG[i-1][j] + 1*imG[i-1][j+1]);   //conta com os pesos da matriz de sobel para o eixo x
					int segundaxG = (-2*imG[i][j-1] + 0*imG[i][j] + 2*imG[i][j+1]);
					int terceiraxG = (-1*imG[i+1][j-1] + 0*imG[i+1][j] + 1*imG[i+1][j+1]);
					int somaxG = primeiraxG + segundaxG + terceiraxG;
				
					int primeirayG = (-1*imG[i-1][j-1] + -2*imG[i-1][j] + -1*imG[i-1][j+1]); //conta com os pesos da matriz de sobel para o eixo y
					int segundayG = (0*imG[i][j-1] + 0*imG[i][j] + 0*imG[i][j+1]);
					int terceirayG = (1*imG[i+1][j-1] + 2*imG[i+1][j] + 1*imG[i+1][j+1]);
					int somayG = primeirayG + segundayG + terceirayG;
					
					int resultadoG = abs(somaxG) + abs(somayG); // Soma os valores absolutos para não dar resultados negativos
					if (resultadoG > 255)					 //trava para não ultrapassar o 255
						resultadoG = 255;
					//para a matriz azul
					auxB[i][j] = imB[i][j];
					int primeiraxB = (-1*imB[i-1][j-1] + 0*imB[i-1][j] + 1*imB[i-1][j+1]);   //conta com os pesos da matriz de sobel para o eixo x
					int segundaxB = (-2*imB[i][j-1] + 0*imB[i][j] + 2*imB[i][j+1]);
					int terceiraxB = (-1*imB[i+1][j-1] + 0*imB[i+1][j] + 1*imB[i+1][j+1]);
					int somaxB = primeiraxB + segundaxB + terceiraxB;
				
					int primeirayB = (-1*imB[i-1][j-1] + -2*imB[i-1][j] + -1*imB[i-1][j+1]); //conta com os pesos da matriz de sobel para o eixo y
					int segundayB = (0*imB[i][j-1] + 0*imB[i][j] + 0*imB[i][j+1]);
					int terceirayB = (1*imB[i+1][j-1] + 2*imB[i+1][j] + 1*imB[i+1][j+1]);
					int somayB = primeirayB + segundayB + terceirayB;
					
					int resultadoB = abs(somaxB) + abs(somayB); // Soma os valores absolutos para não dar resultados negativos
					if (resultadoB > 255)					 //trava para não ultrapassar o 255
						resultadoB = 255;
						
					
					auxR[i][j] = (unsigned char)resultadoR;
					auxG[i][j] = (unsigned char)resultadoG;
					auxB[i][j] = (unsigned char)resultadoB;
			}
			for (int i=0; i<altura ;i++)
				for (int j=0; j<largura ; j++) {
					imR[i][j] = auxR[i][j]; 				//passando o valor da matriz auxiliar de volta para a matriz original da imagem
					imG[i][j] = auxG[i][j]; 
					imB[i][j] = auxB[i][j]; 
				}
			}
		}
		
//*************************//

//*** Pixelização/Mosaico ***//
	else if (num==7) {
		int tam;
		cout << "Qual sera o tamanho dos pixels? (1-50)" << endl;
		cin >> tam;
		while (tam<1 || tam>50) {
			cout << "tamanho invalido, por favor digite um numero entre 0 e 50" << endl;
			cin >> tam;
		}
		int x,y;
		if (cor==true) {
			for (int i=0; i<altura; i+=tam)   		//pegando blocos de (tam)x(tam) pixels 
				for (int j=0; j<largura; j+=tam) {
					int somaR=0, somaG=0, somaB=0, cont=0;		//variaveis para guardar a soma dos pixels que são zeradas a cada janela de (tam)x(tam)
					for (int x=i; x<i+tam && x<altura; x++)		//em cada bloco de (tam)x(tam) é feito a soma dos valores dos pixels
						for (int y=j; y<j+tam && y<largura; y++) { 	//existe uma trava para se o programa "vazar" da imagem nas bordas
							somaR += imR[x][y];
							somaG += imG[x][y];
							somaB += imB[x][y];
							cont++; 		
						}
						int mediaR = somaR / cont;		//media das somas dos valores dos pixels
						int mediaG = somaG / cont;
						int mediaB = somaB / cont;
					
					for (int x=i; x<i+tam && x<altura; x++) 		//atribuição das medias a janela (tam)x(tam), dando um efeito de mosaico ou pixels "maiores"
						for (int y=j; y<j+tam && y<largura; y++) {
							imR[x][y] = mediaR;
							imG[x][y] = mediaG;
							imB[x][y] = mediaB;
						}
					}
				}
		else {										//mesma estrutura mas para imagens não coloridas
			for (int i=0; i<altura; i+=tam)   		
				for (int j=0; j<largura; j+=tam) {
					int soma=0, cont=0;		
					for (int x=i; x<i+tam && x<altura; x++)		
						for (int y=j; y<j+tam && y<largura; y++) { 	
							soma += imagem[x][y];
							cont++; 		
						}
						int media = soma / cont;		
					
					for (int x=i; x<i+tam && x<altura; x++) 		
						for (int y=j; y<j+tam && y<largura; y++)
							imagem[x][y] = media;
				}
			}
		}
//*************************//

//*** FIM DO TRATAMENTO DA IMAGEM ***//

//*** GRAVACAO DA IMAGEM ***//

//*** Grava a nova imagem ***//
	char novo[100];
	cout << "Qual nome do arquivo da nova imagem? (Escreva no formato .pnm)" << endl; 	//nomear o arquivo novo
	cin >> novo;
	arqsaida.open(novo,ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;							//tipo
	arqsaida << "# TP2-INF110, by AGS\n";	//comentario
	arqsaida << largura << " " << altura;	//dimensoes
	arqsaida << " " << 255 << endl;				//maior valor
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
			if (cor==true) {
			arqsaida << (int)imR[i][j] << endl;		//pixels coloridos
			arqsaida << (int)imG[i][j] << endl;
			arqsaida << (int)imB[i][j] << endl;
		}
			else
			arqsaida << (int)imagem[i][j] << endl;	//pixels em tons de cinza

	arqsaida.close();		//fecha o arquivo
	//***************************//

//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}

	
