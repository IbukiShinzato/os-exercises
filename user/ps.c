#include "kernel/pstat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    struct pstat st;

    if (getpinfo(&st) < 0)
    {
        fprintf(2, "ps: getpinfo failed\n");
        exit(1);
    }

    printf("\nPID\tTICKETS\tPASS\t\tSTRIDE\tTIMES\n");

    for (int i = 0; i < 64; i++)
    {
         if (st.inuse[i])
         {
             printf("%d\t%d\t%d\t\t%d\t%d\n", st.pids[i], st.tickets[i], st.pass[i], st.stride[i],
                    st.times[i]);
         }

        // printf("%d\t%d\t%d\t%d\t%d\n", st.pids[i], st.tickets[i], st.pass[i], st.stride[i], st.times[i]);
    }

    exit(0);
}
