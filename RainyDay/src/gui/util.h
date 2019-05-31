#ifndef GUIUTIL_H
#define GUIUTIL_H

struct point{
    int x;
    int y;
};

struct size{
    int width;
    int height;
};

struct frame{
    struct point origin;
    struct size size;
};

#endif // GUIUTIL_H
