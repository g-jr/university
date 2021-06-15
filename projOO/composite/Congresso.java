package Aplicacao;

import java.util.ArrayList;
import java.util.List;

public class Congresso {
  private static List<Individuo> individuoList = new ArrayList();
  private static List<Instituicao> instituicaoList = new ArrayList<>();

  public void createIndividuo (){
    Individuo novoIndividuo = Individuo.create();
    individuoList.add(novoIndividuo);
    System.out.println("Individuo adicionado.");
  }

  public void createInstituicao (int membros) {
    Instituicao novaInstituicao = Instituicao.create(membros);
    instituicaoList.add(novaInstituicao);
    System.out.println("Instituicao adicionada.");
  }

  public void totalParticipantes() {
    System.out.println("Estao participando " + individuoList.size() + " pessoas individuais.");
    System.out.println("Estao participando " + instituicaoList.size() + " instituicoes.");
  }

  public void totalAssentos() {
    int total = 0;
    for(Individuo i: individuoList)
      total += i.getAssento();
    for(Instituicao i: instituicaoList)
      total += i.getMembro();
    System.out.println("O congresso possui " + total + " assento(s) ocupado(s).");
  }

}
