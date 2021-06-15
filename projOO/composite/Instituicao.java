package Aplicacao;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class Instituicao {
  private List<Individuo> individuoList;

  private static List<Individuo> createList() {
    List<Individuo> ret = new ArrayList<>();
    return ret;
  }

  public static Instituicao create(int membros) {
    Instituicao instituicao = new Instituicao();
    instituicao.individuoList = createList();
    for(int i = 0; i < membros; i++) {
      Individuo individuo = Individuo.create();
      instituicao.individuoList.add(individuo);
    }
    return instituicao;
  }

  public int getMembro() {
    int total = 0;
    for(Individuo i : individuoList)
      total += i.getAssento();
    return total;
  }
}
