package Matricula;

public class Curso {
  private int id;
  private String name;

  static Curso create(int id, String name) {
    Curso c = new Curso();
    c.id = id;
    c.name = name;
    return c;
  }
  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getName() {
    return name;
  }
}
