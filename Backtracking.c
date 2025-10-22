#include <stdio.h>
#include <stdlib.h>

void imprimirCombinacoesChar(char *vet, int pos, int n, char *vetAux) {
  int i;
  if (pos == n) {
    int contA = 0, contI = 0, contE = 0;
    for (i = 0; i < n; i++) {
      switch (vet[i]) {
      case 'a':
        contA++;
        break;
      case 'i':
        contI++;
        break;
      case 'e':
        contE++;
        break;
      }
    }
    for (i = 0; i < n; i++) {
      if (contA > contI && contA > contE) {
        printf("%c", vet[i]);
        if (i == n - 1)
          printf("\n");
      }
    }
  } else {
    for (i = 0; i <= 2; i++) {
      vet[pos] = vetAux[i];
      imprimirCombinacoesChar(vet, pos + 1, n, vetAux);
    }
  }
}

void imprimirCombinacoesInt(int *vet, int pos, int n, int *vetAux) {
  int i;
  if (pos == n) {
    int soma = 0;
    for (i = 0; i < n; i++) {
      soma += vet[i];
    }
    if (soma % 2 == 0) {
      for (i = 0; i < 4; i++) {
        printf("%d ", vet[i]);
      }
      printf("\n");
    }
  } else {
    for (i = 0; i <= 3; i++) {
      vet[pos] = vetAux[i];
      imprimirCombinacoesInt(vet, pos + 1, n, vetAux);
    }
  }
}

int calcularTotal(int *vet) {
  int total = 0;
  for (int i = 0; i <= 4; i++) {
    switch (i) {
    case 0:
      total += 1 * vet[i];
      break;
    case 1:
      total += 5 * vet[i];
      break;
    case 2:
      total += 10 * vet[i];
      break;
    case 3:
      total += 25 * vet[i];
      break;
    case 4:
      total += 50 * vet[i];
      break;
    }
  }
  return total;
}

void imprimirCombinacoesMoedas(int *vet, int pos, int valor, int *moedas) {
  int i;
  int total = calcularTotal(vet);
  if (total == valor) {
    for (i = 0; i <= 4; i++) {
      printf("%d ", vet[i]);
    }
    printf("\n");
  } else {
    if (pos <= 4) {
      for (i = 0; i <= (valor - total) / moedas[pos]; i++) {
        vet[pos] = i;
        imprimirCombinacoesMoedas(vet, pos + 1, valor, moedas);
        vet[pos] = 0;
      }
    }
  }
}

void CombinarVF(int *vet, int pos, int nvariaveis) {
    if(pos == nvariaveis){
    	int i;
        int A, B, C;
        A = vet[0];
        B = vet[1];
        C = vet[2];
        if ((A||B) && C) {
            printf("A = %d, B = %d, C = %d\n", A, B, C);
        	}
        }
	else{
        for(int i=0; i<=1; i++) {
            vet[pos] = i;
            CombinarVF(vet, pos+1, nvariaveis);
        }
    }
}