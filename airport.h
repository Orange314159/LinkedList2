#include <string>

#ifndef AIRPORT_H
#define AIRPORT_H

class Airport {
public:
    char     code[20];
    double   longitude;
    double   latitude;


    bool equals(Airport other){
        return this->code == other.code && this->latitude == other.latitude && this->longitude == other.longitude;
    }
    
    std::string toString(){
        return this->code;
    }
};

#endif