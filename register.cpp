#include <iostream>
#include <mysql/mysql.h>

using namespace std;

int main() {
    cout << "Content-type: text/html\n\n";
    cout << "<html><head><title>Users List</title></head><body>";
    cout << "<h1>Registered Users</h1>";
    
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(0);
    if (!conn) {
        cout << "<p>MySQL initialization failed.</p></body></html>";
        return 1;
    }

    // Connect to database
    if (!mysql_real_connect(conn, "localhost", "messi", "Xavier@1234", "simpledb", 0, NULL, 0)) {
        cout << "<p>Connection Failed: " << mysql_error(conn) << "</p></body></html>";
        return 1;
    }

    // Query the users table
    if (mysql_query(conn, "SELECT id, username, password FROM users")) {
        cout << "<p>Query Failed: " << mysql_error(conn) << "</p></body></html>";
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);
    if (!res) {
        cout << "<p>No users found.</p></body></html>";
        mysql_close(conn);
        return 1;
    }

    cout << "<table border='1' cellpadding='5'><tr><th>ID</th><th>Username</th><th>Password</th></tr>";
    while ((row = mysql_fetch_row(res)) != NULL) {
        cout << "<tr><td>" << row[0] << "</td><td>" << row[1] << "</td><td>" << row[2] << "</td></tr>";
    }
    cout << "</table>";

    mysql_free_result(res);
    mysql_close(conn);

    cout << "</body></html>";
    return 0;
}
