package Tests;

import Model.GestReviewsModel;
import Model.Queries.Queries;
import Model.Queries.RowQuery4;
import View.NewMenu;

import java.util.Map;

public class Query4Test {
    private static NewMenu menu = new NewMenu(new String[]{
            "Teste"
    });
    public static void show(String busId, GestReviewsModel model) {
        String[] meses  = {
                "Janeiro",
                "Fevereiro",
                "Março",
                "Abril",
                "Maio",
                "Junho",
                "Julho",
                "Agosto",
                "Setembro",
                "Outubro",
                "Novembro",
                "Dezembro"
        };
        Crono.start();
        Queries.query4(model, busId);
        Crono.stop();
        menu.message("Time: " + Crono.getTimeAsString());
        Map<Integer, RowQuery4> res = Queries.query4Table;

        for(Map.Entry<Integer, RowQuery4> tmp : res.entrySet()) {
            menu.message("> " + meses[tmp.getKey() - 1] + " Nº reviews: " +
                    tmp.getValue().getNumReviewed() + "; Nº users únicos: " +
                    tmp.getValue().getNumUnique() + "; Nº média stars: " +
                    tmp.getValue().getMedia());
        }

    }
    public static void main(String[] args) {
        GestReviewsModel model = new GestReviewsModel();
        show("jFYIsSb7r1QeESVUnXPHBw", model);
        show("t35jsh9YnMtttm69UCp7gw", model);
        show("D4JtQNTI4X3KcbzacDJsMw", model);









    }
}

