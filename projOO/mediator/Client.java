package Aplicacao;

public class Client {
  public static void main(String[] args) {
    ServidorConcreto server = new ServidorConcreto();

    // Cria tres usuarios
    Usuario u1 = server.createUsuario();
    Usuario u2 = server.createUsuario();
    Usuario u3 = server.createUsuario();

    // Sera imprimido a mensagem para os tres diferentes usuarios.
    server.enviaMensagem(u1, "Hello World!");
    server.enviaMensagem(u2, "Ola!");
  }
}
