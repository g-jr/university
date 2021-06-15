package Application;

import java.util.ArrayList;

public class Zelador {
  private ArrayList<Memento> mementos;

  public Zelador() {
    mementos = new ArrayList<>();
  }

  // adiciona um novo memento
  public void addMemento(Memento m) {
    mementos.add(m);
  }

  public Memento getMemento() {
    Memento m = mementos.get(mementos.size() - 1);
    // remove o ultimo estado da lista
    mementos.remove(m);
    return mementos.get(mementos.size() - 1);
  }
}
