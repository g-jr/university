package Aplicacao;

public class Client {
  public static void main(String[] args) {
    Diretor diretor = new Diretor();

    // Constroi empresas
    diretor.construirEmpresa("Gaspar", "11111111111", "Arroz", "44444444444444");
    diretor.construirEmpresa("Maria", "22222222222", "Feijao", "55555555555555");
    diretor.construirEmpresa("Joao", "33333333333", "Salada", "66666666666666");

    // Imprime todas empresas cadastradas
    diretor.verEmpresas();

    // Constroi pessoas
    diretor.construirPessoa("Lucas", "11111111112");
    diretor.construirPessoa("Larissa", "11111111113");

    //Imprime todas as pessoas cadastradas
    diretor.verPessoas();
  }
}
