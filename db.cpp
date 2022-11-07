//
// Created by Ali Bahja on 18/10/2022.
//
//
// Created by Ali Bahja on 14/10/2022.
//

#include "db.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "student.h"


void db_save(database_t *db, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        perror("Could not open the DB file");
        exit(1);
    }
    if (fwrite(db->data, sizeof(student_t), db->lsize, f) < 0) {
        perror("Could not write in the DB file");
        exit(1);
    }
    fclose(f);
}
void db_load(database_t *db, const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Could not open the DB file");
        exit(1);
    }
    student_char studentchar; // c-style array string
    student_t student;//std::string c++-style string
    while (fread(&studentchar, sizeof(student_char),1, file)) {
        student.id = studentchar.id; student.fname = studentchar.fname; student.lname = studentchar.lname;
        student.section = studentchar.section;  student.birthdate = studentchar.birthdate;
        db_add(db, student);
    }
    fclose(file);
}

void db_init(database_t *db) {
    db->data =  new std::vector<student_t>  ;    //s1 :on peut changer le type de student_t par std::vector<student_t> comme ça c plus facile à gerer la database
    db->lsize = 0;
    db->psize = 0;


}

void db_add(database_t *db, student_t student) {
    db->data->push_back(student);
    //db->data->insert(db->data->end(),student);
    db->lsize += 1;
    db->psize += sizeof(student);
}