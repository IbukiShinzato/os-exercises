#include "kernel/types.h"
#include "user/user.h"

#define MAX_MSG_LEN 512

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: set_msg <message>\n");
        exit(1);
    }

    int user_len = strlen(argv[1]);

    if (user_len > MAX_MSG_LEN)
    {
        fprintf(2, "Error: message must be %d bytes or less\n", MAX_MSG_LEN);
        exit(1);
    }

    char* user_buf = argv[1];

    fprintf(1, "user_buf: %s\n", user_buf);
    fprintf(1, "user_len: %d\n", user_len);

    if (set_msg(user_buf, user_len) < 0)
    {
        fprintf(2, "Error: could not write message to kernel buffer\n");
        exit(1);
    }

    fprintf(1, "Successfully wrote message: %s\n", user_buf);

    exit(0);
}
