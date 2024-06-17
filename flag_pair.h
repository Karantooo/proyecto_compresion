#ifndef FLAG_PAIR.H
#define FLAG_PAIR.H

class flag_pair{
public:
    bool char_flag;
    int index;
    int module;
public:
    flag_pair();
    flag_pair(bool char_flag, int index, int module) : char_flag(char_flag), index(index), module(module){};
};

#endif