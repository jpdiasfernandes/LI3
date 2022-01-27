<hr>

<div> <p align="left"><i> "Sem dados você é apenas <br> mais uma pessoa sem opinião"</i> <br>
W. Edwards Deming </div>
<p align="right"><font size="5" style="color:black"> <b>Capítulo V </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b>STATS </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **5.1** Como interligamos os ficheiros? 
* **5.2** TABLE STATS_2  
* **5.3** TABLE STATS 

<hr>

Neste capítulo, faz-se uma apresentação e descrição do módulo **STATS**, responsável por interligar informação de *TABLES* distintas, otimizando consideravelmente alguma das queries.


<p><font size="5" style="color:black"><b>5.1 Como interligamos os ficheiros? </b></font> </p>

Uma das partes essenciais para a otimização das **queries** é conseguir relacionar eficientemente as informações dos ficheiros **users**, **businesses** e **reviews**. Tivemos um *Trade-off* entre a quantidade de espaço que iríamos reservar para estas estruturas de otimização, e em que momento iríamos criá-las. Nossa decisão final foi a criação de *2 TABLES* para tal conceito de *interligação de informação*. Ambas possuem o mesmo *tamanho*, isto é, vão possuir o *número de ROWS* equivalente a quantidade de *business que possuem reviews*. E em termos de *momento de criação*, realizamos suas construções durante o **load_sgr()**. Mas o mais importante a sublinhar é que, uma dessas *TABLES* construímos durante o *upload do ficheiro reviews* e outra ocorre em *tempo linear* à quantidade de **ROWS** da *TABLE* business (numa operação de ```table_join()```). Assim, em termos de *tempo de criação* e *espaço ocupado*, acreditamos ter encontrado um bom equilíbrio. Tais *TABLES* estão armazenadas na ```struct sgr```, dentro de uma ```struct stats```. Para não haver dúvidas (pois reconhecemos a péssima escolha dos nomes), fica desde já esclarescido: a ```struct stats``` possui *2 TABLES*, uma chamada *STATS* e outra *STATS_2*. Assim, toda vez que ser dito ao longo do relatório que utilizamos o módulo *STATS*, estamos a nos referir a ```struct stats```, e quando for dito que usamos a *TABLE STATS* e *TABLE STATS_2* estamos a nos referir as *TABLES* que estão armazenadas dentro da ```struct stats```. Vejamos agora particularmente cada uma dessas *TABLES*.

<p><font size="5" style="color:black"><b>5.2 TABLE STATS_2 </b></font> </p>

A *TABLE STATS_2* é aquela que é preenchida durante o upload do ficheiro **reviews**. Para um melhor entendimento do contexto em que criaremos tal **TABLE**, temos de ter em conta quando preenchemos as **TABLES reviews, users e business**. Este processo é realizado dentro da query ```load_sgr()```, nomeadamente pela função ```fill_table()```. Porém, a função ```fill_table()``` já recebe a **TABLE** a qual será preenchida. Assim, antes de tal função, será encontrado algo do tipo:

```c
TABLE * t = table_new(...);
```
E além do mais, a função ```fill_table()``` recebe 2 *TABLES*: uma que preencheremos com base no ficheiro que estamos a ler e outra que é justamente a *TABLE STATS_2*. Porém só chamamos tal função com um dos argumentos sendo a **TABLE STATS_2** quando formos ler o ficheiro **reviews**. Quando vamos fazer a ```fill_table()``` para qualquer outro ficheiro sem ser o de **reviews**, basta preencher a **NULL** o campo que seria da **TABLE STATS_2**. Assim, antes da ```fill_table()``` criamos a **TABLE STATS_2** da seguinte forma:

```TABLE *t_stats = table_new(3, 0, "s | f | d ", "business_id", "mean_stars", "quantity");```

Como já foi explicado na secção **TABLE**, criaremos então tal **TABLE STATS_2** com 3 campos, com indexação com base em "business_id". Agora restar invocar a ```fill_table()``` com a **TABLE reviews** e a **TABLE STATS_2** e tal TABLE será preenchida. Mas de que forma isso acontecerá?

A cada linha válida do ficheiro reviews, fazemos uma operação a qual resultará em algo que vamos inserir (ou atualização) na *TABLE STATS_2*. Após ler uma linha do ficheiro **reviews** e separar devidamente o conteúdo dela de acordo com os campos da *TABLE reviews*, filtramos da linha os seguintes dados:

* número de estrelas;
* business_id.

O que fazemos então é um ```table_search_row_id()``` do ```business_id``` na **TABLE STATS_2**. Esta **search** é o começo da "operação" citada anteriormente para inserir algo na *TABLE STATS_2*. Caso não for encontrado uma **ROW** indexada pelo *business_id*, o que faremos é inserir na **TABLE STATS_2** os campos filtrados no passo anterior (business_id e número de estrelas) e também o valor ***1*** no campo *quantity*, que simbolizará que nesse momento foi encontrado a primeira *review* desse *business_id*. A indexação usada nessa inserção será com base no campo *business_id*. O cenário muda quando a **search**, citada anteriormente, encontrar uma **ROW** indexada pelo *business_id*. Nesse caso, extraímos da **ROW** encontrada o valor do campo **mean_stars**, somamos ao valor do "número de estrelas" filtrado da linha atual em análise do ficheiro **reviews** e dividimos pelo valor que está no campo "reviews" da **ROW** encontrada. Por fim, inserimos o valor obtido dessas operações matemáticas no campo **mean stars** e incrementamos em ***1*** o valor que está no campo **quantity**. Ou seja, o que está acontecer aqui é resumidamente uma atualização da média de estrelas de uma **ROW** que já existia na **TABLE STATS_2**. Assim, quando acabar o processo de ```fill_table()``` da **TABLE reviews**, acabaremos também por preencher a *TABLE STATS_2*, que será indexada por *business_id* e possuirá a quantiade de *reviews* correspondentes, bem como sua média de estrelas. Ter essa **TABLE** permitirá acessarmos em tempo ***O(log(n))*** a média de estrelas de qualquer *business_id*, que será útil em algumas queries.

