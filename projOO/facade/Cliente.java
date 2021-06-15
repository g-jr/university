package Matricula;

import java.util.Scanner;

public class Cliente {
  public static void main(String[] args) {
    //Cria um objeto do tipo facade
    Facade f1 = new Facade();
    Scanner input = new Scanner(System.in);

    //Menu com opcoes
    System.out.println("Entre com alguma operacao (-1 p/ sair)");
    System.out.println("1 - Add aluno");
    System.out.println("2 - Add curso");
    System.out.println("3 - Consultar Aluno ");
    System.out.println("4 - Consultar curso");
    int in = 0;
    while(in != -1) {
      in = input.nextInt();
      switch (in) {
        case 1:
          int idAluno = input.nextInt();
          String nameAluno = input.nextLine();
          f1.setAluno(idAluno, nameAluno);
          break;
        case 2:
          int idCurso = input.nextInt();
          String nameCurso = input.nextLine();
          f1.setCurso(idCurso, nameCurso);
          break;
        case 3:
          int idAlunoConsulta = input.nextInt();
          f1.getAluno(idAlunoConsulta);
          break;
        case 4:
          int idCursoConsulta = input.nextInt();
          f1.getCurso(idCursoConsulta);
          break;
        case -1:
          return;
        default:
          break;
      }
      System.out.println("Entre com uma nova operacao!! (-1 p/ sair)");
    }
  }
}
