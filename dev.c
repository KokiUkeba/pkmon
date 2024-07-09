#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define Physical 0
#define Special 1
#define Other 2
#define Buff 3
#define Debuff 4
#define EV_ALL 510
#define EV_MAX 252
#define IV_MAX 31
#define LEVEL 60
#define CORRECTION 0.05

typedef struct MONSTER MONSTER;
typedef struct MOVE MOVE;
typedef struct MOVES MOVES;
typedef struct EFFORT_VALUE EFFORT_VALUE;
typedef struct INDIVIDUAL_VALUE INDIVIDUAL_VALUE;
typedef struct POKEMON POKEMON;


struct MOVE {
    char name[256];
    int category;
    int power;
    //int accuracy
};

struct MONSTER {
    char name[256];
    int number;
    int hitpoint;
    int attack;
    int block;
    int contact;
    int diffence;
    int speed;
    struct MOVE move[20];
};

struct MOVES { 
    struct MOVE move[4];
};

struct EFFORT_VALUE {
    int hitpoint;
    int attack;
    int block;
    int contact;
    int diffence;
    int speed;
};

struct INDIVIDUAL_VALUE {
    int hitpoint;
    int attack;
    int block;
    int contact;
    int diffence;
    int speed;
};

struct POKEMON {
    MONSTER origin;
    char nickname[256];
    MOVES moves;
    EFFORT_VALUE effort;
    INDIVIDUAL_VALUE indivi;
    int hitpoint;
    int attack;
    int block;
    int contact;
    int diffence;
    int speed;
};

int Random(int min, int max);
MONSTER choose_origin(MONSTER *pmon);
MOVES choose_moves(MOVE *pmv);
EFFORT_VALUE Random_EV(void);
char* nickname(void);
POKEMON make_poke(MOVE *pmv, MONSTER *pmon);
INDIVIDUAL_VALUE Random_IV(void);
void battle(struct MONSTER mon1, struct MONSTER mon2);
POKEMON Battle(struct POKEMON r1, struct POKEMON r2);

//関数ポインタを定義してみた(tukawanai...)
//MONSTER (*ch_origin)(MONSTER *pmon);
//MOVES (*ch_move)(MOVE *pmv);
//EFFORT_VALUE (*rand_ev)(void);
//INDIVIDUAL_VALUE (*rand_iv)(void);

