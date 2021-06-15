package Aplicacao;

// Classe para a criacao de cada individual
public class UsuarioConcreto extends Usuario{
  public UsuarioConcreto(Servidor s) {
    super(s);
  }

  @Override
  public void recebeMensagem(String msg) {
    System.out.println(msg);
  }
}
