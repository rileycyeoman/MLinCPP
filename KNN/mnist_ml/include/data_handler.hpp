#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <fstream>
#include "stdint.h" //for uint8
#include "data.hpp" 
#include <vector>
#include <string>
#include <map> //map class to enumerated value
#include <unordered_set> //for keeping track of indexes of split data

class data_handler{
    std::vector<data *> *data_array; //all data, pre-split
    std::vector<data *> *training_data;
    std::vector<data *> *test_data;
    std::vector<data *> *validation_data;

    int num_classes;
    int feature_vector_size;
    std::map<uint8_t, int> class_map;

    const double TRAIN_SET_PERCENT = 0.75;
    const double TEST_SET_PERCENT = 0.20;
    const double VALIDATION_PERCENT = 0.05;

    public:
        data_handler(); //constructor
        ~data_handler(); //destructor

        void read_feature_vector(std::string path); //read feature file seperately
        void read_feature_labels(std::string path);
        void split_data();
        void count_classes();
        
        uint32_t convert_to_little_endian(const unsigned char* bytes);

        std::vector<data *> *get_training_data();
        std::vector<data *> *get_testing_data();
        std::vector<data *> *get_validation_data();
};  





#endif