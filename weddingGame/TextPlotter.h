/* 
 * File:   TextPlotter.h
 * Author: marco
 *
 * Created on 09 July 2013, 22:34
 */

#ifndef TEXTPLOTTER_H
#define	TEXTPLOTTER_H

#include "Allegro.h"
#include <string>
#include <deque>

using std::string;

class ConversationHandler;

class TextPlotter {
public:
    TextPlotter(CompositeSprite&,Color,int,int);
    TextPlotter(const TextPlotter& orig);
    virtual ~TextPlotter();
    
    void pushBackString(string s);
    void popFrontString();
    //return true if it reach the end of a line
    bool postString(Color c=0);
    bool complete();
    
    void clear();
    inline unsigned size(){return lines.size();}
    inline void setColor(Color col){c=col;}
    
    friend class ConversationHandler;
private:
    
    unsigned pos;
    unsigned line;
    
    string font;
    
    deque<string> lines;
    
    CompositeSprite* textLayer;
    CompositeBitmap::iterator current;
    
    Color c;
    
    int initPosX;
    int initPosY;
};

#endif	/* TEXTPLOTTER_H */

