package Tests;

import Controller.GestReviewsController;
import Exceptions.UserInexistente;
import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.RowQuery5;
import View.GestReviewsView;

import java.util.Map;

public class Query5Test {
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();

        /******************** 1 Teste ******************/
        try {
            Crono.start();
            Queries.query5(model, "IP8jFeEL_g8vixlHpNvRbg");
            Crono.stop();
            System.out.println("\n-------------------------------------------");
            System.out.println("$ Teste 1");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery5> query5Table = Queries.query5Table;

            for(RowQuery5 r: query5Table.values()){
                System.out.println(r.toString());
            }
        }
        catch (UserInexistente e) {
            System.out.println("-------------------------------------------\n");
            System.out.println("$ Teste 1\n");
            System.out.println("> Usuário não existe");
        }
        /******************** 2 Teste ******************/
        try {
            Crono.start();
            Queries.query5(model, "UGFp2xLEP9_c05lpj3eMew");
            Crono.stop();
            System.out.println("\n-------------------------------------------");
            System.out.println("$ Teste 2");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery5> query5Table = Queries.query5Table;

            for(RowQuery5 r: query5Table.values()){
                System.out.println(r.toString());
            }
        }
        catch (UserInexistente e) {
            System.out.println("\n-------------------------------------------\n");
            System.out.println("$ Teste 2\n");
            System.out.println("> Usuário não existe");
        }
        /******************** 3 Teste ******************/
        try {
            Crono.start();
            Queries.query5(model, "trfyguhij");
            Crono.stop();
            System.out.println("\n-------------------------------------------\n");
            System.out.println("$ Teste 3");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery5> query5Table = Queries.query5Table;

            for(RowQuery5 r: query5Table.values()){
                System.out.println(r.toString());
            }
        }
        catch (UserInexistente e) {
            System.out.println("\n-------------------------------------------\n");
            System.out.println("$ Teste 3");
            System.out.println("> Usuário não existe");
        }
    }
}
