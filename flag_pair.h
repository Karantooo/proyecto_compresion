#ifndef FLAG_PAIR_H
#define FLAG_PAIR_H

class flag_pair{
public:
    bool int_flag;
    int index;
    int module;
public:
    flag_pair(){};
    flag_pair(bool int_flag, int index, int module) : int_flag(int_flag), index(index), module(module){};
};

#endif