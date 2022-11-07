//
// Created by Ali Bahja on 14/10/2022.
//

#include "student.h"
#include <vector>

#include <iomanip>
#include <sstream>

void student_to_str(std::string &buffer, student_t *s) {
    std::ostringstream timetm ;
    timetm << std::put_time(&s->birthdate,"%d-%m-%Y");
    std::string timestr = timetm.str();// convert the time to a string
    buffer += "ID : " + std::to_string(s->id)+ "  First Name : " +s->fname +"  Last Name : "+s->lname +" Section : " +s->section +" Birthdate : " + timestr+"\n";
}

int student_equals(student_t* s1, student_t* s2) {
    if (s1->id != s2->id){
        return 1;
    }
    else{
      return 0;
    }

}