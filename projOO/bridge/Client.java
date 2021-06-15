package Aplicacao;

import java.io.FileOutputStream;

public class Client {
  public static void main(String[] args) {
    FIFOQueue fq = new FIFOQueue();
    fq.implementador = new VectorQueue();

    Object o = new Object();
    fq.enqueue(o);
    System.out.println("A fila esta vazia: " + fq.isEmpty());
    System.out.println("Tamanho da fila: " + fq.size());
  }
}
