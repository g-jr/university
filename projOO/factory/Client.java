/*
 * Projeto Orientado a Objetos, 1sem 2020 - ICT UNIFESP
 * 12 - Factory Method (Design Patterns)
 * Desenvolvido por Gaspar Andrade
 */
package Aplicacao;

public class Client {
  public static void main(String[] args) {
    // Cria fachada
    Facade facade = new Facade();

    // Cria figuras atraves do metodo estatico getFigura
    // E realiza algumas operacoes atraves da fachada
    Figura circulo = facade.getFigura("Circulo");
    facade.setRaioCirculo(circulo, 2);
    facade.getArea(circulo);

    Figura quadrado = facade.getFigura("Quadrado");
    facade.setLadoQuadrado(quadrado, 14);
    facade.getArea(quadrado);

    Figura triangulo = facade.getFigura("TrEquilatero");
    facade.setLadoTriangulo(triangulo, 3);
    facade.getArea(triangulo);
  }
}
