//
// Created by Ali Bahja on 14/10/2022.
//

#ifndef _STUDENT_H
#define _STUDENT_H
#include <iostream>
#include <ctime>

/**
 * Student structure type.
 **/
using student_t = struct {
    unsigned id;         /** Unique ID **/
    //char fname[64];      /** Firstname **/
    //char lname[64];      /** Lastname **/
   // char section[64];
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