int main(int argv,const char* argc[])
{
    //関数ポインタを定義してみた(tukawanai...)
    //ch_origin = choose_origin;
    //ch_move = choose_moves;
    //rand_ev = Random_EV;
    //rand_iv = Random_IV;

    MOVE mv[13] = {
        {"tyoipanti", Physical, 40},
        {"panti", Physical, 60},
        {"kyoupanti", Physical, 80},
        {"tyoupanti", Physical, 100},
        {"tyoibi-mu", Special, 40},
        {"bi-mu", Special, 60},
        {"kyoubi-mu", Special, 80},
        {"tyoubi-mu", Special, 100},
        {"bougyo", Other, 0},
        {"yarukidasu", Buff, 0},
        {"arumidedekitemasu", Buff, 0},
        {"itaihurisuru", Debuff, 0},
        {"bunkaisuru", Debuff, 0}
        };

    MONSTER robo[3] = {
        {"robota",1,45,49,49,65,65,45,mv[20]},
        {"robokiti",2,39,52,43,60,50,65,mv[20]},
        {"roby",3,44,48,65,50,64,43,mv[20]}
        };

    //struct MONSTER robo1 = {"robota",1,45,49,49,65,65,45,mv[20]};
    //struct MONSTER robo2 = {"robokiti",2,39,52,43,60,50,65,mv[20]};
    //struct MONSTER robo3 = {"roby",3,44,48,65,50,64,43,mv[20]};
    //MONSTER origin = choose_origin(robo);
    //MOVES chosen = choose_moves(mv);
    //EFFORT_VALUE ev = Random_EV();
    //INDIVIDUAL_VALUE iv = Random_IV();
    //printf("%10s\t%d\n", origin.name, origin.number);
    //printf("%15s, %15s\n", chosen.move[0].name, chosen.move[1].name);
    //printf("%15s, %15s\n", chosen.move[2].name, chosen.move[3].name);
    //printf("%d, %d, %d, %d, %d, %d\n", ev.hitpoint, ev.attack, ev.block, ev.contact, ev.diffence, ev.speed);
    //printf("%d, %d, %d, %d, %d, %d\n", iv.hitpoint, iv.attack, iv.block, iv.contact, iv.diffence, iv.speed);
    POKEMON poke1, poke2;
    poke1.origin = choose_origin(robo);
    strcpy(poke1.nickname, "karakurikozo");
    poke1.moves = choose_moves(mv);
    poke1.effort = Random_EV();
    poke1.indivi = Random_IV();
    poke1.hitpoint = (poke1.origin.hitpoint * 2 + poke1.indivi.hitpoint + poke1.effort.hitpoint / 4) * LEVEL / 100 + LEVEL + 10;
    poke1.attack = (poke1.origin.attack * 2 + poke1.indivi.attack + poke1.effort.attack / 4) * LEVEL / 100 + 5;
    poke1.block = (poke1.origin.block * 2 + poke1.indivi.block + poke1.effort.block / 4) * LEVEL / 100 + 5;
    poke1.contact = (poke1.origin.contact * 2 + poke1.indivi.contact + poke1.effort.contact / 4) * LEVEL / 100 + 5;
    poke1.diffence = (poke1.origin.diffence * 2 + poke1.indivi.diffence + poke1.effort.diffence / 4) * LEVEL / 100 + 5;
    poke1.speed = (poke1.origin.speed * 2 + poke1.indivi.speed + poke1.effort.speed / 4) * LEVEL / 100 + 5;

    poke2 = make_poke(mv, robo);
    printf("%10s\n", poke1.nickname);
    printf("%10s\n", poke2.nickname);
    POKEMON winner = Battle(poke1, poke2);
    printf("%d\n", winner.origin.number);
    return 0;
}

int Random(int min, int max)
{
    static int flag;

    if (flag == 0) {
        srand((unsigned int)time(NULL));
        flag = 1;
    }

    return min + (int)(rand() * (max - min + 1.0) / (1.0 + (double)RAND_MAX));
}

MONSTER choose_origin(MONSTER *pmon)
{
    MONSTER temp = *(pmon + Random(0, 2));

    return temp; 
}

MOVES choose_moves(MOVE *pmv)
{
    MOVES temp;
    int n[13] = {0};
    int i = 0;
    
    while (i < 4) {
        int k = Random(0, 12);
        if (n[k] == -1)
            continue;
        temp.move[i++] = *(pmv + k);
        n[k] = -1;
    }
        
    return temp;
}

EFFORT_VALUE Random_EV(void)
{
    EFFORT_VALUE temp;
    int n, i = 0;

    while (i <= EV_ALL) {
        n = Random(0,5);
        switch (n) {
        case 0:
            if (temp.hitpoint == EV_MAX)
                continue;
            temp.hitpoint++;
            break;
        case 1:
            if (temp.attack == EV_MAX)
                continue;
            temp.attack++;
            break;
        case 2:
            if (temp.block == EV_MAX)
                continue;
            temp.block++;
            break;
        case 3:
            if (temp.contact == EV_MAX)
                continue;
            temp.contact++;
            break;
        case 4:
            if (temp.diffence == EV_MAX)
                continue;
            temp.diffence++;
            break;
        case 5:
            if (temp.speed == EV_MAX)
                continue;
            temp.speed++;
            break;
        }
        i++;
    }

    return temp;       
}

