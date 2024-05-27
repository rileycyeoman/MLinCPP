#include "data_handler.hpp"

data_handler::data_handler(){//constructor
    data_array = new std::vector<data *>; //apply all to the heap
    test_data = new std::vector<data *>;
    training_data = new std::vector<data *>; 
    validation_data = new std::vector<data *>;
   
}
data_handler::~data_handler(){ //destructor
// free dynamic memory

}
void data_handler::read_feature_vector(std::string path){

}
void data_handler::read_feature_labels(std::string path){

}
void data_handler::split_data(){

}
void data_handler::count_classes(){

}

uint32_t data_handler::convert_to_little_endian(const unsigned char* bytes);

std::vector<data *> data_handler::get_training_data();
std::vector<data *> data_handler::get_testing_data();
std::vector<data *> data_handler::get_validation_data();