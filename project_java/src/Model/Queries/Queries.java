package Model.Queries;

import Exceptions.AnoNaoValido;
import Exceptions.BusinessSemReview;
import Exceptions.MesNaoValido;
import Exceptions.UserInexistente;
import Model.Catalogs.Businesses;
import Model.Catalogs.Reviews;
import Model.Catalogs.RowBusinesses;
import Model.Catalogs.RowReviews;
import Model.GestReviewsModel;

import Model.Queries.Comparator.MapEntryComparator;
import Model.Queries.Comparator.Query6Comparator;
import Model.Queries.Comparator.Query8Comparator;
import Model.Queries.Query9.RowQuery9;
import Model.Queries.Query9.RowQuery9Tuplas;

import java.util.stream.Collectors;


import java.time.LocalDate;
import java.util.*;
import java.util.Map;
import java.io.Serializable;

public class Queries implements Serializable {


    public static TreeSet<String> query1Table;
    public static Map<String, RowQuery2> query2Table;
    public static Map<Integer, RowQuery3> query3Table;
    public static Map<Integer, RowQuery4> query4Table;
    public static Map<Integer, RowQuery5> query5Table;
    public static Map<Integer, Set<RowQuery6>> query6Table;
    public static Set<RowQuery7> query7Table;
    public static Set<RowQuery8> query8Table;
    public static Map<Integer, RowQuery9> query9Table;
    public static Map<String, Map<String, Map<String, Float>>> query10Table;



    public static void query1(GestReviewsModel model) {
        Businesses b = (Businesses) model.getBusinesses();
        Map<String, RowBusinesses> busTable = b.getMainTable();
        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> revTable = r.getMainTable();
        TreeSet<String> busReviewed = new TreeSet<>();
        TreeSet<String> busNReviewd = new TreeSet<>();

        for (RowReviews rowRev : revTable.values())
            busReviewed.add(rowRev.getBusiness_id());

        for (RowBusinesses rowBus : busTable.values()) {
            String bus = rowBus.getBusiness_id();
            if (!busReviewed.contains(bus))
                busNReviewd.add(bus);
        }

        Queries.query1Table = busNReviewd;
    }

    public static void query2(GestReviewsModel model, int ano, int mes) throws MesNaoValido, AnoNaoValido {
        Map<String, RowReviews> aux = new HashMap<>();
        if (ano > LocalDate.now().getYear()) throw new AnoNaoValido("" + ano);
        if (mes <= 0 || mes > 12) throw new MesNaoValido("" + mes);

        int count = 0;

        Set<String> users = new HashSet<>();
        Reviews r = (Reviews) model.getReviews();
        aux = r.getMainTable();

        for (RowReviews row : aux.values()) {
            String tmp = row.getDate();
            //Provavelmente não adicionar se uma data tiver mal? Don't know.
            String[] dateStr = tmp.split(" ");
            LocalDate date = LocalDate.parse(dateStr[0]);
            if (date.getYear() == ano && date.getMonth().getValue() == mes) {
                count++;
                users.add(row.getUser_id());
            }
        }

        RowQuery2 result = new RowQuery2(count, users.size());

        query2Table = new HashMap<>();
        query2Table.put("Resultado", result);

    }

    public static void query3(GestReviewsModel model, String userID) throws UserInexistente {
        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> aux = r.getMainTable();
        query3Table = new HashMap<>();

        List<Set<String>> businessesMonth = new ArrayList<>();

        for (int i = 0; i < 12; i++)
            businessesMonth.add(new HashSet<>());

        for (RowReviews row : aux.values()) {
            String user = row.getUser_id();
            if (user.equals(userID)) {
                int month = LocalDate.parse(row.getDate().split(" ")[0]).getMonthValue();
                RowQuery3 rowTmp;
                if ((rowTmp = query3Table.get(month)) == null)
                    rowTmp = new RowQuery3(month, 0, 0, 0);

                //Calcular a média
                float totStars = rowTmp.getNumReviews() * rowTmp.getMedia();
                float avg = (totStars + row.getStars()) / (rowTmp.getNumReviews() + 1);
                rowTmp.setMedia(avg);

                rowTmp.setNumReviews(rowTmp.getNumReviews() + 1);

                // Adicionar o business_id aos sets
                Set<String> bus = businessesMonth.get(month - 1);
                bus.add(row.getBusiness_id());
                rowTmp.setNumBusinesses(bus.size());

                query3Table.put(month, rowTmp);
            }

        }
        if (query3Table.size() == 0) throw new UserInexistente();

    }

