#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

#define SEEK_SET 0
#define SEEK_HOLE 3
#define BLOCK 1024

int main(int argc, char* argv[])
{
    // lseek を 1つのファイルサイズに対して合計何回呼ぶか
    // 0 になる場合はこの数字を 10000, 50000 と増やしてください
    int total_lseek_ops = 5000;
    char buf[BLOCK];
    memset(buf, 'A', BLOCK);

    printf("Starting Linear Search benchmark...\n");

    for (int b = 1; b <= 20; b++)
    {
        // 準備：ファイルを作成して目的のサイズにする
        unlink("bench_file");
        int fd = open("bench_file", O_CREATE | O_RDWR);
        for (int k = 0; k < b; k++)
        {
            write(fd, buf, BLOCK);
        }
        write(fd, "\0", 1);  // 末尾に穴

        // --- ここから計測 ---
        int start_tick = uptime();
        for (int i = 0; i < total_lseek_ops; i++)
        {
            // 常に先頭から末尾の穴を探させる
            // ファイルサイズ(b)大きくなるほど、この1周のコストが微増する
            lseek(fd, 0, SEEK_HOLE);
        }
        int end_tick = uptime();
        // ------------------

        // 結果出力
        printf("%d %d\n", b, end_tick - start_tick);
        close(fd);
    }

    exit(0);
}
