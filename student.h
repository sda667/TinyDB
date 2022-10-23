//
// Created by Ali Bahja on 14/10/2022.
//

#ifndef _STUDENT_H
#define _STUDENT_H
#include <iostream>
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
#include <ctime>

/**
 * Student structure type.
 **/
using student_t = struct {
    unsigned id;         /** Unique ID **/
    std::string fname;      /** Firstname **/
    std::string lname;      /** Lastname **/
    std::string section;    /** Section **/
    struct tm birthdate; /** Birth date **/
};

/**
 * @brief Convert a student to a human-readlable string.
 **/
void student_to_str(std::string *buffer, student_t* s);

/**
 * @brief Return whether two students are equal or not.
 **/
int student_equals(student_t* s1, student_t* s2);

#endif