//
// Created by Ali Bahja on 18/10/2022.
//
//
// Created by Ali Bahja on 14/10/2022.
//

#include "query.h"
#include "db.h"
#include <ctime>


query_result_t insert_query(database_t *db, std::string fname, std::string lname, unsigned int id, std::string section,struct tm birthday){
    query_result_t res;
    struct timespec now{};
    clock_gettime(CLOCK_REALTIME, &now);
    res.start_ns = now.tv_nsec + 1e9 * now.tv_sec;
    for (int i = 0;i < db->lsize; i++){
            if(db->data->at(i).id == id){
                res.status = QUERY_FAILURE;
                clock_gettime(CLOCK_REALTIME, &now);
                res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
                return res;
            }
        }
    student_t newstudent;//new student to add to the db
    newstudent.id = id; newstudent.section = section;newstudent.lname = lname;newstudent.fname=fname;newstudent.birthdate = birthday;
    db_add(db,newstudent);
    res.status = QUERY_SUCCESS;
    res.lsize +=1;
    res.psize += sizeof(newstudent);
    res.students->push_back(newstudent);
    clock_gettime(CLOCK_REALTIME, &now);
    res.end_ns = now.tv_nsec + 1e9 * now.tv_sec;
    return res;
}

void query_result_init(query_result_t* result, const char* query) {
    struct timespec now{};
    clock_gettime(CLOCK_REALTIME, &now);
    result->start_ns = now.tv_nsec + 1e9 * now.tv_sec;
    result->status = QUERY_SUCCESS;
    }

