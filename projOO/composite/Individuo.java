package Aplicacao;

public class Individuo {
  private int id;
  private String nome;

  public static Individuo create() {
    Individuo individuo = new Individuo();
    return individuo;
  }

  public int getAssento() {
    return 1;
  }
}
