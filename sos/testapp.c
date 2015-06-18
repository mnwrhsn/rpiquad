#include "os_task.h"

DECLARE_TASK(t1, OS_CONFIG_STACK_DEFAULT_SIZE);
DECLARE_TASK(t2, OS_CONFIG_STACK_DEFAULT_SIZE);

void task1(void *data)
{
    while(1) {
    }
}

void task2(void *data)
{
    while(1) {
    }
}

int main(void)
{
    os_init();
    CREATE_TASK(t1, task1, NULL, OS_CONFIG_STACK_DEFAULT_SIZE, SOS_CONFIG_TASK_PRIO_MEDI1);
    CREATE_TASK(t2, task2, NULL, OS_CONFIG_STACK_DEFAULT_SIZE, SOS_CONFIG_TASK_PRIO_MEDI2);

    os_start();
    //will never reach this point

    return 0;           //to satisfy compiler
}
