package Aplicacao;

import java.util.ArrayList;

public class ArrayListQueue implements Implementador {
  ArrayList<Object> arrayQueue;

  public ArrayListQueue() {
    arrayQueue = new ArrayList<>();
  }

  @Override
  public void enqueue(Object o) {
    arrayQueue.add(o);
  }

  @Override
  public Object dequeue() {
    Object o = arrayQueue.get(0);
    arrayQueue.remove(o);
    return o;
  }

  @Override
  public boolean isEmpty() {
    return arrayQueue.isEmpty();
  }

  @Override
  public int size() {
    return arrayQueue.size();
  }
}
