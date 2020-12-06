/* TRAB_1: Implementacao de um Shell     
 * Gaspar Andrade Jr R.A. 133633          
 * UC: Sistemas Operacionais Prof. Dr. Bruno Kimura
 * 2020 - UNIFESP-ICT  
 */                                       
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> // strcmp()
#include <fcntl.h> // open()
#include <sys/stat.h>

void escreverPipe(int *fd) {
  close(fd[0]);
  close(STDOUT_FILENO);
  dup2(fd[1], STDOUT_FILENO);
  close(fd[1]);
}

void lerPipe(int *fd) {
  close(fd[1]);
  close(STDIN_FILENO);
  dup2(fd[0], STDIN_FILENO);
  close(fd[0]);
}

void escreverArquivoFinal(char *nomeArquivo) {
  int fdArquivo = open(nomeArquivo, O_CREAT | O_RDWR | O_APPEND, 0);
  close(STDOUT_FILENO);
  dup2(fdArquivo, STDOUT_FILENO);
  close(fdArquivo);
}

void escreveArquivo(char *nomeArquivo) {
  int fdArquivo = open(nomeArquivo, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
  close(STDOUT_FILENO);
  dup2(fdArquivo, STDOUT_FILENO);
  close(fdArquivo);
}

void lerArquivo(char *nomeArquivo) {
  int fdArquivo = open(nomeArquivo, O_RDONLY, 0);
  close(STDIN_FILENO);
  dup2(fdArquivo, STDIN_FILENO);
  close(fdArquivo);

}

void getOpPos(char **argv, int argc, int p[][2]) {
  int i, pos = 0;
  for (i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "|")) {
      p[pos][0] = 0;
      p[pos][1] = i;
    } else if (!strcmp(argv[i], "<")) {
      p[pos][0] = 1;
      p[pos][1] = i;
    } else if (!strcmp(argv[i], ">")) {
      p[pos][0] = 2;
      p[pos][1] = i;
    } else if (!strcmp(argv[i], ">>")) {
      p[pos][0] = 3;
      p[pos][1] = i;
    } else {
      continue;
    }
    pos++;
    argv[i] = NULL;
  }
}

int getOpQuantidade(char **argv, int argc, char *c) {
  int i, ret = 0;
  for (i = 0; i < argc; i++)
    if (!strcmp(argv[i], c))
      ret++;

  return ret;
}

int main(int argc, char **argv) {
  // verifica se o usuario entrou com algum argumento
  if (argc == 1) {
    printf("argumentos insuficientes.\n");
    return 0;
  }

  char *cmd = NULL;; // ponteiro para o primeiro binario executavel
  char **cmdArgs = NULL;
  char *operadores[] = {"|", "<", ">", ">>"};

  int n = 0, i; 
  for (i = 0; i < 4; i++) // calcula a quantidade de operadores
    n += getOpQuantidade(argv, argc, operadores[i]);

  int op[n][2];
  getOpPos(argv, argc, op);

  int fd[n][2];
  for (i = 0; i < n; i++)
    if (pipe(fd[i]) == -1) {
      exit(1);
    }

  pid_t filho; // variavel para salvar o pid do processo filho
  char *nomeEntrada, *nomeSaida, *nomeSaidaFinal;
  int temp = 0, key = 0;
  for (i = 0; i <= n; i++, key++) {
    nomeEntrada = nomeSaida = nomeSaidaFinal = NULL;
    temp = 0;

    if (op[i][0] == 1 && i < n) { // tratar o caso '<'
      nomeEntrada = argv[op[i][1] + 1];
      i++;
    } 

    if (op[i][0] == 2) {  // trata o caso '>'
      nomeSaida = argv[op[i][1] + 1];
      if (i == 0)
        temp = 1;
      cmd = argv[op[i - 1][1] + 1];
      cmdArgs = &argv[op[i - 1][1] + 1];
      i += 2;
    } else if (op[i][0] == 3) { // trata o caso '>>'
      nomeSaidaFinal = argv[op[i][1] + 1];
      if (i == 0)
        temp = 1;
      cmd = argv[op[i - 1][1] + 1];
      cmdArgs = &argv[op[i - 1][1] + 1];
      i += 2;
    }

    if (i == 0 || nomeEntrada != NULL || temp != 0) {
      cmd = argv[1];
      cmdArgs = &argv[1];
    } else if (nomeSaida == NULL && nomeSaidaFinal == NULL) {
      // seta posicao dos ponteiros para o proximo comando
      cmd = argv[op[i - 1][1] + 1];
      cmdArgs = &argv[op[i - 1][1] + 1];
    }
    //printf("i: %d, cmd: %s, nomEntrada: %s, nomeSaida: %s\n", i, cmd, nomeEntrada, nomeSaida);


    filho = fork(); // cria processo filho
    if (filho == 0) { // verifica se eh o processo filho

      if (key > 0) // se nao for o primeiro processo filho
        lerPipe(fd[key - 1]);

      if (nomeEntrada)
        lerArquivo(nomeEntrada);

      if (nomeSaida)
        escreveArquivo(nomeSaida);
      else if (nomeSaidaFinal)
        escreverArquivoFinal(nomeSaidaFinal);

      if (key < n && i < n) // se nao for o ultimo processo filho
          escreverPipe(fd[key]);

      if (execvp(cmd, cmdArgs)) {
        perror("execvp()");
        exit(1);
      }
    } else { // processo pai
      waitpid(filho, NULL, 0);
      if (key > 0) // verifica se o filho atual nao eh o primeiro
        close(fd[key - 1][0]);
      if (key != n && i < n) // verifica se o filho atual nao eh o ultimo
        close(fd[key][1]);
    }
  }
  return 0;
}
