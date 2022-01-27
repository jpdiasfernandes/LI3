package Model;

import Model.Catalogs.*;

import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

import java.io.Serializable;
import java.util.stream.Collectors;


public class Statistics implements Serializable {
    private GestReviewsModel model;
    private List<String> ficheirosLidos;
    private int numeroRegistosReviewsErradas;
    private int numeroTotalDeNegocios;
    private int numeroDiferentesNegociosAvaliados;
    private int numeroTotalUsers;
    private int numeroDiferentesUsersRealizaramReviews;
    private int numeroDiferentesUsersNaoRealizaramReviews;
    private int numeroReviewsSemImpacto;
    private List<Integer> numeroReviewsPorMes;
    private List<Double> mediaReviewsPorMes;
    private double mediaGlobalReviews;
    private List<Integer> numeroUtilizadoresQueDeramReviewsPorMes;


    public Statistics(GestReviewsModel model){
        this.model = model;

        ficheirosLidos = new ArrayList<>();
        ficheirosLidos.add(model.getFileUsers());
        ficheirosLidos.add(model.getFileBusiness());
        ficheirosLidos.add(model.getFileReviews());
    }

    public List<String> getFicheirosLidos() {
        return ficheirosLidos;
    }

    public void setFicheirosLidos(List<String> ficheirosLidos) {
        this.ficheirosLidos = ficheirosLidos;
    }

    public int getNumeroRegistosReviewsErradas() {
        return numeroRegistosReviewsErradas;
    }

    public void setNumeroRegistosReviewsErradas(int numeroRegistosReviewsErradas) {
        this.numeroRegistosReviewsErradas = numeroRegistosReviewsErradas;
    }

    public int getNumeroTotalDeNegocios() {
        return numeroTotalDeNegocios;
    }

    public void setNumeroTotalDeNegocios(int numeroTotalDeNegocios) {
        this.numeroTotalDeNegocios = numeroTotalDeNegocios;
    }

    public int getNumeroDiferenteNegociosAvaliados() {
        return numeroDiferentesNegociosAvaliados;
    }

    public void setNumeroDiferenteNegociosAvaliados(int numeroDiferenteNegociosAvaliados) {
        this.numeroDiferentesNegociosAvaliados = numeroDiferenteNegociosAvaliados;
    }

    public int getNumeroTotalUsers() {
        return numeroTotalUsers;
    }

    public void setNumeroTotalUsers(int numeroTotalUsers) {
        this.numeroTotalUsers = numeroTotalUsers;
    }

    public int getNumeroUsersRealizaramReviews() {
        return numeroDiferentesUsersRealizaramReviews;
    }

    public void setNumeroUsersRealizaramReviews(int numeroUsersRealizaramReviews) {
        this.numeroDiferentesUsersRealizaramReviews = numeroUsersRealizaramReviews;
    }

    public int getNumeroReviewsSemImpacto() {
        return numeroReviewsSemImpacto;
    }

    public void setNumeroReviewsSemImpacto(int numeroReviewsSemImpacto) {
        this.numeroReviewsSemImpacto = numeroReviewsSemImpacto;
    }

    List<Integer> getNumeroReviewsPorMes() {
        return numeroReviewsPorMes;
    }

    public void setNumeroReviewsPorMes(List<Integer> numeroReviewsPorMes) {
        this.numeroReviewsPorMes = numeroReviewsPorMes;
    }

    public List<Double> getMediaReviewsPorMes() {
        return mediaReviewsPorMes;
    }

    public void setMediaReviewsPorMes(List<Double> mediaReviewsPorMes) {
        this.mediaReviewsPorMes = mediaReviewsPorMes;
    }

    public List<Integer> getNumeroUtilizadoresQueDeramReviewsPorMes() {
        return numeroUtilizadoresQueDeramReviewsPorMes;
    }

    public void setNumeroUtilizadoresQueDeramReviewsPorMes(List<Integer> numeroUtilizadoresQueDeramReviewsPorMes) {
        this.numeroUtilizadoresQueDeramReviewsPorMes = numeroUtilizadoresQueDeramReviewsPorMes;
    }

    public void calculaNumeroTotalUsers(){
        Users users = (Users) model.getUser();
        Map<String, RowUsers> usersTable = users.getMainTable();
        numeroTotalUsers = usersTable.size();
    }

    public void calculaNumeroTotalBusiness(){
        Businesses businesses = (Businesses) model.getBusinesses();
        Map<String, RowBusinesses> businessTable = businesses.getMainTable();
        numeroTotalDeNegocios = businessTable.size();
    }

