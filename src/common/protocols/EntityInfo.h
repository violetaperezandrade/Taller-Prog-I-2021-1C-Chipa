#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#define LEN 11

class EntityInfo {
private:
    char info[LEN];
public:
    EntityInfo();
    EntityInfo(char t, int x, int y, int w, int h, char s, char p);
    char* getPtr();
    int getLen();
};

#endif //ENTITYINFO_H
