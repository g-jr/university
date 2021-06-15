package Matricula;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Facade {
  Map<Integer, Aluno> mapAluno = new HashMap();
  Map<Integer, Curso> mapCurso= new HashMap();

  public void setAluno(int id, String name) {
    Aluno a = Aluno.create(name, id);
    mapAluno.put(id, a);
  }
  public void setCurso(int id, String name) {
    Curso c = Curso.create(id, name);
    mapCurso.put(id, c);
  }
  public void getAluno(int id) {
    Aluno a = mapAluno.get(id);
    System.out.println("O nome do aluno eh: " + a.getName() + ".");
  }
  public void getCurso(int id) {
    Curso c = mapCurso.get(id);
    System.out.println("O nome do curso eh: " + c.getName());
  }
}
