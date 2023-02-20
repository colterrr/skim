#include "basic.h"

int main()
{
    while(1){
        info* basic_info = init();
        while(1){
            draw(basic_info);
            if (basic_info->Switch ==TURN_PROCEED){
                inquire(basic_info);
            }
            else if(basic_info->Switch == TURN_OVER){
                printf("\nround %d over\n\n",basic_info->current_length);
                system("pause");
                //进行下一局
                basic_info->current_length++;
                basic_info->Switch = TURN_PROCEED;
                basic_info->arr[basic_info->current_length - 1] = (char*)((*(basic_info->alg[basic_info->strategy_index - 1]))(ALGOR_MODE_ARR, basic_info->cur_data));
                if(basic_info->current_length > basic_info->whole_length){
                    basic_info->Switch = TURN_WHOLE_OVER;
                }
                continue;
            }
            else if(basic_info->Switch == TURN_WHOLE_OVER){
                system("pause");
                system("cls");
                break;
            }
            calc(basic_info);
        }
    }
}

/*
    //进行下一局
    if(basic_info->Switch == TURN_OVER){
        
        //总局完成判定
        if(basic_info->current_length > basic_info->whole_length){
            basic_info->Switch = TURN_WHOLE_OVER;
        }
    }
*/