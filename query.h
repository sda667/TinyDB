#ifndef _QUERY_H
#define _QUERY_H

#include "db.h"

using QUERY_STATUS = enum { QUERY_SUCCESS, QUERY_FAILURE, UNRECOGNISED_FIELD };

/**
 * A query_result_t describes the result of a query.
 */
using query_result_t = struct {
    student_t* students; /** A list of students **/
    size_t lsize;        /** Logical size **/
    size_t psize;        /** Physical size **/
    QUERY_STATUS status; /** The return status of the query **/
    char *query;     /** The actual query that was submitted **/
    long start_ns;       /** The start of the query in nanoseconds **/
    long end_ns;         /** The end of the query in nanoseconds **/
};

/**
 * Initialise a query_result_t structure.
 **/
void query_result_init(query_result_t* result, const char* query);

/**
 * Add a student to a query result.
 **/
void query_result_add(query_result_t* result, student_t s);

/**
 * add a new student to the database
 */
void insert_query(std::string fname, std::string lname,std::string id, std::string section, std::string birthday);
/**
 * Filter and return a list of the wanted students
 */
void select_query(std::string champs, std::string valeur);
/**
 * Delete all the filtered students
 */
void delete_query(std::string champs, std::string valeur);
/**
 * Update all the filtered students with the wanted value
 */
 void update_query(std::string filtre, std::string valeur,std::string champs_modifie, std::string champs_modefiee );

#endif