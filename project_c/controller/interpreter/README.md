<p align="center">
  <img src="https://img.shields.io/static/v1?label=Bliclioteca&message=HP&color=7159c1&style=for-the-badge&logo=ghost"/>
</p>

<h1 align="center">
      🧘‍♂️ <a href="#" alt="site do ecoleta"> Interpretador padrão </a> 🧘‍♀️
</h1>

<img  src="../../../pictures/bannerhenrique(final).png">

<h4 align="center">
	🚀 Em andamento 🚀 
</h4>

🎨 Índice
=================
<!--ts-->
   * [Sobre o projeto](#-sobre-o-projeto)
   * [Guia do usuário](#-layout)
     * [Implementação](#mobile)
     * [Funções disponibilizadas](#web)
     * [Dependências]()
   * [Guia do Programador](#-como-executar-o-projeto)
     * [Pré-requisitos](#pré-requisitos)
     * [O sistema por trás](#user-content--rodando-o-backend-servidor)
   * [Como contribuir](#-tecnologias)
   * [Autor](#-autor)

<!--te-->


## 💻 Sobre o projeto

📜 O **Interpretador padrão** é uma biblioteca feita em **C** com o propósito de automatizar a parte *chata* de lidar com o gerenciamento e validação de argumentos/comandos inseridos pelo usuário de seu programa. Como existem infinitas formas de se criar um programa em **C**, é de se esperar que pelo menos uma parte da validação dos comandos seja feita por você, isto é, não tem como eu saber quais são os **typedefs** que o senhor criou para pode validar. Assim, limitamo-nos a adoptar uma estratatégia e sistema que venha a encaixar em qualquer projeto. Sendo assim, o que esta biblioteca oferece é:


- [x] ⚡ Estrutura de dados para guardar argumentos e ativar funções consoante o comando do usuário
- [x] 👨‍🎓 Interpretação de argumentos com base em 3 diferentes metodologias (sendo algo que posteriormente aumentará):
    - Comandos que chamam apenas uma função
    - Comandos que chamam uma função e guardam seu resultado em variáveis
    - Comandos de acessos a matrizes
- [x] 🖌️ Prompt estilizado:
    - Coloração com base na validação do comando
- [x] 🧙‍♂️ Integração de suas funções dentro das funções da biblioteca (através da magia do *function pointer*)

## 🀄 Guia do usuário

### :wrench: Implementação

A Biblioteca *Interpretador padrão* auxilia você a lidar com os comandos de seu programa de acordo com o seguinte protocolo tripartido:

* Criação de tabela de opções e inserção de comandos
* Invocação da leitura do comando feito pelo usuário
* Analise do comando inserido pelo usuário

#### :closed_book: Criação da tabela de opções e inserção de comandos

A biblioteca fornece um tipo de dados chamado **_OPTS_TABLE**. Deverá ser criado um *apontador* para uma **_OPTS_TABLE** e igualar ele a função **init_itp** que recebe como argumento o número de comandos que seu programa tem. Segue um exemplo:

```c
	_OPTS_TABLE * opts_table = init_itp(3);
```

Nesse exemplo, estamos a dizer que nosso programa terá 3 comandos. Para entender a escolha desses nomes, *OPTS* vêm de *Options* e *Table* de *Tabela*. Ou seja, acabamos de criar um apontador para uma *Tabela de opções*. Para fins consensuais, *comandos* e *opções* são a mesma coisa nesse raciocínio. E porque é uma **tabela de opções** e não uma **lista de opções**. Bom, isto porque vamos guardar nela várisas coisas associadas a um comando para além  do comando em si. Agora precisamos avisar a biblioteca quais as informações que um comando tem, isto é:

* O nome da função associada ao comando (em forma de string);
* O nome da função associada ao comando (o mesmo nome anterior, mas sem ser em string, apenas o nome mesmo confia);
* O número de argumentos que a função associada ao comando tem;
* O **tipo da sintaxe da função**;
* Uma mensagem sem forma de string de informação relativa ao comando.

Avisamos a biblioteca dessas informações invocando a função **insert_op() com os seguintes argumentos ilustrados no exemplo seguinte:

```c
  insert_op(opts_table, "funcao1", funcao1, 3, FUNC_ONLY, "Invoca a funcao1");
```

Nesse exemplo estamos a *inserir* em nossa tabela de opções (criada anteriormente) um dos comandos que nosso programa terá. Esse comando se chama "funcao1" e ele invoca diretamente a **funcao1** que recebe **3** argumentos. O quarto argumento é relativo ao **tipo da sintaxe da função**. Lembra que foi dito na apresentação do projeto que existiam *3 meotodologias de interpretação de argumentos*? Então, é aqui que esse conceito entra. A metodologia identificada pela **MACRO** *FUNC_ONLY* se refere aos comandos que tem a seguinte estrutura:

    [PROMPT $] nome_funcao(arg1,arg2,arg3 ... );

## ❗Atenção ❗
* Inferimos que **nome_funcao** seja o mesmo que o nome inserido no segundo argumento de uma das chamadas a função **insert_op()**;
* O terceiro argumento da função **insert_op** não precisa ser necessariamente igual ao **nome_funcao** mas deve ser igual ao nome da **função primária que será invocada diretamente pelo comando**;
* Não pode haver separação entre o **nome_funcao** e os **parentêses**;
* Tudo que estiver entre as vírgulas será interpretado como argumento do tipo **(char * )**. Isto é, as funções primárias diretamente associadas aos comandos devem receber uma **matriz de carácteres** e um campo inteiro relativo a quantidade de argumento da função. Obs: cuidado com os espaços entre as vírgulas, eles vão ser acrescentados aos argumentos.
* O ";" não precisa necessariamente estar junto dos parentêses

Exemplo de função primária que satisfaça esses requisitos:

```c
    void funcao1(char **args, int argc);
```
Chamarei essas funções de **primárias** porque elas serão aquelas que serão as primeiras a serem chamadas pelos comandos e é dentro delas que você deve terminar a validar os argumentos, isto é, ver se os **tipos** dos argumentos são satisfeitos.

Para ser mais fácil compreender esta parte, vamos considerar um cenário, que tenha um programa que deve ser capaz de interpretar comando que realiza a soma de 2 números inteiros:

    [PROMPT $] soma(1,3);

Para seu programa ser capaz de realizar este comando você deve ter de realizar as seguintes linhas de código:

```c
  _OPTS_TABLE * opts_table = init_itp(3);
  insert_op(opts_table, "soma", soma , 2, FUNC_ONLY, "Soma 2 inteiros");
```
Para além disso deve ter a **função auxiliar primária**:

```c
  void soma(char **args, int args){
    /* exemplo de como realizar a validação dos tipos */
    int n1, n2;
    if ((sscanf(args[0],%d,&n1) != EOF) && (sscanf(args[1],%d,&n2) != EOF))
      funcao_secundaria(n1,n2);
    else printf("ERRO!\n");
  }
```
:nail_care: Repare na beleza do **interpretador padrão**. Se você decidir que seu programa seguirá a metodologia **FUNC_ONLY** de comandos, a única coisa que você precisará fazer (com os **TIPOS** desse exemplo mais concretamente)  para validar o argumento será verificar se o conteúdo das strings de **args**, isto é, os argumentos são do **tipo INT** (foi usado o *sscanf* nesse exemplo que retorna *EOF* em caso de erro). Ou seja, o **Interpretador padrão** lidou com:

* A quantidade de argumentos da função;
* A sintaxe geral do comando, isto é, se ele é da forma: func(arg1, arg2, ...);
* A verificação da existência da função

A verificação da existência da função é feita comparando o valor que vem antes dos *parentêses* do comando com o valor inserido por você no segundo argumento da função **insert_op()**, e é por isso que ambos devem ser iguais como dito anteriormente. O valor do terceiro argumento será a função primária que será invocada caso a verificação *existêncial* anterior mostrar que existe algo na tabela *opts_table* que corresponde ao comando. E por isso deve ser **exatamente igual ao nome da função primária**, sem aspas nem nada (isso pode parecer estranho caso seja novo em **C** mas isto é possível graças ao conceito de **apontadores para funções**, nesse caso eles funcionam escrevendo literalmente o nome da função).

#### :telescope: Invocação da leitura do comando feito pelo usuário

Uma vez criado a Tabela de comandos/opções e inserido alguns comandos que seu programa tem, agora temos de ser esse comando do usuário. Fazemos isso da seguinte forma:

```c
  char *line = NULL;
  line = n_e_readline(line, HELP);
```

A função **n_e_readline** disponibilizada pelo **Interpretador padrão** é uma espécie de **readline** melhorado. Melhorado no sentido de para além de fazer print de um **prompt** e guardar em **line** o que foi inserido pelo usuário, também faz:

* Coloração do **PROMPT** de acordo com a validação do comando;
* Adição do comando ao histórico de comandos, para depois poder repeti-lo fácilmente com **keystrokes** (comandos vazios não são adicionado ao histórico);

O nome **n_e_readline** vêm de **No_empty_readline**  justamente pelo que foi dito de não adicionar comandos vazios ao histórico.

O primeiro argumento desta função é um *apontador* onde ficará guardado o início do comando inserido pelo usuário e o segundo é o status que será importante para a coloração do **PROMPT**. Nesse exemplo inserimos nós mesmo o status de **HELP** (um **TIPO enum** disponibilizado) que por consequência vai colorir o **PROMPT** com a cor azul. Dentro do ciclo principal do programa poderá garantir que esse **STATUS** seja atualizado automaricamente de acordo com a validação do comando como veremos mais a frente ... Ah e btw, as cores funcionam caso você utiliza sistema UNIX, caso contrário pedimos carinhosamente desculpa.

Pelo facto desta função depender do **readline**, a seguinte flag deverá ser considerada quando for compilar seu projeto (mais a frente é falado melhor disto):

    -L/usr/local/lib -I/usr/local/include -lreadline

#### :crystal_ball: Analise do comando inserido pelo usuário

Ok, até agora já aprendemos a inserir os comandos que nosso programa terá e a obter o comando inserido pelo usuário, resta agora fazer a analise desse tal comando. Fazemos isso da seguinte forma:

```c
  _ARGS * args
  args = parse(line, opts_table);
```
A função **parse** recebe o *comando* inserido pelo usuário e a tabela de comandos/opções -  *opts_table* - criada por você anteriormente. Esta função devolve um apontador para um **TIPO _ARGS** onde será guardada a informações relevantes da analise do comando *line* inserido pelo usuário. Tão simples quanto isso, a analise de validação parcial do comando já foi feita.

Resta agora chamar a sua *função primária* para validar os *TIPOS* dos argumentos do comando. E como você fará isso? Invocando a função:
    
```c
      do_apt(args);
```

Sim, é isso mesmo, você nem precisou chamar sua função, nem fazer nenhum *if* nem nada, é tudo por conta da casa. O argumento desta função é um apontador para algo do **TIPO** *args* citado anteriormente. Porém diria que vale mais a pena chamar a função primária apenas se a analise parcial do comando ter dado resultado positivo, pois senão o comando já está errado mesmo. Conseguimos ver o resultado da analise parical do comando invocando a função:

```c
  get_status(args);
```
Essa função recebe um apontador para algo do **TIPO** *args* citado anteriormente (que carrega toda informação relevante da analise parcial do argumento). A função get_status devolve um **TIPO enum** disponibilizado que pode ser **ERROR, SUCCESSFUL ou HELP**. E é aqui que entra a coloração automática do **PROMPT** que foi dita anteriormente. Para concretizar este conceito vamos ver um exemplo completo usando tudo que foi dito:

```c
  #include <stdio.h> /* printf() */
  #include <string.h> /* strcmp() */
  #include "interpretador.h"

  void funcao_mult(float a, float b, float c){
    printf("%f\n", a * b * c);
  }

  void funcao_soma(int a, int b){
    printf("%d", a + b),
  }

  void mult(char **args, int argc){
    /* exemplo de como realizar a validação dos tipos */
    float n1, n2, n3;
    if ((sscanf(args[0],%f,&n1) != EOF) && (sscanf(args[1],%f,&n2) != EOF) && (sscanf(args[2],%f,&n3) != EOF))
      funcao_mult(n1,n2,n3);
    else printf("ERRO!\n");
  }

  void soma(char **args, int argc){
    /* exemplo de como realizar a validação dos tipos */
    int n1, n2;
    if ((sscanf(args[0],%d,&n1) != EOF) && (sscanf(args[1],%d,&n2) != EOF))
      funcao_soma(n1,n2);
    else printf("ERRO!\n");
  }

  int main(){

    _OPTS_TABLE * opts_table = init_itp(2);
    insert_op(opts_table, "soma", soma, 2, FUNC_ONLY, "Soma 2 inteiros");
    insert_op(opts_table, "mult", mult, 3, FUNC_ONLY, "Multiplica 3 floats");

    char *line = NULL;
    line = n_e_readline(line, HELP);

    _ARGS * args;
    while(strcmp(line,"exit")){
        args = parse(line, opts_table);
        
        if(get_status(args) == ERROR) printf("ERRO!\n");
        else do_apt(args);

        line = n_e_readline(line, get_status(args));
    }
  }
```

## TODO

### A nível de código

  * close_itp()
  * close_args()

### A nível de README.md
  * get_error()
  * Funções disponibilizadas

### Funções disponibilizadas

### Dependências

<h3 align="center">
    🏭 Readline 🏭
</h3>

#### 🏁 Flag para compilar projetos com a biblioteca *Readline* 

	-L/usr/local/lib -I/usr/local/include -lreadline

#### Exemplo

	gcc prog.c -L/usr/local/lib -I/usr/local/include -lreadline

#### ❗ Detalhe da utilização do *readline.h*

Tal biblioteca usa o *FILE Type* e por isso se quiser testar as funcionalidades dela terá de incluir a biblioteca *stdio.h* antes da inclusão da *readline*. Caso contrário, provavelmente terá o erro : *Unknown type: FILE*

## Guia do Programador

```c 
	readline(const char *prompt) 
```
Print prompt as prompt and return the line read (without *\n*, with only the **charachers that you write**). This functon reads everything until find EOF (enter key). The pointer to the line read is allocated with malloc, so you must have to free this pointer when you don't need it anymore (for example in "while statements" you must have to free the char *line before you again readline()).

```c
	add_history(char *word) 
```
Add the word to the history (so after this you can search this word in the command line from your program). To save only *no empty* strings see my "n_e_readline" function.

rl_completitions_functions is the set of functions that manipulate de "completition mecanism" (like use TAB) 

## User guide

##### When you use readline function in your program, you can use special keystrokes that help you to walk into the line that you are doing

* *Ctrl + d* -> clean screen (like the bash terminal)

* *Ctrl + a* -> move to the start of the line 

* *Ctrl + e* -> move to the end of the line

* *up key* -> suggest world from history (if you add your line to history in the program). The suggestions "back in time" with you touch "up key" several times.

* *(down key)* -> the same of last keystroke but move forward the time.

* *TAB (''\t')*  -> completition keystroke. Complete actual word with the options in the current directory 

---

⚒️ Feito por Henrique Costa 👋🏽 

---
