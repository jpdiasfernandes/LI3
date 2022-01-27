package Controller;

import Exceptions.AnoNaoValido;
import Exceptions.BusinessSemReview;
import Exceptions.MesNaoValido;
import Exceptions.UserInexistente;
import Model.GestReviewsModel;
import Model.Queries.*;
import Model.Queries.Query9.RowQuery9;
import Model.Queries.RowQuery1;
import Model.Queries.RowQuery2;
import Model.Queries.RowQuery5;
import Model.Queries.RowQuery7;
import Model.Statistics;
import Tests.Crono;
import View.GestReviewsView;
import View.NewMenu;
import com.sun.source.tree.Tree;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.time.LocalDate;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import Model.Queries.*;
import java.util.*;


public class GestReviewsController {
    GestReviewsModel model;
    GestReviewsView view;
    public static Scanner sc = new Scanner(System.in);
    private static NewMenu menu = new NewMenu(new String[]{
            "Query1",
            "Query2",
            "Query3",
            "Query4",
            "Query5",
            "Query6",
            "Query7",
            "Query8",
            "Query9",
            "Query10",
            "Estatísticas",
            "Guardar ficheiro objeto",
            "Ler ficheiro objeto,"
    });

    public GestReviewsController(GestReviewsModel model, GestReviewsView view) {
        this.model = model;
        this.view = view;
    }

    public void run(){

        menu.setHandler(1,()->query1Handler());
        menu.setHandler(2,()->query2Handler());
        menu.setHandler(3,()->query3Handler());
        menu.setHandler(4,()->query4Handler());
        menu.setHandler(5,()->query5Handler());
        menu.setHandler(6,()->query6Handler());
        menu.setHandler(7,()->query7Handler());
        menu.setHandler(8,()->query8Handler());
        menu.setHandler(9,()->query9Handler());
        menu.setHandler(10,()->query10Handler());
        menu.setHandler(11,()->estatisticasHandler());
        menu.setHandler(12,()-> saveObjectFileHandler());
       menu.setHandler(13,()-> readObjectFileHandler());

        menu.run();
    }

    private void query1Handler(){
        Crono.start();
        Queries.query1(this.model);
        Crono.stop();
        System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
        TreeSet<String> nonReviewed = Queries.query1Table;
        for(String bus : nonReviewed)
           menu.message(bus);

        menu.message("Número não reviewed" + nonReviewed.size());

    }

    private void query2Handler(){

        Integer ano = query2Getyear();
        Integer mes = query2GetMonth();

        try {
            Crono.start();
            Queries.query2(this.model, ano, mes);
            Crono.stop();
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<String, RowQuery2> tm = Queries.query2Table;
            for(RowQuery2 row : tm.values()) {
                menu.message("Num reviews : " + row.getNumReviews());
                menu.message("Num unique businesses : " + row.getNumUsers());
            }

        } catch (MesNaoValido | AnoNaoValido e) {

        }

    }

    private static Integer query2Getyear(){
        System.out.println("Insira um Ano:");
        Integer year;
        try {
            year = getYear();
            return year;
        } catch (AnoNaoValido e){
            year = query2Getyear();
        }
        return year;
    }

    private static Integer query2GetMonth(){
        System.out.println("Insira um mês:");
        Integer mes;
        try {
            mes = getMonth();
            return mes;
        } catch (MesNaoValido e){
            mes = query2GetMonth();
        }
        return mes;
    }

    private static Integer getYear () throws  AnoNaoValido{
        if (sc.hasNextInt()) {
            Integer value = sc.nextInt();
            if (value > 2021) throw new AnoNaoValido();
            return value;
        }
        else {
            throw new AnoNaoValido();
        }
    }

    private static Integer getMonth () throws  MesNaoValido{
        if (sc.hasNextInt()) {
            Integer value = sc.nextInt();
            if (value > 12 || value < 0) throw new MesNaoValido();
            return value;
        }
        else {
            throw new MesNaoValido();
        }
    }

    private void query3Handler(){
        menu.message("\n> Insira um id de Usuário:");
        String userId = sc.next();
        try {
            Crono.start();
            Queries.query3(this.model, userId);
            Crono.stop();
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery3> qt = Queries.query3Table;

            if (qt.get(1) != null)menu.message("> Janeiro " + qt.get(1).getMedia());
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
            menu.message("User não fez review!\n");
        }
    }

    private void query4Handler(){
        menu.message("Insira um código de um negócio:");
        String busId = sc.nextLine();
        Crono.start();
        Queries.query4(this.model, busId);
        Crono.stop();
        Map<Integer, RowQuery4> res = Queries.query4Table;
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
        for(Map.Entry<Integer, RowQuery4> tmp : res.entrySet()) {
            menu.message("> " + meses[tmp.getKey() - 1] + " Nº reviews: " +
                    tmp.getValue().getNumReviewed() + "; Nº users únicos: " +
                    tmp.getValue().getNumUnique() + "; Nº média stars: " +
                    tmp.getValue().getMedia());
        }
        menu.message("Time: " + Crono.getTimeAsString());

    }

