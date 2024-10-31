#include <bits/stdc++.h>
#include <sqlite3.h>

void executeQuery(sqlite3* db, const std::string& query) {
    char* errorMessage;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Operation completed successfully." << std::endl;
    }
}

// Function to set up the test table
void setupTable(sqlite3* db) {
    std::string createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS playlist (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            artist TEXT NOT NULL,
            album TEXT,
            duration INTEGER
        );
    )";
    executeQuery(db, createTableQuery);
}

// Function to test creating a record
void testCreate(sqlite3* db) {
    std::string insertQuery = R"(
        INSERT INTO playlist (title, artist, album, duration)
        VALUES ('Song A', 'Artist A', 'Album A', 240);
    )";
    executeQuery(db, insertQuery);
}

// Function to test reading records
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    std::cout << std::endl;
    return 0;
}

void testRead(sqlite3* db) {
    std::string selectQuery = "SELECT * FROM playlist;";
    char* errorMessage;
    int result = sqlite3_exec(db, selectQuery.c_str(), callback, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Read operation completed successfully." << std::endl;
    }
}

// Function to test updating a record
void testUpdate(sqlite3* db) {
    std::string updateQuery = "UPDATE playlist SET title = 'Updated Song A' WHERE id = 1;";
    executeQuery(db, updateQuery);
}

// Function to test deleting a record
void testDelete(sqlite3* db) {
    std::string deleteQuery = "DELETE FROM playlist WHERE id = 1;";
    executeQuery(db, deleteQuery);
}

int main() {
    sqlite3* db;
    int exit = sqlite3_open("test_database.db", &db);

    if (exit) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    } else {
        std::cout << "Database opened successfully!" << std::endl;
    }

    setupTable(db);
    testCreate(db);
    testRead(db);  // Should print the inserted record
    testUpdate(db);
    testRead(db);  // Should print the updated record
    testDelete(db);
    testRead(db);  // Should print nothing if deletion was successful

    sqlite3_close(db);
    return 0;
}
