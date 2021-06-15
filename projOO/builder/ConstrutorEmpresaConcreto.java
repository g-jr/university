package Aplicacao;

public class ConstrutorEmpresaConcreto extends ConstrutorEmpresa {
  private Empresa empresa;

  public ConstrutorEmpresaConcreto() {
    empresa = new Empresa();
  }

  @Override
  public void construirResponsavel(String nome, String cpf) {
    ConstrutorPessoaConcreto c = new ConstrutorPessoaConcreto();
    c.construirNome(nome);
    c.construirCPF(cpf);
    empresa.setResponsavel(c.getPessoa());
  }

  @Override
  public void construirNomeEmpresa(String nome) {
    empresa.setNome(nome);
  }

  @Override
  public void construirCnpjEmpresa(String cnpj) {
    empresa.setCnpj(cnpj);
  }

  @Override
  public Empresa getEmpresa() {
    return empresa;
  }
}
