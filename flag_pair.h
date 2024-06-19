#ifndef FLAG_PAIR_H
#define FLAG_PAIR_H

class flag_pair{
public:
    int index;
    unsigned char module;
public:
    flag_pair(){};
    flag_pair(int index, unsigned char module) : index(index), module(module){};
};

#endif