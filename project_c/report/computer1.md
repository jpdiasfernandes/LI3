<p align="right"><font size="5" style="color:black"> <b>Capítulo VII </b></font> </p>
<p align="right"><font size="9" style="color:black"> <b>Testes de performance </b></font> </p>

<p style="color:black"><b><font size="5">Conteúdo</font></b></p>
<hr>

* **7.1** Computador 1   
* **7.2** Computador 2 

<hr>

Neste capítulo, faz-se uma apresentação dos resultados obtidos em alguns comandos analisados.

## 7.1 Computador 1

<br>

Nas tabelas seguintes está exposto um breve resumo  dos testes que fizemos para medir o desempenho do programa. Quando falamos em **desempenho** nos referimos ao **tempo de execução** de um comando face o **tamanho** dos argumentos envolvidos numa operação. Nesta secção trazemos as informações relativas a um dos computadores em que realizamos os *testes de desempenho*, assim como os resultados dos testes em função de alguns comandos possíveis de se fazer no programa. 

<br>

<b>Tabela 1: Características do <computador 1> usado nos testes de desempenho</b>
<center>

<style>

.tabela th {
background: #aeaeae;
color: #1d1d1d;
}

</style>

<div class="tabela">

| Processor | # of Cores | # of Threads | Frequency (GHz) | Max Turbo Frequency| RAM (Gb) |
|-|-|-|-|-|-|
|AMD A6-7310 APU | 4|4|2.0 | 2.4| 8 |

</div>

</center>

<br>
<br>

<center>

<b> Tabela 2: Resultados dos testes de desempenho do computador 1

<div class="tabela">

| Comando | Tempo de execução (seg)|
|-|-|
| load_sgr (*default files*)| ~ 62 |
| businesses_started_by_letter (***sgr***, ***'A'***) | ~ 0.16 |
| business_info(***sgr***, *"0IWCmdWbv1w-5IgpKqtY8A"*)| ~ 0.000075 |
| businesses_reviewed (*sgr*, *"Jx5CzS0sVXf5oXbGKhhgHA"*)| ~ 0.0001 |
| businesses_with_stars_and_city(*sgr*,*3*,"*Jamaica Plain") | ~ 0.1 |
| top_businesses_by_city(*sgr*,*5*) | ~ 0.037 |
| international_users(*sgr*)| ~ 4.8 |
| top_businesses_with_category(*sgr*,*5*,*"Food"*)| ~ 0.25 |
| reviews_with_word(*sgr*,*"Carrots"*)| ~ 18 |

</div>

</center>

