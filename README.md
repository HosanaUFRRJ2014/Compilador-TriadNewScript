# Compilador-TriadNewScript
Este repositório contém o trabalho da disciplina de Compiladores, de 2017-2, do curso de Ciência da Computação, da Universidade Federal Rural do Rio de Janeiro, feito pelos bacharelandos [Hosana Gomes](https://github.com/HosanaUFRRJ2014), [Lívia de Azevedo](https://github.com/liviadeazevedo) e [William Anderson](https://github.com/wabgomes).

O objetivo do trabalho é implementar um analisador léxico e sintático, usando as ferramentas Lex e Bison, a fim de compilar uma linguagem criada pelos integrantes do grupo.


##Estrutura do diretório:

Na pasta "arquivos_diversos" encontram-se arquivos de testes para o compilador, arquivo-texto para teste da funcionalidade de string dinâmica, e alguns esboços de código intermediário.

Na pasta "exemplos" encontram-se os exemplos de código apresentados na entrega do trabalho.

As bibliotecas e os demais arquivos-fonte da aplicação estão no diretório principal.

## Como instalar:
  É necessário ter o Lex e o Bison instalados na máquina para a aplicação funcionar.
  Caso o Lex e o Bison não estejam instalados, digitar os seguintes comandos num terminal Linux baseado em Ubuntu/Debian :

    sudo apt-get install lex
    sudo apt-get install bison

### Bibliotecas Externas:
Esta aplicação precisa da libboost para funcionar. Para instalá-la, digite o seguinte comando no terminal:

    sudo apt-get install libboost-dev -y

### Permissões:
Para poder executar o arquivo bash, não esqueça de dar as devidas permissões com o comando:

    chmod 777 runTeste.sh


##  Para compilar:
  No terminal, digite o seguinte comando:

    make all

  Ou se preferir, utilize ao arquivo de bash ```runTeste.sh``` para informar o arquivo a ser compilado e uma opção
      ( t - exibir o código no terminal; r - executar o código ou c - apagar os arquivos de compilação).

  Ex :

    ./runTeste.sh hexemplo01.tns t

  O exemplo acima irá imprimir no terminal o código fonte do arquivo fornecido.
