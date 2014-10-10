#ifndef FONT_H
#define FONT_H

#include <allegro.h>
#include <cassert>
#include <list>
#include <string>

using namespace std;

class Text;

class Font {
    friend class Text;
public:
    Font();
    Font(const string& filename);
    Font(const Font& init);
    virtual ~Font();

protected:
    FONT* data;

    static list<pair<string, FONT*> > instances;
};

#endif

