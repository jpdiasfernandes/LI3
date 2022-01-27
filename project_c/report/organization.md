<br>

<p align="left"><i> "Planear é uma arte ...<br> A arte de antecipar o futuro  "</i> <br>
Henrique Costa </div>
<p align="right"><font size="5" style="color:black"> <b>Capítulo VIII </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b> Organização </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **8.1** Organização estrutural de pastas
* **8.2** Tratando bem o Github

<hr>



Neste capítulo, faz-se uma descrição de como nosso grupo de organizou, tanto a nível de código, tanto a nível comunicativo. 

<p><font size="5" style="color:black"><b> 8.1 Organização estrutural de pastas </b></font> </p>

<p>
Seguindo o enunciado, utilizamos implicitamente (e explicitamente também) o conceito **MVC** de modularidade. Assim, estando dentro da pasta **root** do projeto, serão encontrado os seguintes ficheiros e pastas:

		controller model view main.c Makefile mydConfig.cfg README.md report

Indo agora dentro de uma das pastas ```controller```. ```model``` ou ```view``` o seguinte padrão será encontrado:

<hr>

```
.___.module1
|   |___.src
|   |   |
|   |   |__ file1.c
|   |   |
|   |   |__ file2.c
|   |   
|   |___.includes
|       |
|       |__ file1.h
|       |
|       |__ file2.h
|
|___.module2
|   |___.src
|   |   |
|   |   |__ file3.c
|   |   |
|   |   |__ file2.c
|   |   (...)
|   |
|   |___.includes
|       |
|       |__ file1.h
|       |
|       |__ file2.h
|      (...)
(...)
```
<hr>
<br>

Isto porque optamos por escolher o padão **MF** (**M**odule **F**irst) de organização de pastas. Tal método estipula que os ficheiros de um mesmo **tema** devem ser agrupados dentro de um **módulo** e, cada módulo terá suas próprias pastas ```src``` e ```includes```. Escolhemos proceder estruturalmente assim para poder ter uma visão mais **independente** de cada módulo a nível organizacional e funcional. Isto porque imagine o seguinte cenário:

```Foi decidido que o José Pedro será o responsável pelo módulo TABLE ```

Assim, o José acabará por ter de criar tudo a respeito do tema **TABLE** de acordo com as regras anteriormente ditas. Se ele quiser pode até adicionar sua própria ```main_table.c```, ```Makefile``` e ```README.md``` dentro da pasta **TABLE**, ressaltando ainda mais a modularidade e independência de seu código. E usando ainda este exemplo, vemos que o módulo **TABLE** acabou por ficar do seguinte modo:

<hr>

```
.table
|___.src
|   |__ generic.c
|   |__ helpers.c
|   |__ memory.c
|   |__ search.c
|   |__ table.c
|   
|___.includes
|   |__ generic.h
|   |__ helpers.h
|   |__ memory.h
|   |__ search.h
|   |__ table.h
|   |__ table_p.h
|
|___ TEST_table.c
|___ Makefile
|___ README.md
```

A beleza disto é que quem olha apenas para um módulo é capaz de ver um ```projeto independente```. Assim, no fundo, temos vários ```sub-projetos``` dentro do grande ```projeto```.

Separamos os módulos em:

* sgr; 
* table;
* pagination;
* messages;
* interpreter;

Dentro do módulo ```table``` está a **API** **STable** e dentro do ```ìnterpreter``` está a **API SInterpreter**. O módulo de **messages** possui os **warnigs** e **informações** para promover a interação ```usuário-programa```. O módulo ```sgr``` possui as **queries**, funções de **parsing** e declaração de ```estruturas``` específicas do trabalho pedido pelo enunciado. Por fim, o módulo ```pagination``` possui uma **extensão** da **API STable**, que foi separada do módulo *table* para manter a estrutura **MVC**.

<br>

<p><font size="5" style="color:black"><b> 8.2 Tratando bem o Github </b></font> </p>

Tendo em conta a devida atenção dada pelos professores a utilização do **Github**, nós retribuímos com mais detalhes ainda. Aqui entra a **secção de comunicação** da equipa. De modo a garantir um padrão ao longo do projeto e já manter uma postura mais profissional, utilizamos o conceito de **commits semânticos**. Para explicar esta parte, segue um excerto de nosso prórpio **README.md**:

<hr>

```For best pratices, in order to help to track specified information and create a beautiful CHANGELOG, we following the Convential Commits: https://www.conventionalcommits.org/en/v1.0.0/ that is inspired by on the Angular Commit Guidelines: https://github.com/angular/angular/blob/22b96b9/CONTRIBUTING.md#-commit-message-guidelines```

<hr>

Assim, todos nossos **commits** possuem a seguinte estrutura:

```<type>[optional scope]: <description>```

Um exemplo real foi quando o Henrique alterou o código das *time-functions* do interpretador, para uma nova versão:

```refactor(interpreter): change <time-functions>```

Para uma melhor leitura dos **commits** todos devem seguir a regra mais importante: serem consistentes semânticamente e sintáticamente com a frase:

```Ìf applied, this commit will <will your subject line here>```

Quanto ao nome dados as **branches**, seguimos o padrão:

```<branch-user-name>_<branch type>_<branch-name>```

Um exemplo disto foi quando o josé foi testar as queries:

```[BRANCH-NAME] jose_tests_queries```

<hr>


**Conclusão**, seguimos regras, nos organizamos com *commits semânticos e atómicos*, assim como *branches por temas*, como foi tudo anteriormente caracterizado. Tais informações podem ser acessadas também em nosso **README.md** onde separamos uma secção para aqueles que um dia podem querer contribuir para o projeto, ter em conta as normas de dinamização de equipa. Assim, acreditamos ter respeitado o modelo **MVC** e ainda grantindo uma base bem sólida de organização tanto a nível de código, como entre os membros de equipa.

<hr> 

</p>
