
#include <iostream>
#include <sqlite3.h>

sqlite3* db;

void initializeDatabase() {
    int rc = sqlite3_open(":memory:", &db);
    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

void createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT);";
    char* errMsg;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void run_query(const std::string& user_input) {
    // Detect SQL injection pattern
    if (user_input.find("OR") != std::string::npos || user_input.find("value=value;") != std::string::npos) {
        std::cout << "Warning: Potential SQL injection attack detected!" << std::endl;
        return;
    }

    // Use a parameterized query to prevent SQL injection
    const char* sql = "SELECT * FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, user_input.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Process the results
        int id = sqlite3_column_int(stmt, 0);
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        std::cout << "User ID: " << id << ", Username: " << username << ", Password: " << password << std::endl;
    }

    sqlite3_finalize(stmt);
}

int main() {
    initializeDatabase();
    createTable();

    std::string user_input;
    std::cout << "Enter a username: ";
    std::cin >> user_input;

    run_query(user_input);

    sqlite3_close(db);
    return 0;
}
