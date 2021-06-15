package Aplicacao;

public class CirculoConcreto implements Circulo {
  private int ponto;
  private int raio;

  @Override
  public void setCirculo(int ponto, int raio) {
    this.ponto = ponto;
    this.raio = raio;
  }

  @Override
  public void getArea() {
    System.out.println("A area do circulo eh: " + 3.14 * raio * raio + ".");
  }
}
