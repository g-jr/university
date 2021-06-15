package Aplicacao;
import java.util.Scanner;

public class Client {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    Congresso c = new Congresso();
    int op = 0;

    System.out.println("-- Menu -- ");
    System.out.println("1 - Adicionar participante individual.");
    System.out.println("2 - Adicionar Instituicao.");
    System.out.println("3 - Total de participantes.");
    System.out.println("4 - Total de assentos ocupados.");

    while(op != -1) {
      System.out.println("(Entre com -1 p/ sair");
      op = input.nextInt();
      switch(op) {
        case 1:
          c.createIndividuo();
          break;
        case 2:
          int membrosInstituicao = input.nextInt();
          c.createInstituicao(membrosInstituicao);
          break;
        case 3:
          c.totalParticipantes();
          break;
        case 4:
          c.totalAssentos();
          break;
        case -1:
          break;
        default:
          System.out.println("Opcao invalida, tente novamente!!");
          break;
      }
    }
  }
}
