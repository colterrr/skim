#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALGOR_MODE_ARR 0
#define ALGOR_MODE_INT 1

#define ALGOR_NUM 2

#define TURN_OVER 0
#define TURN_PROCEED 1
#define TURN_WHOLE_OVER 2

typedef struct _data{
    char** arr;
    char** Ans;
    int num;
    int whole_length;
    int current_length;
}data;

typedef void* (algor)(int, data*);

typedef struct _info
{
    char** arr;
    char** Ans;

    int pointA;
    int pointB;    

    char ans;            //当前回答
    int Switch;

    int num;             //序列长度     
    int strategy_index;  //1起头(1 ~ ALGOR_NUM)
    int whole_length;    //总共局数
    int current_length;  //1起头(1 ~ whole_length)

    algor** alg;
    data* cur_data;
}info;



#endif