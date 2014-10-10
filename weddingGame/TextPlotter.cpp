/* 
 * File:   TextPlotter.cpp
 * Author: marco
 * 
 * Created on 09 July 2013, 22:34
 */

#include "TextPlotter.h"
#include <iostream>

using namespace std;

TextPlotter::TextPlotter(CompositeSprite& tL,Color color, int posX=10, int posY=10):pos(0),line(0),font("acme-ext-24.tga"),textLayer(&tL), c(color), initPosX(posX), initPosY(posY){
    current = textLayer->end();
}

TextPlotter::TextPlotter(const TextPlotter& orig) {
    pos = orig.pos;
    textLayer = orig.textLayer;
    current = textLayer->end();
}

TextPlotter::~TextPlotter() {
}

void TextPlotter::clear() {
        
    pos=0;
    line=0;
    
    
    lines.clear();
    
    current=textLayer->end();   
}

bool TextPlotter::postString(Color col){
   
    if(lines.size()<=line)
    {
       current = textLayer->end();
       return true;
    }
        
    if(current!=textLayer->end() && lines[line].length() != pos)
    {
        textLayer->remove(current);
    }    
       
    if(lines[line].length() == pos)
    {
        pos=0;
        line++;

        current = textLayer->end();
        return true;
    }
    
    current= textLayer->add(Text(lines[line].substr(0,++pos), Point(initPosX, initPosY+(initPosY*4*line)), col==0? c : col, Text::ALIGN_LEFT, Font(font)));
    
    
    return false;
}

void TextPlotter::pushBackString(string s)
{
    lines.push_back(s);
}

void TextPlotter::popFrontString()
{
    lines.pop_front();
    if(textLayer->begin()!=textLayer->end())
    textLayer->remove(textLayer->begin());
    
    if(line>0)
        line--;
}

bool TextPlotter::complete()
{
    return lines.size()>=line && pos==lines[line].length();
}