#ifndef FLAG_PAIR_H
#define FLAG_PAIR_H

class flag_pair{
public:
    int index;
    int module;
public:
    flag_pair(){};
    flag_pair(int index, int module) : index(index), module(module){};
};

#endif