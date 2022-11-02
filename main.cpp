#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "db.h"
#include "parsing.h"
#include "query.h"


int main(int argc, char const *argv[]) {
    const char *db_path = "students.bin";
    database_t db;
    db_init(&db);
    db_load(&db, db_path);
    char commande[256] = "";//stocks the commands entred in the terminal
    pid_t pere = fork();
    if (pere>0){
        wait(NULL);
        pid_t p_select = fork();
        if (p_select >0){
            wait(NULL);
            pid_t p_insert = fork();
            if (p_insert>0){
                wait(nullptr);
                pid_t p_update = fork();
                if (p_update >0){

                }else{

                }

            }else{

            }

        }else{

        }



    }
    else{

    }
    db_save(&db, db_path);
    printf("Bye bye!\n");
    return 0;
}