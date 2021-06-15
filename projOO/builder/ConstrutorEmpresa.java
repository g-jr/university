package Aplicacao;

public abstract class ConstrutorEmpresa {
  public abstract void construirResponsavel(String nome, String cpf);
  public abstract void construirNomeEmpresa(String nome);
  public abstract void construirCnpjEmpresa(String cnpj);
  public abstract Empresa getEmpresa();
}
