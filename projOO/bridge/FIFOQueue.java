package Aplicacao;

public class FIFOQueue extends Queue{
  @Override
  public Object dequeue() {
    return implementador.dequeue();
  }

  @Override
  public void enqueue(Object o) {
    implementador.enqueue(o);
  }

  @Override
  public boolean isEmpty() {
    return implementador.isEmpty();
  }

  @Override
  public int size() {
    return implementador.size();
  }
}
