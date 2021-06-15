package Aplicacao;

public class Client {
  public static void main(String[] args) {
    Circulo c = new CirculoConcreto();
    c.setPonto(2);
    System.out.println(c.getPonto());
  }
}
