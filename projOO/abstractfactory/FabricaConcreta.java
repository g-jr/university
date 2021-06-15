package Aplicacao;

import java.util.ArrayList;
import java.util.HashMap;

public class FabricaConcreta extends Fabrica {
  private Pontos p;
  private Circulo c;
  private Retangulo r;
  private Triangulo t;

  @Override
  public Pontos criaPontos() {
    p = new PontosConcreto();
    return p;
  }

  @Override
  public Circulo criaCirculo() {
    c = new CirculoConcreto();
    return c;
  }

  @Override
  public Retangulo criaRetangulo() {
    r = new RetanguloConcreto();
    return r;
  }

  @Override
  public Triangulo criaTriangulo() {
    t = new TrianguloConcreto();
    return t;
  }
}