    public static void query4(GestReviewsModel model, String businessId) {
        Map<Integer, RowQuery4> res = new HashMap<>();
        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> revTable = r.getMainTable();
        Map<Integer, TreeSet<String>> auxUnique = new HashMap<>();

        for(RowReviews rowRev : revTable.values()) {
            String busId = rowRev.getBusiness_id();
            if (busId.equals(businessId)) {
                String tmp = rowRev.getDate();
                String[] dateStr = tmp.split(" ");
                LocalDate date = LocalDate.parse(dateStr[0]);
                int month = date.getMonthValue();

                RowQuery4 row4 = res.get(month);
                if (row4 == null)
                    row4 = new RowQuery4(0, 0, 0);

                TreeSet<String> userUnique = auxUnique.get(month);
                if (userUnique == null)
                    userUnique = new TreeSet<>();
                userUnique.add(rowRev.getUser_id());
                auxUnique.put(month, userUnique);

                int numRev = row4.getNumReviewed();
                float avg = row4.getMedia();
                row4.setNumReviewed(numRev + 1);
                avg = ((avg * numRev) + rowRev.getStars()) / (numRev + 1);
                row4.setMedia(avg);
                row4.setNumUnique(userUnique.size());
                res.put(month, row4);
            }

        }

        query4Table = res;
    }

    public static void query5(GestReviewsModel model, String id) throws UserInexistente {
        final class RowQuery5Aux {
            String businessId;
            int quantidade;

            public RowQuery5Aux(String businessId, int quantidade) {
                this.businessId = businessId;
                this.quantidade = quantidade;
            }

            public String getBusinessId() {
                return businessId;
            }

            public void setBusinessId(String businessId) {
                this.businessId = businessId;
            }

            public int getQuantidade() {
                return quantidade;
            }

            public void setQuantidade(int quantidade) {
                this.quantidade = quantidade;
            }
        }
        Map<String, RowQuery5Aux> query5TableAux = new HashMap<>();

        Reviews review = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = review.getMainTable();

        for (RowReviews r : reviewsTable.values()) {
            if (r.getUser_id().equals(id)) {
                // business já está na tabela, incrementar quantidade
                if (query5TableAux.containsKey(r.getBusiness_id())) {
                    RowQuery5Aux row = query5TableAux.get(r.getBusiness_id());
                    row.setQuantidade(row.getQuantidade() + 1);
                    query5TableAux.replace(r.getBusiness_id(), row);
                } else {
                    RowQuery5Aux row = new RowQuery5Aux(r.getBusiness_id(), 1);
                    query5TableAux.put(r.getBusiness_id(), row);
                }
            }
        }

        Businesses business = (Businesses) model.getBusinesses();
        Map<String, RowBusinesses> businessTable = business.getMainTable();

        query5Table = new TreeMap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        RowQuery5 rowQuery5 = new RowQuery5();

        for (RowQuery5Aux r : query5TableAux.values()) {
            //quantidade já existe, adicionar businessName ordenadamente na lista
            if (query5Table.containsKey(r.getQuantidade())) {
                // Busco businessName no ficheiro de Business
                RowBusinesses businessName = businessTable.get(r.getBusinessId());
                rowQuery5.getBusinessesName().add(businessName.getName());
                // Replace com a adição do bussinessName a lista ordenado alfabeticamente
                rowQuery5.setQuantidade(r.getQuantidade());
                query5Table.replace(r.getQuantidade(), rowQuery5);
            } else {
                Set<String> businessesName = new TreeSet<>();
                RowBusinesses businessName = businessTable.get(r.getBusinessId());
                businessesName.add(businessName.getName());
                rowQuery5.setBusinessesName(businessesName);
                rowQuery5.setQuantidade(r.getQuantidade());
                query5Table.put(r.getQuantidade(), rowQuery5);
            }
        }

        if (query5Table.size() == 0) throw new UserInexistente();
    }


