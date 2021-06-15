package Aplicacao;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class UsuarioProxy implements UsuarioConcreto{
  private int senha;
  private Usuario usuario;

  public UsuarioProxy create(int id, int senha) {
    UsuarioProxy up = new UsuarioProxy();
    Usuario u = Usuario.create(id);
    usuario = u;
    this.senha = senha;
    return up;
  }

  // Valida se o usuario podera realizar suas operacoes
  public boolean validarUsuario() {
    Scanner in = new Scanner(System.in);
    System.out.println("Senha (somente numeros):");
    int s = in.nextInt();
    if(senha == s)
      return true;
    System.out.println("Senha invalida");
    return false;
  }

  @Override
  public void receberTransferencia(double v) {
    usuario.receberTransferencia(v);
  }

  @Override
  public void transferir(double v) {
    if(validarUsuario())
      usuario.transferir(v);
  }

  @Override
  public void saldo() {
    if(validarUsuario())
      usuario.saldo();
  }

  @Override
  public void depositar(double v) {
    if(validarUsuario())
      usuario.depositar(v);
  }

  @Override
  public int getId() {
    return usuario.getId();
  }
}
