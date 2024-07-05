#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define Physical 0
#define Special 1
#define Other 2
#define EV_MAX 510
#define LEVEL 60

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
INDIVIDUAL_VALUE Random_IV(void);
void battle(struct MONSTER mon1, struct MONSTER mon2);

MONSTER (*ch_origin)(MONSTER *pmon);
MOVES (*ch_move)(MOVE *pmv);
EFFORT_VALUE (*rand_ev)(void);
INDIVIDUAL_VALUE (*rand_iv)(void);

int main(int argv,const char* argc[])
{
    ch_origin = choose_origin;
    ch_move = choose_moves;
    rand_ev = Random_EV;
    rand_iv = Random_IV;

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
        {"yarukidasu", Other, 0},
        {"aruminokarada", Other, 0},
        {"itagaru", Other, 0},
        {"bunkaisuru", Other, 0}
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
    strcpy(poke1.nickname, "taro");
    poke1.moves = choose_moves(mv);
    poke1.effort = Random_EV();
    poke1.indivi = Random_IV();
    poke1.hitpoint = (poke1.origin.hitpoint * 2 + poke1.indivi.hitpoint + poke1.effort.hitpoint / 4) * LEVEL / 100 + LEVEL + 10;
    poke1.attack = (poke1.origin.attack * 2 + poke1.indivi.attack + poke1.effort.attack / 4) * LEVEL / 100 + 5;
    poke1.block = (poke1.origin.block * 2 + poke1.indivi.block + poke1.effort.block / 4) * LEVEL / 100 + 5;
    poke1.contact = (poke1.origin.contact * 2 + poke1.indivi.contact + poke1.effort.contact / 4) * LEVEL / 100 + 5;
    poke1.diffence = (poke1.origin.diffence * 2 + poke1.indivi.diffence + poke1.effort.diffence / 4) * LEVEL / 100 + 5;
    poke1.speed = (poke1.origin.speed * 2 + poke1.indivi.speed + poke1.effort.speed / 4) * LEVEL / 100 + 5;

    printf("%10s\n", poke1.nickname);
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

    while (i <= EV_MAX) {
        n = Random(0,5);
        switch (n) {
        case 0:
            if (temp.hitpoint == 252)
                continue;
            temp.hitpoint++;
            break;
        case 1:
            if (temp.attack == 252)
                continue;
            temp.attack++;
            break;
        case 2:
            if (temp.block == 252)
                continue;
            temp.block++;
            break;
        case 3:
            if (temp.contact == 252)
                continue;
            temp.contact++;
            break;
        case 4:
            if (temp.diffence == 252)
                continue;
            temp.diffence++;
            break;
        case 5:
            if (temp.speed == 252)
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

    temp.hitpoint = Random(0, 31);
    temp.attack = Random(0, 31);
    temp.block = Random(0, 31);
    temp.contact = Random(0, 31);
    temp.diffence = Random(0, 31);
    temp.speed = Random(0, 31);

    return temp;
}

//POKEMON make_poke(void)
//{
//    
//}

void battle(struct MONSTER mon1, struct MONSTER mon2)
{
    struct MONSTER first;
    struct MONSTER second;
    int turn = 0;

    first = ((mon1.speed > mon2.speed) ? mon1 : mon2);
    second = ((mon1.speed <= mon2.speed) ? mon1 : mon2);
    printf("Battle start!!\n");
    printf("first %10s HP=%3d VS second %10s HP=%3d\n", first.name, first.hitpoint, second.name, second.hitpoint);

    while(first.hitpoint > 0 && second.hitpoint > 0) {
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