    private void query5Handler(){
        try {
            menu.message("Insira um user_id: ");
            String userId = sc.nextLine();
            Crono.start();
            Queries.query5(this.model, userId);
            Crono.stop();
            menu.message("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery5> query5Table = Queries.query5Table;

            for(RowQuery5 r: query5Table.values()){
                menu.message(r.toString());
            }

        } catch (UserInexistente e) {
            menu.message("Usuário não existe");
        }
    }

    private void query6Handler(){
        System.out.println("Insira o número de negócios limite: ");
        try {
            int number = sc.nextInt();
            Crono.start();
            Queries.query6(this.model, number);
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
        catch (InputMismatchException e) {
            menu.message("Input inválido. Tente outra vez.");
        }


    }

    private void query7Handler(){
        Crono.start();
        Queries.query7(this.model);
        Crono.stop();
        menu.message("> Tempo: " + Crono.getTimeAsString() + "\n");
        Set<RowQuery7> tm = Queries.query7Table;
        for (RowQuery7 row : tm) {
            menu.message("Top 3: " + row.getCity());
            for (Map.Entry<String, Integer> aux : row.getTop3()) {
                menu.message("Bussiness id: " + aux.getKey());
            }
        }

    }

    private void query8Handler(){
        menu.message("Insira uma quantidade de utilizadores.");
        try {
            int top = sc.nextInt();
            Crono.start();
            Queries.query8(this.model, top);
            Crono.stop();
            Set<RowQuery8> res = Queries.query8Table;
            for(RowQuery8 row : res)  {

                menu.message("User id: " + row.getUserId() + "; Nº negócios: "
                + row.getNumBus());
            }
            menu.message(">Tempo: " + Crono.getTimeAsString());


        }
        catch (InputMismatchException e) {
            menu.message("Input inválido. Tente outra vez");
        }

    }

    private void query9Handler(){

        System.out.println("Insira um BusinessId:");
        String business_id = sc.next();
        System.out.println("Insira uma quantidade users:");
        Integer quantidade = sc.nextInt();

        try {
            Crono.start();
            Queries.query9(model, business_id, quantidade);
            Crono.stop();
            System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
            Map<Integer, RowQuery9> query9Table = Queries.query9Table;
            for (Map.Entry<Integer, RowQuery9> r : query9Table.entrySet()){
                System.out.println("$ Quantidade: " + r.getKey() + "\n");
                System.out.println((r.toString()));
            }
        } catch (BusinessSemReview e) {
            System.out.println("Business inserido não tem review!\n");
        }
    }

    private void query10Handler(){
        Crono.start();
        Queries.query10(this.model);
        Crono.stop();
        System.out.println("> Tempo: " + Crono.getTimeAsString() + "\n");
        Map<String, Map<String, Map<String, Float>>> tm = Queries.query10Table;
        for (Map.Entry<String, Map<String, Map<String, Float>>> aux : tm.entrySet()) {
            menu.message("State: " + aux.getKey());
            for (Map.Entry<String, Map<String, Float>> aux2 : aux.getValue().entrySet()) {
                menu.message("City: " + aux2.getKey());
                for (Map.Entry<String, Float> avg : aux2.getValue().entrySet()) {
                    menu.message("Business id: " + avg.getKey() + " Avg: " + avg.getValue());
                }
            }
        }

    }

    private void estatisticasHandler(){
        Statistics statistics = new Statistics(this.model);

        statistics.calculaNumeroTotalUsers();
        statistics.calculaNumeroTotalBusiness();
        statistics.calculaNumeroReviewsSemImpacto();
        statistics.calculaDiferentesUsersRealizaramReviews();
        statistics.calculaDiferentesUsersNaoRealizaramReviews();
        statistics.calculaNumeroTotalReviewsPorMes();
        statistics.calculaMediaReviewsPorMes();
        statistics.calculaNumeroDeUtilizadoresReviewsPorMes();
        statistics.calculaMediaGlobalClassificacaoReviewPorMes();
        statistics.numeroReviewsErradas();
        statistics.numeroBusReviewed();

        System.out.println(statistics.toString());
    }

    private void saveObjectFileHandler() {
        menu.message("Qual o nome do ficheiro que pretende gravar: ");
        Scanner scanner = new Scanner(System.in);
        String nameFile = scanner.nextLine();
        this.model.saveObjectFile(nameFile);
    }

    private void readObjectFileHandler() {
        menu.message("Qual o nome do ficheiro que pretende ler: ");
        Scanner scanner = new Scanner(System.in);
        String namefile = scanner.nextLine();
        this.model = GestReviewsModel.readObjectFile(namefile);
    }

}
