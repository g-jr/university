package Application;

public class Client {
  public static void main(String[] args) {
    Zelador z = new Zelador();
    Fonte f = new Fonte();

    // cria alguns mementos
    f.setMemento("estado1");
    z.addMemento(f.criarMemento());

    f.setMemento("estado2");
    z.addMemento(f.criarMemento());

    f.setMemento("estado3");
    z.addMemento(f.criarMemento());

    // restaura para o estado2
    f.restaurar(z.getMemento());

    // restaura para o estado1
    f.restaurar(z.getMemento());
  }
}
