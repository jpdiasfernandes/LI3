<br>

<hr>

<div> <p align="left"><i> "Tudo que uma pessoa pode imaginar, <br> outras podem tornar real"</i> <br>
Júlio Verne </div>
<p align="right"><font size="5" style="color:black"> <b>Capítulo VI </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b>Queries </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **6.1** Pensando como um <i>puzzle</i>   
* **6.2** Otimizações  
* **6.3** Análise de complexidade 

<hr>

Neste capítulo, faz-se uma apresentação do **raciocínio** para construção de algumas queries, bem como suas **otimizações** e **análise de complexidade**.

<p><font size="5" style="color:black"><b>6.1 Pensando como um <i>puzzle</i> </b></font> </p>

Tratamos a criação das queries assim como uma criança brinca com um *puzzle*. Em nosso caso as peças do *puzzle* são as funções de *search* disponibilizadas pela ***API STable***. Criamos as funções de *search* com o intuito de ser as ***mais genéricas possíveis*** para servir não exclusivamente para o nosso projeto e sim nosso projeto se servir delas.


<p><font size="5" style="color:black"><b>6.2 Otimizações </b></font> </p>

Mostraremos agora algumas das otimizações mais relevantes que fizemos nas queries ```3,4,5 e 6```.

<p><font size="4" style="color:black"><b>6.2.1 Query 3 </b></font> </p>

Declaração da função:

```c 
business_info (SGR sgr, char * business_id);
```

Para **otimizarmos** tal query recorremos ao módulo de **STATS**. Como já citado anteriormente, criamos 2 *TABLES* auxiliares com o intuito de servir de *ponte de ligação* entre **TABLES** distintas. Tais *TABLES* auxiliares foram concebidas de modo há, para além de relacionar *TABLES* diferentes, fazer tal relação de maneira otimizada. E um dos casos em que podemos ver isso é nessa query em análise. O que acontece nela é o seguinte:

```c
ROW row = table_search_row_id (stats, &business_id);
```

 Buscamos pela **ROW** indexada pelo *business_id* na *TABLE STATS_2*. Como sabemos, tal *TABLE* possui as seguintes informações: ```business_id, média de estrelas do business_id, quantidade de reviews do business_id```. Como fazemos a busca pelo ```business_id``` e a *TABLE* está indexada justamente por tal campo, a busca é ***O(log n)***, onde **n** é o número de ROWS da *TABLE STATS_2*. 

```c
ROW business_row = table_search_row_id (business, &business_id);
```

De seguida (caso encontrarmos a **ROW** na busca anterior), fazemos uma nova busca, procurando pelo mesmo *business_id*, mas dessa vez na *TABLE business*. Isto porque precisamos preencher a *TABLE final* com alguns campos que a *TABLE STATS_2* não possui, e quem possui é justamente a *TABLE business* (esses campos são ```name, city e state```). Como a *TABLE business* está indexada pelo campo *business_id*, a procura será ***O(log h)*** (onde ***h*** é o número de ***ROWS*** da *TABLE business*), tal como a anterior.

De resto basta juntarmos os dados anteriormente obtidos pelas procuras e ir acrescentando na *TABLE final*. Como as ***operações relevantes*** aqui podem ser reduzidas as 2 procuras anteriormente mencionadas, tal função possui uma complexidade  ***O(log n)*** + ***O(log h)*** assimptóticamente.


<p><font size="4" style="color:black"><b>6.2.2 Query 4 </b></font> </p>

Declaração da função:

```c
businesses_reviewed (SGR sgr, char * user_id);
```

Nessa query não recorremos ao módulo *STATS* na otimização. Fizemos proveito da *TABLE* armazenar informação numa **árvore binária balanceada** numa parte do código e percorremos algumas das *TABLES* noutras partes. Isto é, primeiramente criamos uma *TABLE* com todos os *business_id* em que o *user* dado como argumento fez *review*. Fazemos isso em:

