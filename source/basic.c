#include "basic.h"
#include "robot_opponent.h"

char* constrain_input(int num)
{
    char* target = malloc(sizeof(char) * num);
    char tem;int n = 0;

    //前文换行符处理
    while((tem = getchar()) == '\n');
    *(target + (n % num)) = tem;
    n++;

    //一直读到换行符
    while((tem = getchar()) != '\n')
    {
        *(target + (n % num)) = tem;
        n++;
    }

    if (n == num)return target;
    else {
        free(target);
        return NULL;
    }
}

void Swap(char* arr, int a, int b)
{
    char tem = arr[a];
    arr[a] = arr[b];
    arr[b] = tem;
}

void print_basic(info* basic_info)
{
    printf("--------------------\n");
    printf("current round: %d/%d\n", basic_info->current_length, basic_info->whole_length);
    printf("strategy index: %d\n", basic_info->strategy_index);
    printf("length of array: %d\n", basic_info->num);
    printf("--------------------\n");
    printf("A (player):  %d\n",basic_info->pointA);
    printf("B (program): %d\n",basic_info->pointB);
    printf("--------------------\n");    
    printf("current array:%s\n", (*(basic_info->arr + basic_info->current_length - 1)) );
}

void draw(info* basic_info)
{
    system("cls");
    char **arr = basic_info->arr;
    char **Ans = basic_info->Ans;

    if(basic_info->Switch == TURN_WHOLE_OVER){
        printf("--------------------\n");
        char winner[16] = "";
        if(basic_info->pointA > basic_info->pointB)memcpy(winner, "winner: player", 15);
        else if(basic_info->pointA < basic_info->pointB)memcpy(winner, "program", 16);
        else memcpy(winner, "draw", 5);
        printf("%s\n",winner);

        printf("A (player):  %d\n",basic_info->pointA);
        printf("B (program): %d\n",basic_info->pointB);

        printf("--------------------\n"); 
        printf("all rounds:\n");
        for(int i = 0; i < basic_info->whole_length; i++){
            printf("round %d\n",i+1);
            printf("%s\n%s\n",arr[i],Ans[i]);
            printf("--------------------\n"); 
        }  
    }
    else if(basic_info->Switch == TURN_OVER){
        print_basic(basic_info);
    } 
    else if(basic_info->Switch == TURN_PROCEED){
        print_basic(basic_info);
    }
}

void calc(info* basic_info)
{
    int n = 0;

    //序列更新
    while(basic_info->arr[basic_info->current_length - 1][n++] != '\0');
    Swap(basic_info->arr[basic_info->current_length - 1], n-1, n);

    //答案储存
    basic_info->Ans[basic_info->current_length - 1][n - 1] = basic_info->ans;

    //单局完成判定
    if(n == (basic_info->num)){    /*此处n是序列更新前的值*/
        basic_info->Switch = TURN_OVER;
    }
    
    //得分计算
    if(basic_info->ans == basic_info->arr[basic_info->current_length - 1][n - 1]){
        basic_info->pointA++;
    }
}

info* init(void)
{
    int n, len, stra;
    printf("total number of rounds:");scanf("%d", &len);
    printf("strategy index:");scanf("%d", &stra);
    printf("length of array:");scanf("%d", &n);

    //cur_data配置
    data* cur_data = malloc(sizeof(data));
    cur_data->current_length = 1;
    cur_data->num = n;
    cur_data->whole_length = len;

    //机器人策略初始化
    algor** alg = algor_init();

    //基本信息配置
    info* basic_info = malloc(sizeof(info));
    basic_info->cur_data = cur_data;
    basic_info->alg = alg;
    basic_info->whole_length = len;
    basic_info->strategy_index = stra;
    basic_info->num = n;
    basic_info->current_length = 1;

    //动态分配arr
    char ** arr = malloc(sizeof(char*) * len);
    basic_info->arr = arr;

    //给出第一个序列
    *(arr + basic_info->current_length - 1) = (char*)((*(alg[basic_info->strategy_index - 1]))(ALGOR_MODE_ARR, cur_data));
    
    //动态分配Ans
    char ** Ans = malloc(sizeof(char*) * len);
    for(int i = 0; i<n; i++){
        Ans[i] = malloc(sizeof(char) * (n + 1));
    }
    basic_info->Ans = Ans;

    basic_info->Switch = TURN_PROCEED;
    basic_info->pointA = 0;
    basic_info->pointB = 0;

    return basic_info;
}

//询问
void inquire(info* basic_info)
{
    while(1)
    {
        printf("guess next one: (L or R) ");
        char * tem = constrain_input(1);
        if (tem == NULL || (*tem != 'L' && *tem != 'R')){
            printf("invaild input\n");
        }
        else {
            basic_info->ans = *tem;            
            break;
        }
    }
}