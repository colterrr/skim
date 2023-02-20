#include "robot_opponent.h"

algor** algor_init(void)
{
    algor** alg = malloc(sizeof(algor*) * ALGOR_NUM);
    alg[0] = algorithm_1_random;
    alg[1] = algorithm_2;
    return alg;
}

/*注意: 给出的字符数组以空字符打头*/

void* algorithm_1_random(int mode, data* cur_data)
{
    if(mode == ALGOR_MODE_ARR){
        char* tem = malloc(sizeof(char) * (cur_data->num + 1));
        int ran = 0;
        srand((unsigned)time(NULL));
        for(int i = 1; i <= cur_data->num; i++){
            ran = rand() % 2;
            tem[i] = ran ? 'L': 'R'; 
        }
        tem[0] = '\0';
        return tem;
    }
    else if(mode == ALGOR_MODE_INT){
        int* p = malloc(sizeof(int));
        *p = rand() % 2;
        return p;
    }
}

void* algorithm_2(int mode, data* cur_data)
{

}