INDIVIDUAL_VALUE Random_IV(void)
{
    INDIVIDUAL_VALUE temp;

    temp.hitpoint = Random(0, IV_MAX);
    temp.attack = Random(0, IV_MAX);
    temp.block = Random(0, IV_MAX);
    temp.contact = Random(0, IV_MAX);
    temp.diffence = Random(0, IV_MAX);
    temp.speed = Random(0, IV_MAX);

    return temp;
}

char* nickname(void)
{
    static POKEMON temp;
    char nick[256];
    static long int gene;

    /*
    while (fgets(nick, 256, stdin) != NULL) 
        if (nick[strlen(nick) - 1] == '\n')
            nick[strlen(nick) - 1] = '\0';
        
    strcpy(temp.nickname, nick);
    */

    sprintf(nick, "%ld", ++gene);
    strcpy(temp.nickname, nick);

    return temp.nickname;
}

POKEMON make_poke(MOVE *pmv, MONSTER *pmon)
{
    POKEMON temp;
    char *s;

    temp.origin = choose_origin(pmon);
    strcpy(temp.nickname, s = nickname());
    temp.moves = choose_moves(pmv);
    temp.effort = Random_EV();
    temp.indivi = Random_IV();
    temp.hitpoint = (temp.origin.hitpoint * 2 + temp.indivi.hitpoint + temp.effort.hitpoint / 4) * LEVEL / 100 + LEVEL + 10;
    temp.attack = (temp.origin.attack * 2 + temp.indivi.attack + temp.effort.attack / 4) * LEVEL / 100 + 5;
    temp.block = (temp.origin.block * 2 + temp.indivi.block + temp.effort.block / 4) * LEVEL / 100 + 5;
    temp.contact = (temp.origin.contact * 2 + temp.indivi.contact + temp.effort.contact / 4) * LEVEL / 100 + 5;
    temp.diffence = (temp.origin.diffence * 2 + temp.indivi.diffence + temp.effort.diffence / 4) * LEVEL / 100 + 5;
    temp.speed = (temp.origin.speed * 2 + temp.indivi.speed + temp.effort.speed / 4) * LEVEL / 100 + 5;

    return temp;
}

/*
void battle(struct MONSTER mon1, struct MONSTER mon2)
{
    struct MONSTER first;
    struct MONSTER second;
    int turn = 0;

    first = ((mon1.speed > mon2.speed) ? mon1 : mon2);
    second = ((mon1.speed <= mon2.speed) ? mon1 : mon2);
    printf("Battle start!!\n");
    printf("first %10s HP=%3d VS second %10s HP=%3d\n", first.name, first.hitpoint, second.name, second.hitpoint);

    while (first.hitpoint > 0 && second.hitpoint > 0) {
        second.hitpoint -= ((first.attack - second.block) > 0) ? (first.attack - second.block) : 1;
        first.hitpoint -= ((second.attack - first.block) > 0) ? (second.attack - first.block) : 1;
        ++turn;

        if (first.hitpoint < 0)
            first.hitpoint = 0;
        
        if (second.hitpoint < 0)
            second.hitpoint = 0;

        printf("turn%3d:first %10s HP=%3d :second %10s HP=%3d\n", turn, first.name, first.hitpoint, second.name, second.hitpoint);
    }
       
    char *winner;
    winner = ((first.hitpoint == 0) ? (first.name) : (second.name));
    printf("winner!%s!!!\n", winner); 
}
*/

MOVE* select_mv(struct POKEMON mon1)
{
    MOVE *temp;

    temp = mon1.moves.move + Random(0, 3);

    return temp;
}


