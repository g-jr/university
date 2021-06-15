package Adapter;

import java.util.Enumeration;
import java.util.Iterator;

public class enuAdapter implements Iterator{
  private Enumeration enumeration;

  // metodo construtor
  public enuAdapter(Enumeration enumeration) {
    this.enumeration = enumeration;
  }

// adapta o comando hasNext para a interface Enumeration
  @Override
  public boolean hasNext() {
    return enumeration.hasMoreElements();
  }

  @Override
  // adapta a interface
  public Object next() {
    return enumeration.nextElement();
  }

  // comando nao contem suporte na interface Iterator
  public void remove() {
    System.out.println("Comando nao suportado.");
  }
}
