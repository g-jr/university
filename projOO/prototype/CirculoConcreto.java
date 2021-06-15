package Aplicacao;

public class CirculoConcreto implements Circulo {
  private int ponto;
  private int raio;

  @Override
  public void setRaio(int raio) {
    this.raio = raio;
  }

  @Override
  public int getRaio() {
    return raio;
  }

  @Override
  public void setPonto(int ponto) {
    this.ponto = ponto;
  }

  @Override
  public int getPonto() {
    return ponto;
  }
}
