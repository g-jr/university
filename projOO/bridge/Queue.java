package Aplicacao;

public abstract class Queue {
  Implementador implementador;

  public abstract Object dequeue();
  public abstract void enqueue(Object o);
  public abstract boolean isEmpty();
  public abstract int size();
}
