/**
 Example showing correct usage of sqlite3 API commands bind, prepare, step
 Gary "ChunkyKs" Briggs <chunky@icculus.org>

 gcc -o sqlite3_example_bind sqlite3_example_bind.c -lsqlite3 
*/


#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


void check(sqlite3 *db, int rc, int status, char *exec_errmsg, unsigned char abrt ){

	if(status != rc) {

		fprintf(stderr, "Error creating table (%i): %s\n", rc, exec_errmsg);

		if(abrt){		

			sqlite3_free(exec_errmsg);
			sqlite3_close(db);
			exit(1);
		}
	}
	else if(!abrt){

		printf("\nsuccess!!\n");
	
	}
}

int init(sqlite3 *db){

	int rc;
	char *exec_errmsg;
	const char create_sql[] = "CREATE TABLE test ("
			"id INTEGER PRIMARY KEY,"
			"foo REAL,"
			"bar TEXT"
			")";
	// Use exec to run simple statements that can only fail/succeed
	rc = sqlite3_exec(db, create_sql, NULL, NULL, &exec_errmsg);

	check(db, SQLITE_OK, rc, exec_errmsg,1);

	return rc;
}


int main() {

	// Create an in-memory database
	const char dbname[] = ":memory:";

	// Actual database handle
	sqlite3 *db = NULL;


	/* Note the question marks. No quoting or anything,
	    just put a ? where you'd otherwise put the contents of
	    mysql_real_escape_string */

	const char insert_sql[] = "INSERT INTO test (foo, bar) VALUES (?,?)";
	const char select_sql[] = "SELECT foo, bar FROM test WHERE id=?";

	// For the insert and select, we will prepare statements
	sqlite3_stmt *insert_stmt = NULL;
	sqlite3_stmt *select_stmt = NULL;

	// SQLite return value
	int rc;

	// Open the database
	rc = sqlite3_open(dbname, &db);

	check(db, SQLITE_OK, rc,(char *) sqlite3_errmsg(db) ,1);

	// SQLite exec returns errors with this
	char *exec_errmsg;

	rc = init(db);
	
	// Prepare the two statements we need to prepare
	//  The last parameter, dbend, is used if you have multiple sql statements in one string

	rc = sqlite3_prepare_v2(db, insert_sql, -1, &insert_stmt, NULL);// db, sql, stmt, string[] sql query multiple

	check(db, SQLITE_OK, rc, exec_errmsg,1);

	rc = sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, NULL);

	check(db, SQLITE_OK, rc, exec_errmsg,1);

	// Now actually bind the values (1-indexed)
	double realvalue = 3.14159;
	rc = sqlite3_bind_double(insert_stmt, 1, realvalue);
	// bind dei dati nella query e prepara lo statement

	check(db, SQLITE_OK, rc, exec_errmsg,1);

	const char injectionattack[] =  "Chunkys'; DROP TABLE test;";
	// The NULL is "Don't attempt to free() the value when it's bound", since it's on the stack here
	rc = sqlite3_bind_text(insert_stmt, 2, injectionattack, sizeof(injectionattack), NULL);

	check(db, SQLITE_OK, rc, exec_errmsg,1);

	// Actually do the insert!
	rc = sqlite3_step(insert_stmt);

	check(db, SQLITE_DONE, rc, exec_errmsg,0);

	// Now attempt to get that row out
	sqlite3_int64 id = sqlite3_last_insert_rowid(db);
	sqlite3_bind_int64(select_stmt, 1, id);

	// This is your standard pattern
	while(SQLITE_ROW == (rc = sqlite3_step(select_stmt))) {

		int col;

		printf("Found row\n");

		for( col=0 ; col < sqlite3_column_count(select_stmt) ; col++ ) {

			// Note that by using sqlite3_column_text, sqlite will coerce the value into a string
			printf("\tColumn %s(%i): '%s'\n",
				sqlite3_column_name( select_stmt, col ), col,
				sqlite3_column_text( select_stmt, col ) );//recupero dati riga per riga
		}
	}

	check(db, SQLITE_DONE, rc, exec_errmsg,0);

	sqlite3_finalize(insert_stmt);
	sqlite3_finalize(select_stmt);

	sqlite3_close(db);

	return 0;
}

