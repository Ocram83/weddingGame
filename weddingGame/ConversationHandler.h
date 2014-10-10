/* 
 * File:   ConversationHandler.h
 * Author: marco
 *
 * Created on 13 July 2013, 14:27
 */

#ifndef CONVERSATIONHANDLER_H
#define	CONVERSATIONHANDLER_H

#include "TextPlotter.h"
#include <map>

//Questa classe è un wrapper per il TextPlotter, ne estende le funzionalita registrando il nome
//del pesonaggio che pronuncia una frase
class ConversationHandler {
public:
    ConversationHandler(CompositeSprite&, Color, int posX=10, int posY=10);
    ConversationHandler(const ConversationHandler& orig);
    virtual ~ConversationHandler();
    
    void setLayer(CompositeSprite&);
    void clear();
    
    void pushBackString(string, string, SampleSound* = 0, int = 0);
    void popFrontSentence();
    //Ritorna true se un personaggio ha terminato la sua battuta
    bool postSentence(Color = 0);
    bool hasNext();

    bool inPause(int);
    bool qualcunoParla(int);
    void setPause(int);
    void setLatenzaFrase(int);
    

    bool wait(int);

    inline int getPause(){return pause;}
    inline int getFrasiCounter(){return frasiCounter;}
    inline int getLatenzaFrase(){return latenzaFrase;}
    
    void playCurrentSentence(int tick);
    
    string getCharacter(int);
    
private:

    TextPlotter plotter;
    
    //Contiene il nome di ogni personaggio nel plotter
    deque<string> names;
    map<string,Color> colors;
    
    int pause;
    int numeroFrasi;
    unsigned frasiCounter;
    int latenzaFrase;
    
    int tickUltimaFrase;
    
    vector<SampleSound*> conversationSentencesSound;
    vector<int> conversationSentencesDuration;
    vector<string> conversationSentencesNames;
    
    bool conversationStarted;
};

#endif	/* CONVERSATIONHANDLER_H */

