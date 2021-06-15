package Aplicacao;

// Classe contendo metodos e atributos comuns aos usuarios
public abstract class Usuario implements Servidor {
  private Servidor servidor;

  public Usuario(Servidor s) {
    servidor = s;
  }

  @Override
  public void enviaMensagem(Usuario u, String msg) {
    servidor.enviaMensagem(this, msg);
  }

  public abstract void recebeMensagem(String msg);
}
