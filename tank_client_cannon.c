// http://blog.livedoor.jp/akf0/archives/51585502.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <winsock2.h>

#define SPACE 80

typedef struct point {
    int x;  // x座標
    int y;  // y座標
} point;

int GetRandom(int min, int max);

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
    char name[] = "name:RAIGEKI\n";
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
    char str[100];
    char *token;

    while (1) {
        // 全方位に対して探索を行い，砲弾の位置，敵の座標を構造体に格納
        point cannon[20];  // 砲弾の位置を保存しておく．(余裕を持って20個)
        point enemy;
        enemy.x = 0;
        enemy.y = 0;

        int i, n = 0;
        for (i = 1; i < 9; i++) {
            switch (i) {
                case 1:
                    send(s, search1, strlen(search1), 0);
                    break;
                case 2:
                    send(s, search2, strlen(search2), 0);
                    break;
                case 3:
                    send(s, search3, strlen(search3), 0);
                    break;
                case 4:
                    send(s, search4, strlen(search4), 0);
                    break;
                case 5:
                    send(s, search5, strlen(search5), 0);
                    break;
                case 6:
                    send(s, search6, strlen(search6), 0);
                    break;
                case 7:
                    send(s, search7, strlen(search7), 0);
                    break;
                case 8:
                    send(s, search8, strlen(search8), 0);
                    break;
                case 9:
                    send(s, search9, strlen(search9), 0);
                    break;
            }
            memset(buffer, '\0', sizeof(buffer));
            recv(s, buffer, sizeof(buffer), 0);
            printf("→ %s", buffer);

            strcpy(str, buffer);
            strtok(str, ":");
            token = strtok(NULL, ":");  // x座標,y座標,種類を分離
            // もし砲弾か敵に当たった場合，その座標を保存
            if (strcmp(token, "null\n") != 0) {
                int xt, yt;
                xt = atoi(strtok(token, ","));
                yt = atoi(strtok(NULL, ","));
                token = strtok(NULL, ",");
                if (strcmp(token, "cannon\n") == 0) {
                    printf("砲弾を発見しました。\n");
                    cannon[n].x = xt;
                    cannon[n++].y = yt;
                } else if (strcmp(token, "enemy\n") == 0) {
                    enemy.x = xt;
                    enemy.y = yt;
                    printf("敵の位置を把握しました。\n");
                }
            }
        }

        // 攻撃のブロック文
        {
            // 砲弾の数を確認
            send(s, state_cannon, strlen(state_cannon), 0);
            memset(buffer, '\0', sizeof(buffer));
            recv(s, buffer, sizeof(buffer), 0);
            printf("→ %s", buffer);

            strcpy(str, buffer);
            strtok(str, ":");
            token = strtok(NULL, ":");
            int cannonnum = atoi(token);

            if (cannonnum == 5) {
                // 敵の位置が把握できてない場合(500,300,700,100,900の順で撃ってみる)
                if (enemy.x == 0 && enemy.y == 0) {
                    printf("1弾目：500\n");
                    // サーバにデータを送信 移動指令
                    send(s, cannon3, strlen(cannon3), 0);
                    // サーバから返信データを受信
                    memset(buffer, '\0', sizeof(buffer));
                    recv(s, buffer, sizeof(buffer), 0);
                    printf("→ %s", buffer);

                    printf("2弾目：300\n");
                    // nullが返ってくる限り打ち続ける
                    do {
                        send(s, cannon2, strlen(cannon2), 0);
                        // サーバから返信データを受信
                        memset(buffer, '\0', sizeof(buffer));
                        recv(s, buffer, sizeof(buffer), 0);
                        printf("→ %s", buffer);

                        strcpy(str, buffer);
                        strtok(str, ":");
                        token = strtok(NULL, ":");
                    } while (strcmp(token, "null\n") == 0);

                    printf("3弾目：700\n");
                    // nullが返ってくる限り打ち続ける
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

                    printf("4弾目：100\n");
                    // nullが返ってくる限り打ち続ける
                    do {
                        send(s, cannon1, strlen(cannon1), 0);
                        // サーバから返信データを受信
                        memset(buffer, '\0', sizeof(buffer));
                        recv(s, buffer, sizeof(buffer), 0);
                        printf("→ %s", buffer);

                        strcpy(str, buffer);
                        strtok(str, ":");
                        token = strtok(NULL, ":");
                    } while (strcmp(token, "null\n") == 0);

                    printf("5弾目：900\n");
                    // nullが返ってくる限り打ち続ける
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
                } else {  // 敵の位置が把握できてる場合(SPACE間隔で撃つ)
                    char tmp[100];

                    printf("1弾目：%d\n", enemy.y);
                    sprintf(tmp, "cannon:%d\n", enemy.y);
                    // サーバにデータを送信 移動指令
                    send(s, tmp, strlen(tmp), 0);
                    // サーバから返信データを受信
                    memset(buffer, '\0', sizeof(buffer));
                    recv(s, buffer, sizeof(buffer), 0);
                    printf("→ %s", buffer);

                    if (enemy.y - SPACE >= 100) {
                        printf("2弾目：%d\n", enemy.y - SPACE);
                        sprintf(tmp, "cannon:%d\n", enemy.y - SPACE);
                    } else {  // とりあえず100へ
                        printf("2弾目：100\n");
                        sprintf(tmp, "cannon:100\n");
                    }
                    // nullが返ってくる限り打ち続ける
                    do {
                        send(s, tmp, strlen(tmp), 0);
                        // サーバから返信データを受信
                        memset(buffer, '\0', sizeof(buffer));
                        recv(s, buffer, sizeof(buffer), 0);
                        printf("→ %s", buffer);

                        strcpy(str, buffer);
                        strtok(str, ":");
                        token = strtok(NULL, ":");
                    } while (strcmp(token, "null\n") == 0);

                    if (enemy.y + SPACE <= 900) {
                        printf("3弾目：%d\n", enemy.y + SPACE);
                        sprintf(tmp, "cannon:%d\n", enemy.y + SPACE);
                    } else {  // とりあえず900へ
                        printf("3弾目：900\n");
                        sprintf(tmp, "cannon:900\n");
                    }
                    // nullが返ってくる限り打ち続ける
                    do {
                        send(s, tmp, strlen(tmp), 0);
                        // サーバから返信データを受信
                        memset(buffer, '\0', sizeof(buffer));
                        recv(s, buffer, sizeof(buffer), 0);
                        printf("→ %s", buffer);

                        strcpy(str, buffer);
                        strtok(str, ":");
                        token = strtok(NULL, ":");
                    } while (strcmp(token, "null\n") == 0);

                    if (enemy.y - 2*SPACE >= 100) {
                        printf("4弾目：%d\n", enemy.y - 2*SPACE);
                        sprintf(tmp, "cannon:%d\n", enemy.y - 2*SPACE);
                    } else {  // とりあえず100へ
                        printf("4弾目：100\n");
                        sprintf(tmp, "cannon:100\n");
                    }
                    // nullが返ってくる限り打ち続ける
                    do {
                        send(s, tmp, strlen(tmp), 0);
                        // サーバから返信データを受信
                        memset(buffer, '\0', sizeof(buffer));
                        recv(s, buffer, sizeof(buffer), 0);
                        printf("→ %s", buffer);

                        strcpy(str, buffer);
                        strtok(str, ":");
                        token = strtok(NULL, ":");
                    } while (strcmp(token, "null\n") == 0);

                    if (enemy.y + 2*SPACE <= 900) {
                        printf("5弾目：%d\n", enemy.y + 2*SPACE);
                        sprintf(tmp, "cannon:%d\n", enemy.y + 2*SPACE);
                    } else {  // とりあえず900へ
                        printf("5弾目：900\n");
                        sprintf(tmp, "cannon:900\n");
                    }
                    // nullが返ってくる限り打ち続ける
                    do {
                        send(s, tmp, strlen(tmp), 0);
                        // サーバから返信データを受信
                        memset(buffer, '\0', sizeof(buffer));
                        recv(s, buffer, sizeof(buffer), 0);
                        printf("→ %s", buffer);

                        strcpy(str, buffer);
                        strtok(str, ":");
                        token = strtok(NULL, ":");
                    } while (strcmp(token, "null\n") == 0);
                }
            }
        }

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
            int hp_diff = hp_before - hp_after;
            int hp_flag = 0;
            if (hp_diff != 0) hp_flag = 1;

            // hpが減っているので移動
            if (hp_flag) {
                usleep(2000);  // 受信するパケットが混ざらないように待つ

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
                    srand((unsigned int)time(NULL));
                    int rand_num = GetRandom(1, 10);
                    int target_place;
                    // 砲弾のサイズを70と推定
                    if (rand_num % 2 == 0 && enemy_placeY < 850)
                        // target_place = enemy_placeY + 200;    // 動作確認用
                        target_place = enemy_placeY + GetRandom(71, 150);
                    else
                        // target_place = enemy_placeY - 200;    // 動作確認用
                        target_place = enemy_placeY - GetRandom(-71, 150);
                    itoa(target_place, place, 10);
                    sprintf(place, "%s%d\n", new_move, target_place);
                    printf("移動します: %s", place);

                    send(s, place, strlen(place), 0);
                    // サーバから返信データを受信
                    memset(buffer, '\0', sizeof(buffer));
                    recv(s, buffer, sizeof(buffer), 0);
                    printf("→ %s", buffer);

                    // 2回目の移動を防ぐためにフラグを折る
                    while (1) {
                        memset(buff_enemy, '\0', sizeof(buff_enemy));
                        printf("自陣の敵弾を探索\n");
                        send(s, state_hight, strlen(state_hight), 0);
                        // サーバから返信データを受信
                        recv(s, buff_enemy, sizeof(buff_enemy), 0);
                        printf("→ %s", buff_enemy);
                        strcpy(str, buff_enemy);
                        strtok(str, ":");
                        int my_placeY = atoi(strtok(NULL, ":"));
                        if (abs(my_placeY - target_place) < 30) {
                            printf("現在地: %d, 目的地: %d(移動完了)\n",
                                   my_placeY, target_place);
                            break;
                        }
                    }
                }
            }
        }
    }

    closesocket(s);

    WSACleanup();

    return 0;
}

int GetRandom(int min, int max) {
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}