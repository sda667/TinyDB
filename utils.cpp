//
// Created by Ali Bahja on 14/10/2022.
//

#include "utils.h"
#include <fstream>
#include <unistd.h>
#include <vector>
#include "query.h"
#include "student.h"

size_t safe_read(int fd, void* buffer, size_t nbytes) {
    ssize_t nbytes_read = read(fd, buffer, nbytes);
    if (nbytes_read < 0) {
        perror("read error: ");
        exit(1);
    }
    return (size_t)nbytes_read;
}

size_t safe_write(int fd, const void* buffer, size_t nbytes) {
    ssize_t bytes_written = write(fd, buffer, nbytes);
    if (bytes_written < 0) {
        perror("write: ");
        exit(1);
    }
    return (size_t)bytes_written;
}

void log_query(query_result_t* result) {
    std::string buffer ;
    if (result->status == QUERY_SUCCESS) {
        std::string filename;
        std::string type = result->query;
        filename=  "logs/" + std::to_string(result->start_ns) + "-" + type + ".txt" + "\n"; //s2 : used instead of printf(filename,"logs/%ld-%s.txt", result->start_ns, type)
        std::cout << filename <<std::endl;
        std::ofstream f(filename);  // s3 : instead of FILE* f = fopen(filename, "w")
        double duration = (float)(result->end_ns - result->start_ns) / 1.0e6;
        buffer = "Query " + type + " completed in "+ std::to_string(duration) + "s with " +std::to_string(result->lsize)+ " results.\n";
        f<< buffer;
        if (result->lsize > 0) {
            for (int i = 0; i < result->lsize; i++) {
                student_to_str(buffer,&result->students->at(i));
                buffer += "\n";
                f<< buffer;
            }
        }
        f.close();
    } else if (result->status == UNRECOGNISED_FIELD) {
        fprintf(stderr, "Unrecognized field in query %s\n", result->query);
    }
}
