import java.sql.*;

public class MovieService {
    private DBManager dbManager;

    public MovieService(DBManager dbManager) {
        this.dbManager = dbManager;
    }

    public void getAllMovies() {
        Statement stmt = dbManager.issueStatement();

        String query = "select name, year_of_release, length_in_min, " + 
                        "language, description, genre," + 
                        "concat(director.fname, concat(' ', director.lname)) as director " +  
                        "from movie, director where movie.directed_by = director.dir_id";
        
        ResultSet rs = dbManager.findQueryResults(stmt, query);
    
        this.viewMovies(rs);

        dbManager.closeConnection(stmt, rs);
    } 

    public void viewMovies(ResultSet rs) {
        try {
            while (rs.next()) {
                String movieName = rs.getString("name");
                int yearOfRelease = rs.getInt("year_of_release");
                int length = rs.getInt("length_in_min");
                String language = rs.getString("language");
                String description = rs.getString("description");
                String genre = rs.getString("genre");
                String director = rs.getString("director");

                System.out.println("** MOVIE DETAILS **");
                System.out.println("NAME: " + movieName);
                System.out.println("Year of release: " + Integer.toString(yearOfRelease));
                System.out.println("Length: " + Integer.toString(length));
                System.out.println("Language: " + language);
                System.out.println("Description: " + description);
                System.out.println("Genre: " + genre);
                System.out.println("Director: " + director);
                System.out.println();
                System.out.println();
            }
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }
    }
}
