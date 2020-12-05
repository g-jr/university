/* UC: Algoritmos e Estruturas de Dados II - 1sem 2020, ICT-UNIFESP
 * Desenvolvido por Gaspar Andrade Jr.
 *  Problema 2 - AED2 - 2020
 *   -Eleicoes otimizadas
 *   -Tempo Limite de exec. do programa: 0,5s
**/
 
#include <iostream>
#include <iomanip>
 
void merge(int *arr[2], int p, int q, int r) {
  int n1, n2;
  n1 = q - p + 1;
  n2 = r - q;
  int L[n1][2], R[n2][2];
 
  for (int i = 0; i < n1; ++i) {
    L[i][0] = arr[p + i][0];
    L[i][1] = arr[p + i][1];
  }
  for (int i = 0; i < n2; ++i) {
    R[i][0] = arr[q + i + 1][0];
    R[i][1] = arr[q + i + 1][1];
  }
 
  int i, j;
  i = j = 0;
 
  while (n1 > i || n2 > j) {
    // ordena o numero do candidato e votos de acordo com seus votos
    if (n2 == j || (L[i][1] < R[j][1] && n1 > i)) {
      arr[p][0] = L[i][0];
      arr[p][1] = L[i][1];
      i++;
      p++;
    } else {
      arr[p][0] = R[j][0];
      arr[p][1] = R[j][1];
      j++;
      p++;
    }
  }
}
 
void mergeSort(int *arr[2], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
    mergeSort(arr, p, q);
    mergeSort(arr, q + 1,  r);
    merge(arr, p, q, r);
  }
}
 
int **primeiroTurno(int *p[3], int n, int c) {
  int **votos = new int*[c];
  for (int i = 0; i < c; i++)
    votos[i] = new int[2];
 
  int tmp;
  // inicia a matriz de votos
  for (int i = 0; i < c; i++) {
    votos[i][0] = i + 1;
    votos[i][1] = 0;
  }
 
  for (int i = 0; i < n; i++) {
    tmp = p[i][0];
    // if verificar se voto eh valido
    if (tmp > 0 && tmp <= c) 
      votos[tmp - 1][1]++;
  }
  mergeSort(votos, 0, c - 1);
 
  return votos;
}
 
int **segundoTurno(int *p[3], int n, int c, int **v) {
  // verificar se o voto eh valido
  int *tmp;
 
  for (int i = 0; i < n; i++) {
    tmp = p[i];
    // seu voto nao esta contabilizado no primeiro turno
    if (tmp[0] != v[c - 1][0] && tmp[0] != v[c - 2][0]) {
      if (tmp[1] == v[c - 1][0])
        v[c - 1][1]++;
      else if (tmp[1] == v[c - 2][0])
        v[c - 2][1]++;
      else {
        if (tmp[2] == v[c - 1][0])
          v[c - 1][1]++;
        else if (tmp[2] == v[c - 2][0])
          v[c - 2][1]++;
      }
    }
  }
  // ordena o array de contagem de votos de acordo com os votos obtidos
  mergeSort(v, 0, c - 1);
 
  return v;
}
 
void realizarEleicao(int *p[3], int n, int c) {
  int **votos;
  float votosValidos = 0, num, resultado, maiorVoto;
 
  // realiza a contagem de votos do primeiro turno
  votos = primeiroTurno(p, n, c);
 
  // contabiliza os votos validos
  for (int i = 0; i < c; i++)
    votosValidos += votos[i][1];
 
  maiorVoto = votos[c - 1][1];
  resultado = (maiorVoto / votosValidos) * 100;
 
  // verifica, se nao possuir votos validos imprime 0 e finaliza
  int indexMaior;
  if (votosValidos == 0)
    std::cout << "0\n";
   else {
    std::cout << votos[c - 1][0] << ' '
              << std::setprecision(2) << std::fixed
              << resultado << '\n';
    if (resultado < 50) { // realiza segundo turno
      votos = segundoTurno(p, n, c, votos); 
      votosValidos = votos[c - 1][1] + votos[c - 2][1];
      // verifica se a eleicao esta empatada
      // e se qual candidato eh o mais velho, e o declara vencedor
      int indexMaior;
      if ((votos[c - 1][1] == votos[c - 2][1]) && (votos[c - 1][0] > votos[c - 2][0]))
        indexMaior = c - 2;
      else
        indexMaior = c - 1;
 
      resultado = (votos[indexMaior][1] / votosValidos) * 100;
      std::cout << votos[indexMaior][0] << ' '
                << std::setprecision(2) << std::fixed
                << resultado << '\n';
    }
  }
 
  // desaloca memoria
  for (int i = 0; i < c; i++)
    delete [] votos[i];
  delete [] votos;
}
 
int main() {
  int v, c;
  std::cin >> v >> c;
  // aloca memoria matrix de votos
  int **arr = new int*[v];
  for (int i = 0; i < v; i++)
    arr[i] = new int[3];
 
  for(int i = 0; i < v; ++i)
    for(int j = 0; j < 3; ++j)
      std::cin >> arr[i][j];
  // chama a funcao para realizar a eleicao
  realizarEleicao(arr, v, c);
  
  // desaloca matrix de votos
  for (int i = 0; i < v; i++)
    delete [] arr[i];
  delete [] arr;
  return 0;
}
