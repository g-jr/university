package Application;

public class Fonte {
  private String estado;

  public Memento criarMemento() {
    System.out.println("Estado salvado.");
    return Memento.criarMemento(estado);
  }

  public void setMemento(String s) {
    System.out.println("Memento salvado " + s);
    this.estado = s;
  }

  public void restaurar (Memento m) {
    estado = m.getEstado();
    System.out.println("Estado restaurado para " + estado);
  }
}