    public void calculaNumeroReviewsSemImpacto(){
        Reviews reviews = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = reviews.getMainTable();

        for(RowReviews rowReviews: reviewsTable.values()) {
            if ((rowReviews.getCool() == 0) && (rowReviews.getFunny() == 0) && (rowReviews.getUseful() == 0)) {
                numeroReviewsSemImpacto++;
            }
        }
    }

    public void calculaDiferentesUsersRealizaramReviews(){
        Reviews reviews = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = reviews.getMainTable();
        Map<String, String> usersReviewedTable = new HashMap<>();

        numeroDiferentesUsersRealizaramReviews = 0;
        for(RowReviews row: reviewsTable.values()){
            if(!usersReviewedTable.containsKey(row.getUser_id())){
                numeroDiferentesUsersRealizaramReviews++;
                usersReviewedTable.put(row.getUser_id(),row.getUser_id());
            }
        }
    }

    public void calculaDiferentesUsersNaoRealizaramReviews(){
        numeroDiferentesUsersNaoRealizaramReviews =  numeroTotalUsers - numeroDiferentesUsersRealizaramReviews;
    }

    public void calculaNumeroTotalReviewsPorMes(){
        numeroReviewsPorMes = new ArrayList<>(12);
        for(int i = 0; i < 12; i++) numeroReviewsPorMes.add(i,0);

        Reviews reviews = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = reviews.getMainTable();
        for(RowReviews row: reviewsTable.values()) {
            Integer mes = Integer.parseInt(row.getDate().subSequence(5,7).toString()) - 1;
            Integer quantidade = numeroReviewsPorMes.get(mes);
            numeroReviewsPorMes.set(mes,quantidade + 1);
        }
    }

    public void calculaMediaReviewsPorMes(){
        List<Double> totalStarsPorMes = new ArrayList<>(12);
        for(int i = 0; i < 12; i++) totalStarsPorMes.add(i, (double) 0);

        Reviews reviews = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = reviews.getMainTable();

        for(RowReviews row: reviewsTable.values()) {
            Integer mes = Integer.parseInt(row.getDate().subSequence(5,7).toString()) - 1;
            Double stars = totalStarsPorMes.get(mes);
            totalStarsPorMes.set(mes, stars + row.getStars());
        }
        mediaReviewsPorMes = new ArrayList<>(12);
        for(int i = 0; i < 12; i++) {
            mediaReviewsPorMes.add(i, totalStarsPorMes.get(i) / numeroReviewsPorMes.get(i));
        }
    }

    public void calculaNumeroDeUtilizadoresReviewsPorMes(){
        Map<String,String> usersPorMes = new HashMap<>();
        numeroUtilizadoresQueDeramReviewsPorMes = new ArrayList<>(12);

        Reviews reviews = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = reviews.getMainTable();

        for (int i = 0; i < 12; i++) {
            for (RowReviews row : reviewsTable.values()) {
                Integer mes = Integer.parseInt(row.getDate().subSequence(5, 7).toString()) - 1;
                if (mes == i && !usersPorMes.containsKey(row.getUser_id())){
                    usersPorMes.put(row.getUser_id(), row.getUser_id());
                }
            }
            numeroUtilizadoresQueDeramReviewsPorMes.add(i, usersPorMes.size());
            usersPorMes.clear();
        }
    }

    public void numeroReviewsErradas() {
        this.numeroRegistosReviewsErradas = 0;
        Reviews r = (Reviews) this.model.getReviews();
        Map<String, RowReviews> revTable = r.getMainTable();
        Businesses b = (Businesses) this.model.getBusinesses();
        Map<String, RowBusinesses> busTable = b.getMainTable();
        Users u = (Users) this.model.getUser();
        Map<String, RowUsers> userTable = u.getMainTable();
        for(RowReviews revRow : revTable.values()) {
            String userId = revRow.getUser_id();
            String busId = revRow.getBusiness_id();
            if (busTable.get(busId) == null || userTable.get(userId) == null)
                this.numeroRegistosReviewsErradas++;
        }
    }

    public void numeroBusReviewed() {
        Reviews r = (Reviews) this.model.getReviews();
        Map<String, RowReviews> revTable = r.getMainTable();

        this.numeroDiferentesNegociosAvaliados = revTable.values().stream()
                .map(RowReviews::getBusiness_id)
                .collect(Collectors.toSet())
                .size();
    }

    public void calculaMediaGlobalClassificacaoReviewPorMes(){
        double total = 0;
        for (double mes: mediaReviewsPorMes) total = mes + total;

        mediaGlobalReviews = total / 12;
    }