```c
TABLE * business_id = table_search_row (reviews, "user_id", headers_out, 2, &user_id);
```
A função ```table_search_row()``` disponibilizada pela **API STable** se enquadramente perfeitamente nesse primeiro processo de *filtrar*, isto porque com ela podemos escolher **o campo de comparação** para filtrar as *ROWS* (nesse caso é o campo "user_id") e também podemos escolher os campos que vão estar na *TABLE de retorno*, indicado por *headers_out* (escolhemos o *business_id* nesse caso). Como temos de percorer toda a *TABLE* para fazer tal processo de filtragem, o tempo de execução é ***O(n)***, onde ***n*** é a quantidade de ***ROWS*** da *TABLE reviews*.

De seguida temos de, para cada *business* da *TABLE obtida anteriormente*, procurar o seu *name* correspondente na *TABLE business*. Fazemos assim um *foreach* na *TABLE business_id* e para cada elemento, realizamos um ```table_search_row_id()``` na *TABLE business* e como tal *TABLE* está indexada por *business_id*, tal procura será feita em ***O (log z)***, onde ***z*** é a quantidade de ***ROWS*** da *TABLE business*. Tal processo de **fazer uma travessia na TABLE e realizar alguma operação** é feito através da linha:

```c
table_search_foreach(business_id, businesses_reviewed_helper, (tpointer) user_data);
```
<br>

Onde **businesses_id** é a *TABLE* em que realizaremos a travessia, **businesses_reviewed_helper** é um *function pointer* que será responsável por realizar a operação de ```table_search_row_id()``` para cada **ROW** da *TABLE* em que se está a fazer a travessia e **user_data** é a informação adicional que o *function pointer* precisa receber para realizar seu propósito, como por exemplo a *return TABLE* que será preenchida durante a travessia.

Assim, podemos concluir que tal query é realizada em tempo de execução ***O(n)*** + ***O(y log(z))***, onde ***n*** é o número de **ROWS** da *TABLE reviews*, ***y*** é o número de ***ROWS*** da *TABLE* resultado da primeira operação de *search mencionada* e ***z*** é o número de ***ROWS*** da *TABLE business*.

<p><font size="4" style="color:black"><b>6.2.3 Query 5 </b></font> </p>

Declaração da função:

```c 
business_with_stars_and_city (SGR sgr, float stars, char * city);
```

Para otimizarmos tal função recorremos ao módulo de *STATS*. Primeiramente fazemos uma ***busca*** na *TABLE business* por todas as **os business que estão na cidade dada como argumento da função**. Utilizamos para tal a função ```table_search_row()``` disponibilizada pela **API Stable**. Com esta função podemos , para além de filtrar as **ROWS** a partir da comparação do campo *city*, escolher quais são os campos dessas **ROWS** filtradas que estarão na *TABLE de retorno*. Escolhemos então os campos ```business_id e name``` que são os campos que a *query* devolverá na *TABLE final*. Este procedimento dito é realizado em tempo ***O(n)***, onde ***n*** é o número de ***ROWS*** da *TABLE business* percorrida (como devemos filtrar todos os campos da *TABLE* a partir de um valor de comparação, obviamente temos de percorrer toda a *TABLE*). Este processo é realizado em:

```c
TABLE * business_in_city = table_search_row (business, "city", headers_out, 2, &city);
```

O que temos agora é uma *TABLE* com todos os *businesses* da cidada dada no comando do usuário. Resta agora filtrar dessa *Table* apenas aqueles que possuem média de estrelas maior ou igual ao que foi dado no comando. E é aqui que entra a *TABLE STATS_2* para otimizar este processo. Isto porque tal *TABLE* já possui a média de estrelas de cada *business*, mas para além disso o que faz diferença aqui, é o facto de tal *TABLE* estar **indexada** por *businesses_id's*. Assim, para cada *business* da *TABLE business_in_city*, basta verificarmos sua média de estrelas na *TABLE STATS_2*. Como tal *TABLE* está indexada por **business**, a procura é ***O(log z)***, onde ***z*** é o número de ***ROWS*** da *TABLE STATS_2*. Este processo de *para cada ROW fazer alguma coisa* é realizado pela parte do código:

```c
table_search_foreach(business_in_city, businesses_stars_and_city_helper, (tpointer) user_data);
```
<br>

