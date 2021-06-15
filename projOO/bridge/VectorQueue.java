package Aplicacao;

import java.util.Vector;

public class VectorQueue implements Implementador{
  Vector<Object> vectorQueue;

  public VectorQueue() {
    vectorQueue = new Vector<>();
  }

  @Override
  public void enqueue(Object o) {
    vectorQueue.add(o);
  }

  @Override
  public Object dequeue() {
    Object o = vectorQueue.get(0);
    vectorQueue.remove(0);
    return o;
  }

  @Override
  public boolean isEmpty() {
    return vectorQueue.isEmpty();
  }

  @Override
  public int size() {
    return vectorQueue.size();
  }
}
