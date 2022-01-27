package Model.Catalogs;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;
import java.io.Serializable;

public class SavedUsers implements Parser, Serializable {
	private Users users;
	public SavedUsers(String filename) throws IOException, LoadInfoException {
		this.users = new Users();
		this.users = (Users) parser(filename);
	}

	public Catalog parser(String filename) throws IOException, LoadInfoException {
		Users parsed = this.users;
		Map<String, RowUsers> parsedTable = parsed.getMainTable();

		File f = new File(filename);
		BufferedReader br = new BufferedReader(new FileReader(f));
		String str;
		br.readLine();

		while ((str = br.readLine()) != null) {
			String[] data = str.split(";", 3);

			if (data.length == 3) {
				String[] friends = data[2].split(",");


				List<String> friendsTmp = new ArrayList<>();
				//friendsTmp = Arrays.asList(friends.clone());

				RowUsers tmp = new RowUsers(data[0], data[1], friendsTmp);
				parsedTable.put(data[0], tmp);
			}

		}

		parsed.setMainTable(parsedTable);
		br.close();
		return parsed;
	}

	public Users getUsers() {
		return this.users;
	}
}
