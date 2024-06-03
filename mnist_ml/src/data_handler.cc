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
    uint32_t header[4]; //magic number | num images |row size| column size
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");
    if (f){ //if there is a pointer to the file
        for (int i = 0; i< 4; i++){ 
            if (fread(bytes, sizeof(bytes), 1, f)){
                header[i] = convert_to_little_endian(bytes);
            }
        }
    printf("Done getting input file header.\n");
    int image_size = header[2]*header[3]; //row * col
    for (int i = 0; i < header[1]; i++){
            data *d = new data();
            uint8_t element[1];
            for (int j = 0; j<image_size; j++){
                if (fread(element, sizeof(element), 1, f)){
                    d->append_to_feature_vector(element[0]);
                }
                else{
                    printf("Error reading from file.\n");
                    exit(1);
                }
            }
            data_array -> push_back(d);
        }
        printf("Successful in reading and storing feature vectors\n", data_array->size());
    }
    else{ //no pointer to file
        printf("Could not find file");
        exit(1);
    }
}


void data_handler::read_feature_labels(std::string path){
    uint32_t header[2]; //magic number | num images |
    unsigned char bytes[2];
    FILE *f = fopen(path.c_str(), "r");
    if (f){ //if there is a pointer to the file
        for (int i = 0; i< 2; i++){
            if (fread(bytes, sizeof(bytes), 1, f)){
                header[i] = convert_to_little_endian(bytes);
            }
        }
    printf("Done getting label file header.\n");
    for (int i = 0; i < header[1]; i++){
            uint8_t element[1];
            if (fread(element, sizeof(element), 1, f)){
                data_array->at(i)->set_label(element[0]);
            }
            else{
                printf("Error reading from file.\n");
                exit(1);
            }
        }
        printf("Successful in reading and storing labels\n", data_array->size());
    }
    else{ //no pointer to file
        printf("Could not find file");
        exit(1);
    }
};


void data_handler::split_data(){
    std::unordered_set<int> used_indexes;
    int train_size = data_array -> size() * TRAIN_SET_PERCENT;
    int test_size = data_array -> size() * TEST_SET_PERCENT;
    int validation_size = data_array -> size() * VALIDATION_PERCENT;

    //Train Data
    int count = 0;
    while (count < train_size){
        int rand_index = rand() % data_array->size();
        if (used_indexes.find(rand_index) == used_indexes.end()){ //rand index is not in set
            training_data->push_back(data_array->at(rand_index));
            used_indexes.begin(rand_index);
            count++;
        }

    }

    //Test Data
    count = 0;
    while (count < test_size){
        int rand_index = rand() % data_array->size();
        if (used_indexes.find(rand_index) == used_indexes.end()){
            test_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }

//Validation Data
    count = 0;
    while (count < validation_size){
        int rand_index = rand() % data_array->size();
        if (used_indexes.find(rand_index) == used_indexes.end()){
            validation_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }
    printf("Training Data Size: %lu.\n", training_data->size());
    printf("Testing Data Size: %lu.\n", test_data->size());
    printf("Validation Data Size: %lu.\n", validation_data->size());
}


void data_handler::count_classes(){
    int count = 0;
    for (unsigned i = 0; i<data_array->size(); i++){
        if (class_map.find(data_array->at(i)->get_label()) == class_map.end()){ //if don't find current label in class map
            class_map[data_array->at(i)->get_label()] = count; //count the current number of unique labels
            data_array->at(i)->set_enumerated_label(count);
            count++;
        }
    }
    num_classes = count;
    printf("Successfully extracted %d unique classes", num_classes);
}

uint32_t data_handler::convert_to_little_endian(const unsigned char* bytes){
    //this function was new to me. This is pratically to ensure that info is read in a consistent fashion accross computers
    //little endian stores least significant byte first. Basically the same as humans reading right to left
    
    return (uint32_t)((bytes[0] << 24) | //0th byte (first 8 bits) are shifted left to 3rd position
                      (bytes[1] << 16) | //second set becomes 2nd place
                      (bytes[2] << 8) |  //third set becomes 3rd place
                      (bytes[3]));       //fourth stays in place
}

std::vector<data *> * data_handler::get_training_data(){
    return training_data;
}
std::vector<data *> * data_handler::get_testing_data(){
    return test_data;
}
std::vector<data *> * data_handler::get_validation_data(){
    return validation_data;
}


int main(){
    data_handler *dh = new data_handler();
    dh->read_feature_labels("file path");
    dh->read_feature_vector("file path");
    dh->split_data();
    dh->count_classes();
}