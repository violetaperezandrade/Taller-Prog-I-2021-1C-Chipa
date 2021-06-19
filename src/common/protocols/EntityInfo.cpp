#include "EntityInfo.h"

EntityInfo::EntityInfo() {
    for(int i = 0; i<LEN; i++){
        info[i] = -1;
    }
}

EntityInfo::EntityInfo(char t, int x, int y, int w, int h, char s, char p) {
    info[0] = t;
    info[1] = (x >> 8) & 0xFF;
    info[2] = x & 0xFF;
    info[3] = (y >> 8) & 0xFF;
    info[4] = y & 0xFF;
    info[5] = (w >> 8) & 0xFF;
    info[6] = w & 0xFF;
    info[7] = (h >> 8) & 0xFF;
    info[8] = h & 0xFF;
    info[9] = s;
    info[10] = p;
}

unsigned char * EntityInfo::getPtr() {
    return info;
}

int EntityInfo::getLen() {
    return LEN;
}