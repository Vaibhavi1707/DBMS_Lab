import java.sql.*;

public class MovieService {
    private DBManager dbManager;

    public MovieService(DBManager dbManager) {
        this.dbManager = dbManager;
    }

    public void getMovies(String criteria) {
        Statement stmt = dbManager.issueStatement();

        String query = "select name, year_of_release, length_in_min, " + 
                        "language, description, genre," + 
                        "concat(director.fname, concat(' ', director.lname)) as director " +  
                        "from movie, director where movie.directed_by = director.dir_id and " + criteria;
        
        ResultSet rs = dbManager.findQueryResults(stmt, query);
    
        this.viewMovies(rs);

        dbManager.closeResultSet(rs);
        dbManager.closeStatement(stmt);
    } 

    public void addMovie(String movieName, int yearOfRelease, int lengthInMin, String language, String description,
        String genre, String directorName) 
    {
        Statement stmt = dbManager.issueStatement();

        String getDirectorIdQuery = "select dir_id from director where concat(fname, concat('$', lname)) = '" + directorName + "'";

        ResultSet dir_rs = dbManager.findQueryResults(stmt, getDirectorIdQuery);

        
//  java -classpath "mysql-connector-java-8.0.18.jar:." Application MobileService DBManager
        String query = "";
        try {
            if (! dir_rs.isBeforeFirst()) {
                System.out.println("No such director");
                return;
            }
            dir_rs.next();
            query = "insert into movie(name, year_of_release, length_in_min, language, description, genre, directed_by) "
            + "VALUES('"+ movieName + "', " + Integer.toString(yearOfRelease) + ", " 
            + Integer.toString(lengthInMin) + ", '" + language + "', '" 
            + description + "', '" + genre + "', " + Integer.toString(dir_rs.getInt("dir_id")) + ")" ;
        
            dir_rs.close();
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        dbManager.doUpdateQuery(stmt, query);

        dbManager.closeStatement(stmt);
    }

    public void updateMovie(int movieId, String movieName, int yearOfRelease, int lengthInMin, String language, String description,
        String genre, String directorName) 
    {
        Statement stmt = dbManager.issueStatement();

        String getDirectorIdQuery = "select dir_id from director where concat(fname, concat('$', lname)) = '" + directorName + "'";

        ResultSet dir_rs = dbManager.findQueryResults(stmt, getDirectorIdQuery);
        
//  java -classpath "mysql-connector-java-8.0.18.jar:." Application MobileService DBManager
        String query = "";
        try {
            if (! dir_rs.isBeforeFirst()) {
                System.out.println("No such director");
                return;
            }
            dir_rs.next();
            query = "update movie "
            + "set name = '"+ movieName + "', year_of_release = " + Integer.toString(yearOfRelease) + ", length_in_min = " 
            + Integer.toString(lengthInMin) + ", language = '" + language + "', description = '" 
            + description + "', genre = '" + genre + "', directed_by = " + Integer.toString(dir_rs.getInt("dir_id")) 
            + " where movie_id = " +  Integer.toString(movieId);
        
            dir_rs.close();
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        dbManager.doUpdateQuery(stmt, query);

        dbManager.closeStatement(stmt);
    }

    public void deleteMovieByName(String movieName) 
    {
        Statement stmt = dbManager.issueStatement();

//  java -classpath "mysql-connector-java-8.0.18.jar:." Application MobileService DBManager
        String query = "delete from movie where name = '" + movieName + "'";

        dbManager.doUpdateQuery(stmt, query);

        dbManager.closeStatement(stmt);
    }

    public void viewMovies(ResultSet rs) {
        try {
            if (!rs.next()) {
                System.out.println("No such movie found.");
                return;
            }

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
