#include "../h/collision.h"

//Détection collision entre 2 objets
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    if(maxV(x1, x2) < minV(x1 + w1, x2 + w2) && maxV(y1, y2) < minV(y1 + h1, y2 + h2))
        return (1);
    else
        return(0);
}

int maxV(int x, int y){
    if(x>y)
        return x;
    else
        return y;
}

int minV(int x, int y){
    if(x<y)
        return x;
    else
        return y;
}
