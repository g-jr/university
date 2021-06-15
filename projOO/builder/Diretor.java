package Aplicacao;

import java.util.ArrayList;

public class Diretor {
  private ArrayList<Pessoa> pessoasCadastradas;
  private ArrayList<Empresa> empresasCadastradas;

  public Diretor() {
    pessoasCadastradas = new ArrayList<>();
    empresasCadastradas = new ArrayList<>();
  }

  public void construirPessoa(String nome, String cpf) {
    ConstrutorPessoaConcreto construtor = new ConstrutorPessoaConcreto();
    construtor.construirNome(nome);
    construtor.construirCPF(cpf);
    Pessoa p = construtor.getPessoa();

    // Adiciona pessoa na lista de cadastradas
    pessoasCadastradas.add(p);
  }

  public void construirEmpresa
    (String nomeResponsavel, String cpf, String nomeEmpresa, String cnpj) {
    ConstrutorEmpresaConcreto construtor = new ConstrutorEmpresaConcreto();
    construtor.construirResponsavel(nomeResponsavel, cpf);
    construtor.construirNomeEmpresa(nomeEmpresa);
    construtor.construirCnpjEmpresa(cnpj);
    Empresa e = construtor.getEmpresa();

    // Adiciona empresa na lista de cadastradas
    empresasCadastradas.add(e);
  }

  // Imprimir todas pessoas cadastradas
  public void verPessoas() {
    for (Pessoa p : pessoasCadastradas)
      System.out.println("Nome: " + p.getNome() + ", CPF: " + p.getCpf());
  }

  // Imprime todas as empresas cadastradas
  public void verEmpresas() {
    for (Empresa p : empresasCadastradas) {
      System.out.println("Nome Empresa: " + p.getNome() + ", CNPJ: " + p.getCnpj());
      System.out.println("\t\tNome Responsavel: " + p.getResponsavel().getNome() +
        ", CPF Responsavel: " + p.getResponsavel().getCpf());
    }
  }
}
