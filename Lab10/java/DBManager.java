import java.sql.*;

public class DBManager {
    static final String DB_URL = "jdbc:mysql://localhost/moviedb?useSSL=false"; 

    static final String USER = "root"; 
    static final String PASSWORD = "sharvari!13";

    private Connection conn;

    public DBManager() 
    {
        try {
            this.conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }
    }

    public Statement issueStatement() {
        Statement stmt = null;

        try {
            stmt = this.conn.createStatement();
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        return stmt;
    }

    public ResultSet findQueryResults(Statement stmt, String query) {
        ResultSet rs = null;

        try {
            rs = stmt.executeQuery(query);
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        return rs;
    }

    public void closeConnection(Statement stmt, ResultSet rs) {
        try {
            rs.close();
            stmt.close();
            this.conn.close();
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
                   this.conn.close();
            } catch (SQLException se3) {
                se3.printStackTrace();
            }
        }
    }
}
