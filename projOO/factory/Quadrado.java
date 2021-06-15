package Aplicacao;

public class Quadrado extends Figura {
  private int lado;

  @Override
  public void setLado(int lado) {
    this.lado = lado;
  }

  @Override
  public void area() {
    System.out.println("A area do quadrado eh: " + lado*lado + ".");
  }
}
