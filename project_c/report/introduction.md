<div> <p align="left"><i> "Se eu fui capaz de ver mais longe <br> é porque estava de pé nos ombros dos gigantes"</i> <br>
Isaac Newton </div>
<p align="right"><font size="9" style="color:black"> <b>Introdução </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **1.1** Autorreflexão incial  
* **1.2** Uma escolha um tanto diferente  
* **1.3** Pensando para além do trabalho 

<hr>

Neste capítulo, faz-se uma apresentação, reflexão e descrição da perspetiva do nosso grupo face o trabalho. Pedimos categoricamente para ser tomada a devida **atenção** nessa introdução por ser nela em que começaremos por explicar as decisões e planeamento tomados ao longo do projeto.


<p><font size="5" style="color:black"><b>1.1 Autorreflexão inicial </b></font> </p>

O processo *abstrato* inicial de *projetar uma estrutura global* para o projeto resultou numa abordagem do enunciado que acreditamos não ser a mais **intuitiva**. Reconhecemos que nossa perspetiva provavelmente não vai diretamente de encontro com aquilo que os professores tencionam encontrar. Porém, tomamos uma decisão e assentamos sobre um ponto de vista em que acreditamos ter bastante potencial e pode ser alternativamente tão válido como qualquer outro. Focamo-nos essencialmente em fazer o famoso **código genérico**, e acabamos por ter 85% do trabalho totalmente independente em si do enunciado. A base por trás dos mecanismos das *queries* e *interpretação de comandos* são totalmente independentes do projeto, sendo possível usar grande parte do código em qualquer outro projeto.

Sendo assim, era de se esperar que o código atingisse uma certa **complexidade**. Por conta disso não iremos abordar todos os detalhes aqui, pois existe muita informação. Em contrapartida, disponibilizamos tais **informações** através de 2 formas: ficheiros ***README*** dentro das pastas do projeto, ou repositórios independentes donde foram criadas, por nós, as **API'S** que utilizamos. Dentro da pasta *ROOT* do projeto temos um ***README*** com as informações relativas ao programa em si, sobre como utilizar e as posturas que um contribuidor do projeto deve ter. Dentro do *interpretador* e do módulo *table* existem outros ***README*** com mais informações específicas. Na seccão de **Referências** encontram-se os links respetivos dos repositórios anteriormente mencionados.

<p><font size="5" style="color:black"><b>1.2 Uma escolha um tanto diferente </b></font> </p>

Vamos direto ao assunto, nossa decisão para o projeto foi visualizar tudo como **TABLE**. Pegamos no conceito das **TABLES** que são os resultados das *queries* e vimos para além dele, generalizando-o como sendo a ***unidade de estrutura de armazenamento da informação*** do projeto, seguindo o mesmo padrão do tratamento de dados das base de dados como, **MySQL** e **MongoDB**. Óbviamente, o resultado de uma query é uma entidade diferente do tipo *SGR*. Porém o próprio *SGR* utiliza **TABLES** como forma de guardar informação. Seguimos o seguinte paradigma:
	
```buscas em "TABLES" resultam em outras "TABLES", normalmente sendo uma espécie de "sub-conjunto" da "TABLE" em que foi realizada a busca.``` 

A **TABLE** é uma estrutura de dados implementada nomeadamente a partir de uma *árvore balanceada de procura*, em que cada nodo é uma representação das **ROWS** de uma tabela. Com isso temos a possibilidade de realizar operações de procura com os benefícios trazidos por tal tipo de dados (árvore balanceada). A vantagem disto é poder continuar a ter as propriedades de *árvores binárias balanceadas* se quisermos fazer *buscas* a partir dos resultados das *queries*. Ou seja, em nosso trabalho, o resultado de uma *query* não serve apenas para ser "mostrado", como também para fazermos **buscas otimizadas sobre ele**, com as mesmas propriedades das *buscas feitas para ter obtido a própria TABLE em questão*. Isto porque afinal, tudo é guardado na forma de **TABLE**.


Ou seja, daí surge uma outra vantagem de tal organização: a manutenção do código. Vamos supor que o tipo **TABLE** encontra uma forma mais eficiente de guardar informação e subsitui a tal *árvore balanceada de procura* por outra estrutura de dados. Nada precisará ser feito a nível de manutenção de código das *queries*. Isto porque as *queries* apenas conhecem o tipo *SGR*; que por sua vez apenas conhece o tipo *TABLE*. As funções de *busca* sobre as **TABLES** continuarão a funcionar da mesma forma, pois o utilizador da **API** **TABLE** nem sequer tem noção de que a *árvore balanceada de procura* foi subsituída por outra entidade. O utilizador apenas aplica funções de *busca* sobre uma *TABLE* e a invocação de tais funções não muda. Com isso conseguimos tratar qualquer tipo de *ficheiro* de dados da mesma forma, seja ele *reviews, users, businesses*, etc. Armazenar a informação de cada ficheiros numa **TABLE** (estrutura implementada internamente por uma árvore binária já armazenando **ROWS** em cada nodo, mantendo o aspecto natural de uma "tabela em si") e após aplicar *queries* continuar a ter uma **TABLE**, foi a escolha um tanto "diferente" que tomamos.


Sendo assim, naturalmente tivemos de criar uma **API** para implementar a simulação de um **banco de dados**, possuindo funções de *busca* super otimizadas. Estas funções de *busca* são as unidade funcionais das *queries*, funcionando como **peças de um puzzle** para criar um grande **puzzle** que são as queries.

<br>
<br>
<br>
<br>
<br>

<p><font size="5" style="color:black"><b>1.3 Pensando para além do trabalho</b></font> </p>

<hr>

<p align="center">
<img src="../../pictures/bannerJose(final).png">
</p>

<hr>

Como já citado anteriormente, criamos a **API** chamada ***Standart Table***. Tal **API** simula uma **base de dados** e possui essencialmente 3 partes distintas:

* ```#include <table/table.h>``` disponibilização de funções para criação de uma **TABLE** bem como inserção de elementos;

* ```#include <table/search.h>``` disponibilização de funções para **buscas** em **TABLES**;

* ```#include <table/show.h>``` disponibilização de funções para visualização de **TABLES**

As informações de tal **API** são dadas com mais detalhes na secção  **TABLE**. 

<hr>

<img  src="../../pictures/bannerhenrique(final).png">

<hr>

Para realizarmos o processo de **validação de comandos** por parte do utilizador, criamos a **API** chamada **Standart Interpreter**. Tal **API** fornece funcionalidades para tratar de diversas sintaxes de comandos (podendo aumentar para além do que o enunciado pede). O **Standart Interpreter** lida parcialmente com o **parsing dos comandos** pois há coisas que apenas seu programa por vezes está preparado para conhecer (como por exemplo uma das queries possuir como argumento strings como *EQ*, *LT* ou *GT*). Nesse caso a **API** não avalia se tais strings correspondem exatamente ao que a query pede ... Porém o **Standart Interpreter** possui um mecanismo que para além de dar à volta a esse problema, interliga o resto de teu programa ao interpretador, realizando todo o fluxo do código **por trás das cortinas do interpretador**. Esse mecanismo é possível graças a possibilidade do usuário inserir as funções que são chamadas mediante cada comando do usuário. Isso é posivel graças ao conceito de **function pointer** que será abordado mais detalhadamente na secção do **Interpretador**.
