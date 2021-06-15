package Aplicacao;

public class TrianguloConcreto implements Triangulo {
  private int pontoA;
  private int pontoB;
  private int pontoC;

  @Override
  public void setPontos(int a, int b, int c) {
    this.pontoA = a;
    this.pontoB = b;
    this.pontoC = c;
  }
}
