#include "dummy.h"

void AnduinTheSecond(uint32_t *value){
    ++(*value);
}

void VarianTheFirst(uint32_t *vector, uint32_t length){
    for(int i = 0; i<length; ++i){
        if(vector[i] >= 3){
            vector[i] = (uint32_t) 0;
        }else{
            AnduinTheSecond(&vector[i]);
        }
    }
}