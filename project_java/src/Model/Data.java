package Model;

import Model.Catalogs.Businesses;
import Model.Catalogs.RowUsers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.io.FileOutputStream;
import java.io.BufferedOutputStream;
import java.io.ObjectOutputStream;
import java.util.Map;


public class Data implements Serializable {
    public static final String delimiter = ";";

    public static void read(String csvFile) {
        try {
            File file = new File(csvFile);
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line = "";
            String[] tempArr;
            while((line = br.readLine()) != null) {
                tempArr = line.split(delimiter);
                for(String tempStr : tempArr) {
                    System.out.print(tempStr + "");
                }
                System.out.println();
            }
            br.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    public void readRowUsers(String filename) throws IOException {

        int invalid_rows = 0;
        RowUsers u = new RowUsers();
        BufferedReader buf;
        String row;
        buf = new BufferedReader(new FileReader (filename));

        while((row = buf.readLine()) != null) {
            String[] splitRow = row.split(";");
            try {
                String user_id = splitRow[0];
                String name = splitRow[1];
               // for (Map.Entry<String, Integer> friends : u.getFriends().entrySet()) {
                //    String key = friends.getKey();
                 //   Integer value = friends.getValue();
                //}

                //if (u.getFriends().containsKey(u.getName())) {
                    // completar

                //} else {
                 //   invalid_rows++;
                //}
            }

                catch(NumberFormatException | ArrayIndexOutOfBoundsException e) {
                    invalid_rows++;
                }
        }
    }




    public void save(String filename) throws IOException{
        FileOutputStream fos = new FileOutputStream(filename);
        BufferedOutputStream bos = new BufferedOutputStream(fos);
        ObjectOutputStream oos = new ObjectOutputStream(bos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }
}
