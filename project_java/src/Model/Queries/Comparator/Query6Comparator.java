package Model.Queries.Comparator;

import Model.Queries.RowQuery6;

import java.util.Comparator;

import java.io.Serializable;


public class Query6Comparator implements Comparator<RowQuery6>, Serializable {
    public int compare(RowQuery6 t1, RowQuery6 t2) {

        if (t1.getNumReviews() == t2.getNumReviews())
            return t1.getBusinessId().compareTo(t2.getBusinessId());


        else
            return t2.getNumReviews() - t1.getNumReviews();

    }
}
