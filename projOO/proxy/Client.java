package Aplicacao;

import java.util.Scanner;

public class Client {
  public static void main(String[] args) {
    // Cria a facade para realizar a interassao do usuario com sua conta
    BancoFacade bf = new BancoFacade();
    Scanner input = new Scanner(System.in);
    int op = 0;
    while(op != -1) {
      System.out.println("Menu (-1 p/ sair)");
      System.out.println("1 - Criar conta");
      System.out.println("2 - Acessar conta existe");
      op = input.nextInt();
      switch(op) {
        case 1:
          System.out.println("ID:");
          int idCriar = input.nextInt();
          System.out.println("Senha (somente numeros):");
          input.nextLine();
          int senhaCriar = input.nextInt();
          bf.createUsuario(idCriar, senhaCriar);
          break;
        case 2:
          System.out.println("ID:");
          int idLogar = input.nextInt();
          bf.logarUsuario(idLogar);
          break;
        default:
          break;
      }
      if(op == -1)
        break;
    }
  }
}
