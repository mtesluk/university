package currency;

import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;

public class DatabaseHandler {
	private Connection conn = null;
	String url = "jdbc:sqlite:C://sqlite/data.db";
	
	public void connect() {
		try {
			conn = DriverManager.getConnection(url);
		} catch (SQLException e) {
			System.out.println(e.getMessage());
		}
	}
	
	public void disconnect() {
		try {
			if (conn != null) {
				conn.close();
			}
		} catch (SQLException ex) {
			System.out.println(ex.getMessage());
		}
	}
 
   
	public void createNewTableIfNotExist(String fileName) {
		String sql = "CREATE TABLE IF NOT EXISTS " + fileName + " (\n"
               + "	id integer PRIMARY KEY,\n"
               + "	USD_bid real NOT NULL,\n"
               + "	USD_ask real NOT NULL,\n"
               + "	EUR_bid real NOT NULL,\n"
               + "	EUR_ask real NOT NULL,\n"
               + "	GBP_bid real NOT NULL,\n"
               + "	GBP_ask real NOT NULL,\n"
               + "	CHF_bid real NOT NULL,\n"
               + "	CHF_ask real NOT NULL,\n"
               + "	AUD_bid real NOT NULL,\n"
               + "	AUD_ask real NOT NULL,\n"
               + "	date text NOT NULL"
               + ");";

		Statement stmt = null;
		try {
			stmt = conn.createStatement();
		} catch (SQLException ex) {
			System.out.println(ex.getMessage());
		} finally {
			try {
				stmt.execute(sql);
			} catch (SQLException ex) {
				System.out.println(ex.getMessage());
			}
		}

	}
	
	public void insert(String fileName, String date, HashMap<String, ArrayList<Double>> data) {
        String sql = "INSERT INTO " + fileName + "(USD_bid,USD_ask,EUR_bid,EUR_ask,GBP_bid,GBP_ask,CHF_bid,CHF_ask,AUD_bid,AUD_ask,date) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setDouble(1, data.get("USD").get(0));
            pstmt.setDouble(2, data.get("USD").get(1));
            pstmt.setDouble(3, data.get("EUR").get(0));
            pstmt.setDouble(4, data.get("EUR").get(1));
            pstmt.setDouble(5, data.get("GBP").get(0));
            pstmt.setDouble(6, data.get("GBP").get(1));
            pstmt.setDouble(7, data.get("CHF").get(0));
            pstmt.setDouble(8, data.get("CHF").get(1));
            pstmt.setDouble(9, data.get("AUD").get(0));
            pstmt.setDouble(10, data.get("AUD").get(1));
            pstmt.setString(11, date);
            pstmt.executeUpdate();
            System.out.println("INFO: Data has been insert to db");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            System.out.println("ERROR: Did not insert data");
        }
    }
	
	public void delete(String fileName, String date) {
        String sql = "DELETE FROM " + fileName + " WHERE date = '" + date + "'";

        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

	public boolean ifExistsRow(String fileName, String queryName, String date) {
		String sql = "SELECT " + queryName + " FROM " + fileName;
        ArrayList<String> query = new ArrayList<String>();

        try (Statement stmt = conn.createStatement();
            ResultSet rs  = stmt.executeQuery(sql)) {
        	while (rs.next()) {
        		final String row = rs.getString(queryName);
            	query.add(row);
                if (query.contains(date)) {
                	return true;
                }
        	}
        }
        catch (SQLException e) {
               System.out.println(e.getMessage());
               return true;
           }
        return false;
	}

	public ArrayList<String> selectAll(String fileName, String queryName){
        String sql = "SELECT " + queryName + " FROM " + fileName;
        ArrayList<String> query = new ArrayList<String>();
        
        try (Statement stmt = conn.createStatement();
             ResultSet rs  = stmt.executeQuery(sql)) {
            while (rs.next()) {
            	query.add(rs.getString(queryName));
            }
        } catch (SQLException e) {
        	System.out.println("ERROR: Did not select all data");
            System.out.println(e.getMessage());
        }

        return query;
    }
	
	public HashMap<String, ArrayList<Double>> selectRow(String fileName, String queryName, String data){
        String sql = "SELECT * FROM " + fileName + " WHERE " + queryName + " = '" + data + "'";
        ArrayList<Double> query = new ArrayList<Double>();
        HashMap<String, ArrayList<Double>> ratesMap = new HashMap<String, ArrayList<Double>>();
        try (Statement stmt = conn.createStatement();
             ResultSet rs  = stmt.executeQuery(sql)) {
            
            while (rs.next()) {
            	Double row = rs.getDouble("USD_bid");
            	query.add(row);
            	row = rs.getDouble("USD_ask");
            	query.add(row);
            	ratesMap.put("USD", new ArrayList<Double>(query));
            	query.clear();
            	
            	row = rs.getDouble("EUR_bid");
            	query.add(row);
            	row = rs.getDouble("EUR_ask");
            	query.add(row);
            	ratesMap.put("EUR", new ArrayList<Double>(query));
            	query.clear();
            	
            	row = rs.getDouble("GBP_bid");
            	query.add(row);
            	row = rs.getDouble("GBP_ask");
            	query.add(row);
            	ratesMap.put("GBP", new ArrayList<Double>(query));
            	query.clear();
            	
            	row = rs.getDouble("CHF_bid");
            	query.add(row);
            	row = rs.getDouble("CHF_ask");
            	query.add(row);
            	ratesMap.put("CHF", new ArrayList<Double>(query));
            	query.clear();
            	
            	row = rs.getDouble("AUD_ask");
            	query.add(row);
            	row = rs.getDouble("AUD_ask");
            	query.add(row);
            	ratesMap.put("AUD", new ArrayList<Double>(query));
            	query.clear();

                return ratesMap;
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return ratesMap;
    }
}
