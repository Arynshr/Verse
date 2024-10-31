// src/data/database/connection.hpp
#ifndef DATABASE_CONNECTION_HPP
#define DATABASE_CONNECTION_HPP

#include <sqlite3.h>
#include <bits/stdc++.h>

namespace database {

// Custom exception class for database errors
class DatabaseException : public std::runtime_error {
public:
    explicit DatabaseException(const std::string& message) 
        : std::runtime_error(message) {}
};

// Statement wrapper class for RAII
class Statement {
private:
    sqlite3_stmt* stmt_;
    bool finished_;

public:
    explicit Statement(sqlite3_stmt* stmt) : stmt_(stmt), finished_(false) {}
    ~Statement() { sqlite3_finalize(stmt_); }

    // Prevent copying
    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    sqlite3_stmt* get() { return stmt_; }
    bool step() {
        int result = sqlite3_step(stmt_);
        finished_ = (result != SQLITE_ROW);
        return !finished_;
    }
    void reset() {
        sqlite3_reset(stmt_);
        finished_ = false;
    }
    bool isFinished() const { return finished_; }
};

// Main database connection class
class Connection {
private:
    sqlite3* db_;
    std::string db_path_;
    bool in_transaction_;

    // Custom deleter for smart pointer
    struct SqliteDeleter {
        void operator()(sqlite3* db) const {
            sqlite3_close(db);
        }
    };
    std::unique_ptr<sqlite3, SqliteDeleter> db_handle_;

public:
    explicit Connection(const std::string& db_path) : db_path_(db_path), in_transaction_(false) {
        sqlite3* db;
        int rc = sqlite3_open(db_path.c_str(), &db);
        
        if (rc != SQLITE_OK) {
            std::string error = "Failed to open database: ";
            error += sqlite3_errmsg(db);
            sqlite3_close(db);
            throw DatabaseException(error);
        }
        
        db_handle_.reset(db);
        
        // Enable foreign keys
        execute("PRAGMA foreign_keys = ON;");
    }

    // Prevent copying
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    // Execute a simple SQL statement
    void execute(const std::string& sql) {
        char* error_message = nullptr;
        int rc = sqlite3_exec(db_handle_.get(), sql.c_str(), nullptr, nullptr, &error_message);
        
        if (rc != SQLITE_OK) {
            std::string error = "SQL error: ";
            error += error_message;
            sqlite3_free(error_message);
            throw DatabaseException(error);
        }
    }

    // Prepare a statement
    std::unique_ptr<Statement> prepare(const std::string& sql) {
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db_handle_.get(), sql.c_str(), -1, &stmt, nullptr);
        
        if (rc != SQLITE_OK) {
            throw DatabaseException("Failed to prepare statement: " + 
                std::string(sqlite3_errmsg(db_handle_.get())));
        }
        
        return std::make_unique<Statement>(stmt);
    }

    // Transaction management
    void beginTransaction() {
        if (!in_transaction_) {
            execute("BEGIN TRANSACTION;");
            in_transaction_ = true;
        }
    }

    void commit() {
        if (in_transaction_) {
            execute("COMMIT;");
            in_transaction_ = false;
        }
    }

    void rollback() {
        if (in_transaction_) {
            execute("ROLLBACK;");
            in_transaction_ = false;
        }
    }

    // Get last inserted row ID
    int64_t lastInsertRowId() const {
        return sqlite3_last_insert_rowid(db_handle_.get());
    }

    // Get number of rows changed by last statement
    int changes() const {
        return sqlite3_changes(db_handle_.get());
    }

    // Execute with callback for each row
    void executeWithCallback(
        const std::string& sql,
        std::function<void(sqlite3_stmt*)> row_callback
    ) {
        auto stmt = prepare(sql);
        while (stmt->step()) {
            row_callback(stmt->get());
        }
    }

    // Transaction RAII wrapper
    class Transaction {
    private:
        Connection& conn_;
        bool committed_;

    public:
        explicit Transaction(Connection& conn) : conn_(conn), committed_(false) {
            conn_.beginTransaction();
        }

        ~Transaction() {
            if (!committed_) {
                conn_.rollback();
            }
        }

        void commit() {
            conn_.commit();
            committed_ = true;
        }

        void rollback() {
            conn_.rollback();
            committed_ = true;
        }
    };
};

} // namespace database

#endif // DATABASE_CONNECTION_HPP
