#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "db.h"
#include "parsing.h"
#include "query.h"
#include <time.h>
#define READ 0
#define WRITE 1
#include <signal.h>

void handler(int signal_r){
    if (signal_r == SIGINT){
    std::cout<<"ctrl+c was pressed"<<std::endl;
        exit(0);

    }
}
int main(int argc, char const *argv[]) {
    const char *db_path = "students.bin";
    //const char *db_path = argv[1];
    database_t db;
    db_init(&db);
    std::cout<<"Loading the database..."<<std::endl;
    db_load(&db, db_path);
    std::cout<<"Done"<<std::endl;
    char commande[256] = "";//stocks the commands entred in the terminal
    int maindelete[2];
    int mainupdate[2];
    int mainselect[2];
    int maininsert[2];
    pipe(mainselect);
    pipe(maindelete);
    pipe(maininsert);
    pipe(mainupdate);
    if (pid_t p_delete = fork(); p_delete==0){
        //the delete process
        wait(nullptr);
        std::string buffer;
        close(maindelete[WRITE]);
        read(maindelete[READ],&buffer, sizeof(buffer));
        if (buffer == "delete"){
            char field[256];
            char value[256];
            read(maindelete[READ],&field, sizeof(field));
            read(maindelete[READ],&value, sizeof(value));
            close(maindelete[READ]);
            delete_query(&db,field,value);
        }}

    else if (pid_t p_select = fork();p_select == 0){
        //the select process
        wait(nullptr);
        std::string buffer;
        close(mainselect[WRITE]);
        read(mainselect[READ],&buffer, sizeof(buffer));
        if (buffer == "select"){
            char field[256];
            char value[256];
            read(mainselect[READ],&field, sizeof(field));
            read(mainselect[READ],&value, sizeof(value));
            close(mainselect[READ]);
            select_query(&db,field,value);
        }}
    else if (pid_t p_insert = fork();p_insert==0){
            //the insert process
        wait(nullptr);
        std::string buffer;
        close(maininsert[WRITE]);
        read(maininsert[READ],&buffer, sizeof(buffer));
        if (buffer == "insert") {
            char fname[256];
            char lname[256];
            unsigned id;
            char section[256];
            struct tm birthday;
            read(maininsert[READ],&fname,sizeof(fname));
            read(maininsert[READ],&lname,sizeof(lname));
            read(maininsert[READ],&id,sizeof(id));
            read(maininsert[READ],&section, sizeof(section));
            read(maininsert[READ],&birthday, sizeof(birthday));
            close(maininsert[READ]);
            insert_query(&db,fname,lname,id,section,birthday);

        }}

    else if (pid_t p_update = fork();p_update ==0){
            //the update process
            wait(nullptr);
        std::string buffer;
        close(mainupdate[WRITE]);
        read(mainupdate[READ],&buffer, sizeof(buffer));
        if (buffer == "update"){
            char field[256];
            char value[256]; char changed_field[256]; char updated_value[256];
            read(mainupdate[READ],&field, sizeof(field));
            read(mainupdate[READ],&value, sizeof(value));
            read(mainupdate[READ],&changed_field, sizeof(changed_field));
            read(mainupdate[READ],&updated_value, sizeof(updated_value));
            close(mainupdate[READ]);
            update_query(&db,field,value,changed_field,updated_value); }
        }
    else{//the main process
        if (signal(SIGINT,handler)){
            db_save(&db, db_path);
            printf("Bye bye!\n");
        }
        while (fgets(commande, sizeof(commande),stdin) != NULL){
            std::string query = commande;// stocks the query command
            query.resize(6);
            if (query == "select"){
                close(mainselect[READ]);
                char value[256];
                char field[256];
                parse_selectors(commande,field,value);// parse the command and send it to the concerned child via an anonymous pipe
                write(mainselect[WRITE],&query, sizeof(query));
                write(mainselect[WRITE],&field, sizeof(field));
                write(mainselect[WRITE],&value, sizeof(value));
                close(mainselect[WRITE]);
            }
            else if(query == "update"){
                close(mainupdate[READ]);
                char value[256];
                char field[256];
                char updated_value[256];
                char changed_field[256];
                parse_update(commande,field,value,changed_field,updated_value);
                write(mainupdate[WRITE],&query, sizeof(query));
                write(mainupdate[WRITE],&field, sizeof(field));
                write(mainupdate[WRITE],&value, sizeof(value));
                write(mainupdate[WRITE],&changed_field, sizeof(changed_field));
                write(mainupdate[WRITE],&updated_value, sizeof(updated_value));
                close(mainupdate[WRITE]);
            }
            else if (query == "delete"){
                close(maindelete[READ]);
                char value[256];
                char field[256];
                parse_selectors(commande,field,value);// parse the command and send it to the concerned child via an anonymous pipe
                write(maindelete[WRITE],&query, sizeof(query));
                write(maindelete[WRITE],&field, sizeof(field));
                write(maindelete[WRITE],&value, sizeof(value));
                close(maindelete[WRITE]);
            }
            else if (query == "insert"){
                close(maininsert[READ]);
                char fname[256];
                char lname[256];
                unsigned id;
                char section[256];
                struct tm birthday;
                parse_insert(commande, fname, lname, &id, section, &birthday);
                write(maininsert[WRITE],&query, sizeof(query));
                write(maininsert[WRITE],&fname, sizeof(fname));
                write(maininsert[WRITE],&lname, sizeof(lname));
                write(maininsert[WRITE],&id, sizeof(id));
                write(maininsert[WRITE],&section, sizeof(section));
                write(maininsert[WRITE],&birthday, sizeof(birthday));
                close(maininsert[WRITE]);

            }
        }

        }


    while (wait(NULL) != -1|| errno != ECHILD  ){
        printf("waited for child ");
    }
}
