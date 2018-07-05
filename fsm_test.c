#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define g_max_num 5

enum state
{
    GET_UP,
    GO_TO_SCHOOL,
    HAVE_LUNCH,
    DO_HOMEWORK,
    SLEEP,
};

enum event
{
    EVENT1 = 1,
    EVENT2,
    EVENT3,
};

typedef struct fsmTable_s
{
    int event;
    int CurState;
    void (*eventActFun)(void);
    int NextState;
}fsmTable_t;

typedef struct new_table
{
    fsmTable_t* FsmTable;
    int curState;
}FSM_t;

void FSM_Regist(FSM_t* pFsm, fsmTable_t* pTable)
{
    pFsm->FsmTable = pTable;
}

void FSM_StateTransfer(FSM_t* pFsm, int state)
{
    pFsm->curState = state;
}


void GetUp(void)
{
    printf("xiaoMing GetUp\n");
}

void Go2School(void)
{
    printf("xiaoMing go to school\n");
}

void HaveLunch(void)
{
    printf("xiaoMing  Have Lunch\n");
}

void DoHomework(void)
{
    printf("xiaoMing  Do Homework\n");
}

void Go2Bed(void)
{
    printf("xiaoMing go to bed\n");
}

void FSM_EventHandle(FSM_t* pFsm, int event)
{
    fsmTable_t* pActTable = pFsm->FsmTable;
    void (*eventActFun)() = NULL;  //函数指针初始化为空
    int NextState;
    int CurState = pFsm->curState;
    int flag = 0; //标识是否满足条件
    int i;

    /*获取当前动作函数*/
    for (i = 0; i<g_max_num; i++)
    {
        //当且仅当当前状态下来个指定的事件，我才执行它
        if (event == pActTable[i].event && CurState == pActTable[i].CurState)
        {
            flag = 1;
            eventActFun = pActTable[i].eventActFun;
            NextState = pActTable[i].NextState;
            break;
        }
    }


    if (flag) 
    {
        /*do func*/
        if (eventActFun)
        {
            eventActFun();
        }

        FSM_StateTransfer(pFsm, NextState);
    }
    else
    {
        printf("xiaoMing playing\n");
    }
}



fsmTable_t XiaoMingTable[] =
{
    /*arrive event state_new, do_func, next_state*/
    { EVENT1,  SLEEP,           GetUp,        GET_UP },
    { EVENT2,  GET_UP,          Go2School,    GO_TO_SCHOOL },
    { EVENT3,  GO_TO_SCHOOL,    HaveLunch,    HAVE_LUNCH },
    { EVENT1,  HAVE_LUNCH,      DoHomework,   DO_HOMEWORK },
    { EVENT2,  DO_HOMEWORK,     Go2Bed,       SLEEP },
};

void InitFsm(FSM_t* fsm)
{
    FSM_Regist(fsm,XiaoMingTable);
    fsm->curState = SLEEP;
}

int main()
{
    FSM_t fsm;
    InitFsm(&fsm);
    int i = 0;
    int event[5] = {EVENT1,EVENT2,EVENT3,EVENT1,EVENT2}; 
    
    while (1)
    {
        FSM_EventHandle(&fsm, event[i]);
        if((++i) == 5)
        {
            i = 0;
        }
        sleep(1);  
    }

    return 0;
}