#include "kernel/types.h"
#include "user/user.h"

#define MAX_MSG_LEN 512

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: get_msg <length>\n");
        exit(1);
    }

    int user_len = atoi(argv[1]);

    if (user_len > MAX_MSG_LEN || user_len <= 0)
    {
        fprintf(2, "Error: length must be between 1 and %d\n", MAX_MSG_LEN);
        exit(1);
    }

    char user_buf[MAX_MSG_LEN + 1];

    fprintf(1, "Requesting length: %d\n", user_len);

    int n = get_msg(user_buf, user_len);
    if (n == 0)
    {
        fprintf(1, "Kernel buffer is empty!\n");
        exit(0);
    }

    if (n < 0)
    {
        fprintf(2, "Error: could not read message from kernel\n");
        exit(1);
    }

    user_buf[n] = '\0';

    fprintf(1, "Successfully read %d bytes\n", n);
    fprintf(1, "Message: %s\n", user_buf);

    exit(0);
}
