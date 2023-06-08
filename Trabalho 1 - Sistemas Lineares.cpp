//Sistemas Lineares - Métodos Numéricos Computacionais
/*Trabalho feito por:
	Enzo Campanholo Paschoalini - RA: 221026215
	Manuele S. Christófalo - RA: 221029261
	Paulo Henrique de Camargo Dionysio Martins - RA: 221026169
	Thiago Bigotte Gullo - RA: 221026241
*/
//UNESP Bauru - 11/06/2023

#include <bits/stdc++.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
using namespace std;

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define UP 72
#define DOWN 80

#define BRANCO 127
#define PRETO 112
#define CINZA 120
#define VERDE 114
#define AZUL 113
#define CIANO 115
#define VERMELHO 116

int n;
float M[10][10];

//FORMATAÇÃO =========================================================================================================
void gotoxy(int x, int y){ //Posição do cursor
	COORD pos={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor(bool val){ //Esconde o cursor
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = val;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int SetColor(char color){ //Cor
	HANDLE h;
	h=GetStdHandle (STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute (h,color);
}

void limpaTela(){ //Limpa a tela
	system("cls");
	SetColor(CINZA);
}

void menuSelecao(int pos){ //Menu de Seleção
	limpaTela();
	SetColor(AZUL); cout << "\n Qual a operacao desejada?\n\n\n"; SetColor(BRANCO);
	cout << "  Calcular o determinante" << endl;
	cout << "  Resolver sistema triangular inferior" << endl;
	cout << "  Resolver sistema triangular superior" << endl;
	cout << "  Resolver por Decomposicao LU" << endl;
    cout << "  Resolver por Cholesky" << endl;
	cout << "  Resolver por Gauss Compacto" << endl;
	cout << "  Resolver por Gauss-Jordan" << endl;
	cout << "  Resolver por Jacobi" << endl;
	cout << "  Resolver por Gauss-Seidel" << endl;
	cout << "  Calcular matriz inversa" << endl;
	cout << "  SAIR";

	switch(pos){
		case 1: gotoxy(2, 4); SetColor(CINZA); cout << "  Calcular o determinante" << endl; break;
		case 2: gotoxy(2, 5); SetColor(CINZA); cout << "  Resolver sistema triangular inferior" << endl; break;
		case 3: gotoxy(2, 6); SetColor(CINZA); cout << "  Resolver sistema triangular superior" << endl; break;
		case 4: gotoxy(2, 7); SetColor(CINZA); cout << "  Resolver por Decomposiçao LU" << endl; break;
		case 5: gotoxy(2, 8); SetColor(CINZA); cout << "  Resolver por Cholesky" << endl; break;
		case 6: gotoxy(2, 9); SetColor(CINZA); cout << "  Resolver por Gauss Compacto" << endl; break;
		case 7: gotoxy(2, 10); SetColor(CINZA); cout << "  Resolver por Gauss-Jordan" << endl; break;
		case 8: gotoxy(2, 11); SetColor(CINZA); cout << "  Resolver por Jacobi" << endl; break;
		case 9: gotoxy(2, 12); SetColor(CINZA); cout << "  Resolver por Gauss-Seidel" << endl; break;
		case 10: gotoxy(2, 13); SetColor(CINZA); cout << "  Calcular matriz inversa" << endl; break;
		case 11: gotoxy(2, 14); SetColor(VERMELHO); cout << "  SAIR"; break;
	}
}

bool voltaMenu(){ //Opção tentar ou voltar
	char saida='a'; cursor(false);
	SetColor(CINZA); cout << endl << endl << endl << endl << "Pressione ";
	SetColor(CIANO); cout << "<ENTER>"; SetColor(CINZA); cout << " para tentar com outros valores ou ";
	SetColor(CIANO); cout << "<ESC>"; SetColor(CINZA); cout << " para voltar ao menu de opcoes.";
	while(saida!=ENTER && saida!=ESC) saida=getch();

	if(saida==ESC) return 1;
	return 0;
}

//FUNÇÕES ===========================================================================================================
void insereMatriz(){ //Inserção da matriz para cada opção
	n=11;
	SetColor(BRANCO); cout << endl << endl << endl << "Digite a ordem da sua matriz (max. 10): ";
	while(n>10 || n<1){
		gotoxy(40, 3); cout << "          "; gotoxy(40, 3);
		SetColor(AZUL); cin >> n;
	}

	SetColor(BRANCO); cout << endl << "Insira a sua matriz (" << n << "x" << n << "):" << endl; SetColor(AZUL);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> M[i][j];
		}
	}
}

float Determinante(int ordem, float matriz[10][10]){
	if(ordem==1) return matriz[0][0]; //Matriz de ordem 1
	else{
		float resp=0;
		int jj, ii;

		for(int i=0; i<ordem; i++){
			if(matriz[0][i]!=0){ //Sempre escolhe a linha 0 para calcular
				float matrizAux[10][10];
				ii=jj=0;
				
				for(int linha=1; linha<ordem; linha++){ //Como escolheu a linha 0, compara com linha 1 da inicial
					for(int col=0; col<ordem; col++){
						if(col!=i){ //Exclusão da coluna 
							matrizAux[ii][jj]=matriz[linha][col];
							jj++;
						}
					}

					ii++;	//Linha montada -> soma para a próxima coluna
					jj=0;
				}

				float pivo=(i%2==0)? matriz[0][i] : -matriz[0][i];
				resp=resp+pivo*Determinante(ordem-1, matrizAux);
			}
		}

		return resp;
	}
}

//MAIN ==============================================================================================================
int main(){
    system("color 70");
	HWND console=GetConsoleWindow();
 	RECT r;
  	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 400, TRUE);
	setlocale(LC_ALL, "Portuguese_Brasil");

	bool ON=true;
	int pos;
	char selecao, teste;
	

	//PARTE 1: PROGRAMA
	while(ON==true){
		selecao='a'; pos=1;

		while(selecao!=ENTER){ //1.0 - Controle do menu
			cursor(false);
			menuSelecao(pos);

			if(pos==11) SetColor(VERMELHO);
			else SetColor(AZUL);

			gotoxy(0, 3+pos); cout << ">";

			selecao=getch();
			if(pos!=11) if(selecao==DOWN) pos++;
			if(pos!=1) if(selecao==UP) pos--;
		}
			
		

		//PARTE 2: SELEÇÃO FEITA
		while(pos==1){ //2.1 - Calcular determinante
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Calcular o determinante"; SetColor(BRANCO);

			insereMatriz();
			SetColor(VERDE); cout << endl << endl << endl << "-> ";
			SetColor(BRANCO); cout << "O determinante eh: ";
			SetColor(VERDE); cout << "det(M)=" << Determinante(n, M);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==2){ //2.2 - Sistema Triangular Inferior
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver sistema triangular inferior"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==3){ //2.3 - Sistema Triangular Superior
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver sistema triangular superior"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==4){ //2.4 - Decomposição LU
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver por Decomposicao LU"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==5){ //2.5 - Cholensky
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver por Cholensky"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==6){ //2.6 - Gauss Compacto
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver por Gauss Compacto"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==7){ //2.7 - Gauss-Jordan
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver por Gauss-Jordan"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==8){ //2.8 - Jacobi
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver por Jacobi"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==9){ //2.9 - Gauss-Seidel
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Resolver por Gauss-Seidel"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==10){ //2.10 - Matriz inversa
			limpaTela();
			SetColor(BRANCO); cout << "Opcao selecionada: ";
			SetColor(AZUL); cout << "Calcular matriz inversa"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}
		
		if(pos==11){ //2.11 - SAIR
			SetColor(AZUL); cout << "\n\nAgradecemos por ver o nosso trabalho. Espero que tenha gostado :)\n";
			ON=false;
			system("pause");
		}
	}
}
