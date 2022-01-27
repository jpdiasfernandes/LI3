package Tests;

import Exceptions.UserInexistente;
import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.RowQuery3;
import View.NewMenu;

import java.util.Map;

public class Query3Test {
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();
        NewMenu menu = new NewMenu(new String[]{
                "Teste"
        });

        /******************** 1 Teste ******************/
        try {
            Crono.start();
            Queries.query3(model, "vybuhnijmko");
            Crono.stop();
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery3> qt = Queries.query3Table;

            if (qt.get(1) != null) menu.message("> Janeiro " + qt.get(1).getMedia());
            if (qt.get(2) != null)menu.message("> Fevereiro" + qt.get(2).getMedia());
            if (qt.get(3) != null)menu.message("> Março " + qt.get(3).getMedia());
            if (qt.get(4) != null)menu.message("> Abril " + qt.get(4).getMedia());
            if (qt.get(5) != null)menu.message("> Maio" + qt.get(5).getMedia());
            if (qt.get(6) != null)menu.message("> Junho " + qt.get(6).getMedia());
            if (qt.get(7) != null)menu.message("> Julho " + qt.get(7).getMedia());
            if (qt.get(8) != null) menu.message("> Agosto " + qt.get(8).getMedia());
            if (qt.get(9) != null)menu.message("> Setembro " + qt.get(9).getMedia());
            if (qt.get(10) != null)menu.message("> Outubro " + qt.get(10).getMedia());
            if (qt.get(11) != null) menu.message("> Novembro " + qt.get(11).getMedia());
            if (qt.get(12) != null)menu.message("> Dezembro " + qt.get(12).getMedia());
        }catch (UserInexistente e){
            menu.message("User não fez review!");
        }

        /******************** 2 Teste ******************/
        try {
            Crono.start();
            Queries.query3(model, "YoVfDbnISlW0f7abNQACIg");
            Crono.stop();
            menu.message("-----------------------\n");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery3>  qt = Queries.query3Table;

            if (qt.get(1) != null) menu.message("> Janeiro " + qt.get(1).getMedia());
            if (qt.get(2) != null)menu.message("> Fevereiro" + qt.get(2).getMedia());
            if (qt.get(3) != null)menu.message("> Março " + qt.get(3).getMedia());
            if (qt.get(4) != null)menu.message("> Abril " + qt.get(4).getMedia());
            if (qt.get(5) != null)menu.message("> Maio" + qt.get(5).getMedia());
            if (qt.get(6) != null)menu.message("> Junho " + qt.get(6).getMedia());
            if (qt.get(7) != null)menu.message("> Julho " + qt.get(7).getMedia());
            if (qt.get(8) != null) menu.message("> Agosto " + qt.get(8).getMedia());
            if (qt.get(9) != null)menu.message("> Setembro " + qt.get(9).getMedia());
            if (qt.get(10) != null)menu.message("> Outubro " + qt.get(10).getMedia());
            if (qt.get(11) != null) menu.message("> Novembro " + qt.get(11).getMedia());
            if (qt.get(12) != null)menu.message("> Dezembro " + qt.get(12).getMedia());

        }catch (UserInexistente e){
            menu.message("-----------------------\n");
            menu.message("User não fez review!");
        }

        /******************** 3 Teste ******************/
        try {
            Crono.start();
            Queries.query3(model, "0kA0PAJ8QFMeveQWHFqz2A");

            Crono.stop();
            menu.message("-----------------------\n");
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery3> qt = Queries.query3Table;

            if (qt.get(1) != null) menu.message("> Janeiro " + qt.get(1).getMedia());
            if (qt.get(2) != null)menu.message("> Fevereiro" + qt.get(2).getMedia());
            if (qt.get(3) != null)menu.message("> Março " + qt.get(3).getMedia());
            if (qt.get(4) != null)menu.message("> Abril " + qt.get(4).getMedia());
            if (qt.get(5) != null)menu.message("> Maio" + qt.get(5).getMedia());
            if (qt.get(6) != null)menu.message("> Junho " + qt.get(6).getMedia());
            if (qt.get(7) != null)menu.message("> Julho " + qt.get(7).getMedia());
            if (qt.get(8) != null) menu.message("> Agosto " + qt.get(8).getMedia());
            if (qt.get(9) != null)menu.message("> Setembro " + qt.get(9).getMedia());
            if (qt.get(10) != null)menu.message("> Outubro " + qt.get(10).getMedia());
            if (qt.get(11) != null) menu.message("> Novembro " + qt.get(11).getMedia());
            if (qt.get(12) != null)menu.message("> Dezembro " + qt.get(12).getMedia());

        }catch (UserInexistente e){
            menu.message("-----------------------\n");
            menu.message("User não fez review!");
        }
    }
}
