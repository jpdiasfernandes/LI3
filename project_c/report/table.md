<br>

<hr>

<p align="right"><font size="5" style="color:black"> <b>Capítulo III </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b>Table </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* 3.1 O funcionamento interno da API
* 3.2 Utilização da API no projeto  
  * 3.2.1 Utilizando as funções de procuras  
  * 3.2.2 Principais funções da <b><i>API</i></b>

<hr>

<img  src="../../pictures/bannerJose(final).png">

<hr>

Neste capítulo, faz-se uma breve introdução ao módulo **TABLE**, compost pela *API STable* **(Standart Table)**. Tal módulo encontra-se presente na secção **model** de nosso código.

<p><font size="5" style="color:black"><b>3.1 O funcionamento interno da API </b></font> </p>

O **Standart Table** surgiu a partir do raciocínio que optamos inicialmente de utilizarmos **Tables** tanto para guardar a informação que vem do *upload* dos ficheiros, tanto para guardar a informação representada pelas **queries**. Assim teríamos de encontrar algo suficienteente genérico, tanto para ser capaz de armazenar qualquer tipo de informação, ser uma estrutura suficientemente otimizada (para buscarmos padrões rapidamente) e que de uma certa forma representa uma **tabela**.

Sendo assim, escolhemos representar internamente a **TABLE** sendo composta por:

```c
struct table {
      int fields;
      int index;
      HEADER header;
      GTree **gtree; 
};
```

O campo **fields** representa a quantidade de *colunas* que a **TABLE** terá, isto é, a quantidade de campos existentes em cada linha do ficheiro **CSV** em estudo. O campo **header** traz a informação das características de cada **field** (cada coluna). Para ser mais claro, tal **header** é um **array** de **INFO'S**:

```
struct info {
    int type;
    int size;
    int header_no;
    const char *field_name;
};
```
Assim, cada **INFO** armazena a característica de uma coluna, que é composta por:
* **type** ```indica se a coluna guarda informação do tipo int, float, string, char ou double através de algumas macros```;
* **size** ```indica o tamanho que o *type* ocupa no contexto na arquitetura do computador```;
* **header_no** ```indica o índice da coluna```;
* **field_name** ```indica o nome da coluna```

Já conhecendo então aquilo que o **header** armazena, voltemos a **TABLE**. Esta, como dizemos anteriormente, armazena informação em **árvores binárias balanceadas**. Isto está representado na estrutura através do ```GTree ** gtree```. 
<br>
A forma como conseptualizamos a table foi por forma a existir uma tree principal. Esta gtree principal alocava o conteúdo da table e estaria indexada pela coluna do identificador único (índice index). 
As outras gtrees estariam disponíveis se o utilizador quisesse um acesso mais rápido a uma dada coluna. Está disponível uma função que possibilita a indexação de outras colunas. 
O que esta função faz é criar uma gtree no índice dessa coluna. Estas trees são "secundárias". Isto porque não alocam outra vez o conteúdo. Apenas pegam no conteúdo da coluna e usam o conteúdo como uma *key*. Esta key estará associada a um array de **ROW**. Este array tem todas as **ROW**'s que têm o mesmo conteúdo na dada coluna.
<br>
Esta indexação permite uma acesso que não é possível ter em hashtables. Por exemplo em tops. Se um utilizador quiser saber um top pode aceder a uma coluna indexada e é possível aceder essa gtree de forma decrescente. Por outro lado numa hashtable não seria possível fazer este acesso decrescente sem ter que percorrer todos os elementos.

Em nosso projeto utilizamos maioritariamente apenas uma (a tree principal), mas por questões de otimização, há mais do que esta possibilidade. 


<p><font size="5" style="color:black"><b>3.2 Utilização da API no projeto </b></font> </p>
<p><font size="4" style="color:black"><b>3.2.1 Criação de table</b></font> </p>
Para criar uma table apenas é necessário o número de colunas, a coluna que vai possuir a coluna com elementos únicos e por fim o nome das colunas.


```TABLE * new = table_new(3, 0, "id", "Primeiro Nome", "Sobrenome")```

Este código cria uma nova table com 3 colunas com os respetivos nomes das colunas. 
<br>
O que esta função faz é fazer o parsing dos argumentos e enviar para uma função genérica que faz a criação da table. 
<br>
Esta função recebe argumentos num formato já tratado.
<br>
```
char *colunas[3] = {"id", "Primeiro Nome", "Sobrenome"};
TABLE * new = table_new_generic(3, 0, colunas);
```
O resultado é o mesmo. A única vantagem de ter uma função genérica é que é possível automatizar criações de table sem saber de antemão o número de argumentos necessários. Como acontece na **table_new**. 
<br>

<p><font size="4" style="color:black"><b>3.2.2 Funções de procura </b></font> </p>
São disponibilizadas funções de procura que permitem fazer procuras à table. O intuíto principal delas é servirem como "building blocks" para que a partir delas seja possível fazer qualquer tipo de procura exigida. Desta forma o usuário da API deverá conseguir através da manipulação das funções de procura, chegar ao seu resultado pretendido. 
<br>
As principais funções são:

* ```ROW table_search_row_id(TABLE *t, void *key);``` 
	* Esta função devolve a **ROW** de um id único 
*  ```TABLE *table_search_row(TABLE *t, char *header_in, char **headers_out, int h_quant, void *cont);```
	* Esta função permite a partir de um conteúdo, de qualquer coluna, dar uma table com todas as **ROWS**'s que possuem esse conteúdo. Esta table pode ser costumizada através dos headers_out para ter apenas um *subset* de colunas.
* ```TABLE * table_join (TABLE * t1, TABLE * t2, char ** headers_out, int h1, int h2, int *types, tpointer (*func) (tpointer, tpointer, tpointer, tpointer), tpointer user_data);```
	* Dadas duas table esta função faz o join das duas
* ```TABLE *table_search_letter (TABLE * t, char * header_in, char ** headers_out, int h_quant, char letter);```
* ```void table_search_foreach(TABLE * t, int (*func) (tpointer, tpointer, tpointer), tpointer user_data);```
* ```void table_search_foreach_inverse (TABLE * t, int (*func) (tpointer, tpointer, tpointer), tpointer user_data);```
* ```int table_search_foreach_indexed(TABLE *t, int index, void (*func) (tpointer, tpointer), tpointer user_data);```

