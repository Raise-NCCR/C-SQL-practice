#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>

int main(){
    MYSQL *conn = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char sql[255];
    char *sql_server = "localhost";
    char *user = "root";
    char *passwd = "****;
    char *db_name = "test";
    memset(&sql[0], 0, sizeof(sql));

    conn = mysql_init(NULL);
    if (!mysql_real_connect(
        conn, sql_server, user, passwd, db_name, 0, NULL, 0)){
            fprintf(stderr, "%s", "sql connection error");
            exit(EXIT_FAILURE);
    }

    /*snprintf(&sql[0], sizeof(sql) - 1, "insert into tb_test(id, name) values(2, 'hoge')");
    if (mysql_query(conn, &sql[0])){
        fprintf(stderr, "query error");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }*/

    snprintf(&sql[0], sizeof(sql) - 1, "select * from tb_test");
    if (mysql_query(conn, &sql[0])){
        fprintf(stderr, "query error");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);
    FILE *fp = fopen("output.json", "w");
    if (fp == NULL){
        fprintf(stderr, "file error");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "[\n");
    while((row = mysql_fetch_row(res)) != NULL){
        fprintf(fp, "{\"id\":\"%d\",\"name\":\"%s\"}\n", atoi(row[0]), row[1]);
    }
    fprintf(fp, "]\n");

    fclose(fp);
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
