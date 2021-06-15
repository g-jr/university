package Aplicacao;

public class Circulo extends Figura {
  private int raio;

  public void setRaio(int raio) {
    this.raio = raio;
  }

  @Override
  public void area() {
    System.out.println("A area do circulo eh: " + (3.14 * raio * raio) + ".");
  }
}
