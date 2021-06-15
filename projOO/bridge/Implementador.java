package Aplicacao;

public interface Implementador {
  public void enqueue(Object o);

  public Object dequeue();

  public boolean isEmpty();

  public int size();
}
