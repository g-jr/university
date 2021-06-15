package Aplicacao;

import java.util.List;

public class ListQueue implements Implementador{
  List<Object> list;

  @Override
  public void enqueue(Object o) {
    list.add(o);
  }

  @Override
  public Object dequeue() {
    Object o = list.get(0);
    list.remove(0);
    return o;
  }

  @Override
  public boolean isEmpty() {
    return list.isEmpty();
  }

  @Override
  public int size() {
    return list.size();
  }
}
