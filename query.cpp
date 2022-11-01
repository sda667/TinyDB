//
// Created by Ali Bahja on 18/10/2022.
//
//
// Created by Ali Bahja on 14/10/2022.
//

#include "query.h"
#include <ctime>


void select_query(std::string champs, std::string valeur);

void query_result_init(query_result_t* result, const char* query) {
    struct timespec now{};
    clock_gettime(CLOCK_REALTIME, &now);
    result->start_ns = now.tv_nsec + 1e9 * now.tv_sec;
    result->status = QUERY_SUCCESS;
    }