    public static int query6(GestReviewsModel model, int x) {
        Map<Integer, Map<String, RowQuery6>> aux2 = new HashMap<>();
        Map<Integer, Map<String, Set<String>>> uniqueReviews = new HashMap<>();
        Map<Integer, Set<RowQuery6>> res = new HashMap<>();


        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> aux = r.getMainTable();
        RowQuery6 rowTmp;


        for (RowReviews row : aux.values()) {
            int year = LocalDate.parse(row.getDate().split(" ")[0]).getYear();
            String businessID = row.getBusiness_id();
            Map<String, RowQuery6> mapTmp = aux2.get(year);
            if (mapTmp == null) mapTmp = new HashMap<>();


            if ((rowTmp = mapTmp.get(businessID)) == null)
                rowTmp = new RowQuery6(businessID, 0, 0);

            rowTmp.setNumReviews(rowTmp.getNumReviews() + 1);
            Map<String, Set<String>> aux3 = uniqueReviews.get(year);
            if (aux3 == null) aux3 = new HashMap<>();
            Set<String> aux4 = aux3.get(businessID);
            if(aux4 == null) aux4 = new HashSet<>();
            aux4.add(row.getUser_id());
            rowTmp.setNumDistinctUsers(aux4.size());
            aux3.put(businessID, aux4);
            uniqueReviews.put(year,aux3);
            mapTmp.put(businessID, rowTmp);
            aux2.put(year, mapTmp);
        }

        for(Map.Entry<Integer, Map<String, RowQuery6>> result  : aux2.entrySet()) {
            Set<RowQuery6> tmpSet;
            tmpSet = result.getValue().values().stream().sorted(new Query6Comparator()).limit(x).collect(Collectors.toSet());
            res.put(result.getKey(), tmpSet);
        }
        query6Table = res;

        return 0;
    }

    public static void query7(GestReviewsModel model) {
        Map<String, TreeSet<Map.Entry<String, Integer>>> aux = new HashMap<>();
        Map<String, Integer> aux2 = new HashMap<>();
        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> auxTable = r.getMainTable();
        Businesses b = (Businesses) model.getBusinesses();
        Map<String, RowBusinesses> busTable = b.getMainTable();
        MapEntryComparator comp = new MapEntryComparator();
        boolean found = false;


        for (RowReviews row : auxTable.values()) {

            String businessId = row.getBusiness_id();
            String city = busTable.get(businessId).getCity();

            TreeSet<Map.Entry<String, Integer>> tmp = aux.get(city);

            if (tmp == null)
                tmp = new TreeSet<>(comp);

            Iterator<Map.Entry<String, Integer>> tmpMap = tmp.iterator();

            while (tmpMap.hasNext() && !found) {

                Map.Entry<String, Integer> tmp2 = tmpMap.next();

                String busCity = tmp2.getKey();
                int busValue = tmp2.getValue();

                if (busCity.equals(businessId)) {
                    busValue++;
                    tmp2.setValue(busValue);
                    found = true;
                }


            }

            if (!found)
                tmp.add(new AbstractMap.SimpleEntry<>(businessId, 1));
            aux.put(city, tmp);
            found = false;
        }


        Set<RowQuery7> res = new HashSet<>();

        for (Map.Entry<String, TreeSet<Map.Entry<String, Integer>>> tmpRes : aux.entrySet()) {
            RowQuery7 rowAux = new RowQuery7(tmpRes.getKey(), 0, new HashSet<>());

            rowAux.setTop3(tmpRes.getValue().stream().limit(3).collect(Collectors.toSet()));
            res.add(rowAux);
        }

        query7Table = res;
    }

    public static void query8(GestReviewsModel model, int x) {
        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> revTable = r.getMainTable();
        Map<String, Set<String>> uniqueUserBus  = new HashMap<>();
        TreeSet<RowQuery8> res = new TreeSet<>(new Query8Comparator());



        for(RowReviews revRow : revTable.values()) {
            String userId = revRow.getUser_id();
            String busId = revRow.getBusiness_id();

            Set<String> uniqueBus = uniqueUserBus.get(userId);
            if(uniqueBus == null)
                uniqueBus = new HashSet<>();

            uniqueBus.add(busId);
            uniqueUserBus.put(userId, uniqueBus);
        }

        for (Map.Entry<String, Set<String>> entry : uniqueUserBus.entrySet()) {
            RowQuery8 tmp = new RowQuery8(entry.getKey(), entry.getValue().size());
            res.add(tmp);
        }

        query8Table = res.stream().limit(x).collect(Collectors.toSet());

    }

