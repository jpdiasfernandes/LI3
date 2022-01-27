package Tests;

import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.RowQuery6;
import View.NewMenu;

import java.util.Map;
import java.util.Set;

public class Query6Test {
    private static NewMenu menu = new NewMenu(new String[]{
            "Teste"
    });

    public static void show(int number, GestReviewsModel model) {
        Crono.start();
        Queries.query6(model, number);
        Crono.stop();
        menu.message("> Tempo: " + Crono.getTimeAsString() + "\n");
        Map<Integer, Set<RowQuery6>> aux = Queries.query6Table;
        for(Map.Entry<Integer, Set<RowQuery6>> mapTmp : aux.entrySet()) {
            menu.message("Ano: " + mapTmp.getKey());
            for (RowQuery6 setAux : mapTmp.getValue()) {
                menu.message("Business id " + setAux.getBusinessId() + " Número total distintos users: " + setAux.getNumDistinctUsers());
            }
        }
    }
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();
        show(10, model);
        show(5, model);
        show(4, model);
        show(3, model);
        show(2, model);
        //show(100, model);

    }
}
