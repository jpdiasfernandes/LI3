package Tests;

import Exceptions.BusinessSemReview;
import Exceptions.UserInexistente;
import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.Query9.RowQuery9;
import Model.Queries.RowQuery5;

import java.util.Map;

public class Query9Test {
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();

        /******************** 1 Teste ******************/
        try {
            Crono.start();
            Queries.query9(model, "7ekQCFJCaReFnw-LqFuOWA",9);
            Crono.stop();
            System.out.println("$ Teste 1");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery9> query9Table = Queries.query9Table;
            for (Map.Entry<Integer, RowQuery9> r : query9Table.entrySet()){
                System.out.println("$ Quantidade: " + r.getKey() + "\n");
                System.out.println((r.toString()));
            }
        }
        catch (BusinessSemReview e) {
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 1\n");
            System.out.println("> Business inserido não tem review!\n");
        }
        /******************** 2 Teste ******************/
        try {
            Crono.start();
            Queries.query9(model, "7ekQCFJCaReFnw-LqFuOWA",4);
            Crono.stop();
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 2");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery9> query9Table = Queries.query9Table;
            for (Map.Entry<Integer, RowQuery9> r : query9Table.entrySet()){
                System.out.println("$ Quantidade: " + r.getKey() + "\n");
                System.out.println((r.toString()));
            }
        }
        catch (BusinessSemReview e) {
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 2\n");
            System.out.println("> Business inserido não tem review!\n");
        }
        /******************** 3 Teste ******************/
        try {
            Crono.start();
            Queries.query9(model, "7ekQCFJCaReFnw-LqFA",9);
            Crono.stop();
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 3");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery9> query9Table = Queries.query9Table;
            for (Map.Entry<Integer, RowQuery9> r : query9Table.entrySet()){
                System.out.println("$ Quantidade: " + r.getKey() + "\n");
                System.out.println((r.toString()));
            }
        }
        catch (BusinessSemReview e) {
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 3\n");
            System.out.println("> Business inserido não tem review!\n");
        }
        /******************** 4 Teste ******************/
        try {
            Crono.start();
            Queries.query9(model, "1sErmQCcWiLcUeey-FSwPQ",3);
            Crono.stop();
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 4");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery9> query9Table = Queries.query9Table;
            for (Map.Entry<Integer, RowQuery9> r : query9Table.entrySet()){
                System.out.println("$ Quantidade: " + r.getKey() + "\n");
                System.out.println((r.toString()));
            }
        }
        catch (BusinessSemReview e) {
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 4\n");
            System.out.println("> Business inserido não tem review!\n");
        }
        /******************** 5 Teste ******************/
        try {
            Crono.start();
            Queries.query9(model, "OlB0841vj4V7Wje5tTtLWA",8);
            Crono.stop();
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 5");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery9> query9Table = Queries.query9Table;
            for (Map.Entry<Integer, RowQuery9> r : query9Table.entrySet()){
                System.out.println("$ Quantidade: " + r.getKey() + "\n");
                System.out.println((r.toString()));
            }
        }
        catch (BusinessSemReview e) {
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 5\n");
            System.out.println("> Business inserido não tem review!\n");
        }
    }
}
