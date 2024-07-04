#include<stdio.h>

typedef struct MONSTER MONSTER;
typedef struct MOVE MOVE;
typedef struct MOVES MOVES;
typedef struct EFFORT_VALUE EFFORT_VALUE;
typedef struct INDIVIDUAL_VALUE INDIVIDUAL_VALUE;
typedef struct POKEMON POKEMON;

struct MONSTER {
    char name[256];
    int number;
    int hitpoint;
    int attack;
    int block;
    int contact;
    int diffence;
    int speed;
};

struct MOVE {
    char name[256];
    int power;
    //int accuracy
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
    char nickname[256];
    struct MOVES moves;
    int hitpoint;
    int attack;
    int block;
    int contact;
    int diffence;
    int speed;
};

void battle(struct MONSTER mon1, struct MONSTER mon2);

int main(int argv,const char* argc[])
{
    struct MONSTER husigidane = {"husigidane",1,45,49,49,65,65,45};
    struct MONSTER hitokage = {"hitokage",4,39,52,43,60,50,65};
    struct MONSTER zenigane = {"zenigame",7,44,48,65,50,64,43};
    
    battle(husigidane, hitokage);
    return 0;
}

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
