import java.sql.*;

public class DBManager {
    static final String DB_URL = "jdbc:mysql://localhost/moviedb?useSSL=false"; 
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String USER = "root"; 
    static final String PASSWORD = "sharvari!13";

    private Connection conn;

    public DBManager() 
    {
        try {
            Class.forName(JDBC_DRIVER);
            this.conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
        } catch (Exception e) {
            e.printStackTrace();
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

    public boolean doUpdateQuery(Statement stmt, String query) {
        boolean status = false;

        try {
            status = stmt.execute(query);
        } catch (SQLException se) {
            se.printStackTrace();
            System.exit(1);
        }

        return status;
    }

    public void closeResultSet(ResultSet rs) {
        try {
            rs.close();
        } catch (SQLException se) {
            se.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void closeStatement(Statement stmt) {
        try {
            stmt.close();
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
        }
    }

    public void closeConnection() {
        try {
            this.conn.close();
        } catch (SQLException se) {
            se.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (conn != null)
                   this.conn.close();
            } catch (SQLException se3) {
                se3.printStackTrace();
            }
        }
    } 
}