    public static void query9(GestReviewsModel model, String businessId, int quantidade) throws BusinessSemReview {
        final class RowQuery9Aux {
            String userId;
            float stars;
            int quantidade;

            public RowQuery9Aux() {
            }

            public RowQuery9Aux(String userId, float stars, int quantidade) {
                this.userId = userId;
                this.stars = stars;
                this.quantidade = quantidade;
            }

            public RowQuery9Aux(RowQuery9Aux row) {
                this.userId = row.getUserId();
                this.stars = row.getStars();
                this.quantidade = row.getQuantidade();
            }

            public String getUserId() {
                return userId;
            }

            public void setUserId(String userId) {
                this.userId = userId;
            }

            public float getStars() {
                return stars;
            }

            public void setStars(float stars) {
                this.stars = stars;
            }

            public int getQuantidade() {
                return quantidade;
            }

            public void setQuantidade(int quantidade) {
                this.quantidade = quantidade;
            }
        }
        Map<String, RowQuery9Aux> users = new TreeMap<>();

        Reviews review = (Reviews) model.getReviews();
        Map<String, RowReviews> reviewsTable = review.getMainTable();

        for (RowReviews r : reviewsTable.values()) {
            if (r.getBusiness_id().equals(businessId)) {
                if (users.containsKey(r.getUser_id())) {
                    float media = r.getStars();
                    RowQuery9Aux rowAux = new RowQuery9Aux(users.get(r.getUser_id()));
                    rowAux.setQuantidade(rowAux.getQuantidade() + 1);
                    rowAux.setStars((rowAux.getStars() + media) / rowAux.getQuantidade());
                    users.replace(r.getUser_id(), rowAux);
                } else {
                    RowQuery9Aux rowAux = new RowQuery9Aux(r.getUser_id(), r.getStars(), 1);
                    users.put(r.getUser_id(), rowAux);
                }
            }
        }
        query9Table = new TreeMap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });

        for (RowQuery9Aux r : users.values()) {
            if (query9Table.containsKey(r.getQuantidade())) {
                RowQuery9 r9 = new RowQuery9();
                r9 = query9Table.get(r.getQuantidade());
                Set<RowQuery9Tuplas> tuplas = r9.getNames();
                RowQuery9Tuplas tupla = new RowQuery9Tuplas(r.getUserId(), r.getStars());
                tuplas.add(tupla);
                r9.setNames(tuplas);
                query9Table.replace(r.getQuantidade(), r9);
            } else {
                Set<RowQuery9Tuplas> names = new TreeSet<>(new Comparator<RowQuery9Tuplas>() {
                    @Override
                    public int compare(RowQuery9Tuplas o1, RowQuery9Tuplas o2) {
                        return o1.getName().compareTo(o2.getName());
                    }
                });
                RowQuery9Tuplas tupla = new RowQuery9Tuplas(r.getUserId(), r.getStars());
                names.add(tupla);
                RowQuery9 r9 = new RowQuery9(names);
                query9Table.put(r.getQuantidade(), r9);
            }
        }

        Map<Integer, RowQuery9> query9TableFinal = new TreeMap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });

        int cont = 0;
        Iterator<RowQuery9> itValue = query9Table.values().iterator();
        Iterator<Integer> itKey = query9Table.keySet().iterator();
        while (itValue.hasNext() && cont < quantidade) {
            RowQuery9 r9 = itValue.next();
            Integer key = itKey.next();
            Iterator<RowQuery9Tuplas> itValueSet = r9.getNames().iterator();
            Set<RowQuery9Tuplas> names = new TreeSet<>(new Comparator<RowQuery9Tuplas>() {
                @Override
                public int compare(RowQuery9Tuplas o1, RowQuery9Tuplas o2) {
                    return o1.getName().compareTo(o2.getName());
                }
            });
            while (itValueSet.hasNext() && cont < quantidade) {
                names.add(itValueSet.next());
                cont++;
            }
            RowQuery9 r9Final = new RowQuery9(names);
            query9TableFinal.put(key, r9Final);
        }

        query9Table = query9TableFinal;

        if (users.size() == 0) throw new BusinessSemReview();
    }

    public static void query10 (GestReviewsModel model) {
        Map<String, Map<String, Map<String, Float>>> aux = new HashMap<>();
        Reviews r = (Reviews) model.getReviews();
        Map<String, RowReviews> auxTable = r.getMainTable();
        Businesses b = (Businesses) model.getBusinesses();
        Map<String, RowBusinesses> busTable = b.getMainTable();
        Map<String, Integer> occurBus = new HashMap<>();

        for (RowReviews row : auxTable.values()) {
            String businessId = row.getBusiness_id();
            String state = busTable.get(businessId).getState();
            String city = busTable.get(businessId).getCity();
            float clas = row.getStars();
            Map<String, Map<String, Float>> citiesState = aux.get(state);


            if (citiesState == null) citiesState = new HashMap<>();
            Map<String, Float> businessCity = citiesState.get(city);
            if (businessCity == null)  businessCity = new HashMap<>();
            Float avg = businessCity.get(businessId);
            if (avg == null) avg = 0.F;
            Integer numOcurrBus = occurBus.get(businessId);
            if (numOcurrBus == null) numOcurrBus = 0;
            numOcurrBus++;
            avg = ((avg * numOcurrBus - 1)  + row.getStars()) / numOcurrBus;
            occurBus.put(businessId, numOcurrBus);
            businessCity.put(businessId,avg);
            citiesState.put(city,businessCity);
            aux.put(state, citiesState);
        }
        query10Table = aux;
    }
}

