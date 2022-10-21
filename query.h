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

#endif