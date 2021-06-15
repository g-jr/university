package Aplicacao;

public class RetanguloConcreto implements Retangulo {
  private int pontoA;
  private int pontoB;

  @Override
  public void setPontos(int a, int b) {
    this.pontoA = a;
    this.pontoB = b;
  }
}