    public String mediaReviewsPorMesToString(){
        return  ">----[Janeiro] " + mediaReviewsPorMes.get(0) + "\n" +
                ">----[Fevereiro] " + mediaReviewsPorMes.get(1) + "\n" +
                ">----[Março] " + mediaReviewsPorMes.get(2) + "\n" +
                ">----[Abril] " + mediaReviewsPorMes.get(3) + "\n" +
                ">----[Maio] " + mediaReviewsPorMes.get(4) + "\n" +
                ">----[Junho] " + mediaReviewsPorMes.get(5) + "\n" +
                ">----[Julho] " + mediaReviewsPorMes.get(6) + "\n" +
                ">----[Agosto] " + mediaReviewsPorMes.get(7) + "\n" +
                ">----[Setembro] " + mediaReviewsPorMes.get(8) + "\n" +
                ">----[Outubro] " + mediaReviewsPorMes.get(9) + "\n" +
                ">----[Novembro] " + mediaReviewsPorMes.get(10) + "\n" +
                ">----[Dezembro] " + mediaReviewsPorMes.get(11) + "\n";
    }

    public String numeroTotalReviewsPorMesToString(){
        return  ">----[Janeiro] " + numeroReviewsPorMes.get(0) + "\n" +
                ">----[Fevereiro] " + numeroReviewsPorMes.get(1) + "\n" +
                ">----[Março] " + numeroReviewsPorMes.get(2) + "\n" +
                ">----[Abril] " + numeroReviewsPorMes.get(3) + "\n" +
                ">----[Maio] " + numeroReviewsPorMes.get(4) + "\n" +
                ">----[Junho] " + numeroReviewsPorMes.get(5) + "\n" +
                ">----[Julho] " + numeroReviewsPorMes.get(6) + "\n" +
                ">----[Agosto] " + numeroReviewsPorMes.get(7) + "\n" +
                ">----[Setembro] " + numeroReviewsPorMes.get(8) + "\n" +
                ">----[Outubro] " + numeroReviewsPorMes.get(9) + "\n" +
                ">----[Novembro] " + numeroReviewsPorMes.get(10) + "\n" +
                ">----[Dezembro] " + numeroReviewsPorMes.get(11) + "\n";

    }

    public String numeroUtilizadoresQueDeramReviewPorMesToString(){
        return  ">----[Janeiro] " + numeroUtilizadoresQueDeramReviewsPorMes.get(0) + "\n" +
                ">----[Fevereiro] " + numeroUtilizadoresQueDeramReviewsPorMes.get(1) + "\n" +
                ">----[Março] " + numeroUtilizadoresQueDeramReviewsPorMes.get(2) + "\n" +
                ">----[Abril] " + numeroUtilizadoresQueDeramReviewsPorMes.get(3) + "\n" +
                ">----[Maio] " + numeroUtilizadoresQueDeramReviewsPorMes.get(4) + "\n" +
                ">----[Junho] " + numeroUtilizadoresQueDeramReviewsPorMes.get(5) + "\n" +
                ">----[Julho] " + numeroUtilizadoresQueDeramReviewsPorMes.get(6) + "\n" +
                ">----[Agosto] " + numeroUtilizadoresQueDeramReviewsPorMes.get(7) + "\n" +
                ">----[Setembro] " + numeroUtilizadoresQueDeramReviewsPorMes.get(8) + "\n" +
                ">----[Outubro] " + numeroUtilizadoresQueDeramReviewsPorMes.get(9) + "\n" +
                ">----[Novembro] " + numeroUtilizadoresQueDeramReviewsPorMes.get(10) + "\n" +
                ">----[Dezembro] " + numeroUtilizadoresQueDeramReviewsPorMes.get(11) + "\n";

    }


    @Override
    public String toString() {
        return  "\n------------------ Estatísticas ------------------\n" +
                "> ficheiros lidos: " + model.filesToString() + "\n" +
                "> número de registos de reviews erradas: " + numeroRegistosReviewsErradas + "\n" +
                "> número total de negócios: " + numeroTotalDeNegocios + "\n" +
                "> número de diferentes negócios avaliados: " + numeroDiferentesNegociosAvaliados + "\n" +
                "> número total de users: " + numeroTotalUsers + "\n" +
                "> número de diferentes que users realizaram reviews: " + numeroDiferentesUsersRealizaramReviews + "\n" +
                "> número de diferentes users que não realizaram reviews: " + numeroDiferentesUsersNaoRealizaramReviews + "\n" +
                "> número de reviews sem impacto: " + numeroReviewsSemImpacto + "\n" +
                "> número de reviews por mês: \n\n" + numeroTotalReviewsPorMesToString() + "\n" +
                "> média de classificação de reviews por mês:\n\n " + mediaReviewsPorMesToString() + "\n" +
                "> média global de classificação reviews: " + mediaGlobalReviews + "\n\n" +
                "> número de utilizadores que deram reviews por Mês: \n\n" + numeroUtilizadoresQueDeramReviewPorMesToString() + "\n";
    }
}
