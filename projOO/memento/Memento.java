package Application;

public class Memento {
  private String estado;

  public static Memento criarMemento(String estado) {
    Memento m = new Memento();
    m.estado = estado;
    return m;
  }

  public String getEstado() {
    return estado;
  }
}
