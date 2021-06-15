package Matricula;

public class Turma {
  private int id;
  private String name;

  public static Turma create (int id, String name) {
    Turma t = new Turma();
    t.id = id;
    t.name = name;
    return t;
  }

  public int getId() {
    return id;
  }

  public void setId(int id) {
    this.id = id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }
}
