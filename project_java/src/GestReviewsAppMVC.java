import Controller.GestReviewsController;
import Model.Catalogs.*;
import Model.GestReviewsModel;
import View.GestReviewsView;

import java.io.IOException;

public class GestReviewsAppMVC {
    public static void main(String[] args) {

        GestReviewsModel model = new GestReviewsModel();
        GestReviewsView view = new GestReviewsView();
        GestReviewsController controller = new GestReviewsController(model,view);

        controller.run();

    }
}
