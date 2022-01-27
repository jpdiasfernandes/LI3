package Model.Queries.Query9;

import java.util.Comparator;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;
import java.io.Serializable;

public class RowQuery9 implements Serializable {
    Set<RowQuery9Tuplas> names = new TreeSet<>(new Comparator<RowQuery9Tuplas>() {
        @Override
        public int compare(RowQuery9Tuplas o1, RowQuery9Tuplas o2) {
            return o1.getName().compareTo(o2.getName());
        }
    });
    public RowQuery9() {
    }
    public RowQuery9(Set<RowQuery9Tuplas> names) {
        this.names = names;
    }

    public Set<RowQuery9Tuplas> getNames() {
        return names;
    }

    public void setNames(Set<RowQuery9Tuplas> names) {
        this.names = names;
    }

    @Override
    public String toString() {
       StringBuilder str = new StringBuilder();
       Iterator<RowQuery9Tuplas> it = names.iterator();
       while(it.hasNext()){
           RowQuery9Tuplas tupla =  new RowQuery9Tuplas(it.next());
           str.append("> UserName: " + tupla.getName() + " » Stars: " + tupla.getStars() + "\n");
       }
       return str.toString();
    }
}
