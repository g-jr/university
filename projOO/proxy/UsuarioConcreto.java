package Aplicacao;

public interface UsuarioConcreto {
  public void receberTransferencia(double v);

  public void transferir(double v);

  public void saldo();

  public void depositar(double v);

  public int getId();
}
