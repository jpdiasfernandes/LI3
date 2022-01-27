<br>

## 7.2 Computador 2

<br>

Nessa  secção trazemos as informações relativas ao segundo computador que utilizamos para testar o **desempenho** de nosso programa.

<br>

<b>Tabela 3: Características do <computador 2> usado nos testes de desempenho</b>
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
|Intel i7-9750H | 6|12|2.60 | 4.50| 8 |

</div>

</center>

<br>
<br>

<center>

<b> Tabela 4: Resultados dos testes de desempenho do computador 2

<div class="tabela">

| Comando | Tamanho do ficheiro (segundos)| 
|-|-|
| load_sgr (*default files*)| ~ 22|
| businesses_started_by_letter(*sgr*,*'A'*)| ~ 0.055|
| business_info(***sgr***, *"0IWCmdWbv1w-5IgpKqtY8A"*)| ~ 0.00005|
| businesses_reviewed(*sgr*, *"Jx5CzS0sVXf5oXbGKhhgHA"*)| ~ 0.000075|
| businesses_with_stars_and_city(*sgr*,*3*,*"Jamaica Plain"*) |~ 0.042|
| top_businesses_by_city(*sgr*,*5*) | ~ 0.001|
| international_users(*sgr*)| ~ 1.9|
| top_businesses_with_category(*sgr*,*5*,*"Food"*)| ~ 0.1|
| reviews_with_word(*sgr*,*"Carrots"*)| ~  8|

</div>

</center>


