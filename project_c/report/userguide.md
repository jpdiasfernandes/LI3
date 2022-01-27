<div> <p align="left"><i> "Um programa capaz de  <br> ensinar o próprio utilizador "</i> <br>
Henrique Costa</div>
<p align="right"><font size="5" style="color:black"> <b>Capítulo II </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b>Guia do usuário </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **2.1** Caro usuário  
* **2.2** Aprendendo a ler o manual 
* **2.3** Sintaxes especiais 
* **2.4** O ficheiro de configuração

<hr>

<img  src="../../pictures/banner1.jpeg">

<hr>

Neste capítulo, faz-se uma breve visitada guiada nos aspectos mais importantes do programa, bem como algumas particularidades essenciais para uma melhor experiência. 

<br>

<p><font size="5" style="color:black"><b>2.1 Caro usuário </b></font> </p>

**Caro** usuário, seja bem-vindo ao **MyD**. O **MyDrawer** é uma espécie de *super armário* que possui suas *gavetas* devidamente otmizadas, de modo a extrair informação em pequenos espaços de tempo. Uma das coisas mais importantes em ter em conta é o mecanismo de **STATUS** do **prompt**. Como o Myd é um programa de *linha de comando*, o mesmo fornece uma validação visual dos comandos inseridos, através de mais de 7 **warnings** diferentes e **coloração** de acordo com o *parsing* do comando. Assim, se o *prompt* ficar vermelho siginifca que o comando inserido foi inválidado pelo *parsing*. Se estiver **verde** é o oposto, o comando foi processado com sucesso. Para além disso é sempre indicado o **tempo** de duração do comando em **segundos**. 

<p><font size="5" style="color:black"><b>2.2 Aprendendo a ler o manual </b></font> </p>

O manual ajuda a compreender a sintaxe dos possíveis comandos a serem feitos. Vale ressaltar que nessa primeira versão do projeto, **não pode haver espaços entre qualquer um dos carácteres inseridos na linha de comando**. Isso será exemplificado mais a frente, mas desde já fica essa informação. Para além disso, todas as queries e comandos (sem contar com os comandos informativos) necessitam do ```;``` no final.

<br>

O manual fornece nomeadamente 5 informações:

* **COMMAND**: indica o nome do comando;
* **ARGS NUMBER**: indica a quantidade de argumentos que a *função principal* associada ao comando recebe;
*  **ARGS TYPE**: indica o **tipo** dos argumentos respetivamente. Vale a pena ressaltar como se escreve cada um dos tipos: 

```s``` Simboliza **string**. Deve ser escrito entre ```""```. Por exemplo: ```"Eren Yeager"```<br>
```c``` Simboliza **carácter**. Deve ser escrito entre ```''```. Por exemlo: ```'c'```<br>
```d``` Simboliza **número inteiro**. Não precisa de nada mais para além do número. <br>
```f``` Simboliza **float**. Não precisa de mais nada para além do número.

* **COMMAND TYPE**: indica se o comando retorna seu valor para uma variável ou não. Isto é:

  ```x=business_info(sgr,...);``` é do tipo **VAR**
  <br>```show(x)```; é do tipo **FUNC**
  <br>```+``` é do tipo **TEXT**


<p><font size="5" style="color:black"><b>2.3 Sintaxes especiais </b></font> </p>

Devido a **API** **stditp** (que será explicada mais a frente) considerar o ```;``` e a```,``` como carácteres especiais, tais carácteres não podem ser usados dentro dos argumentos dos comandos. Assim, quando quiser se referir ao ```;``` utilize ```..```, enquanto para se referir ao ```,```, utilize o ```:```. Mostremos então algum dos comandos particulares:

```x=proj(x,{1:2:4})``` Tal comando realiza a projeção das colunas de uma tablea. Escolhemos as colunas através de um **array**, indicado por ```{}``` e o carácter de separação é o ```:```como citado anterioremnte.

```x=fromCSV("file", '..');``` Tal comando faz **upload** do **file** para uma TABLE, utilizando como carácter de separação dos campos o ```;```(pois como foi citado anteriormente, ```..``` representa o ```;```.

<br>
<p><font size="5" style="color:black"><b>2.4 O ficheiro de configuração </b></font> </p>

O **MyD** utiliza o ficheiro de configuração **mydConfig.cfg** para 2 efeitos:

* obter o **path** para os ficheiros que serão utilizados;
* indicar se o utilizador quer ou não ler o campo **fields** do ficheiro **users**.

Segue exemplo de ficheiro de config:

```
  set path=/home/bekele/files/
  set friends=yes
  ```

É importante respeitar a sintaxe do **set** separado por **path** (e escrever a partir do início da linha). O carácter ```=``` tem de vir junto do **set** e do início do seu valor inserido.
