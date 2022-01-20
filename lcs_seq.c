/*
 * Trabalho de Computação Concorrente: Implementação do algoritmo que encontra 
 * 				       a maior subsequencia comum entre duas 
 * 				       sequências (LCS) de forma sequencial.
 * 				       O algoritmo usa o método de solução 
 * 				       matricial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b){
	return a > b? a : b;
}

void show_lcs(int tam, int mat_show[][tam], char *Y, int i, int j){
	if(i == 0 || j == 0)
		return;
	if(mat_show[i][j] == 1){ // Diagonal
		show_lcs(tam, mat_show, Y, i - 1, j - 1);
		printf("%c", Y[i - 1]);
	}else if(mat_show[i][j] == 2) // Vertical
		show_lcs(tam, mat_show, Y, i - 1, j);
	else
		show_lcs(tam, mat_show, Y, i, j - 1); // Horizontal
}

int lcs(char *X, char *Y){
	int m = strlen(X);  // Coleta o tamanho da sequência X
	int n = strlen(Y); //  Coleta o tamanho da sequência Y
	int i, j;
	int mat[n + 1][m + 1]; // Matriz usada para LCS
	int mat_show[n + 1][m + 1]; // Matriz usada para mostar LCS
	
	// Preenche a matriz
	for(i = 0; i <= n; i++){
		for(j = 0; j <= m; j++){
			if(i == 0 || j == 0){
				mat_show[i][j] = mat[i][j] = 0;
			}
			
			/*else if(X[j - 1] == Y[i - 1])
				mat[i][j] = mat[i - 1][j - 1] +  1;
			else
				mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
			*/
			
			else if(X[j - 1] == Y[i - 1]){
				mat[i][j] = mat[i - 1][j - 1] +  1;
				mat_show[i][j] = 1; // 1 --> Diagonal
			}
			else if(mat[i - 1][j] >= mat[i][j - 1]){
				mat[i][j] = mat[i - 1][j];
				mat_show[i][j] = 2; // 2 --> Vertical
			}else{
				mat[i][j] = mat[i][j - 1];
				mat_show[i][j] = 3; // 3 --> Horizontal
			}
			printf("%d%c", mat_show[i][j], j != m ?'\t':'\n');
		}
	}
	printf("\n");
	show_lcs((m + 1), mat_show, Y, (i - 1), (j - 1));

	return mat[n][m];

}

// Fluxo principal
int main(int argc, char* argv[]){
	char X[] = "CAGAXTCACGACGTA", Y[] = "TCGTGTTGCGTYACT";

	printf("X: %s\nY: %s\n", X, Y);
	printf("\n%d\n", lcs(X, Y));
}

