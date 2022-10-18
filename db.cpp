//
// Created by Ali Bahja on 18/10/2022.
//
//
// Created by Ali Bahja on 14/10/2022.
//

#include "db.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <altivec.h>
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
    student_t student;
    while (fread(&student, sizeof(student_t),1, file)) {
        db_add(db, student);
    }
    fclose(file);
}

void db_init(database_t *db) {
    std::vector<int> v1;

}

void db_add(database_t *db, student_t student) {
    //code
}