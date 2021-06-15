package Aplicacao;

public class PontosConcreto implements Pontos {
  private int pontoA;
  private int pontoB;

  @Override
  public void setPontos(int a, int b) {
    this.pontoA = a;
    this.pontoB = b;
  }
}
