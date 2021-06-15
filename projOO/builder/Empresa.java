package Aplicacao;

public class Empresa {
  private String nome;
  private String cnpj;
  private Pessoa responsavel;

  public String getNome() {
    return nome;
  }

  public Pessoa getResponsavel() {
    return responsavel;
  }

  public String getCnpj() {
    return cnpj;
  }

  public void setNome(String nome) {
    this.nome = nome;
  }

  public void setCnpj(String cnpj) {
    this.cnpj = cnpj;
  }

  public void setResponsavel(Pessoa responsavel) {
    this.responsavel = responsavel;
  }
}
