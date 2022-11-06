//
// Created by Ali Bahja on 18/10/2022.
//
//
// Created by Ali Bahja on 14/10/2022.
//

#include "parsing.h"
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "student.h"

bool parse_update(char* query, char* field_filter, char* value_filter, char* field_to_update, char* update_value) {
    strtok_r(NULL, " ", &query);    //discards the query keyword(first word)
    char* key_val_filter = strtok_r(NULL, " ", &query);  // key=val filter
    if (key_val_filter == NULL) {
        return false;
    }
    if (strtok_r(NULL, " ", &query) == NULL) {  // discard the "set" keyword
        return false;
    }

    char* key_val_update = strtok_r(NULL, " ", &query);  // key=val updated value
    if (key_val_update == NULL) {
        return false;
    }

    if (parse_selectors(key_val_filter, field_filter, value_filter) == 0) {
        return false;
    }
    if (parse_selectors(key_val_update, field_to_update, update_value) == 0) {
        return false;
    }
    return true;
}

bool parse_insert(char* query, char* fname, char* lname, unsigned* id, char* section, struct tm* birthdate) {
    char* token = strtok_r(NULL, " ", &query);  //discards the query keyword(first word)
    if (token == NULL) {
        return false;
    }
    token = strtok_r(NULL, " ", &query);
    if (token == NULL) {
        return false;
    }
    strcpy(fname, token);
    token = strtok_r(NULL, " ", &query);
    if (token == NULL) {return false;
    }
    strcpy(lname, token);
    token = strtok_r(NULL, " ", &query);
    if (token == NULL) {
        return false;
    }
    *id = (unsigned)atol(token);
    token = strtok_r(NULL, " ", &query);
    if (token == NULL) {
        return false;
    }
    strcpy(section, token);
    token = strtok_r(NULL, " ", &query);
    if (token == NULL) {
        return false;
    }
    if (strptime(token, "%d/%m/%Y", birthdate) == NULL) {
        return false;
    }
    return true;
}

bool parse_selectors(char* query, char* field, char* value) {
    char* token = strtok_r(NULL, "=", &query);//discards the query keyword(first word)
    if (token == NULL) {
        return false;
    }
    char* last = strchr(token,' ');// returns the field of the query
    if (last != NULL){
        token = last+1;
    }

    strcpy(field, token);
    token = strtok_r(NULL, " ", &query);
    if (token == NULL) {
        return false;
    }
    strcpy(value, token);
    return true;
}


