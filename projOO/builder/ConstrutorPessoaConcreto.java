package Aplicacao;

public class ConstrutorPessoaConcreto extends ConstrutorPessoa {
  private Pessoa p = new Pessoa();

  @Override
  public void construirNome(String nome) {
    p.setNome(nome);
  }

  @Override
  public void construirCPF(String cpf) {
    p.setCpf(cpf);
  }

  @Override
  public Pessoa getPessoa() {
    return p;
  }
}
