package Tests;

import Exceptions.AnoNaoValido;
import Exceptions.MesNaoValido;
import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.RowQuery2;
import View.NewMenu;

import java.util.Map;

public class Query2Test {
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();
        NewMenu menu = new NewMenu(new String[]{
                "Teste"
        });

        /******************** 1 Teste ******************/
        try {
            Crono.start();
            Queries.query2(model, 2020, 4);
            Crono.stop();
            menu.message("> Tempo: " + Crono.getTimeAsString());
            menu.message("\n> Ano 2020 » mês: abril ");
            Map<String, RowQuery2> tm = Queries.query2Table;
            for(RowQuery2 row : tm.values()) {
                menu.message("Num reviews : " + row.getNumReviews());
                menu.message("Num unique businesses : " + row.getNumUsers());
            }

        } catch (MesNaoValido | AnoNaoValido e) {
            menu.message("\n> Ano 2020 » mês: abril ");
            menu.message("Data inválida!\n");
        }

        /******************** 2 Teste ******************/
        try {
            Crono.start();
            Queries.query2(model, 2018, 9);
            Crono.stop();
            menu.message("--------------------------------------");
            menu.message("> Tempo: " + Crono.getTimeAsString());
            menu.message("\n> Ano 2018 » mês: Setembro ");
            Map<String, RowQuery2> tm = Queries.query2Table;
            for(RowQuery2 row : tm.values()) {
                menu.message("Num reviews : " + row.getNumReviews());
                menu.message("Num unique businesses : " + row.getNumUsers());
            }

        } catch (MesNaoValido | AnoNaoValido e) {
            menu.message("--------------------------------------");
            menu.message("\n> Ano 2018 » mês: Setembro ");
            menu.message("Data inválida!\n");
        }

        /******************** 3 Teste ******************/
        try {
            Crono.start();
            Queries.query2(model, 2019, 14);
            Crono.stop();
            menu.message("--------------------------------------");
            menu.message("> Tempo: " + Crono.getTimeAsString());
            menu.message("\n> Ano 2019 » mês: 14 (inválido) ");
            Map<String, RowQuery2> tm = Queries.query2Table;
            for(RowQuery2 row : tm.values()) {
                menu.message("Num reviews : " + row.getNumReviews());
                menu.message("Num unique businesses : " + row.getNumUsers());
            }

        } catch (MesNaoValido | AnoNaoValido e) {
            menu.message("--------------------------------------");
            menu.message("\n> Ano 2019 » mês: 14 (inválido) ");
            menu.message("Data inválida!\n");
        }

        /******************** 4 Teste ******************/
        try {
            Crono.start();
            Queries.query2(model, 2018, 1);
            Crono.stop();
            menu.message("--------------------------------------");
            menu.message("> Tempo: " + Crono.getTimeAsString());
            menu.message("\n> Ano 2018 » mês: Janeiro ");
            Map<String, RowQuery2> tm = Queries.query2Table;
            for(RowQuery2 row : tm.values()) {
                menu.message("Num reviews : " + row.getNumReviews());
                menu.message("Num unique businesses : " + row.getNumUsers());
            }

        } catch (MesNaoValido | AnoNaoValido e) {
            menu.message("--------------------------------------");
            menu.message("\n> Ano 2018 » mês: Janeiro ");
            menu.message("Data inválida!\n");
        }

        /******************** 5 Teste ******************/
        try {
            Crono.start();
            Queries.query2(model, 1918, 5);
            Crono.stop();
            menu.message("--------------------------------------");
            menu.message("> Tempo: " + Crono.getTimeAsString());
            menu.message("\n> Ano 1918 » mês: Maio");
            Map<String, RowQuery2> tm = Queries.query2Table;
            for(RowQuery2 row : tm.values()) {
                menu.message("Num reviews : " + row.getNumReviews());
                menu.message("Num unique businesses : " + row.getNumUsers());
            }

        } catch (MesNaoValido | AnoNaoValido e) {
            menu.message("--------------------------------------");
            menu.message("\n> Ano 1918 » mês: Maio");
            menu.message("Data inválida!\n");
        }
    }
}
