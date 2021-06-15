package Aplicacao;

import java.util.ArrayList;

// Classe responsavel pela criacao e comunicao entre os usuarios do chat
public class ServidorConcreto implements Servidor {
  public static ArrayList<Usuario> usuarios;

  public ServidorConcreto() {
    usuarios = new ArrayList<>();
  }

  // Cria um novo usuario
  public Usuario createUsuario() {
    Usuario u = new UsuarioConcreto(this);
    usuarios.add(u);
    return u;
  }

  @Override
  public void enviaMensagem(Usuario usuario, String msg) {
    for(Usuario u : usuarios)
      u.recebeMensagem(msg);
  }
}