POKEMON Battle(struct POKEMON r1, struct POKEMON r2)
{
    POKEMON first, second;
    MOVE *r1mv, *r2mv;
    int damage;
    int turn = 1;
    
    //先攻後攻を決める
    first = ((r1.speed > r2.speed) ? r1 : r2);
    second = ((r1.speed <= r2.speed) ? r1 : r2);
    //if (r1.speed == r2.speed) {
    //    int n = Random(1, 10000);
    //    first = ((n % 2 == 0) ? r1 : r2);
    //    second = ((n % 2 != 0) ? r1: r2);
    //}

    printf("Battle start!\n");

    while (1) {
        //技の選択(ランダム)今後入力を受け付けることを想定し、別で関数とした
        r1mv = select_mv(first);
        r2mv = select_mv(second);

        if (r1mv->category != Other && r2mv->category == Other) { 
            printf("second:%s:%s\n", second.nickname, r2mv->name);
        }

        printf("first:%s:%s\n", first.nickname, r1mv->name);
        
        switch (r1mv->category) {
            case Physical:
                if (r2mv->name == "bougyo")
                    break;
                damage = (int)((int)((int)((double)LEVEL * 0.4 + 2) * (double)r1mv->power * (double)first.attack / (double)second.block) / 50. + 2);
                second.hitpoint -= (damage > 0 ? damage : 1);
                break;
            case Special:
                if (r2mv->name == "bougyo")
                    break;
                damage = (int)((int)((int)((double)LEVEL * 0.4 + 2) * (double)r1mv->power * (double)first.contact / (double)second.diffence) / 50. + 2);
                second.hitpoint -= (damage > 0 ? damage : 1);
                break;
            case Buff:
                if (r1mv->name == "yarukidasu") {
                    first.attack *= 1 + CORRECTION;
                    first.contact *= 1 + CORRECTION;
                }
                else {
                    first.block *= 1 + CORRECTION;
                    first.diffence *= 1 + CORRECTION;
                }
                break;
            case Debuff:
                if (r1mv->name == "itaihurisuru") {
                    second.attack *= 1 - CORRECTION;
                    second.contact *= 1 - CORRECTION;
                }
                else {
                    second.block *= 1 - CORRECTION;
                    second.diffence *= 1 - CORRECTION;
                }
                break;
        }
        printf("second:hitpoint=%d\n", (second.hitpoint>=0) ? second.hitpoint : 0);
        if (second.hitpoint <= 0) {
            second.hitpoint = 0;
            printf("winner : %s!\n", first.nickname);
            return first;
        }

        if (r2mv->category != Other)
            printf("second:%s:%s\n", second.nickname, r2mv->name);

        switch (r2mv->category) {
            case Physical:
                if (r1mv->name == "bougyo")
                    break;
                damage = (int)((int)((int)((double)LEVEL * 0.4 + 2) * (double)r2mv->power * (double)second.attack / (double)first.block) / 50. + 2);
                first.hitpoint -= (damage > 0 ? damage : 1);
                break;
            case Special:
                if (r1mv->name == "bougyo")
                    break;
                damage = (int)((int)((int)((double)LEVEL * 0.4 + 2) * (double)r2mv->power * (double)second.contact / (double)first.diffence) / 50. + 2);
                first.hitpoint -= (damage > 0 ? damage : 1);
                break;
            case Buff:
                if (r2mv->name == "yarukidasu") {
                    second.attack *= 1 + CORRECTION;
                    second.contact *= 1 + CORRECTION;
                }
                else {
                    second.block *= 1 + CORRECTION;
                    second.diffence *= 1 + CORRECTION;
                }
                break;
            case Debuff:
                if (r2mv->name == "itaihurisuru") {
                    first.attack *= 1 - CORRECTION;
                    first.contact *= 1 - CORRECTION;
                }
                else {
                    first.block *= 1 - CORRECTION;
                    first.diffence *= 1 - CORRECTION;
                }
                break;
        }
        printf("first:hitpoint=%d\n", (first.hitpoint>=0) ? first.hitpoint : 0);
        if (first.hitpoint <= 0) {
            first.hitpoint = 0;
            printf("winner : %s!\n", second.nickname);
            return second;
        }
        
        printf("turn%3d:first %10s HP=%3d :second %10s HP=%3d\n", turn, first.nickname, first.hitpoint, second.nickname, second.hitpoint);
        printf("--------------------------------------------\n");
        turn++;
    }
}
