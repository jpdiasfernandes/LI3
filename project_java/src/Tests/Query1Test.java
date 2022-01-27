package Tests;

import Exceptions.UserInexistente;
import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.RowQuery5;
import View.NewMenu;

import java.util.Map;
import java.util.TreeSet;

public class Query1Test {
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();
        NewMenu menu = new NewMenu(new String[]{
                "Teste"
        });

        /******************** Teste único ******************/
        Crono.start();
        Queries.query1(model);
        Crono.stop();
        System.out.println("\n-------------------------------------------");
        System.out.println("$ Teste único");
        System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
        TreeSet<String> nonReviewed = Queries.query1Table;
        for(String bus : nonReviewed)
            menu.message(bus);

        menu.message("Número não reviewed " + nonReviewed.size());
    }
}
