package Matricula;

public class Aluno {
  private int id;
  private String name;

  static Aluno create(String name, int id) {
    Aluno a = new Aluno();
    a.name = name;
    a.id = id;
    return a;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getName() {
    return name;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }
}
