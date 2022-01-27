<br>
<br>
<br>
<br>
<br>

<div> <p align="left"><i> "Feito para se preocupar apenas <br>com o que importa em seu código"</i> <br>
Henrique Costa </div>
<p align="right"><font size="5" style="color:black"> <b>Capítulo IV </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b>Interpretador </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **4.1** Descrição da API
* **4.2** Utilização da API no projeto  
	* **4.2.1** Inserção dos comandos 
	* **4.2.2** Funções primárias 
	* **4.2.3** Análise e execução dos comandos
* **4.3** Principais funções da API
<hr>

<img  src="../../pictures/bannerhenrique(final).png">

<hr>

Neste capítulo, faz-se uma breve introdução ao módulo do **Interpretador**, composto nomeadamente pela *API stditp* **(Standart Interpreter)** , *funções primárias* e *função de load*.

<p><font size="5" style="color:black"><b>4.1 Descrição da API </b></font> </p>

O ***stditp*** nasceu a partir de dois conceitos: **reutilização de código** e **interligação genérica modular**. De modo a criarmos um interpretador que possa ser utilizado em qualquer projeto e que tenha capacidade de se "comunicar" com qualquer parte do programa, dividimos o **parsing** dos comandos em 2 partes:
* Análise sintática, funcional e paramétrica;
* Análise dos **particular types** do programa em questão.


O primeiro **pilar** do parsing fica à cargo do **Standart Interpreter**, que disponiliza **estruturas** e **funções** preparadas para lidar com vários tipos de sintaxe de comandos - tais sintaxes são *features* que podem ser facilmente atualizadas.
<br>

As **Funções primárias** são as responsáveis pela segunda parte do parsing, e são elas que conhecem e manipulam as particularidades de nosso programa. A vantagem de utilizar tal separação de processos é poder noutros futuros projetos apenas criar *funções primárias* novas de acordo com o objetivo do programa, sendo *75%* do **parsing** já realizado pela *API* anteriormente dita. Mas a estratégia envolvida vai muito além de "reutilização" ... engloba também **interligação** (como veremos mais à frente).

<p><font size="5" style="color:black"><b>4.2 Utilização da API no projeto </b></font> </p>
<p><font size="4" style="color:black"><b>4.2.1 Inserção dos comandos </b></font> </p>

O **Standart Interpreter** controla majoritariamente o escopo da função ***main*** do programa. Inicialmente criamos uma **TABELA de opções**, a partir da função ```init_opts_table()```, e armazenamos este tipo de dados numa ```_OPTS_TABLE```. Tal tabela será responsável por todos os comandos do programa, bem como suas características e informações associadas. Tendo iniciado uma ```_OPTS_TABLE``` chamamos a função ```insert_opt() ``` para inserir os comandos de nosso programa. Segue uma demonstração de como tal proceco foi feito:

```c
/* criação da tabela de opções */
_OPTS_TABLE opts_table = init_opts_table ();

/* inserção do comando relativo a query 1*/
insert_opt (opts_table, "business_info", PRIMARY_business_info, 2, VAR, "busines info", varlist);

/* inserção dos restantes comandos ... */
```
Explicaremos agora o que signifca cada argumento da função ```opts_table```:

* ```1º ARG``` _OPTS_TABLE onde vamos inserir a opção (comando);
* ```2º ARG``` nome do comando - forma com que ele é escrito pelo usuário;
* ```3º ARG``` function pointer da função associada ao comando
* ```4º ARG``` número de argumentos do comando;
* ```5º ARG``` tipo de sintaxe do comando;
* ```6º ARG``` informação associada ao comando;
* ```7º ARG``` **ipointer** para a informação, a nível de dados, trasnferida a função associada ao comando.

<br>

<p><font size="4" style="color:black"><b>4.2.2 Funções primárias </b></font> </p>

O 3º argumento citado anteriormente, a ***função primária*** associada ao comando e o ***iponter*** (7º argumento) é que o permite a **interligação** modular da API do **stditp** com o seu programa. Isto porque usamos o conceito de **FUNCTION POINTER** para tal mecanismo de ligação. Para explicar este conceito no contexto do projeto, vamos usar como exemplo a query *business_info ()*. Conectaremos tal query com o **stditp** criando uma função intermediária a que chamaremos de ```PRIMARY_business_info ()```. Essa função apenas deverá seguir as seguinte regras:
* receber 1 parâmetro do tipo ```_ARGS``` disponilizo pela *API*
* ter valor de retorno do tipo ```(void *)```

