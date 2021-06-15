package Aplicacao;

public class Usuario implements UsuarioConcreto{
  private int id;
  private double saldo;

  public static Usuario create(int id) {
    Usuario u = new Usuario();
    u.id = id;
    u.saldo = 0;
    return u;
  }

  @Override
  public void receberTransferencia(double v) {
    saldo += v;
  }

  @Override
  public void transferir(double v) {
    saldo -= v;
  }

  @Override
  public void saldo() {
    System.out.println("O saldo atual eh: " + saldo + ".");
  }

  @Override
  public void depositar(double v) {
    saldo += v;
  }

  @Override
  public int getId() {
    return id;
  }
}
