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

#define MAX 10;

int n;
double M[10][10], B[10], X[10];

//FORMATAÇÃO =========================================================================================================
void gotoxy(int x, int y){ //Posição do cursor
	COORD pos={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor(bool val){ //Esconde o cursor
   HANDLE consoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize=10;
   info.bVisible=val;
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
	cout << "  Calcular matriz inversa por Decomposicao LU" << endl;
	cout << "  Calcular matriz inversa por Gauss Compacto" << endl;
	cout << "  SAIR";

	switch(pos){
		case 1: gotoxy(2, 4); SetColor(CINZA); cout << "  Calcular o determinante" << endl; break;
		case 2: gotoxy(2, 5); SetColor(CINZA); cout << "  Resolver sistema triangular inferior" << endl; break;
		case 3: gotoxy(2, 6); SetColor(CINZA); cout << "  Resolver sistema triangular superior" << endl; break;
		case 4: gotoxy(2, 7); SetColor(CINZA); cout << "  Resolver por Decomposicao LU" << endl; break;
		case 5: gotoxy(2, 8); SetColor(CINZA); cout << "  Resolver por Cholesky" << endl; break;
		case 6: gotoxy(2, 9); SetColor(CINZA); cout << "  Resolver por Gauss Compacto" << endl; break;
		case 7: gotoxy(2, 10); SetColor(CINZA); cout << "  Resolver por Gauss-Jordan" << endl; break;
		case 8: gotoxy(2, 11); SetColor(CINZA); cout << "  Resolver por Jacobi" << endl; break;
		case 9: gotoxy(2, 12); SetColor(CINZA); cout << "  Resolver por Gauss-Seidel" << endl; break;
		case 10: gotoxy(2, 13); SetColor(CINZA); cout << "  Calcular matriz inversa por Decomposicao LU" << endl; break;
		case 11: gotoxy(2, 14); SetColor(CINZA); cout << "  Calcular matriz inversa por Gauss Compacto" << endl; break;
		case 12: gotoxy(2, 15); SetColor(VERMELHO); cout << "  SAIR"; break;
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


//FUNÇÕES BASE =======================================================================================================
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

double Determinante(int n, double matriz[][10]){ //Calcula determinante
	if(n==1) return matriz[0][0]; //Matriz de n 1
	else{
		float resp=0;
		int jj, ii;

		for(int i=0; i<n; i++){
			if(matriz[0][i]!=0){ //Sempre escolhe a linha 0 para calcular
				double matrizAux[10][10];
				ii=jj=0;
				
				for(int linha=1; linha<n; linha++){ //Como escolheu a linha 0, compara com linha 1 da inicial
					for(int col=0; col<n; col++){
						if(col!=i){ //Exclusão da coluna 
							matrizAux[ii][jj]=matriz[linha][col];
							jj++;
						}
					}

					ii++;	//Linha montada -> soma para a próxima coluna
					jj=0;
				}

				double pivo=(i%2==0)? matriz[0][i] : -matriz[0][i];
				resp=resp+pivo*Determinante(n-1, matrizAux);
			}
		}

		return resp;
	}
}

bool simetrica(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++) if(M[i][j]!=M[j][i]) return false;
	}

	return true;
}


//TRIANGULO INFERIOR E SUPERIOR =================================================================================================
void TriInferior(int n, double M[][10], double B[], double X[]){
	for(int i=0 ; i<n ; i++){
			if(i==0) X[0]=B[0]/M[0][0];
			else{
				double soma=0;
				for(int j=0; j<i; j++) soma+=M[i][j]*X[j];
				X[i]=(B[i]-soma)/M[i][i];
			}
	}
}

void TriSuperior(int n, double M[][10], double B[], double X[]){
	for(int i=n-1; i>=0; i--){
		if(i==n-1) X[i]=B[i]/M[i][i];
		else{
			double soma=0;
			for(int j=0; j<n; j++) soma+=M[i][j]*X[j];
			X[i]=(B[i]-soma)/M[i][i];
		}
	}
}

//CHOLENSKY =========================================================================================================
double somatorioPrincipal(int i, double L[][10]){
    double soma=0;
    for(int k=0; k<i; k++) soma+=pow(L[i][k], 2);

    return soma;
}

void DiagPrincipal(int i, double matriz[][10], double L[][10]){
    if(i==0) L[0][0]=sqrt(matriz[0][0]);
	
	else L[i][i]=sqrt(matriz[i][i] - somatorioPrincipal(i, L));
}

double somatorioPadrao(int i, int j, double L[][10]){
    double soma=0;
    for(int k=0; k<j; k++) soma+=L[i][k]*L[j][k];
    
    return soma;
}

void OutrosElem(int i, int j, double matriz[][10], double L[][10]){
    if(i==0){
        L[i][j]=matriz[i][j] / L[i][i];
        L[j][i]=L[i][j];
    }
	
	else L[i][j]=(matriz[i][j] - somatorioPadrao(i, j, L)) / L[j][j];
}

void EquacaoLY(int n, double L[][10], double Y[], double B[]){
	SetColor(CINZA); cout << endl << "Vetor Y:" << endl; SetColor(BRANCO);

    for(int i=0; i<n; i++){
        double soma=B[i];

        for(int j=0; j<i; j++) soma-=L[i][j]*Y[j];

        Y[i]=soma/L[i][i];
		cout << fixed << setprecision(3) << Y[i] << "  ";
    }
}

void EquacaoXY(double n, double Lt[][10], double X[], double Y[]){
    for(int i=n-1; i>=0; i--){
        double soma=Y[i];
        for(int j=n-1; j>i; j--) soma-=Lt[i][j]*X[j];

        X[i]=soma/Lt[i][i];
    }
}

void Cholesky(int n, double matriz[][10], double B[], double X[]){
    double L[10][10];

    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++) OutrosElem(i, j, matriz, L);
        DiagPrincipal(i, matriz, L);
    }


    double Y[10];
    EquacaoLY(n, L, Y, B);

	SetColor(CINZA); cout << endl << endl << endl << "Matriz L:" << endl; SetColor(BRANCO);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout << fixed << setprecision(3) << L[i][j] << "  ";

        cout << endl;
    }


    double Lt[10][10];
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            Lt[i][j]=L[j][i];
        }
    }

	SetColor(CINZA); cout << endl << endl << "L Transposta:" << endl; SetColor(BRANCO);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout << fixed << setprecision(3) << Lt[i][j] << "  ";

        cout << endl;
    }

    EquacaoXY(n, Lt, X, Y);
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
	char selecao;
	

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

			insereMatriz(); //Leitura da matriz

			SetColor(VERDE); cout << endl << endl << endl << "-> ";
			SetColor(BRANCO); cout << "O determinante eh: ";

			SetColor(VERDE); cout << "det(M)=" << Determinante(n, M); //Calculo do determinante

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==2){ //2.2 - Sistema Triangular Inferior
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver sistema triangular inferior"; SetColor(BRANCO);

			n=11;
			SetColor(BRANCO); cout << endl << endl << endl << "Digite a ordem da sua matriz (max. 10): ";
			while(n>10 || n<1){
				gotoxy(40, 3); cout << "          "; gotoxy(40, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Insira a sua matriz triangular inferior:" << endl; SetColor(AZUL);
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					cin >> M[i][j];
				}
			}

			SetColor(BRANCO); cout << endl << "Insira o vetor B: " << endl; SetColor(AZUL);
			for(int i=0; i<n; i++) cin >> B[i];

			TriInferior(n, M, B, X);

			SetColor(VERDE); cout << endl << endl << "Vetor X (solucao):" << endl; SetColor(VERDE);
			cout << "X=(";
			for(int i=0; i<n; i++){
				if(X[i]>=0.001 || X[i]<=-0.001) cout << fixed << setprecision(3) << X[i];
				else cout << 0;

				if(i!=n-1) cout << "  ";
			}
			cout << ")";


			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==3){ //2.3 - Sistema Triangular Superior
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver sistema triangular superior"; SetColor(BRANCO);

			n=11;
			SetColor(BRANCO); cout << endl << endl << endl << "Digite a ordem da sua matriz (max. 10): ";
			while(n>10 || n<1){
				gotoxy(40, 3); cout << "          "; gotoxy(40, 3);
				SetColor(AZUL); cin >> n;
			}

			SetColor(BRANCO); cout << endl << "Insira a sua matriz triangular superior:" << endl; SetColor(AZUL);
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					cin >> M[i][j];
				}
			}

			SetColor(BRANCO); cout << endl << "Insira o vetor B: " << endl; SetColor(AZUL);
			for(int i=0; i<n; i++) cin >> B[i];

			TriSuperior(n, M, B, X);

			SetColor(VERDE); cout << endl << endl << "Vetor X (solucao):" << endl; SetColor(VERDE);
			cout << "X=(";
			for(int i=0; i<n; i++){
				if(X[i]>=0.001 || X[i]<=-0.001) cout << fixed << setprecision(3) << X[i];
				else cout << 0;

				if(i!=n-1) cout << "  ";
			}
			cout << ")";

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==4){ //2.4 - Decomposição LU
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver por Decomposicao LU"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==5){ //2.5 - Cholesky
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver por Cholesky"; SetColor(BRANCO);

			insereMatriz(); //Inserção da matriz

			int flag=1; //Teste de convergência
			if(simetrica()==false) flag=-1;
			for(int n=1; n<=n; n++) if(Determinante(n, M)<=0) flag=0;

			if(flag<1){
				SetColor(VERMELHO); cout << endl << endl << "A matriz inserida nao converge -> ";
				SetColor(BRANCO);
				if(flag==-1) cout << "ela nao eh simetrica.";
				else cout << "ela nao eh positiva.";
			}

			else{ //Converge :)
				SetColor(BRANCO); cout << endl << "Insira o vetor B: " << endl; SetColor(AZUL);
				for(int i=0; i<n; i++) cin >> B[i];

				SetColor(CINZA); cout << endl; for(int loop=0; loop<80; loop++) cout << "=";
				Cholesky(n, M, B, X);
				SetColor(VERDE); cout << endl << endl << "Vetor X (solucao):" << endl; SetColor(VERDE);
				cout << "X=(";
				for(int i=0; i<n; i++){
					if(X[i]>=0.001 || X[i]<=-0.001) cout << fixed << setprecision(3) << X[i];
					else cout << 0;

					if(i!=n-1) cout << "  ";
				}
				cout << ")";
			}


			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==6){ //2.6 - Gauss Compacto
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver por Gauss Compacto"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==7){ //2.7 - Gauss-Jordan
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver por Gauss-Jordan"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==8){ //2.8 - Jacobi
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver por Jacobi"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==9){ //2.9 - Gauss-Seidel
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Resolver por Gauss-Seidel"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}

		while(pos==10){ //2.10 - Matriz inversa por LU
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Calcular matriz inversa por Decomposicao LU"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}
		
		while(pos==11){ //2.11 - Matriz inversa Gauss Compacto
			limpaTela(); cursor(true);
			SetColor(CINZA); cout << "-> ";
			SetColor(CINZA); cout << "Opcao selecionada: ";
			SetColor(VERDE); cout << "Calcular matriz inversa por Gauss Compacto"; SetColor(BRANCO);

			if(voltaMenu()==1){
				selecao='a';
				break;
			}
		}
		
		if(pos==12){ //2.12 - SAIR
			SetColor(AZUL); cout << "\n\nAgradecemos por ver o nosso trabalho. Espero que tenha gostado :)\n";
			ON=false;
			system("pause");
		}
	}
}
