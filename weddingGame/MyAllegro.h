/* 
 * File:   MyAllegro.h
 * Author: marco
 *
 * Created on 03 June 2013, 18:16
 */

#ifndef MYALLEGRO_H
#define	MYALLEGRO_H

#include <map>
#include <vector>


#include "Personaggio.h"
#include "TextPlotter.h"
#include "ConversationHandler.h"

enum LevelTicks {PREINTRO=0,INTRO=200,INTROSCENA1=2200,SCENA1=2900,SCENA2=12900,INTROSCENA3=16250,SCENA3=17950,INTROSCENA4=23850,SCENA4=24450,INTROLEVEL1=25950, LEVEL1=27350};
//enum LevelTicks {INTRO=0,SCENA1=2,LEVEL1=10};
//enum LevelTicks {INTRO=0,INTROSCENA1=1,SCENA1=700,SCENA2=6000,SCENA3=7000,SCENA4=8000,LEVEL1=10000};


class MyAllegro : public Allegro{
public:
    MyAllegro();
    virtual ~MyAllegro();
    void onTick();
    
    void initPersonaggi();
    
    inline int getb_height(){return ground_height;}
    inline CompositeSprite& getPlayerLayer(){return playerLayer;}
    inline CompositeSprite& getBackgroundLayer(){return backgroundLayer;}
    inline CompositeSprite& getBulletLayer(){return bulletLayer;}
    inline const unsigned getSpeed()const{return speed;}
    inline const int getWinHeight()const{return winHeight;}
    inline const int getWinWidth()const{return winWidth;}
   
    void prepareInitialScreen(); 
    void initialScreen(); 

        
    void prepareIntro();
    void prepareIntroScena1();
    void prepareIntroScena3();
    void prepareIntroScena4(); 
    void prepareScena1();
    void prepareScena2();
    void prepareScena3();
    void prepareScena4();
    void prepareLevel1();
    void prepareLevel2();
    void prepareLevel3();

    
    void introScena1();
    void introScena3();
    void introScena4();
    void scena1(); 
    void scena2();
    void scena3();
    void scena4();

    void introLevel1();

    void level1();
    void prepareEndlLevel1();
    void endlLevel1();

    void prepareScenaFinale();
    void introScenaFinale();
    void scenaFinale();
    
    void fotoFinale();

    
    void credits();

    
    void clearScene();    

    
    inline const int getSpeed(){return speed;}
    inline const int getLevel(){return level;}
    inline const int getNemicoAttivo(){return nemicoAttivo;}
    
    inline const unsigned getNumOfAliveEnemies(){return numOfAliveEnemies;}

    
    Personaggio* getNemico(string);
    vector<string> getLevelEnemies(unsigned i);
    
    
    Personaggio** getAliveAndActiveEnemies();  
    Personaggio* getFirstAliveEnemy();

        
    inline Personaggio* getEroe(){return eroe;}


private:
    
    void pioggiaDiCuori(unsigned numCuori=30);    
    void fineScena2(); 
    void cuoreEndLevel1(); 
    void cuoreFinale();    


    
    unsigned tick;
    
    CompositeSprite backgroundLayer;
    CompositeSprite energyLayer;
    CompositeSprite playerLayer;
    CompositeSprite bulletLayer;
    CompositeSprite textLayer;
    CompositeSprite textLayerLevel1;
    CompositeSprite fumettoLayer;
    CompositeSprite fumetto;
    
    Personaggio* eroe;
    map<string,Personaggio*> personaggi;
    vector< vector <string> > levelsEnemies;
    map<string,string>  frasiEnemies;
    unsigned numOfLevels;
    
    Personaggio** aliveEnemies;
    unsigned numOfAliveEnemies;
    
    unsigned level;
    
    Circle* myCircle;
    Line* ground;
    
    const int ground_height;
    const unsigned speed;
    
    const int winHeight;
    const int winWidth;
    bool fullScreen;
    
    unsigned int nemicoAttivo;
    
    //Suoni introduzione
    SampleSound introSound;
    SampleSound narrazione1;
    
        
    //Suoni schermata iniziale
    SampleSound initialScreenSound;
    
    //Suoni Scena 1
    SampleSound brusio;
    SampleSound conversazione;
    
    //Suoni Scena 2
    SampleSound happyDappy;

    //Suoni Scena 3
    SampleSound maskedBall;
    
    //Suoni Scena 4
    SampleSound missionImpossible;
    
    //Suoni Livello1
    SampleSound starWars;
    SampleSound winner;
    SampleSound aiuto;
    SampleSound aiuto2;

    //Suoni scena finale
    SampleSound marciaNuziale;
    SampleSound eyeOfTheTiger;

    
    TextPlotter textPlotterIntro;
    ConversationHandler conversationHandlerScena1;
    ConversationHandler conversationHandlerScena3;
    ConversationHandler conversationHandlerScena4;

    
    map<string,CompositeBitmap::iterator> spriteScena1;
    map<string,CompositeBitmap::iterator> spriteScena2;
    map<string,CompositeBitmap::iterator> spriteScena3;
    map<string,CompositeBitmap::iterator> spriteScena4;
    map<string,CompositeBitmap::iterator> spriteLevel1;
    map<string,CompositeBitmap::iterator> spriteScenaFinale;

    list<CompositeBitmap::iterator> cuori;

};

#endif	/* MYALLEGRO_H */

