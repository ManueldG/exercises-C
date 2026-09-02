
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DB_NAME "db.sql"

//#define SQL_STATEMENT "CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT,name TEXT, age INTEGER,created_date DATE DEFAULT CURRENT_TIMESTAMP);"

#define SQL_STATEMENT "INSERT INTO users (name,age) VALUES ('Mario',300);"

//#define SQL_STATEMENT "SELECT * FROM users;"
//#define SQL_STATEMENT ""

/*
 name TEXT NOT NULL,
 email TEXT UNIQUE,
 age INTEGER,

 created_date DATE DEFAULT 

CURRENT_TIMESTAMP

);


*/
#define MAX_ROWS 1024

typedef struct {

	int id;
	char *name;
	int age;
	char *timestamp;

} row_t;

typedef struct {

	row_t* rows;

	int num_rows;
	int max_rows;

} read_result_t;

int sql_read_callback( void* result, int num_columns, char** values, char** labels ){
	
	read_result_t* read_result = (read_result_t*)result;

	row_t* row = malloc( sizeof( row_t ) );

	row->id = atoi( values[ 0 ] );
//	printf("atoi\n%s",(char *) values[ 1 ]);

	char *name;
	name = calloc(sizeof(char),strlen(values[1]));	
	strcpy(name, values[ 1 ] );
	row->name = name;

//	printf("\n%s %s\n",name,row->name);

	row->age = atoi(values[ 2 ]);
	row->timestamp = calloc(sizeof(char),strlen(values[3]));
	strcpy(row->timestamp , values[ 3 ] );

	if( read_result->num_rows == read_result->max_rows ) {
		free( row );

		return 1;

	}

	int index = read_result->num_rows;

	read_result->rows[ index ] = *row;

	read_result->num_rows++;

	return 0;

}

int main( void ){

//	printf("\nbegin\n");
	sqlite3* db;

//	printf("open");
	int ret = sqlite3_open( DB_NAME, &db );
	if( ret ) {

		fprintf( stderr, "Failed to open database - error: %s\n", sqlite3_errmsg( db ) );

		exit( EXIT_FAILURE );

	}

	char* sql_statement = SQL_STATEMENT;

	char* err_msg = NULL;

	read_result_t read_result;

	read_result.max_rows = MAX_ROWS;

	read_result.num_rows = 0;

	read_result.rows = malloc( MAX_ROWS * sizeof( row_t ) );

	ret = sqlite3_exec(db,sql_statement,sql_read_callback,&read_result,&err_msg);

	printf("\n%d %d\n",ret,SQLITE_ROW);
	if( ret != SQLITE_OK ) {

		fprintf(stderr, "Error executing: %s\n", err_msg );

		sqlite3_free( err_msg );

	}

	else {

		// Use data

		row_t* tmp ; 
		tmp = read_result.rows;
 		
		printf("\n Elementi: %d \n",read_result.num_rows);
		for(int i = 0 ; i < read_result.num_rows ; i++ ){

			printf("\nid %d name:%s eta\'%d data %s",tmp[i].id,tmp[i].name,tmp[i].age,tmp[i].timestamp  );	

			printf("\n-\n");

		}				
	}


free( read_result.rows );
sqlite3_close( db );

return 0;
}