A beleza disto é que o tipo ```_ARGS``` será uma struct que possuirá toda a informação necessária para utilizar em seu programa a partir do comando do usuário. Ela contém informação tanto vinda do usuário (a partir do **parse** do ***stditp***) tanto do programador que inseriu no tal ***ipointer*** referido anteriormente. Este ***ipointer*** não é nada mais que um ```typedef``` disponilizado pela *API* que é o mesmo que um ```(void *)```. Assim, voltando ao exemplo com a query *business_info* (), sabendo que tal query recebe uma variável do tipo *SGR* e um *business_id*, o que fizemos foi inserir uma ***VAR_LIST*** como sétimo argumento da função ```opts_table ()``` (sendo o tal ***iponiter***). Uma ***VAR_LIST*** é um apontador para uma **estrutura opaca** de nosso programa que contém uma **Hash_Table** que armazena todas as variáveis de nosso programa, inclusive variáveis *SGR* se existir. Assim, se o usuário inserir na linha de comando:

		x=business_info(sgr,"ishJIXOWQ0W9");
	
A função ```PRIMARY_business_info``` será chamada automaticamente e a partir dos ***getters*** do ***_ARGS*** poderei ter acesso aos:

* argumentos da query através do ```get_args ()```;
* variável em que guardaremos o resultado da query através do ```get_var ()```
* ***VAR_LIST*** com as variáveis existentes do programa com ```get_user_data ()```
* ***_STATUS_PROMPT*** (status do último comando) com ```get_status ()```;
* tempo que durou o *parse* com ```get_time_opt ()```;
* número de argumentos com ```get_argc ()```;
* e muito mais (...)

<br>

<u>OBSERVAÇÃO</u>: criamos uma função chamada ```load_opts ()``` para carregar numa ***_OPTS_TABLE*** toda informações dos comandos existentes em nosso programa.

<p><font size="4" style="color:black"><b>4.2.3 Análise dos comandos  </b></font> </p>

O **Standart Interpreter** fornece uma função chamada ```n_o_readline ()``` (***No Empty Readline***) que é uma espécie de *readline ()* melhorado, que armazena automaticamente os comandos **não vazios** no histórico e **retorna** a linha inserida pelo usuário. Utilizamos esta função para ler os comandos inseridos bem como a função ```parse ()``` que será o ***controle*** da analise dos comandos. Está função retorna o tal tipo ***_ARGS*** referido anteriormente com toda a informação a respeito do último comando inserido. Finalmente basta invocarmos a função ```do_opt ()``` e a função ***primária*** associada ao comando será executada. E assim, conseguimos de forma simples, organizada e eficiente, interligarmos nosso programa com a *API* ***stditp***.

<u>OBSERVAÇÃO</u>: chamamos **funcões primárias** anteriormente pois elas funcionam "antes" da função principal, nesse caso as *queries*. São nessas funções que invocamos as *queries* bem como fazemos o tal *parsing* dos *particular types*, isto é, vericamos se a variável inserida pelo usuário existe em nosso programa, verificamos se um dos argumentos inseridos é um ```float``` por exemplo no caso da query que recebe tal tipo de informação, etc.


<p><font size="4" style="color:black"><b>4.2.3 Principais funções da API </b></font> </p>

```init_opts_table()``` *Cria uma tabela de opções*
<br>
```insert_opt()``` *Insere opções numa tablea de opções*
<br>
```parse()``` *Lida com a análise de um comando e devolve o resultado do estudo
<br>
```n_e_readline()``` *Lê uma linha inserida e disponibiliza atalhos como: **acesso ao histórico***
<br>
```do_opt``` *Invoca a função primária associada do parsing dos comandos*
<br>
```get_args()``` *Devolve uma matriz contento os argumentos validados após feito o *parsing**
<br>
```get_var()``` *Devolve a variável associada ao comando inserido*
<br>
```get_time_opt()```*Informa o tempo de duração do comando* 
<br>
```get_status()```*Informa o **STATUS** do último comando*
<br>
```get_user_data()```*Devolve a informação adicional enviada para a função primária*