O campo **businesses_stars_and_city_helper** é um **function pointer** que faz justamente algo com cada ROW que iremos visitar. O campo *user_data* é a informação que você julgar necessária para o *function pointer* anteriormente dito. Nesse caso enviamos diversos dados através de uma *struct auxiliar*, sendo que o mais relevante a saber é a *TABLE de retorno*, onde iremos preenchendo durante o *foreach*. Em geral, algumas das queries possuem uma estrutura semelhante, principalmente quando é realizado um *foreach*.

Sendo assim, dentro das opeações mais relevantes do código, temos a primeira *search* mencionada que é realizada em tempo de execução ***O(n)*** (onde ***n*** é o número de ***ROWS*** da *TABLE business*), e para cada elemento da *TABLE* resultante desta *search* faremos o *table_search_foreach* mencionado, em tempo ***O(y (log z))*** (onde ***y*** é o número de ***ROWS*** da *TABLE resultado do primeiro search* e ***z*** é o número de ***ROWS*** da *TABLE STATS_2*). Assim podemos concluir que está query é realizada em ***O(n) + O(y(log z))***.

<p><font size="4" style="color:black"><b>6.2.4 Query 6 </b></font> </p>

Declaração da função:

```c 
top_businesses_by_city (SGR sgr, int top);
```
Esta provavelmente é uma das queries em que conseguimos "melhor" **melhorar** nosso tempo. Na teoria tal query exige uma certa complexidade dado que temos de calcular os *top n businesses de cada cidade*. Para isso temos ter em conta que o número de estrelas e o campo de *cidade* estão em ficheiros distintos e ainda pior, inicialmente nem temos diretamente acesso a *média de estrelas* dos *businesses*. Vimos que essa ideia de **não relação direta** entre tais campos encerrou-se com a introdução do módulo *STATS*, onde a já referida *TABLE STATS_2* armazena a informação da média de estrelas, indexadas por *business_id*. Porém isso não era o suficiente para conseguirmos realmente otimizar a *query 6*. Faltava informação da *city* de cada business. O que nós fizemos então foi introduzir mais uma *TABLE* para o módulo *STATS*. Conhecida como *TABLE STATS* (diferente da *TABLE STATS_2* mencionada anteriormente), tal *TABLE* será o grande trunfo na execução de tal query. Como já foi explicado no capítulo **STATS**, a *TABLE STATS* possui indexação tripla a partir do conceito de **GKBDF** (generator key by diferent fields). Deixando de lado esta belíssima sigla criada por nós, usamos tal conceito de modo a já ter na *TABLE STATS* os businesses de cidades iguais seguidamente na *TABLE* e melhor ainda, em ordem crescente de *média de estrelas*. Assim, a única coisa que precisamos fazer é acessar o final da *TABLE* e fazer uma travessia de trás para frente, inserindo numa nova TABLE apenas os ***n*** businesses finais de cada secção de cidades iguais da *TABLE*. Fazemos isso em:

```c
table_search_foreach_inverse (t, top_businesses_by_city_helper, user_data);
```
<br>

Onde ***t*** é a *TABLE STATS*, ***top_businesses_by_city_helper*** é o ***function pointer*** que vai realizar a parte lógica de selecionar apenas ***n*** businesses por cidade (os ***n finais***) e **user_data** é a informação adicional que o **function pointer** recebe, como por exemlo a *return TABLE* que será preenchida. Assim apenas fazemos uma travessia na *TABLE STATS* para realizar a query, por tanto realizamos ela em ***O(n)***, onde ***n*** é igual a quantidade de ***ROWS*** da *TABLE STATS* que acaba por ser a quantidade de *businesses que possuem reviews*.


<p><font size="5" style="color:black"><b>6.3 Análise de complexidade </b></font> </p>

Nessa secção apresentaremos resumidamente a análise assimptótica, realizada anteriormente, dos temos de execução de cada **query** (para melhor informação das variáveis em questão, basta ver a seccão anterior):

* **Query 3**:  ***O(log n) + O(log h)***
* **Query 4**: ***O(n) + O(y(log z))***
* **Query 5**: ***O(n) + O(y(log z))***
* **Query 6**: ***O(n)***
