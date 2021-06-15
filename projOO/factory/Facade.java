package Aplicacao;

import java.util.HashMap;

public class Facade {
  // Armazena keys que retorna um novo objeto que implementa Figura
  private static HashMap<String, Figura> figuras;

  public Facade() {
    figuras = new HashMap<>();
    figuras.put("Circulo", new Circulo());
    figuras.put("Quadrado", new Quadrado());
    figuras.put("TrEquilatero", new TrEquilatero());
  }

  // Metodo responsavel por pesquisar a key e retornar o objeto requerido
  static Figura getFigura(String nomeFigura) {
    Figura f = null;
    f = figuras.get(nomeFigura);

    return f;
  }

  // Metodos para interacao com o objeto criado
  public void getArea(Figura f) {
    f.area();
  }

  public void setRaioCirculo(Figura f, int raio) {
    f.setRaio(raio);
  }

  public void setLadoTriangulo(Figura f, int tam) {
    f.setLado(tam);
  }

  public void setLadoQuadrado(Figura f, int tam) {
    f.setLado(tam);
  }
}
