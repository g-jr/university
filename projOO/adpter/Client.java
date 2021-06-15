package Adapter;

import java.util.Iterator;
import java.util.Vector;


public class Client {
  public static void main(String[] args) {
    Vector<Integer> v = new Vector<>();
    v.add(0, 1);
    v.add(1, 9);
    // target: v.elements()
    Iterator em = new enuAdapter(v.elements());
    while(em.hasNext())
      System.out.println(em.next());
  }
}
