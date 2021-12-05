public class Application {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver"; 
    public static void main(String[] args) {
        DBManager dbManager = new DBManager();
        MovieService movieService = new MovieService(dbManager);

        try {
        Class.forName(JDBC_DRIVER); 
        movieService.getAllMovies();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }    
}
