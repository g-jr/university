package Aplicacao;

import java.util.ArrayList;
import java.util.Scanner;

public class BancoFacade {
  private static ArrayList<UsuarioProxy> usuarios;

  // Inicia o arraylist que contem os usuarios
  public BancoFacade() {
    usuarios = new ArrayList<>();
  }

  // Cria um novo cliente com senha atraves da classe UsuarioProxy
  public void createUsuario(int id, int senha) {
    UsuarioProxy u = new UsuarioProxy();
    u.create(id, senha);
    usuarios.add(u);
  }

  // Interecao do usuario com sua conta
  public void logarUsuario(int id) {
    Scanner input = new Scanner(System.in);
    UsuarioProxy u = null;

    // Procura o usuario na lista atraves do id
    for (UsuarioProxy usuario : usuarios)
      if (usuario.getId() == id)
        u = usuario;

    // Se o usuario nao existir retorna ao main
    if(u == null)
      System.out.println("Usuario nao encontrado.");

    // Valida o usuario requerendo sua senha para realizar operacoes
    else if (u.validarUsuario()) {
      int op = 0;
      while (op != -1) {
        // Cada operacao requer a autenticacao do usuario novamente
        System.out.println("MENU (-1) para sair da sua conta");
        System.out.println("1 - Verificar Saldo");
        System.out.println("2 - Depositar");
        System.out.println("3 - Transferir");
        op = input.nextInt();
        switch (op) {
          case 1:
            u.saldo();
            break;
          case 2:
            double valorDeposito = input.nextDouble();
            u.depositar(valorDeposito);
            break;
          case 3:
            int idDestinatario = input.nextInt();
            double valorTransferencia = input.nextDouble();
            u.transferir(valorTransferencia);
            for(UsuarioProxy usuario : usuarios)
              if(usuario.getId() == idDestinatario)
                usuario.receberTransferencia(valorTransferencia);
            break;
          default:
            break;
        }
        System.out.println();
      }
    }
  }
}
