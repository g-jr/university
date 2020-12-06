# Implementação de um Shell
--
Funcionalidades:

* Executar comandos unitários, com múltiplos parâmetros. Exemplo:

		ls -la
*  Executar comandos encadeados, utilizando o operador pipe "|" para combinar saída e entrada entre os comandos. Exemplo:

		ls -la | grep "teste"
		ls -la | grep "teste" | more
		
*  Redirecionar entrada e saída padrão de comandos para arquivos, utilizando "<" para entrada padrão e ">" para saída padrão. No caso do operador ">", se o arquivo apontado para a saída já existir, o operador trunca a saída do comando sobre o conteúdo do arquivo, ou seja, sobrescreve o arquivo existente com o novo conteúdo. Exemplo:

		sort < teste.txt > novo_teste.txt
* Redirecionar a saída padrão de comandos para arquivos, utilizando ">>". Diferente do operador ">", caso o arquivo de saída exista, o operador ">>" acrescenta a saída do comando ao fim do conteúdo do arquivo existente. Exemplo:

		sort < teste.txt >> novo_teste.txt
		
* Combinar operadores. Exemplo:

		sort < teste.txt | grep "x" > novo_test.txt
		sort < teste.txt | grep "x" >> novo_teste.txt
		
<b>Obs: Os operadores devem ser utilizados com aspas simples.</b><br>
<center>Exemplo de uso:<br>
./shell sort '<' teste.txt '>>' novo_teste.txt</center>