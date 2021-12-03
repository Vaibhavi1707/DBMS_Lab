import java.sql.*;

public class JdbcDemo {
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/moviedb?useSSL=false";

    static final String USER = "root";
    static final String PASSWORD = "sharvari!13";

    public static void main(String[] args) {
        Statement stmt = null;
        Connection conn = null;
        try {
            Class.forName(JDBC_DRIVER);

            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            stmt = conn.createStatement();

            // STEP 3: Query to DB
            String sql;
            sql = "SELECT fname, lname from director";
            ResultSet rs = stmt.executeQuery(sql);

            // STEP 4: Extract data from the result set
            while (rs.next()) {
                String fname = rs.getString("fname");
                String lname = rs.getString("lname");

                System.out.println("fname: " + fname);
                System.out.println("lname: " + lname);
            }

            // STEP 5: Clean up environment
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

            // }
        }

        System.out.println("End of code");
    }
}