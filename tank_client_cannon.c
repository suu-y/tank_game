// http://blog.livedoor.jp/akf0/archives/51585502.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <winsock2.h>

int main(void) {
    // 接続するサーバの情報の構造体を用意

    struct sockaddr_in dest;

    memset(&dest, 0, sizeof(dest));

    // サーバの情報を入力

    char destination[20];
    printf("adress=");
    scanf("%s", destination);
    dest.sin_addr.s_addr = inet_addr(destination);

    char port[6];
    printf("port=");
    scanf("%s", port);
    dest.sin_port = htons(atoi(port));

    // char destination[] = "127.0.0.1";  //アドレス

    // dest.sin_port = htons(12345);  //ポート番号

    dest.sin_family = AF_INET;

    // dest.sin_addr.s_addr = inet_addr(destination);

    // ソケット通信の準備・生成

    WSADATA data;

    WSAStartup(MAKEWORD(2, 0), &data);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

    // サーバへの接続

    if (connect(s, (struct sockaddr *)&dest, sizeof(dest))) {
        printf("%sに接続できませんでした\n", destination);

        return -1;
    }

    printf("%sに接続しました\n", destination);

    // char msg[] = "Hello Server!";
    // char buffer[1024];
    char buffer[1024];
    char name[] = "name:TUYOBI\n";
    char move1[] = "move:300\n";
    char move2[] = "move:500\n";
    char move3[] = "move:700\n";
    char cannon1[] = "cannon:100\n";
    char cannon2[] = "cannon:300\n";
    char cannon3[] = "cannon:500\n";
    char cannon4[] = "cannon:700\n";
    char cannon5[] = "cannon:900\n";
    char search1[] = "search:100\n";
    char search2[] = "search:200\n";
    char search3[] = "search:300\n";
    char search4[] = "search:400\n";
    char search5[] = "search:500\n";
    char search6[] = "search:600\n";
    char search7[] = "search:700\n";
    char search8[] = "search:800\n";
    char search9[] = "search:900\n";
    char search_my0[] = "search:0\n";
    char search_my1000[] = "search:1000\n";
    char state_hp[] = "state:hp\n";
    char state_hight[] = "state:hight\n";
    char state_cannon[] = "state:cannon\n";

    // サーバにデータを送信：名前の送信
    send(s, name, strlen(name), 0);

    // サーバからデータを受信：nameの返信 を受け取る
    memset(buffer, '\0', sizeof(buffer));
    recv(s, buffer, sizeof(buffer), 0);
    printf("→ %s\n\n", buffer);

    // サーバからデータを受信：START を受け取る
    memset(buffer, '\0', sizeof(buffer));
    recv(s, buffer, sizeof(buffer), 0);
    printf("→ %s\n\n", buffer);

    int flag = 0;
    time_t t = time(NULL);
    srand(t);

    while (1) {
        //        flag = rand() % 3;

        /*        if (flag == 0) {
                    // サーバにデータを送信 移動指令
                    send(s, move1, strlen(move1), 0);

                } else if (flag == 1) {
                    // サーバにデータを送信 移動指令
                    send(s, move2, strlen(move2), 0);

                } else if (flag == 2) {
                    // サーバにデータを送信 移動指令
                    send(s, move3, strlen(move3), 0);
                }

                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);
        */
        //        Sleep(1000 * (rand() % 3 + 1));

        //        flag = rand() % 3;

        send(s, state_cannon, strlen(state_cannon), 0);
        memset(buffer, '\0', sizeof(buffer));
        recv(s, buffer, sizeof(buffer), 0);
        printf("→ %s", buffer);

        char str[100];
        char *token;
        strcpy(str, buffer);
        strtok(str, ":");
        token = strtok(NULL, ":");
        int cannonnum = atoi(token);

        if (cannonnum == 5) {
            printf("%s\n", cannon1);
            // サーバにデータを送信 移動指令
            send(s, cannon1, strlen(cannon1), 0);
            // サーバから返信データを受信
            memset(buffer, '\0', sizeof(buffer));
            recv(s, buffer, sizeof(buffer), 0);
            printf("→ %s", buffer);

            printf("%s\n", cannon2);
            // nullかえってくる限り打ち続けるよ！
            do {
                send(s, cannon2, strlen(cannon2), 0);
                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);

                strcpy(str, buffer);
                strtok(str, ":");
                token = strtok(NULL, ":");
                // printf("token: %s", token); -> null
                // int len = strlen(token);
                // printf("長さ：%d\n", len); -> 5
                // TODO: nullなのにstrlen=5はおかしい！
            } while (strcmp(token, "null\n") == 0);

            printf("%s\n", cannon3);
            // nullかえってくる限り打ち続けるよ！
            do {
                send(s, cannon3, strlen(cannon3), 0);
                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);

                strcpy(str, buffer);
                strtok(str, ":");
                token = strtok(NULL, ":");
            } while (strcmp(token, "null\n") == 0);

            printf("%s\n", cannon4);
            // nullかえってくる限り打ち続けるよ！
            do {
                send(s, cannon4, strlen(cannon4), 0);
                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);

                strcpy(str, buffer);
                strtok(str, ":");
                token = strtok(NULL, ":");
            } while (strcmp(token, "null\n") == 0);

            printf("%s\n", cannon5);
            // nullかえってくる限り打ち続けるよ！
            do {
                send(s, cannon5, strlen(cannon5), 0);
                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);

                strcpy(str, buffer);
                strtok(str, ":");
                token = strtok(NULL, ":");
            } while (strcmp(token, "null\n") == 0);
        }

        // search結果を保存する

        // 守り（座標移動）のブロック文
        {
            char buffer[1024];
            int hp_before;
            int hp_after;
            int enemy_placeY;

            memset(buffer, '\0', sizeof(buffer));

            // 自分のhpが減っているかを0.1msecほど待って確認
            // -> 減っていたら移動する
            send(s, state_hp, strlen(state_hp), 0);
            // サーバから返信データを受信
            memset(buffer, '\0', sizeof(buffer));
            recv(s, buffer, sizeof(buffer), 0);
            printf("→ %s", buffer);
            // hpを数字にして保持
            strcpy(str, buffer);
            strtok(str, ":");
            hp_before = atoi(strtok(NULL, ":"));

            // 0.1msec待つ
            // 0.1msecで動作確認、hpが2減るので丁度いい塩梅
            usleep(1000);

            send(s, state_hp, strlen(state_hp), 0);
            // サーバから返信データを受信
            memset(buffer, '\0', sizeof(buffer));
            recv(s, buffer, sizeof(buffer), 0);
            printf("→ %s", buffer);
            // hpを数字にして保持
            strcpy(str, buffer);
            strtok(str, ":");
            hp_after = atoi(strtok(NULL, ":"));

            usleep(1000);  // 受信するパケットが混ざらないように待つ

            // hpが減っているので移動
            if (hp_before != hp_after) {
                char buff_enemy[1024];
                memset(buff_enemy, '\0', sizeof(buff_enemy));
                printf("hp diff: %d, %d\n", hp_before, hp_after);
                printf("自陣の敵弾を探索\n");
                send(s, search_my0, strlen(search_my0), 0);
                // サーバから返信データを受信
                recv(s, buff_enemy, sizeof(buff_enemy), 0);
                printf("→ %s", buff_enemy);
                strcpy(str, buff_enemy);
                strtok(str, ":");
                strtok(NULL, ",");
                enemy_placeY = atoi(strtok(NULL, ","));
                printf("敵弾のY座標: %d\n", enemy_placeY);
                if (enemy_placeY > 0 && enemy_placeY < 1000) {
                    // 新しい命令を作成
                    char *new_move = "move:";
                    char place[1024];
                    enemy_placeY = enemy_placeY + 130;
                    itoa(enemy_placeY, place, 10);
                    // 「Hello, 」の後ろに「World!」を連結する
                    sprintf(place, "%s%d\n", new_move, enemy_placeY);
                    printf("移動します: %s", place);

                    send(s, place, strlen(place), 0);
                    // サーバから返信データを受信
                    memset(buffer, '\0', sizeof(buffer));
                    recv(s, buffer, sizeof(buffer), 0);
                    printf("→ %s", buffer);
                }
                send(s, search_my1000, strlen(search_my1000), 0);
                // サーバから返信データを受信
                memset(buff_enemy, '\0', sizeof(buff_enemy));
                recv(s, buff_enemy, sizeof(buff_enemy), 0);
                printf("→ %s", buff_enemy);
            }
        }

        //        Sleep(1000 * (rand() % 3 + 1));

        /*        if (flag == 0) {
                    // サーバにデータを送信 移動指令
                    send(s, search1, strlen(search1), 0);

                } else if (flag == 1) {
                    // サーバにデータを送信 移動指令
                    send(s, search2, strlen(search2), 0);

                } else if (flag == 2) {
                    // サーバにデータを送信 移動指令
                    send(s, search3, strlen(search3), 0);
                }

                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);

                if (flag == 0) {
                    // サーバにデータを送信 移動指令
                    send(s, state_hp, strlen(state_hp), 0);

                } else if (flag == 1) {
                    // サーバにデータを送信 移動指令
                    send(s, state_hight, strlen(state_hight), 0);

                } else if (flag == 2) {
                    // サーバにデータを送信 移動指令
                    send(s, state_cannon, strlen(state_cannon), 0);
                }

                // サーバから返信データを受信
                memset(buffer, '\0', sizeof(buffer));
                recv(s, buffer, sizeof(buffer), 0);
                printf("→ %s", buffer);*/
    }

    // サーバにデータを送信

    // send(s, "Hello Server!", strlen(msg), 0);

    // サーバからデータを受信

    // recv(s, buffer, 1024, 0);

    // printf("→ %s\n\n", buffer);

    // Windows でのソケットの終了

    closesocket(s);

    WSACleanup();

    return 0;
}