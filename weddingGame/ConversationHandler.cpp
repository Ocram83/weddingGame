/* 
 * File:   ConversationHandler.cpp
 * Author: marco
 * 
 * Created on 13 July 2013, 14:27
 */

#include "ConversationHandler.h"
#include <iostream>

using namespace std;

ConversationHandler::ConversationHandler(CompositeSprite& tL,Color color, int posX, int posY)
        :plotter(tL, color, posX, posY), 
        pause(0),
        numeroFrasi(0), 
        frasiCounter(0),
        latenzaFrase(30),
        tickUltimaFrase(0),
        conversationStarted(false){
}

ConversationHandler::ConversationHandler(const ConversationHandler& orig):plotter(orig.plotter) {
}

ConversationHandler::~ConversationHandler() {
    for(unsigned i=0; i< conversationSentencesSound.size();i++)
        delete conversationSentencesSound[i];
}

void ConversationHandler::setLayer(CompositeSprite& cs)
{
    plotter.textLayer = &cs;
}

void ConversationHandler::clear()
{
    plotter.clear();
    names.clear();
    colors.clear();
    
    pause=0;
    numeroFrasi=0;
    frasiCounter=0;
    latenzaFrase=0;
    
    tickUltimaFrase=0;
    
    cout << "Deleting sound .."<<endl;
    for(unsigned i=0; i< conversationSentencesSound.size();i++)
    {
        cout << i << endl;
        //delete conversationSentencesSound[i];
    }
    conversationSentencesDuration.clear();
    conversationSentencesNames.clear();
    
    conversationStarted=false;
}

void ConversationHandler::pushBackString(string frase, string personaggio, SampleSound* s, int duration)
{
    plotter.pushBackString(frase);
    names.push_back(personaggio);
    if(colors[personaggio]==0)
        colors[personaggio]=Color(255,255,0);
    
    
    if(names.size()==1)
    {
        if(s)
        {
            conversationSentencesDuration.push_back(duration);
            conversationSentencesSound.push_back(s);
            conversationSentencesNames.push_back(personaggio);
        }
        numeroFrasi++;
    }
    else if(*(++names.rbegin())!=personaggio)
    {
         if(s)
         {
            conversationSentencesDuration.push_back(duration);
            conversationSentencesSound.push_back(s);
            conversationSentencesNames.push_back(personaggio);
         }
        numeroFrasi++;
    }
    
}

bool ConversationHandler::postSentence(Color c)
{
    if(pause!=0)
    {
        return true;
    }
    
    // Non ci sono frasi da postare
    if(names.size()<=plotter.line)
        return false;

    //Se la frase è finita
    if(plotter.postString(c==0? (names[plotter.line]!="story"? 0 : Color(0,155,255)) : c))
    {
        //Controllo se non è finito il testo
        if(plotter.lines.size()<= plotter.line )
            return true;
        if(names[plotter.line] == names[plotter.line-1])
            return false;
        else
            return true;
    }
    
    return false;
}

void ConversationHandler::popFrontSentence()
{
    if(names.size()==0)
        return;
    
    string name = names[0];
    
    
    while(name == names[0])
    {
        plotter.popFrontString();
        names.pop_front();
        if(names.size()==0)
            return;
    }
    
}

bool ConversationHandler::hasNext()
{
    return plotter.line < plotter.lines.size();
}

void ConversationHandler::setPause(int p)
{
    pause = p;
}

void ConversationHandler::setLatenzaFrase(int l)
{
    
    latenzaFrase = l < pause?l:pause;
}

bool ConversationHandler::inPause(int ticks)
{
    return pause > 0 ;
}

bool ConversationHandler::wait(int ticks)
{
    //cout << frasiCounter<<" -> pause: "<<pause<<" - latenza: "<<latenzaFrase<<endl;
    
    if(latenzaFrase>=0)
        latenzaFrase--;
    
    if(latenzaFrase==0)
    {
        popFrontSentence();
    }
    
    if(pause>0)
        pause--;
    
    
    if(pause == 0)
    {
        frasiCounter++;
    }
    
    return pause!=0;
}


string ConversationHandler::getCharacter(int ticks)
{   
    if(conversationSentencesNames.size()>0 && frasiCounter < conversationSentencesNames.size() && (!inPause(ticks) || qualcunoParla(ticks)) )
        return conversationSentencesNames[frasiCounter];
     else
        return "idle";
}

void ConversationHandler::playCurrentSentence(int ticks)
{
    if(conversationSentencesSound.size()>0)
    {
        tickUltimaFrase = ticks;
        conversationSentencesSound[frasiCounter]->play();
    }
}

bool ConversationHandler::qualcunoParla(int ticks)
{
    return ticks <= tickUltimaFrase + (conversationSentencesDuration[frasiCounter])*100;
}
