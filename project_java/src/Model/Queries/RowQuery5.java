package Model.Queries;

import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.io.Serializable;

public class RowQuery5 implements Serializable {
    Set<String>businessesName;
    int quantidade;

    public Set<String> getBusinessesName() {
        return businessesName;
    }

    public void setBusinessesName(Set<String> businessesName) {
        this.businessesName = businessesName;
    }

    public int getQuantidade() {
        return quantidade;
    }

    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }

    public RowQuery5(){
        businessesName = new TreeSet<>();
    }

    public RowQuery5(Set<String> businessesName, int quantidade) {
        this.businessesName = businessesName;
        this.quantidade = quantidade;
    }

    @Override
    public String toString() {
        StringBuilder names = new StringBuilder();
        names.append("Quantidade " + quantidade + ":\n");
        Iterator<String> it = businessesName.iterator();
        while(it.hasNext()){
            names.append("> " + it.next() + "\n");
        }
        return names.toString();
    }
}
