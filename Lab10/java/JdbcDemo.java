import java.sql.*;

public class JdbcDemo {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver"; // remove
    static final String DB_URL = "jdbc:mysql://localhost/moviedb?useSSL=false"; // remove

    static final String USER = "root"; // remove
    static final String PASSWORD = "sharvari!13"; // remove

    private Connection connectDB() 
    {
        Connection conn = null;
        
        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        return conn;
    }

    private Statement issueStatement(Connection conn) {
        Statement stmt = null;

        try {
            stmt = conn.createStatement();
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        return stmt;
    }

    private ResultSet findQueryResults(Statement stmt, String query) {
        ResultSet rs = null;

        try {
            rs = stmt.executeQuery(query);
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        return rs;
    }

    private void viewMovies(ResultSet rs) {
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

    private void closeConnection(Connection conn, Statement stmt, ResultSet rs) {
        try {
            rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException se) {
            se.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null)
                    stmt.close();
            } catch (SQLException se2) {
                se2.printStackTrace();
            }

            try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se3) {
                se3.printStackTrace();
            }
        }
    }

    private void getAllMovies(Connection conn) {
        Statement stmt = issueStatement(conn);
        String query = "select name, year_of_release, length_in_min, " + 
                        "language, description, genre," + 
                        "concat(director.fname, concat(' ', director.lname)) as director " +  
                        "from movie, director where movie.directed_by = director.dir_id";
        ResultSet rs = findQueryResults(stmt, query);
    
        viewMovies(rs);

        closeConnection(conn, stmt, rs);
    }

    public static void main(String[] args) {
        JdbcDemo demo = new JdbcDemo();
        try {
        Class.forName(JDBC_DRIVER); 

        Connection conn = demo.connectDB(); 

        demo.getAllMovies(conn);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}