<p><font size="5" style="color:black"><b>5.3 TABLE STATS </b></font> </p>
 
 O motivo pelo qual explicamos primeiro a **TABLE STATS_2** é que ela é criada e preenchida antes da **TABLE STATS** (nós já citamos que foi uma péssima escolha de nomes mesmo). Isto porque a **TABLE STATS_2** faz parte do processo de criação da **TABLE STATS**. Isto é, enquanto o foco da **TABLE STATS_2** é encontrar rapidamente a média de estrelas de um determinado *business_id*, o objetivo da **TABLE STATS** será muito mais ousado: agrupar continuamente *business_id's* de uma determinado cidade ... E também por ordem crescente de **média de estrelas**! Criar tal **TABLE** foi sem dúvida um dos pontos altos do projeto, porque isto exigia uma certa complexidade e só iria compensar se fosse feito em um tempo aceitável. 

 Para conseguir criá-la, tivemos de disponibilizar na **API STable** uma função chamada ```table_join()```. Esta função a priori foi concebida apenas para conseguirmos juntar **ROWS** de 2 **TABLES** que estejam igualmente indexadas. Passado um tempo ampliamos ela de tal modo que seria capaz escolhermos quais os **campos** de cada **TABLE** que seria "juntado" numa **TABLE final**. Assim já teríamos a chave para conseguir criar uma **TABLE** que seria o resultado de juntar as **ROWS** indexadas da **TABLE STATS_2** com as **ROWS** igualmente indexadas da **TABLE business**, escolhendo os campos ```business_id, mean_stars, quantity, city e name``` para fazer parte da **TABLE final**. Porém, apesar de já termos *média de estrelas, business_id e city* reunidas numa **TABLE** só, ainda faltava o famoso "algo a mais" ... E é aqui que entra o conceito de **GKBDF** ...

<p align="center"> <b>G</b>enerator <b>K</b>ey <b>B</b>y <b>D</b>iferent <b>F</b>ields </p>

Tal conceito criado por nós (é o que julgamos pelo menos) surge para solucionar a problemática de como **indexar uma ROW numa TABLE com base em diferentes parâmetros**. A ideia consiste em precisar existir apenas um **campo de inexação único**. Por exemplo o *business_id* da **TABLE STATS_2** é único para cada **ROW**. Então pensamos, como seria possível deixar todas os *business_id's* de uma mesma cidade agrupados continuamente numa **TABLE**? Se usarmos o campo *city* como indexação teríamos o problema do **replace** (pois ao inserir algo com uma chave já existente na **árvore balanceada da glib**, acontece o "replace" desse nodo e não a adição). A solução que encontramos foi simples e bela: ```concatenar a cidade com o business_id```. Assim, pelo facto do "business_id" ser único para cada **ROW**, automaticamente a string concatenada terá de ser única também. E repare, como numa árvore binária balanceada temos o invariante de ```o nodo ser maior que todos os elementos da sub-árvore da esquerda e menor que os da direita```, e como os conceitos de "maior e menor" aplicados a "strings" correspondem a ordem lexical por conta do código ASCII, conseguimos ter **ROWS** agrupadas por cidades, pois o começo da string concatenada citada anteriormente será igual para *business_id's* de uma mesma cidade. Mas não paramos por aqui, pensamos então: o que aconteceria se juntássemos a média de estrelas na concatenação dessa string? Bom, se a ordem for ```cidade+média_de_estrelas+business_id``` o que aconteceria é que, dado que o código ASCII "entende" a ordem dos digitos, teríamos a chave de indexação perfeita para agrupar *business_id's* de uma mesma cidade e por ordem crescente de média de estrelas. Para visualizar melhor:

<hr>

```Imagine que tenha uma ROW com o business_id = abc, city = braga e média de estrelas = 3. Imagine agora outra com business_id = def, city = braga e média de estrelas = 4. Ao concatenar as strings de cada campo da ROW para formar uma chave de indexação, teríamos: braga3abc e braga4def. Ao comparar as 2 strings (em termos de ser maior ou menor com base no código ASCII) concluímos que braga3abc < braga4def justamente por 3 < 4 com base em ASCII. Podemos usar esse conceito para solucionar o problema de inserir ROWS com base na ordem crescente de média de estrelas!```

<hr>

Tendo em conta isto, ampliamos a função ```table_join()``` de modo a receber um **function pointer** (e um **user_data** para carregar informação necessária para o function pointer) que será a **função de criação de chave de indexação**. No nosso caso, para a *TABLE STATS* tal função vai concatenar os campos **city + média de estrelas + business_id** e inserir a **ROW** (resultado do *join()*)numa *TABLE* com base na **key** criada.

Conseguimos fazer isso com uma travessia na *TABLE business* e por isso dizemos anteriormente que a criação de uma das *STATS TABLE* foi ```em tempo linear a quantidade de ROWS da TABLE business```. Fazemos isto após já termos a *TABLE STATS_2* para fazer o ```join()``` com a *TABLE business* e tal *TABLE* mostra-se super essencial para a otimização da query *top_business_by_city()*.
