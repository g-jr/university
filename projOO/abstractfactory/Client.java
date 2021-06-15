package Aplicacao;

public class Client {
  public static void main(String[] args) {
    Fabrica f = new FabricaConcreta();

    Circulo c = f.criaCirculo();
    c.setCirculo(2, 4);
    c.getArea();

    Pontos p = f.criaPontos();
    p.setPontos(1, 2);

    Triangulo t = f.criaTriangulo();
    t.setPontos(1, 2, 3);

    Retangulo r = f.criaRetangulo();
    r.setPontos(1, 2);
  }
}

