package Aplicacao;
import java.lang.Math;

public class TrEquilatero extends Figura {
  private int lado;

  @Override
  public void setLado(int lado) {
    this.lado = lado;
  }

  @Override
  public void area() {
    double hip = (lado * lado) - (lado / 2) * (lado / 2);
    hip = Math.sqrt(hip);
    System.out.println("A area do triangulo eh: " + (hip * lado) / 2 + ".");
  }
}
