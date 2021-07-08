#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#define LEN 11

class EntityInfo {
private:
    unsigned char info[LEN];
public:
    EntityInfo();
    EntityInfo(int lifes, int points);
    explicit EntityInfo(int end);
    EntityInfo(char t, int x, int y, int w, int h, char s, char p);
    unsigned char* getPtr();
    int getLen();
};

#endif //ENTITYINFO_H
