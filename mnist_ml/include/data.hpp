#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include "stdint.h"
#include "stdio.h"

class data{
    std::vector<uint8_t> *feature_vector; //everything but the class
    uint8_t label; //class
    int enum_label; //storing label as integer for comparison purposes

    public:
        void set_feature_vector(std::vector<uint8_t> *);
        void append_to_feature_vector(uint8_t);
        void set_label(uint8_t);
        void set_enumerated_label(int);

        uint8_t get_feature_vector_size();
        uint8_t get_label();
        int8_t get_enumerated_label();

        std::vector<uint8_t> *get_feature_vector();

};  





#endif