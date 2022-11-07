//
// Created by Ali Bahja on 18/10/2022.
//
//
// Created by Ali Bahja on 14/10/2022.
//

#include "query.h"
#include "db.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include "utils.h"
#include <algorithm>
#include <time.h>

query_result_t insert_query(database_t *db, std::string fname, std::string lname, unsigned int id, std::string section,struct tm birthday){
    query_result_t res;
    query_result_init(&res,"insert");
    student_t newstudent;//new student to add to the db
    newstudent.id = id; newstudent.section = section;newstudent.lname = lname;newstudent.fname=fname;newstudent.birthdate = birthday;
    struct timespec now{};
    for (int i = 0;i < db->lsize; i++){
            if(student_equals(&db->data->at(i), &newstudent)){// db->data->at(i).id == id
                res.status = QUERY_FAILURE;
                clock_gettime(CLOCK_REALTIME, &now);
                res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
                return res;
            }
        }
    db_add(db,newstudent);
    clock_gettime(CLOCK_REALTIME, &now);
    res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
    log_query(&res);
    return res;
}


query_result_t select_query(database_t *db,std::string champs, std::string valeur){
    query_result_t res;
    query_result_init(&res,"select");
    struct timespec now{};
    if (champs == "fname"){
        for(int i = 0; i < db->lsize; i++){
            if (db->data->at(i).fname == valeur){
                query_result_add(&res,db->data->at(i));
            }
        }
    }
    else if(champs == "lname") {
        for (int i = 0; i < db->lsize; i++) {
            if (db->data->at(i).lname == valeur) {
                query_result_add(&res,db->data->at(i));
            }
        }
    }
    else if(champs == "section") {
        for (int i = 0; i < db->lsize; i++) {
            if (db->data->at(i).section == valeur) {
                query_result_add(&res,db->data->at(i));
            }
        }
    }
    else if(champs == "birthdate") {
        for (int i = 0; i < db->lsize; i++) {
            std::ostringstream timetm ;
            timetm << std::put_time(&db->data->at(i).birthdate,"%d-%m-%Y");
            std::string timestr = timetm.str(); //convert birthday date from tm to str and then compare them
            if ( timestr ==valeur) {
                query_result_add(&res,db->data->at(i));
            }
        }
    }
    else if (champs == "id"){
        for (int i=0; i< db->lsize;i++){
            if (std::to_string(db->data->at(i).id) == valeur){
                query_result_add(&res,db->data->at(i));
            }
        }
    }
    else{
        std::cout<<"Field chosen is wrong"<<std::endl;
        res.status = QUERY_FAILURE;
        clock_gettime(CLOCK_REALTIME, &now);
        res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
        return res;
    }
    clock_gettime(CLOCK_REALTIME, &now);
    res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
    log_query(&res);
    return res;
}
query_result_t delete_query(database_t *db,std::string champs, std::string valeur){
    query_result_t res = select_query(db,champs,valeur);
    for(int i = 0; i< res.lsize;i++){
        for (int j = 0;j<db->lsize; i++){
            if(res.students->at(i).id==db->data->at(j).id){
                db->data->erase(db->data->begin()+j);
                break;
            }

        }
    }
    struct timespec now{};
    clock_gettime(CLOCK_REALTIME, &now);
    res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
    log_query(&res);
    return res;

}

query_result_t update_query(database_t *db,std::string filtre, std::string valeur,std::string champs_modifie, std::string champs_modefiee ){
    query_result_t res = select_query(db,filtre,valeur);
    for(int i = 0; i< res.lsize;i++){
        for (int j = 0;j<db->lsize; i++){
            if(res.students->at(i).id==db->data->at(j).id){
                if (champs_modifie == "fname"){
                    db->data->at(j).fname = champs_modefiee;
                }
                else if (champs_modifie == "lname"){
                    db->data->at(j).lname = champs_modefiee;
                }
                else if (champs_modifie == "section"){
                    db->data->at(j).section = champs_modefiee;
                }
                else if (champs_modifie == "bithdate"){
                    struct tm birthdate;
                    char time[128];
                    strcpy(time,champs_modefiee.c_str());
                    strptime(time,"%d/%m/%Y",&birthdate);
                    db->data->at(j).birthdate = birthdate;
                }
            }

        }
    }
    struct timespec now{};
    clock_gettime(CLOCK_REALTIME, &now);
    res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
    log_query(&res);
    return res;

}


void query_result_init(query_result_t* result, const char* query) {
    struct timespec now{};
    clock_gettime(CLOCK_REALTIME, &now);
    result->start_ns = now.tv_nsec + 1e9 * now.tv_sec;
    result->status = QUERY_SUCCESS;
    result->psize = 0;
    result->lsize = 0;
    result->query = (char*)query;//to look after
    }
void query_result_add(query_result_t* result, student_t s){
    result->lsize +=1;
    result->psize += sizeof(s);
    result->students->push_back(s);
}

