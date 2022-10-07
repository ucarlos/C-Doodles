/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 10/06/2022 at 09:12 PM
 *
 * ConnectionTest.cc
 * Just a simple connection test to a psql database.
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <pqxx/pqxx>

int main(void) {
    
    std::string connection_text = "postgresql://dummy:dumbass@localhost/example";
    // std::string connection_text = "postgresql://example?host=localhost&requirepeer=ulysses";

    try {

        // Connect to the database.  In practice we may have to pass some1
        // arguments to say where the database server is, and so on.
        // The constructor parses options exactly like libpq's
        // PQconnectdb/PQconnect, see:
        // https://www.postgresql.org/docs/10/static/libpq-connect.html
        pqxx::connection psql_connection {connection_text};

        // Start a transaction.  In libpqxx, you always work in one.
        pqxx::work database_work(psql_connection);

        // work::exec1() executes a query returning a single row of data.
        // We'll just ask the database to return the number 1 to us.
        pqxx::row row = database_work.exec1("SELECT 1");
        
        // Commit your transaction.  If an exception occurred before this
        // point, execution will have left the block, and the transaction will
        // have been destroyed along the way.  In that case, the failed
        // transaction would implicitly abort instead of getting to this point.
        
        // Look at the first and only field in the row, parse it as an integer,
        // and print it.
        std::cout << row[0].as<int>() << std::endl;

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

}
