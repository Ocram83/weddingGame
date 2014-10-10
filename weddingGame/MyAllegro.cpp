/* 
 * File:   MyAllegro.cpp
 * Author: marco
 * 
 * Created on 03 June 2013, 18:16
 */

#include "MyAllegro.h"
#include "Nemico.h"
#include "Eroe.h"
#include "Sipario.h"

#include <sstream>
#include <iostream>
#include <cmath>


using namespace std;

MyAllegro::MyAllegro()
        :Allegro(640,480,32,false,false),
        tick(0),
        backgroundLayer(640, 480), 
        energyLayer(640,480),
        playerLayer(640, 480), 
        bulletLayer(640,480),
        textLayer(640,480),
        textLayerLevel1(640,480),
        fumettoLayer(300,300),
        fumetto(640,480),
        numOfLevels(3),
        level(100),
        ground_height(400),
        speed(7),
        winHeight(480),
        winWidth(640),
        fullScreen(false),
        nemicoAttivo(0),
        introSound("intro.wav",20, 128, 1000, false),
        narrazione1("narrazione1.wav",200,128,1000,false),   
        initialScreenSound("vForVincenzo.wav",150, 128, 1000, false),
        brusio("brusio.wav",120,128,1000,false),
        conversazione("conversazione.wav",180,128,1000,false),
        happyDappy("happydappy.wav",128, 128, 1000, false),        
        maskedBall("maskedBall3.wav",150, 128, 1000, false),
        missionImpossible("missionImpossible.wav",128, 128, 1000, false),
        starWars("starWars.wav",128, 128, 1000, false),
        winner("winner.wav",255, 128, 1000, false),
        aiuto("aiuto.wav",128, 128, 1000, false),
        aiuto2("aiuto2.wav",160, 128, 1000, false),
        marciaNuziale("marciaNuziale.wav",160, 128, 1000, false),
        eyeOfTheTiger("eyeOfTheTiger.wav",220, 128, 1000, false),
        textPlotterIntro(textLayer,Color(255,255,255),10,10),
        conversationHandlerScena1(textLayer,Color(255,0,0),10,10),
        conversationHandlerScena3(textLayer,Color(255,0,0),10,10),
        conversationHandlerScena4(textLayer,Color(255,0,0),10,10)
{
    //myCircle = new Circle(Point(40,background_height-10),10, Color(255,0,0), true);
    //add(DrawablePointer(*myCircle));
   
    add(DrawablePointer(backgroundLayer));
    initPersonaggi();
    
    srand(time(0));
    

    //ground = new Line(Point(30,ground_height),Point(640,ground_height),Color(255,0,0));
    //backgroundLayer.add(DrawablePointer(*ground));
    
}


MyAllegro::~MyAllegro() {
    
    if (level < 10)
    {
      //  for(unsigned i=0;i<personaggi.size();i++)
        //    delete personaggi[i];
        delete eroe;
        delete [] aliveEnemies;
    }
   // backgroundSound.stop();
}

void MyAllegro::initPersonaggi()
{
    levelsEnemies.push_back(vector<string>());
    
    eroe = new Eroe(this,50,150,"vinc",50, DESTRA, 10);
    
    personaggi.insert(pair<string, Personaggio*>("fotia",new Nemico(this,60,120,"fotia",450, SINISTRA, 3,10,10,2,7,"pallone.bmp")));
    personaggi.insert(pair<string, Personaggio*>("luca",new Nemico(this,75,140,"luca",450, SINISTRA, 3,10,10,2,7,"stellina.bmp")));
    personaggi.insert(pair<string, Personaggio*>("aligi",new Nemico(this,75,140,"aligi",450, SINISTRA, 3,10,10,2,7,"cavolfiore.bmp")));
    personaggi.insert(pair<string, Personaggio*>("riks",new Nemico(this,65,140,"riks",450, SINISTRA, 3,10,10,2,7,"leccaLecca.bmp")));
    personaggi.insert(pair<string, Personaggio*>("cardo",new Nemico(this,50,140,"cardo",450, SINISTRA, 3,10,10,2,7,"hawaianas.bmp")));
    personaggi.insert(pair<string, Personaggio*>("savio",new Nemico(this,55,150,"savio",450, SINISTRA, 3,10,10,2,7,"microfono.bmp")));
    personaggi.insert(pair<string, Personaggio*>("marco", new Nemico(this,55,140,"marco",350, SINISTRA, 3,10,10,2,7,"nota.bmp")));
    
    
    levelsEnemies[0].push_back("fotia");
    levelsEnemies[0].push_back("savio");
    levelsEnemies[0].push_back("luca");
    levelsEnemies[0].push_back("riks");
    levelsEnemies[0].push_back("cardo");
    levelsEnemies[0].push_back("marco");
    levelsEnemies[0].push_back("aligi");
    
    frasiEnemies.insert(pair<string,string>("savio","Ti impediremo di fare questa follia"));
    frasiEnemies.insert(pair<string,string>("marco","Ci tieni così tanto a sconfiggerci?"));
    frasiEnemies.insert(pair<string,string>("riks","Ripensaci finche sei in tempo!"));
    frasiEnemies.insert(pair<string,string>("cardo","Il piano era rimanere single a vita"));
    frasiEnemies.insert(pair<string,string>("luca","Non fare il passo più lungo mmm.."));
    frasiEnemies.insert(pair<string,string>("luca2","... vabbè, della gamba!"));
    frasiEnemies.insert(pair<string,string>("aligi","Attento!!! Se mi sconfiggi ti sposi!"));

    
}

void MyAllegro::clearScene()
{
    backgroundLayer.clear();
    energyLayer.clear();
    playerLayer.clear();
    bulletLayer.clear();
    textLayer.clear();
    fumettoLayer.clear();
    fumetto.clear();
    
    introSound.stop();
    narrazione1.stop();
    brusio.stop();
    conversazione.stop();    
    happyDappy.stop();
    maskedBall.stop();

    textPlotterIntro.clear();
    conversationHandlerScena1.clear();
    
    spriteScena1.clear();
    spriteScena2.clear();
    spriteScena3.clear();
    spriteScena4.clear();
    spriteLevel1.clear();
}

void MyAllegro::prepareLevel1()
{
    add(DrawablePointer(playerLayer));
    add(DrawablePointer(bulletLayer));
    add(DrawablePointer(energyLayer));
    add(DrawablePointer(textLayerLevel1));

    
    Sprite floor("castello.bmp", Point(0,0));
    backgroundLayer.add(floor);
    
    //for(unsigned j=0;j<levelsEnemies[0].size();j++)
    playerLayer.add(DrawablePointer(*personaggi[levelsEnemies[0][0]]));
    
    Sprite vale("valentinaCorpo.bmp",Point(115,129));
    vale.setScaleHeight(0.15f);
    vale.setScaleWidth(0.15f);
    
    spriteLevel1.insert(pair<string,CompositeBitmap::iterator>("valentinaCorpo",backgroundLayer.add(vale)));
    
    for(unsigned j=1;j<levelsEnemies[0].size();j++)
    {
        stringstream ss;
        ss<<levelsEnemies[0][j]<<".bmp";

        Sprite c(ss.str(),Point(100+j*30,getb_height()-150));
        c.setScaleHeight(0.15f);
        c.setScaleWidth(0.15f);
        
        spriteLevel1.insert(pair<string,CompositeBitmap::iterator>(levelsEnemies[0][j],backgroundLayer.add(c)));
    }
        
    playerLayer.add(DrawablePointer(*eroe));

    playerLayer.setNotification(ON_TICK);
    bulletLayer.setNotification(ON_TICK);

    
    aliveEnemies = new Personaggio*[1];
    
    numOfAliveEnemies = 1;
    
    missionImpossible.stop();
    starWars.play();
}

void MyAllegro::prepareLevel2()
{}


void MyAllegro::prepareLevel3()
{}

void MyAllegro::prepareInitialScreen()
{
    Sprite initialScreen("initialScreen.bmp", Point(0,0));
    backgroundLayer.add(initialScreen);
    initialScreenSound.play();
}    

void MyAllegro::prepareIntroScena1()
{
    
    textLayer.clear();
    introSound.stop();
    narrazione1.stop();
    brusio.setLoop(true);
    brusio.play();
        
    Sprite floor("henry.bmp", Point(0,0));
    backgroundLayer.add(floor);
    
    Sprite vinc("vinc.bmp", Point(200,260));
    vinc.setScaleHeight(0.3f);
    vinc.setScaleWidth(0.3f);
    string vincName="vincenzo";
    
    Sprite marco("marco.bmp", Point(270,290));
    marco.setScaleHeight(0.33f);
    marco.setScaleWidth(0.33f);
    string marcoName="marco";


    Sprite fotia("fotia.bmp", Point(130,335));
    fotia.setScaleHeight(0.55f);
    fotia.setScaleWidth(0.4f);
    string fotiaName="fotia";

    Sprite vale("valentina.bmp", Point(420,240));
    vale.setScaleHeight(0.35f);
    vale.setScaleWidth(0.35f);
    string valeName="valentina";
    
    Sprite comparsa1("comparsa1.bmp", Point(470,250));
    comparsa1.setScaleHeight(0.4f);
    comparsa1.setScaleWidth(0.4f);
    
    Sprite comparsa2("comparsa2.bmp", Point(10,310));    
    comparsa2.setScaleHeight(0.35f);
    comparsa2.setScaleWidth(0.35f);

    Sprite comparsa3("comparsa3.bmp", Point(520,250));
    comparsa3.setScaleHeight(0.45f);
    comparsa3.setScaleWidth(0.45f);

    Sprite comparsa4("comparsa4.bmp", Point(370,245));
    
    comparsa4.setScaleHeight(0.45f);
    comparsa4.setScaleWidth(0.45f);

    Sprite comparsa5("comparsa5.bmp", Point(80,260));
    comparsa5.setScaleHeight(0.55f);
    comparsa5.setScaleWidth(0.55f);
    
    Sprite comparsa6("comparsa6.bmp", Point(560,240));
    comparsa6.setScaleHeight(0.4f);
    comparsa6.setScaleWidth(0.4f);



    spriteScena1.insert(pair<string,CompositeBitmap::iterator>("comparsa1",backgroundLayer.add(comparsa1)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>("comparsa2",backgroundLayer.add(comparsa2)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>("comparsa4",backgroundLayer.add(comparsa4)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>("comparsa5",backgroundLayer.add(comparsa5)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>("comparsa6",backgroundLayer.add(comparsa6)));

    
    
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>(vincName,backgroundLayer.add(vinc)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>(marcoName,backgroundLayer.add(marco)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>(fotiaName,backgroundLayer.add(fotia)));
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>(valeName,backgroundLayer.add(vale)));
   
    //Più avanti nella prospettiva
    spriteScena1.insert(pair<string,CompositeBitmap::iterator>("comparsa3",backgroundLayer.add(comparsa3)));
    
    conversationHandlerScena1.pushBackString("Ragà oggi è la stessa  ",marcoName,new SampleSound("scena1-0.wav",255, 128, 1000, false),4);
    conversationHandlerScena1.pushBackString("solfa di ieri...",marcoName);
    conversationHandlerScena1.pushBackString("e domani sarà la stessa solfa ",marcoName);
    conversationHandlerScena1.pushBackString("di oggi.",marcoName);

    conversationHandlerScena1.pushBackString("Marcù mal comune,",vincName, new SampleSound("scena1-1.wav",255, 128, 1000, false),4);
    conversationHandlerScena1.pushBackString("mezzo gaudio.",vincName);
    
    conversationHandlerScena1.pushBackString("Oh guaggliù, pomeriggio ",fotiaName,new SampleSound("scena1-2.wav",255, 128, 1000, false),6);
    conversationHandlerScena1.pushBackString("haiu fattu nu gol che ",fotiaName);
    conversationHandlerScena1.pushBackString("mancu Shevchenko mi po\'!!",fotiaName);
    conversationHandlerScena1.pushBackString("Tinitimi tinitimi!!!",fotiaName);
    
    conversationHandlerScena1.pushBackString("Quand\'ecco che durante il","story", new SampleSound("scena1-3.wav",255, 128, 1000, false),7);
    conversationHandlerScena1.pushBackString("discorso  dei giovani amici, ","story");
    conversationHandlerScena1.pushBackString("Vincenzo scorgeva tra la folla ","story");
    conversationHandlerScena1.pushBackString("un volto conosciuto.","story");

    conversationHandlerScena1.pushBackString("IIIIIIIIII o guggliù Chilla ",vincName, new SampleSound("scena1-4.wav",255, 128, 1000, false),6);
    conversationHandlerScena1.pushBackString("era cu mia alli alimentari ",vincName);
    conversationHandlerScena1.pushBackString("ed è da Bella puru illa. ",vincName);

    conversationHandlerScena1.pushBackString("O Vicì e vacci a parrari, no!",fotiaName, new SampleSound("scena1-5.wav",255, 128, 1000, false),2);

    conversationHandlerScena1.pushBackString("No guggliù e ki ci cuntu?",vincName, new SampleSound("scena1-6.wav",255, 128, 1000, false),3);
    
    conversationHandlerScena1.pushBackString("Se lo fai, diventerai il mio idolo",marcoName,  new SampleSound("scena1-7.wav",255, 128, 1000, false),4);
    conversationHandlerScena1.pushBackString("... sempre dopo Cardillo però!!",marcoName);

    conversationHandlerScena1.pushBackString("(si schiarisce la voce) Vabbè!! ",vincName, new SampleSound("scena1-8.wav",255, 128, 1000, false),2);    
    conversationHandlerScena1.pushBackString("Allora io vado!!",vincName);    

    conversationHandlerScena1.pushBackString("IIIIIIIIIIII. O Vincè vacci serio ",fotiaName, new SampleSound("scena1-9.wav",255, 128, 1000, false),6);    
    conversationHandlerScena1.pushBackString("però un ci ridiri intra a faccia ",fotiaName);    
    conversationHandlerScena1.pushBackString("cumu allu solito tua.",fotiaName);    

    conversationHandlerScena1.pushBackString("Giovà secondo me u minanu, ",marcoName, new SampleSound("scena1-10.wav",255, 128, 1000, false),5);
    conversationHandlerScena1.pushBackString("chiama subito ad Aligi accussì ",marcoName);
    conversationHandlerScena1.pushBackString("si i pia tutti illu.",marcoName);
    
    conversationHandlerScena1.pushBackString("Dopo i commenti dei due amici, ","story", new SampleSound("scena1-11.wav",255, 128, 1000, false),4);    
    conversationHandlerScena1.pushBackString("Vincenzo fa ritorno ridendo..... ","story");    
    conversationHandlerScena1.pushBackString("(commento fuori luogo) ","story");    

    conversationHandlerScena1.pushBackString("Guaggliù ma ha datu u numeru!!!! ",vincName, new SampleSound("scena1-12.wav",255, 128, 1000, false),5); 
    conversationHandlerScena1.pushBackString("Me ne vado",vincName); 
    
    conversationHandlerScena1.pushBackString("Di fronte all\'incredulità dei ","story", new SampleSound("scena1-13.wav",255, 128, 1000, false),8);
    conversationHandlerScena1.pushBackString("colleghi  di sventure e allo  ","story");
    conversationHandlerScena1.pushBackString("stupore generale di tutto","story");
    conversationHandlerScena1.pushBackString("il locale, si concludeva","story");
    conversationHandlerScena1.pushBackString("così la serata.","story");    
    
}

void MyAllegro::prepareIntroScena3()
{
    happyDappy.stop();
    backgroundLayer.clear();
    
    Sprite floor("stanzaBuia.bmp", Point(0,0));
    backgroundLayer.add(floor);
    
    maskedBall.play();
    
    Sprite marco("marco.bmp", Point(200,260));
    marco.setScaleHeight(0.26f);
    marco.setScaleWidth(0.26f);
    string marcoName="marco";


    Sprite fotia("fotia.bmp", Point(150,300));
    fotia.setScaleHeight(0.45f);
    fotia.setScaleWidth(0.3f);
    string fotiaName="fotia";
    
    Sprite luca("luca.bmp", Point(350,260));
    luca.setScaleHeight(0.26f);
    luca.setScaleWidth(0.26f);
    string lucaName="luca";
    
    Sprite savio("savio.bmp", Point(390,250));
    savio.setScaleHeight(0.35f);
    savio.setScaleWidth(0.32f);
    string savioName="savio";
    
    Sprite cardo("cardo.bmp", Point(440,250));
    cardo.setScaleHeight(0.25f);
    cardo.setScaleWidth(0.25f);
    string cardoName="cardo";
    
    Sprite aligi("aligi.bmp", Point(300,310));
    aligi.setScaleHeight(0.40f);
    aligi.setScaleWidth(0.40f);
    string aligiName="aligi";
    
    Sprite riks("riks.bmp", Point(480,310));
    riks.setScaleHeight(0.25f);
    riks.setScaleWidth(0.25f);
    string riksName="riks";
    
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(marcoName,backgroundLayer.add(marco)));
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(fotiaName,backgroundLayer.add(fotia)));
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(lucaName,backgroundLayer.add(luca)));
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(cardoName,backgroundLayer.add(cardo)));
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(savioName,backgroundLayer.add(savio)));
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(aligiName,backgroundLayer.add(aligi)));
    spriteScena3.insert(pair<string,CompositeBitmap::iterator>(riksName,backgroundLayer.add(riks)));  
    
    conversationHandlerScena3.pushBackString("Vi abbiamo convocato ",fotiaName,new SampleSound("scena3-1.wav",255, 128, 1000, false),8);
    conversationHandlerScena3.pushBackString("per darvi una notizia",fotiaName);
    conversationHandlerScena3.pushBackString("tanto sconvolgente",fotiaName);
    conversationHandlerScena3.pushBackString("quanto sconcertante!",fotiaName);
    conversationHandlerScena3.pushBackString("(commento fuori luogo)",fotiaName);
    
    conversationHandlerScena3.pushBackString("Vincenzo è in procinto",marcoName,new SampleSound("scena3-2.wav",255, 128, 1000, false),8);
    conversationHandlerScena3.pushBackString("di lasciare la compagnia",marcoName);
    conversationHandlerScena3.pushBackString("(... preoccuapazione generale ...)",marcoName);
    conversationHandlerScena3.pushBackString("A CAUSA DI UNA RAGAZZA!!",marcoName);
    
    conversationHandlerScena3.pushBackString("No ragazzi!",lucaName,new SampleSound("scena3-3.wav",255, 128, 1000, false),8);    
    conversationHandlerScena3.pushBackString("Abbiamo il dovere",lucaName);
    conversationHandlerScena3.pushBackString("di mettergli il bastone",lucaName);
    conversationHandlerScena3.pushBackString("tra le...(lucata)",lucaName);
    conversationHandlerScena3.pushBackString("va beh ruote!!",lucaName);
    
    conversationHandlerScena3.pushBackString("Oh.. organizziamo",cardoName,new SampleSound("scena3-4.wav",255, 128, 1000, false),3);
    conversationHandlerScena3.pushBackString("un rapimento!!",cardoName);
    
    conversationHandlerScena3.pushBackString("Il treruote",aligiName,new SampleSound("scena3-5.wav",255, 128, 1000, false),3);
    conversationHandlerScena3.pushBackString("è a disposizione!!",aligiName); 
     
    conversationHandlerScena3.pushBackString("Bene! Portiamola ",savioName,new SampleSound("scena3-6.wav",255, 128, 1000, false),6);
    conversationHandlerScena3.pushBackString("a  Pianopoli a casa ",savioName);
    conversationHandlerScena3.pushBackString("di Giovanni finchè",savioName);
    conversationHandlerScena3.pushBackString("Vincenzo non tornerà ",savioName);
    conversationHandlerScena3.pushBackString("in sé!",savioName);

    conversationHandlerScena3.pushBackString("Approvazione generale","story", new SampleSound("scena3-7.wav",255, 128, 1000, false),8);

    conversationHandlerScena3.pushBackString("Uaglù, Vincenzo un giorno ",riksName,new SampleSound("scena3-8.wav",255, 128, 1000, false),4);
    conversationHandlerScena3.pushBackString("ci ringrazierà per questo!",riksName);

}

void MyAllegro::prepareScena1()
{
    backgroundLayer.add(Sipario(0,0,640,200,ColorAlpha(255,255,255,128)));
}

void MyAllegro::prepareScena2()
{   
    backgroundLayer.clear();
    textLayer.clear();
    
    brusio.stop();
    
    Sprite vinc("vinc.bmp", Point(10,238));
    vinc.setScaleHeight(0.20f);
    vinc.setScaleWidth(0.20f);
    string vincName="vincenzo";
    
    Sprite vale("valentina.bmp", Point(45,236));
    vale.setScaleHeight(0.28f);
    vale.setScaleWidth(0.28f);
    string valeName="valentina";
    
    happyDappy.play();
    
    Sprite floor("sfondoMare.bmp", Point(0,0));
    backgroundLayer.add(floor);
    
    backgroundLayer.add(Sipario(0,0,640,150,ColorAlpha(255,255,255,128)));
    
    spriteScena2.insert(pair<string,CompositeBitmap::iterator>(vincName,backgroundLayer.add(vinc)));
    spriteScena2.insert(pair<string,CompositeBitmap::iterator>(valeName,backgroundLayer.add(vale)));
}

void MyAllegro::prepareScena3()
{
    backgroundLayer.add(Sipario(0,0,640,250,ColorAlpha(255,255,255,128)));
}

void MyAllegro::prepareIntroScena4()
{
    backgroundLayer.clear();
    textLayer.clear();
    maskedBall.stop();
    
    Sprite floor("sfondoMare.bmp", Point(0,0));
    backgroundLayer.add(floor);
    
     Sprite vinc("vinc.bmp", Point(280,238));
    vinc.setScaleHeight(0.20f);
    vinc.setScaleWidth(0.20f);
    string vincName="vincenzo";
    
    Sprite vale("valentina.bmp", Point(315,236));
    vale.setScaleHeight(0.28f);
    vale.setScaleWidth(0.28f);
    string valeName="valentina";
    
    Sprite apeAligi("apeAligi.bmp", Point(-300,236));
    apeAligi.setScaleHeight(0.60f);
    apeAligi.setScaleWidth(0.60f);
    string apeAligiName="aligiApe";
    
    missionImpossible.play();
    
    spriteScena4.insert(pair<string,CompositeBitmap::iterator>(vincName,backgroundLayer.add(vinc)));
    spriteScena4.insert(pair<string,CompositeBitmap::iterator>(valeName,backgroundLayer.add(vale)));
    spriteScena4.insert(pair<string,CompositeBitmap::iterator>(apeAligiName,backgroundLayer.add(apeAligi)));
    
    conversationHandlerScena4.pushBackString("Ti piglio ti piglio ti piglio... ", "aligi",new SampleSound("scena4-1.wav",255, 128, 1000, false),8);
    
    conversationHandlerScena4.pushBackString("Eh biiiii!! ", vincName, new SampleSound("scena4-2.wav",255, 128, 1000, false),8);

    conversationHandlerScena4.pushBackString("Braccia forti per la mia terra  ", "aligi", new SampleSound("scena4-3.wav",255, 128, 1000, false),8);

}


void MyAllegro::prepareScena4()
{
}

void MyAllegro::prepareIntro()
{

    add(DrawablePointer(textLayer));
    
    backgroundLayer.clear();
    initialScreenSound.stop();

    textPlotterIntro.pushBackString("Era una cupa sera di luglio");
    textPlotterIntro.pushBackString("quando tre amici di vecchia data ");
    textPlotterIntro.pushBackString("si riunivano in un noto locale");
    textPlotterIntro.pushBackString("della movida lametina. ");
    textPlotterIntro.pushBackString("");
    textPlotterIntro.pushBackString("Come spesso avveniva in quelle ");
    textPlotterIntro.pushBackString("tristi serate, i tre baldi giovani ");
    textPlotterIntro.pushBackString("sorseggiavano birra discorrendo ");
    textPlotterIntro.pushBackString("sul gentil sesso presente ");
    textPlotterIntro.pushBackString("nel locale.");
    
    introSound.setLoop(true);
    introSound.play();
    
    narrazione1.play();

}

void MyAllegro::prepareScenaFinale()
{
    backgroundLayer.clear();
    bulletLayer.clear();
    playerLayer.clear();
    textLayer.clear();
    textLayerLevel1.clear();
    
    starWars.stop();
    
    Sprite floor("chiesa.bmp", Point(0,0));
    backgroundLayer.add(floor);
    
    Sprite vinc("vincSposo.bmp", Point(10,295));
    vinc.setScaleHeight(0.25f);
    vinc.setScaleWidth(0.25f);
    string vincName="vincenzo";
    
    Sprite vale("valentinaSposa.bmp", Point(45,300));
    vale.setScaleHeight(0.28f);
    vale.setScaleWidth(0.28f);
    string valeName="valentina";
    
    spriteScenaFinale.insert(pair<string,CompositeBitmap::iterator>(vincName,backgroundLayer.add(vinc)));
    spriteScenaFinale.insert(pair<string,CompositeBitmap::iterator>(valeName,backgroundLayer.add(vale)));
    
    marciaNuziale.play();
}

void MyAllegro::introScenaFinale()
{
     /** INTRUDUZIONE, COMPARE LA SCENA*/
    
    static bool sipario=false;
    static CompositeBitmap::iterator it;
    static int alpha=255;
    
    if(!sipario)
    {
        sipario = true;
        it = backgroundLayer.add(Sipario(0,0,640,480,ColorAlpha(0,0,0,255)));
    }
    else{  
  
        if(tick%2==0)
            if(alpha>=0)
            {
                Sipario* sp = dynamic_cast<Sipario*> ((*it));
                sp->setColor(ColorAlpha(0,0,0,alpha));

               alpha--;
            }
        
        if(alpha==0)
        {
            level++;
        }
    }
}

void MyAllegro::scenaFinale()
{
    static int numOfTicks=0;
    static bool vincScompare=false;
    static bool valeScompare=false;
    
    const int vel=20;
    
    numOfTicks++;
    
    if(numOfTicks>120)
    {
        if(tick%vel==0)
        {
            if(!vincScompare)
            {        
                //MOVIMENTO VINCENZO
                Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScenaFinale["vincenzo"]));

                int pointX = vinc->getLeftTopCorner().getX()+3;
                int pointY = vinc->getLeftTopCorner().getY();

                if(tick%(vel*5)==0)
                    pointY-=1;

                vinc->setLeftTopCorner(Point(pointX,pointY));

                float scaleX = vinc->getScaleWidth()-0.0014f;
                float scaleY = vinc->getScaleHeight()-0.0014f;

                vinc->setScaleHeight(scaleY);
                vinc->setScaleWidth(scaleX);

                int angle= vinc->getAngle();

                if(tick%(vel*2)==0)
                    angle+= 1;
                else
                    angle-= 1;

                vinc->setAngle(angle);

                //FINE MOVIMENTO VINCENZO
                
                if(310-pointX<4)
                {
                    backgroundLayer.remove(spriteScenaFinale["vincenzo"]);
                    vincScompare=true;
                }
            }
            
            if(!valeScompare)
            {
                //MOVIMENTO VALENTINA
                Sprite* valentina = dynamic_cast<Sprite*> (*(spriteScenaFinale["valentina"]));

                int pointX;
                if(tick%(vel*5)==0)
                    pointX = valentina->getLeftTopCorner().getX()+2;
                else
                    pointX = valentina->getLeftTopCorner().getX()+3;

                int pointY = valentina->getLeftTopCorner().getY();

                if(tick%(vel*5)==0)
                    pointY-=1;

                valentina->setLeftTopCorner(Point(pointX,pointY));

                float scaleX = valentina->getScaleWidth()-0.0016f;
                float scaleY = valentina->getScaleHeight()-0.0016f;

                valentina->setScaleHeight(scaleY);
                valentina->setScaleWidth(scaleX);

                int angle= valentina->getAngle();

                if(tick%(vel*2)==0)
                    angle+= 1;
                else
                    angle-= 1;

                valentina->setAngle(angle);

                //FINE MOVIMENTO VALENTINA
                
                 if(310-pointX<3)
                {
                    backgroundLayer.remove(spriteScenaFinale["valentina"]);
                    valeScompare=true;
                }
            }
            
            
        }
    }
    
    if(numOfTicks>= 400 && numOfTicks<=1300)
    {
        static CompositeBitmap::iterator it;
        static bool ended=false;        
        if(tick%80==0)
        {
            ended=true;
            Sprite start("gameOver.bmp",Point(260,10));
            start.setScaleHeight(0.3f);
            start.setScaleWidth(0.3f);

            it =  backgroundLayer.add(start);
        }
        else if(tick%80==50 && ended)
        {
            backgroundLayer.remove(it);
        }
        
    }
    
    if(numOfTicks>= 1300)
        cuoreFinale();
            
    if(numOfTicks== 1400)
    {
        textLayer.add(Text("The End", Point(240,210), Color(0,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
       
    }
    
    if(numOfTicks == 2100)
        level++;

}

void MyAllegro::fotoFinale()
{
    static int tickParziali = 0;
    
    if(tickParziali==0)
    {
        marciaNuziale.stop();
        backgroundLayer.clear();
        textLayer.clear();

        backgroundLayer.add((Sprite("fotoFinale.bmp",Point(0,0))));
    }
    
    tickParziali++;
    
    if(tickParziali == 2000)
        level++;
       
}


void MyAllegro::credits()
{
    eyeOfTheTiger.play();
    backgroundLayer.clear();
    textLayer.clear();
    
    backgroundLayer.add((Sprite("credits.bmp",Point(0,0))));
}

Personaggio* MyAllegro::getNemico(string name)
{
    return personaggi[name];
    
}

Personaggio* MyAllegro::getFirstAliveEnemy()
{
    for(unsigned i=0; i < levelsEnemies[level].size(); i++)
    {
        if(personaggi[levelsEnemies[level][i]]->alive())
        {
            return personaggi[levelsEnemies[level][i]];
        }
    }
    
    return 0;
}

Personaggio** MyAllegro::getAliveAndActiveEnemies()
{
    assert(levelsEnemies.size()> level);
    assert(aliveEnemies);
    
    delete [] aliveEnemies;
  /*
    for(unsigned i=0; i < levelsEnemies[level].size(); i++)
        if(personaggi[levelsEnemies[level][i]]->alive())
            numOfAliveEnemies++;
    
    aliveEnemies = new Personaggio*[numOfAliveEnemies];
    unsigned pos=0;
    
    for(unsigned i=0; i < levelsEnemies[level].size(); i++)
    {
        if(personaggi[levelsEnemies[level][i]]->alive())
        {
            aliveEnemies[pos++]= personaggi[levelsEnemies[level][i]];
        }
    }
    */      
    
    if(nemicoAttivo<levelsEnemies[level].size())
    {
        numOfAliveEnemies = 1;
        aliveEnemies = new Personaggio*[1];
        aliveEnemies[0]= personaggi[levelsEnemies[level][nemicoAttivo]];
    }
    else
    {
        numOfAliveEnemies = 0;
        aliveEnemies = new Personaggio*[0];
    }
    return aliveEnemies;
    
}


vector<string> MyAllegro::getLevelEnemies(unsigned i)
{
    if(numOfLevels>i)
    {
        return levelsEnemies[i];
    }
    return vector<string>();
}



void MyAllegro::onTick()
{ 
    Allegro::onTick();

   // cout<< "tick:" << tick<< endl;
    
    if(level==100 )
    {
        //rest(20000);
        prepareInitialScreen();
        level++;
    }
    if(level ==101)
    {
        initialScreen();
        
        if(getKeyboard().isKeyPressed(KEY_SPACE)) {
            level=10;
            tick=0;
            
          }
               
    }   
    if(level==10 )
    {
        if(tick==PREINTRO)
        {
            backgroundLayer.clear();
            initialScreenSound.stop();
        }
        if(tick==INTRO)
            prepareIntro();
        if(tick==INTROSCENA1)
            level++;
        else
        {
            if(tick%7==0)
                textPlotterIntro.postString();
        }
    }
    if(level==11 )
    {
        if(tick==INTROSCENA1)
            prepareIntroScena1();
        if(tick==SCENA1)
            level++;
        else
            introScena1();
        
    }
    if(level==12 )
    {
        if(tick==SCENA1)
            prepareScena1();
        else if(tick==SCENA2)
            level++;
        else 
            scena1();
        

    }
    if(level==13 )
    {
        if(tick==SCENA2)
            prepareScena2();
        else if(tick==INTROSCENA3)
            level++;
        else 
        {
            scena2();
        }

    }
    if(level==14 )
    {
        if(tick==INTROSCENA3)
            prepareIntroScena3();
        if(tick==SCENA3)
            level++;
        else
            introScena3();
        
    }
    if(level==15 )
    {
        if(tick==SCENA3)
            prepareScena3();
        else if(tick==INTROSCENA4)
            level++;
        else 
        {
            scena3();
        }
    }
    if(level==16 )
    {
        if(tick==INTROSCENA4)
            prepareIntroScena4();
        if(tick==SCENA4)
            level++;
        else
            introScena4();
        
    }
    if(level==17 )
    {
        if(tick==SCENA4)
            prepareScena4();
        else if(tick>SCENA4)
            scena4();
        if(tick==INTROLEVEL1)
        {
            level=200;
            backgroundLayer.clear();   
        }
    }
    
    if(level==200)
    {
        if(tick==INTROLEVEL1)
            introLevel1();
        else if(tick==LEVEL1)
                level=0;
    }
    
    if(level==0)
    {
        if(tick==LEVEL1)
        {
            prepareLevel1();
        }
        level1();
        
    }
    else if(level==1)
    {         
        static bool finito=false;
        if(!finito)
        {
            finito=true;
            playerLayer.unsetNotification(ON_TICK);
            bulletLayer.unsetNotification(ON_TICK);
            if(eroe->getEnergy()>0)
            {
                winner.play();
               // textLayer.add(Text("You win!!", Point(640/2, 480/2-80), Color(255,0,0), Text::ALIGN_CENTER, Font("arcanum_bold_48.tga")));
            }
            else
                textLayer.add(Text("Game Over!", Point(640/2, 480/2-80), Color(255,0,0), Text::ALIGN_CENTER, Font("arcanum_bold_48.tga")));
        }
        else
        {
            prepareEndlLevel1();
            level++;
        }
    }
    else if(level==2)
    {  
        endlLevel1();
    }
    
    else if(level==3)
    {
        static bool finalSceneReady = false;
        
        if(!finalSceneReady)
        {
            prepareScenaFinale();
            finalSceneReady=true;
        }
        else
        {
            introScenaFinale();
        }
    }
    else if(level==4)
    {
        scenaFinale();
    }
        else if(level==5)
    {
        fotoFinale();
    }
    else if(level==6)
    {
        credits();
        level++;
    }
    
    if(++tick % 10 == 0) {

        if(getKeyboard().isKeyPressed(KEY_Q)) {
              exit = true;
          }
        
        if(getKeyboard().isKeyPressed(KEY_1)) {
            tick=INTRO;
            level=10;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_2)) {
            tick=INTROSCENA1;
            level=11;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_3)) {
            tick=SCENA2;
            level=13;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_4)) {
            tick=INTROSCENA3;
            level=14;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_5)) {
            tick=INTROSCENA4;
            level=16;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_0)) {
            tick=LEVEL1;
            level=0;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_9)) {
            level=3;
            clearScene();
          }
        if(getKeyboard().isKeyPressed(KEY_8)) {
            level=5;
          }
        if(getKeyboard().isKeyPressed(KEY_F)) {
           
            if(!fullScreen)
            {
                fullScreen= true;
                set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,640,480,0,0);
            }
            else 
            {
                fullScreen= false;
                set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);
            }
          }
    }
         draw();

     
}

void MyAllegro::initialScreen()
{
    static CompositeBitmap::iterator it;
    
    if(tick%100==0)
    {
        Sprite start("space.bmp",Point(175,370));
       // start.setScaleHeight(0.7f);
       // start.setScaleWidth(0.7f);
        
        it =  backgroundLayer.add(start);
    }
    else if(tick%100==60)
    {
        backgroundLayer.remove(it);
    }
        
    
}  

void MyAllegro::introLevel1()
{
    backgroundLayer.clear();

    Sprite istruzioni("istruzioni.bmp", Point(0,0));
   // istruzioni.setScaleHeight(0.4f);
   // istruzioni.setScaleWidth(0.4f);
    
    backgroundLayer.add(istruzioni);
    
}
void MyAllegro::level1()
{
    static CompositeBitmap::iterator it;
    static int frase= 0;
    
    if(tick%400==0)
    {
        if(frase%3 <= 1)
        {
            Sprite start("aiuto.bmp",Point(135,85));
            start.setScaleHeight(0.4f);
            start.setScaleWidth(0.4f);

            it =  textLayer.add(start);

            aiuto.play();
        }
        else
        {
            Sprite start("aiuto2.bmp",Point(135,85));
            start.setScaleHeight(0.4f);
            start.setScaleWidth(0.4f);

            it =  textLayer.add(start);

            aiuto2.play();
        }
        frase++;
    }
    else if(tick%400==60)
    {
        if(frase%3 >= 1 )
        {
            textLayer.remove(it);
        }
    }
    else if(tick%400==150)
    {
        if(frase%3 == 0 && frase != 0)
        {
            textLayer.remove(it);
        }
    }
    
    //ENERGY
    energyLayer.clear();

    energyLayer.add(Sprite("barra.bmp",Point(0,440)));

    stringstream s;
    s << "Energia Vincenzo: ";
    
    energyLayer.add(Text(s.str(),Point(0,460)));
    
    for(unsigned i=0;i<eroe->getEnergy();i++)
    {
        Sprite cuoreSmall("cuoreSmall.bmp",Point(15*i+140,455));
        cuoreSmall.setScaleHeight(0.6f);
        cuoreSmall.setScaleWidth(0.6f);
        energyLayer.add(cuoreSmall);
    }

    
    //energyLayer.add(Text)
   
    static bool livelloFinito = false;
    static int forzaAmore=-1;
    static CompositeSprite::iterator itAmore;
          
    if(!livelloFinito)
    {
       
        if(eroe->getEnergy()==0)
        {
            eroe->setEnergy(10);
            forzaAmore=100;
        }
        else
        {
            if(forzaAmore==100)
            {
                itAmore = backgroundLayer.add(Sipario(0,0,640,100,ColorAlpha(255,255,255,128)));
                textLayerLevel1.add(Text("L'amore mi da la forza!!!", Point(0,10), Color(255,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));

                forzaAmore--;

            }
            else if(forzaAmore>0)
                forzaAmore--;
            else if(forzaAmore==0)
            {
                backgroundLayer.remove(itAmore);
                textLayerLevel1.clear();
                forzaAmore--;
            }
        }
        
        if(personaggi[levelsEnemies[level][nemicoAttivo]]->getEnergy()==0)
        {
            if(nemicoAttivo == levelsEnemies[level].size()-1)
                livelloFinito = true;
            else
            {
                eroe->setEnergy(10);
                static unsigned jumped=0;

                static bool saySomething = true;
                static CompositeSprite::iterator it1,it2,it3;

                Sprite* next  = dynamic_cast<Sprite*> (*spriteLevel1[levelsEnemies[level][nemicoAttivo+1]]);


                if(saySomething)
                {
                    textLayerLevel1.clear();
                    it1 =  backgroundLayer.add(Sipario(0,0,640,100,ColorAlpha(255,255,255,128)));
                    it2 =  textLayerLevel1.add(Text(frasiEnemies[levelsEnemies[level][nemicoAttivo+1]], Point(0,10), Color(255,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
                    saySomething=false;
                }

                if(levelsEnemies[level][nemicoAttivo+1] == "luca" && jumped ==5 )
                {
                    it3 = textLayerLevel1.add(Text(frasiEnemies["luca2"], Point(0,50), Color(255,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
                }

                if(jumped<15)
                {

                    if(tick%(20)==0)
                            next->setLeftTopCorner(Point(next->getLeftTopCorner().getX(), next->getLeftTopCorner().getY()+2));
                    else if(tick%(20)==10)
                    {
                            next->setLeftTopCorner(Point(next->getLeftTopCorner().getX(), next->getLeftTopCorner().getY()-2));
                        jumped++;
                    }
                }
                else
                {
                    // backgroundLayer.remove(personaggi[levelsEnemies[level][nemicoAttivo]]);
                    backgroundLayer.remove(it1);
                    textLayerLevel1.clear();

                    saySomething=true;

                    backgroundLayer.remove(spriteLevel1[levelsEnemies[level][++nemicoAttivo]]);
                    playerLayer.add(DrawablePointer(*personaggi[levelsEnemies[level][nemicoAttivo]]));

                    jumped = 0;


                }
            }

        }
      
        /*
        int y=10;
        for(unsigned j=0;j<levelsEnemies[0].size();j++)
        {
            personaggi[levelsEnemies[0][j]]->getEnergy();

            if(personaggi[levelsEnemies[0][j]]->getEnergy()>0 && eroe->getEnergy()>0)
            {
                stringstream ss;
                ss << "Energy "<< levelsEnemies[0][j]<<": " << personaggi[levelsEnemies[0][j]]->getEnergy();

                energyLayer.add(Text(ss.str(),Point(winWidth-150,y)));

                y+=10;
               // for(unsigned i=0;i<personaggi[level]->getEnergy();i++)
                 //   energyLayer.add(Sprite("ortaggi.bmp",Point(winWidth -30*i-30 ,25)));
            }
        }
         * */
        
        Nemico * nemicoCorrente = dynamic_cast<Nemico*>(personaggi[levelsEnemies[0][nemicoAttivo]]);

        stringstream s2;
        s2 << "Energia nemico"<< ": ";

        energyLayer.add(Text(s2.str(),Point(winWidth - nemicoCorrente->getEnergy()*15 -140,460)));
    
        
        for(unsigned j=0;j<nemicoCorrente->getEnergy();j++)
        {
            
            Sprite symb(nemicoCorrente->getMunizioneName(),Point(winWidth-30-15*j,455));
            symb.setScaleHeight(0.4f);
            symb.setScaleWidth(0.4f);
            energyLayer.add(symb);
        }

    }
    
    if(livelloFinito && eroe->getY() == getb_height()-eroe->getRealHeight())
    {
        level++;
    }
    
}

void MyAllegro::prepareEndlLevel1()
{
    backgroundLayer.remove((spriteLevel1["valentinaCorpo"]));
    
    stringstream ss;
    
    ss<<eroe->getName()<<".bmp";
    
    Sprite vinc(ss.str(),Point(eroe->getX(),eroe->getY()));
    vinc.setScaleWidth((float)eroe->getRealWidth()/eroe->getWidth());
    vinc.setScaleHeight((float)eroe->getRealHeight()/eroe->getHeight());
   
    spriteLevel1.insert(pair<string,CompositeBitmap::iterator>(eroe->getName(),backgroundLayer.add(vinc)));
    
    playerLayer.clear();

}


void MyAllegro::endlLevel1()
{
    const int vel=10;
    static unsigned endTick=0;
    
    
    Sprite* vinc  = dynamic_cast<Sprite*> (*(spriteLevel1[eroe->getName()]));   

    int pointX = vinc->getLeftTopCorner().getX();
    int pointY = vinc->getLeftTopCorner().getY();
    
    static int increment = vinc->getLeftTopCorner().getX() < 250? 5: -5;

     static int jumped=0;
        
    if(jumped < 5)
    {      
        if(tick%(20)==0)
            vinc->setLeftTopCorner(Point(pointX, pointY+5));
        else if(tick%(20)==10)
        {
            vinc->setLeftTopCorner(Point(pointX, pointY-5));
            jumped++;
        }
    }
    else
    {
        if(abs(vinc->getLeftTopCorner().getX()-250) > abs(increment))
        {
            textLayer.clear();
            bulletLayer.clear();
            if(tick%vel==0)
            {

                pointX+=increment;
                vinc->setLeftTopCorner(Point(pointX,pointY));

                int angle= vinc->getAngle();


                if(tick%(vel*2)==0)
                    angle+= 2;
                else
                    angle-= 2;

                vinc->setAngle(angle);
            }
        }
        else
        {
            
            static bool aggiuntaVale=false;
            if(!aggiuntaVale)
            {
                energyLayer.clear();
                textLayer.clear();
                aggiuntaVale=true;

                vinc->setAngle(0);
                Sprite vale("valentina.bmp",Point(300,getb_height()-155));

                vale.setScaleWidth(((float)eroe->getRealWidth()/vale.getWidth())*1.5);
                vale.setScaleHeight((float)eroe->getRealHeight()/vale.getHeight());

                spriteLevel1.insert(pair<string,CompositeBitmap::iterator>("valentina",backgroundLayer.add(vale)));

                endTick = tick;
            }

            static bool firstheart=true;
            if(firstheart)
            {
                cuori.clear();
                firstheart=false;
            }

            pioggiaDiCuori(60);

           
            if(tick>= endTick + 400)
                cuoreEndLevel1();
            
            if(tick== endTick + 650)
            {
                textLayer.add(Text("Valentina, purtroppo per te", Point(60,130), Color(0,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
                textLayer.add(Text("           il nostro eroe è ", Point(60,170), Color(0,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
                textLayer.add(Text("  clamorosamente riuscito ", Point(60,210), Color(0,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
                textLayer.add(Text("              nell'impresa...", Point(60,250), Color(0,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));
            }
            if(tick== endTick + 910)
            {
                textLayer.add(Text("... e ti è toccato sposarlo!!!", Point(60,310), Color(0,0,0), Text::ALIGN_LEFT, Font("acme-ext-24.tga")));

            }
            
             if(tick== endTick + 1200)
                 level++;
        }
    }
}



void MyAllegro::introScena1()
{   
    /** INTRUDUZIONE, COMPARE LA SCENA*/
    
    static bool sipario=false;
    static CompositeBitmap::iterator it;
    static int alpha=255;
    
    if(!sipario)
    {
        sipario = true;
        it = backgroundLayer.add(Sipario(0,0,640,480,ColorAlpha(0,0,0,255)));
    }
    else{  
  
        if(tick%2==0)
            if(alpha>=0)
            {
                Sipario* sp = dynamic_cast<Sipario*> ((*it));
                sp->setColor(ColorAlpha(0,0,0,alpha));

               alpha--;
            }
    }
}

void MyAllegro::introScena3()
{   
    /** INTRUDUZIONE, COMPARE LA SCENA*/
    
    static bool sipario=false;
    static bool rimossa=false;

    static CompositeBitmap::iterator it,it2;
    static int alpha=255;
    
    if(!sipario)
    {
        sipario = true;
        it = backgroundLayer.add(Sipario(0,0,640,480,ColorAlpha(0,0,0,255)));
        it2 = backgroundLayer.add(Text("Nel frattempo...", Point(640/2, 480/2-80), Color(255,255,255), Text::ALIGN_CENTER, Font("acme-ext-24.tga")));
        
    }
    else
    {

        if(tick%4==0)
        {
            if(alpha>=0)
            {
                Sipario* sp = dynamic_cast<Sipario*> ((*it));
                sp->setColor(ColorAlpha(0,0,0,alpha));

               alpha--;
            }
            
            if(alpha==150)
            {
                if(!rimossa)
                {
                    rimossa=true;
                    backgroundLayer.remove(it2);
                }
            }
        }       
    }
}

void MyAllegro::introScena4()
{   
    /** INTRUDUZIONE, COMPARE LA SCENA*/
    
    static bool sipario=false;
    static CompositeBitmap::iterator it;
    static int alpha=255;
    
    if(!sipario)
    {
        sipario = true;
        it = backgroundLayer.add(Sipario(0,0,640,480,ColorAlpha(0,0,0,255)));
    }
    else
    {

        if(tick%2==0)
            if(alpha>=0)
            {
                Sipario* sp = dynamic_cast<Sipario*> ((*it));
                sp->setColor(ColorAlpha(0,0,0,alpha));

               alpha--;
            }
    }
}

void MyAllegro::scena1()
{  
    //cout << "tick --> "<<tick<<endl;
    
    unsigned vel = 20;
    
    static bool vincenzoVa=false;
    static bool valentinaVaVia=false;
    
    static unsigned valentinaSaltaTicks=0;
    static bool valentinaSalta=false;

    static unsigned vincenzoVaTicks=0;
    
    
    if(tick==SCENA1+1)
    {
        
        conversationHandlerScena1.playCurrentSentence(tick);
        
    }


    if(tick%5==0 )
    {
        
        if(conversationHandlerScena1.inPause(tick))
        {
            
            if(!conversationHandlerScena1.wait(tick))
            {
                if(conversationHandlerScena1.hasNext())
                {
                   // conversationHandlerScena1.popFrontSentence();
                    conversationHandlerScena1.playCurrentSentence(tick);

                }
            }
        }
        else if(conversationHandlerScena1.postSentence())
        {
            if(!conversationHandlerScena1.inPause(tick))
            {
                switch(conversationHandlerScena1.getFrasiCounter())
                {
                    case 1:
                        conversationHandlerScena1.setPause(60);
                        break;
                    case 2:
                        conversationHandlerScena1.setPause(40);
                        valentinaSaltaTicks = tick+350;
                        valentinaSalta = true;
                        break;  
                    case 3:
                        conversationHandlerScena1.setPause(40);
                        break;
                    case 4:
                        conversationHandlerScena1.setPause(40);
                        break; 
                    case 8:
                        conversationHandlerScena1.setPause(50);
                        break;
                    case 9:
                        conversationHandlerScena1.setPause(90);
                        vincenzoVaTicks = tick+250;
                        vincenzoVa=true;
                        break;
                    case 10:
                        conversationHandlerScena1.setPause(200);
                        valentinaVaVia = true;
                        break;
                    case 11:
                        conversationHandlerScena1.setPause(40);
                        break;
                    case 12:
                        conversationHandlerScena1.setPause(60);
                        break;
                    case 13:
                        conversationHandlerScena1.setPause(130);
                        conversationHandlerScena1.setLatenzaFrase(130);
                        break;
                    default:
                        conversationHandlerScena1.setPause(30);
                        break;
                }

                if(conversationHandlerScena1.getLatenzaFrase()<=0)
                        conversationHandlerScena1.setLatenzaFrase(30);
                //cout<<conversationHandlerScena1.getFrasiCounter() <<" ->" <<conversationHandlerScena1.getPause() <<endl;
            }
        }
       
        
    }


    /* Animazione personaggi quando parlano*/
    
    
    if(tick%10==0)
    {
        string character = conversationHandlerScena1.getCharacter(tick);

//        cout << character <<" - "<<conversationHandlerScena1.qualcunoParla(tick)<< " - "<< conversationHandlerScena1.getFrasiCounter() << " - " << conversationHandlerScena1.getPause() << " - " << conversationHandlerScena1.getLatenzaFrase() <<endl;

        if(character!="idle" && character!="story" )
        {
            Sprite* characterSprite = dynamic_cast<Sprite*> (*(spriteScena1[character]));

            int pointX = characterSprite->getLeftTopCorner().getX();
            int pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));


        }
    }
    
    //TINITI A FOTIA!!!
    Sprite* characterSprite = dynamic_cast<Sprite*> (*(spriteScena1["fotia"]));

    if(tick> SCENA1 + 1450 && tick< SCENA1 + 1601)
    {
        int angle= characterSprite->getAngle();

        characterSprite->setAngle(0);
        if(tick%2==0)
            angle+=5;
        else
            angle-=5;

        characterSprite->setAngle(angle);
    }
    
    //Vale si fa notare
    if(valentinaSalta && tick%10==0 && tick>valentinaSaltaTicks && tick<valentinaSaltaTicks+500)
    {
   
            Sprite* valentina = dynamic_cast<Sprite*> (*(spriteScena1["valentina"]));

            int angle = valentina->getAngle();

            if(tick%(20)==0)
               // valentina->setLeftTopCorner(Point(pointX, pointY+2));
                valentina->setAngle(angle+1);
            else
                //valentina->setLeftTopCorner(Point(pointX, pointY-2));
                valentina->setAngle(angle-1);
            
            /*
            Sprite* vincenzo = dynamic_cast<Sprite*> (*(spriteScena1["vincenzo"]));

            pointX = vincenzo->getLeftTopCorner().getX();
            pointY = vincenzo->getLeftTopCorner().getY();


            if(tick%(20)==0)
                vincenzo->setLeftTopCorner(Point(pointX, pointY+2));
            else
                vincenzo->setLeftTopCorner(Point(pointX, pointY-2));
            */

    }
        
    //Vincenzo e Vale parlano
     if(vincenzoVaTicks!=0 && tick>vincenzoVaTicks+620 && tick<vincenzoVaTicks+1500)
    {
         if(tick%10==0)
         {
            Sprite* vincenzo = dynamic_cast<Sprite*> (*(spriteScena1["vincenzo"]));
            Sprite* valentina = dynamic_cast<Sprite*> (*(spriteScena1["valentina"]));

            int pointX = vincenzo->getLeftTopCorner().getX();
            int pointY = vincenzo->getLeftTopCorner().getY();


            if(tick%(20)==0)
                vincenzo->setLeftTopCorner(Point(pointX, pointY+3));
            else
                vincenzo->setLeftTopCorner(Point(pointX, pointY-3));
            
            pointX = valentina->getLeftTopCorner().getX();
            pointY = valentina->getLeftTopCorner().getY();


            if(tick%(20)==0)
                valentina->setLeftTopCorner(Point(pointX, pointY-3));
            else
                valentina->setLeftTopCorner(Point(pointX, pointY+3));
         }
     }
       
 
    /*--- COMPARSE --- */
    if(tick%100==0)
    {

        static int modulo=20;
        for(unsigned j=1;j<=6;j++)
        {
         
            stringstream ss;
            ss << "comparsa" << j;
                        
            Sprite* comparsa = dynamic_cast<Sprite*> (*(spriteScena1[ss.str()]));

            int random = rand()%modulo ;

            int pointX = comparsa->getLeftTopCorner().getX();
            int pointY = comparsa->getLeftTopCorner().getY();
            
            if(random%modulo == 0)
                comparsa->setLeftTopCorner(Point(pointX, pointY+1));
            else if(random%modulo == 1)
                comparsa->setLeftTopCorner(Point(pointX, pointY-1));
            else if(random%modulo == 2)
                comparsa->setLeftTopCorner(Point(pointX+1, pointY));
            else if(random%modulo == 3)
                    comparsa->setLeftTopCorner(Point(pointX-1, pointY));
            
        }
    }
    
    
    
    /* ANIMAZIONI*/
    
    if(tick%vel==0)
    {
              
        /* VINCENZO va da VALENTINA*/
        if(vincenzoVa && tick>vincenzoVaTicks && tick<=vincenzoVaTicks+620)
        {
            //conversationHandlerScena1.popFrontSentence(); 

            //MOVIMENTO VINCENZO
            Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScena1["vincenzo"]));

            int pointX = vinc->getLeftTopCorner().getX()+5;
            int pointY = vinc->getLeftTopCorner().getY();
            
            if(tick%(vel*5)==0)
                pointY-=2;
                
            vinc->setLeftTopCorner(Point(pointX,pointY));
            
            float scaleX = vinc->getScaleWidth()-0.0015f;
            float scaleY = vinc->getScaleHeight()-0.0015f;

            vinc->setScaleHeight(scaleY);
            vinc->setScaleWidth(scaleX);

            int angle= vinc->getAngle();

            if(tick%(vel*2)==0)
                angle+= 2;
            else
                angle-= 2;

            vinc->setAngle(angle);
            
            //FINE MOVIMENTO VINCENZO
        }
        else if(vincenzoVa && tick>vincenzoVaTicks+620)
        {
            conversazione.play();
            vincenzoVa=false;
        }
        
        
        /* VINCENZO FA RITORNO DAGLI AMICI*/
        if(valentinaVaVia && tick>vincenzoVaTicks+1500 && tick<=vincenzoVaTicks+2120)
        {
            //conversationHandlerScena1.popFrontSentence(); 

            //MOVIMENTO VINCENZO
            Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScena1["vincenzo"]));

            int pointX = vinc->getLeftTopCorner().getX()-5;
            int pointY = vinc->getLeftTopCorner().getY();
            
            if(tick%(vel*5)==0)
                pointY+=2;
                
            vinc->setLeftTopCorner(Point(pointX,pointY));
            
            float scaleX = vinc->getScaleWidth()+0.0015f;
            float scaleY = vinc->getScaleHeight()+0.0015f;

            vinc->setScaleHeight(scaleY);
            vinc->setScaleWidth(scaleX);

            int angle= vinc->getAngle();

            if(tick%(vel*2)==0)
                angle+= 1;
            else
                angle-= 1;

            vinc->setAngle(angle);
            
            //FINE MOVIMENTO VINCENZO
        }
         
        
        /* VALENTINA lascia il locale */
        if(valentinaVaVia && tick>vincenzoVaTicks+1500 && tick<vincenzoVaTicks+2820)
        {
            //conversationHandlerScena1.popFrontSentence(); 

            //MOVIMENTO VALENTINA
            Sprite* vale = dynamic_cast<Sprite*> (*(spriteScena1["valentina"]));

            int pointX = vale->getLeftTopCorner().getX()+5;
            int pointY = vale->getLeftTopCorner().getY();
            
            if(tick%(vel*5)==0)
                pointY-=2;
                
            vale->setLeftTopCorner(Point(pointX,pointY));
            
            float scaleX = vale->getScaleWidth()-0.0015f;
            float scaleY = vale->getScaleHeight()-0.0015f;

            vale->setScaleHeight(scaleY);
            vale->setScaleWidth(scaleX);

            int random = rand();

            int angle= vale->getAngle();

            if(tick%(vel*2)==0)
                angle+= random%2;
            else
                angle-= random%2;

            vale->setAngle(angle);
            
            //FINE MOVIMENTO VALENTINA
        }
        
        /* VINCENZO lascia il locale */
        if(valentinaVaVia && tick>vincenzoVaTicks+3000)
        {
            //conversationHandlerScena1.popFrontSentence(); 

            //MOVIMENTO VINCENZO
            Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScena1["vincenzo"]));

            int pointX = vinc->getLeftTopCorner().getX()+5;
            int pointY = vinc->getLeftTopCorner().getY();
            
            if(tick%(vel*5)==0)
                pointY-=2;
                
            vinc->setLeftTopCorner(Point(pointX,pointY));
            
            float scaleX = vinc->getScaleWidth()-0.0015f;
            float scaleY = vinc->getScaleHeight()-0.0015f;

            vinc->setScaleHeight(scaleY);
            vinc->setScaleWidth(scaleX);

            int angle= vinc->getAngle();

            if(tick%(vel*2)==0)
                angle+= 1;
            else
                angle-= 1;

            vinc->setAngle(angle);
            
            //FINE MOVIMENTO VINCENZO
        }
    }
    
    /** FINALE, SCHERMO DIVENTA NERO*/
    
    static bool sipario=false;
    static CompositeBitmap::iterator it;
    static int alpha=0;
    
    if(!sipario)
    {
        sipario = true;
        it = backgroundLayer.add(Sipario(0,0,640,480,ColorAlpha(0,0,0,0)));
    }
        
  
    if(valentinaVaVia && tick> vincenzoVaTicks+3200)
    {
        if(tick%3==0)
            if(alpha<255)
            {
                Sipario* sp = dynamic_cast<Sipario*> ((*it));
                sp->setColor(ColorAlpha(0,0,0,alpha));

               alpha++;
            }
    }
}


void MyAllegro::scena2()
{
    const unsigned vel = 30;
    const int gelato1Start = 400;
    const int spiaggiaStart = 800;
    const int cinemaStart = 1200;
    const int balloStart = 1600;
    const int cuoriStart = 2000;
    const int cuoreFinale = 2800;


  
    static CompositeBitmap::iterator pizzaIt; 
    static int anglePizza=0;
    
    static CompositeBitmap::iterator gelatoIt1; 
    static int angleGelato1=0;
      
    static CompositeBitmap::iterator spiaggiaIt; 
    static int angleSpiaggia=0;
    
    static CompositeBitmap::iterator cinemaIt; 
    static int angleCinema=0;
    
    static CompositeBitmap::iterator balloIt; 
    static int angleBallo=0;    
    
    if(tick == SCENA2+1)
    {
         Sprite pizza("pizza.bmp", Point(10,25));

         pizza.setScaleHeight(0.25f);
         pizza.setScaleWidth(0.15f);

         pizzaIt =  backgroundLayer.add(pizza);
         spriteScena2.insert(pair<string,CompositeBitmap::iterator>("pizza",pizzaIt));
    }
    else if(tick == SCENA2+gelato1Start)
    {
        Sprite gelato1("gelato1.bmp", Point(10,25));

         gelato1.setScaleHeight(0.25f);
         gelato1.setScaleWidth(0.15f);

         gelatoIt1 =  backgroundLayer.add(gelato1);
         spriteScena2.insert(pair<string,CompositeBitmap::iterator>("gelato1",gelatoIt1));
    }
    else if(tick == SCENA2+spiaggiaStart)
    {
        Sprite spiaggia("spiaggia.bmp", Point(10,25));

         spiaggia.setScaleHeight(0.45f);
         spiaggia.setScaleWidth(0.45f);

         spiaggiaIt =  backgroundLayer.add(spiaggia);
         spriteScena2.insert(pair<string,CompositeBitmap::iterator>("spiaggia",spiaggiaIt));
    }
    else if(tick == SCENA2+cinemaStart)
    {
        Sprite cinema("cinema.bmp", Point(10,25));

         cinema.setScaleHeight(0.25f);
         cinema.setScaleWidth(0.25f);

         cinemaIt =  backgroundLayer.add(cinema);
         spriteScena2.insert(pair<string,CompositeBitmap::iterator>("cinema",cinemaIt));
    }
    else if(tick == SCENA2+balloStart)
    {
        Sprite ballo("ballo.bmp", Point(10,25));

         ballo.setScaleHeight(0.25f);
         ballo.setScaleWidth(0.25f);

         balloIt =  backgroundLayer.add(ballo);
         spriteScena2.insert(pair<string,CompositeBitmap::iterator>("ballo",balloIt));
    }
    

    if(tick%3==0)
    {
    
        //Movimento oggetti in alto
        Sprite* pizza = dynamic_cast<Sprite*> (*pizzaIt);
          
        if(pizza->getLeftTopCorner().getX()<= backgroundLayer.getWidth()+20)
        {
            pizza->setLeftTopCorner(Point(pizza->getLeftTopCorner().getX()+2,pizza->getLeftTopCorner().getY()));

            anglePizza += 2;

            pizza->setPivot(Point((pizza->getWidth()* pizza->getScaleWidth())/2, (pizza->getHeight()*pizza->getScaleHeight())/2 ));

            pizza->setAngle(anglePizza);
            
        }
        
        if(tick >= SCENA2+gelato1Start)
        {
            Sprite* gelato = dynamic_cast<Sprite*> (*gelatoIt1);
            
            if(gelato->getLeftTopCorner().getX()<= backgroundLayer.getWidth()+20)
            {
                gelato->setLeftTopCorner(Point(gelato->getLeftTopCorner().getX()+2,gelato->getLeftTopCorner().getY()));

                angleGelato1 += 2;

                gelato->setPivot(Point((gelato->getWidth()* gelato->getScaleWidth())/2, (gelato->getHeight()*gelato->getScaleHeight())/2 ));

                gelato->setAngle(angleGelato1);

            }
        }
        if(tick >= SCENA2+spiaggiaStart)
        {
            Sprite* oggetto = dynamic_cast<Sprite*> (*spiaggiaIt);
            
            if(oggetto->getLeftTopCorner().getX()<= backgroundLayer.getWidth()+20)
            {
                oggetto->setLeftTopCorner(Point(oggetto->getLeftTopCorner().getX()+2,oggetto->getLeftTopCorner().getY()));

                angleSpiaggia += 2;

                oggetto->setPivot(Point((oggetto->getWidth()* oggetto->getScaleWidth())/2, (oggetto->getHeight()*oggetto->getScaleHeight())/2 ));

                oggetto->setAngle(angleSpiaggia);

            }
        }
        
        if(tick >= SCENA2+cinemaStart)
        {
            Sprite* oggetto = dynamic_cast<Sprite*> (*cinemaIt);
            
            if(oggetto->getLeftTopCorner().getX()<= backgroundLayer.getWidth()+20)
            {
                oggetto->setLeftTopCorner(Point(oggetto->getLeftTopCorner().getX()+2,oggetto->getLeftTopCorner().getY()));

                angleCinema += 2;

                oggetto->setPivot(Point((oggetto->getWidth()* oggetto->getScaleWidth())/2, (oggetto->getHeight()*oggetto->getScaleHeight())/2 ));

                oggetto->setAngle(angleCinema);

            }
        }
        
        if(tick >= SCENA2+balloStart)
        {
            Sprite* oggetto = dynamic_cast<Sprite*> (*balloIt);
            
            if(oggetto->getLeftTopCorner().getX()<= backgroundLayer.getWidth()+20)
            {
                oggetto->setLeftTopCorner(Point(oggetto->getLeftTopCorner().getX()+2,oggetto->getLeftTopCorner().getY()));

                angleBallo += 2;

                oggetto->setPivot(Point((oggetto->getWidth()* oggetto->getScaleWidth())/2, (oggetto->getHeight()*oggetto->getScaleHeight())/2 ));

                oggetto->setAngle(angleBallo);

            }
        }
    }
    
    if(tick>SCENA2+cuoriStart)
    {   
        pioggiaDiCuori();
        
        if(tick>SCENA2+cuoreFinale)
            fineScena2();
    }
     
     if(tick%vel==0)
     {    
        //MOVIMENTO VINCENZO
        Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScena2["vincenzo"]));

        int pointX = vinc->getLeftTopCorner().getX()+5;
        int pointY = vinc->getLeftTopCorner().getY();

        vinc->setLeftTopCorner(Point(pointX,pointY));

        int angle = 0;

        switch(tick%(vel*2))
        {
            case 0:
                angle=1;
                break;
            case vel:
                angle=0;
                break;
            default:
                angle=-1;
                break;
        }

        vinc->setAngle(angle);

        //FINE MOVIMENTO VINCENZO

        //MOVIMENTO VALENTINA
        Sprite* vale = dynamic_cast<Sprite*> (*(spriteScena2["valentina"]));

        pointX = vale->getLeftTopCorner().getX()+5;
        pointY = vale->getLeftTopCorner().getY();

        vale->setLeftTopCorner(Point(pointX,pointY));

        vale->setAngle(angle);

        //FINE MOVIMENTO VALENTINA
     }
     
}

void MyAllegro::pioggiaDiCuori(unsigned numCuori)
{
    
    if(cuori.size()<numCuori && tick%15==0)
    {
        int random = rand()%640;
        Sprite cuore("cuoricino.bmp", Point(random,0));
        cuore.setScaleWidth(0.20f);
        cuore.setScaleHeight(0.20f);
       
        cuori.push_back(backgroundLayer.add(cuore));
    }
    
    for(list<CompositeBitmap::iterator>::iterator it = cuori.begin(); it!=cuori.end();)
    {
        Sprite* oggetto = dynamic_cast<Sprite*> (*(*it));
        
        oggetto->setLeftTopCorner(Point(oggetto->getLeftTopCorner().getX(),oggetto->getLeftTopCorner().getY()+2));

        oggetto->setPivot(Point((oggetto->getWidth()* oggetto->getScaleWidth())/2, (oggetto->getHeight()*oggetto->getScaleHeight())/2 ));

        oggetto->setAngle(oggetto->getAngle()+1);
        
        if(oggetto->getLeftTopCorner().getY()>=480)
        {
            backgroundLayer.remove(*it);
            cuori.erase(it++);
        }
        else
            ++it;

    }

}
void MyAllegro::fineScena2()
{
    static bool aggiungiCuore=false;
    static CompositeBitmap::iterator it;
    
    if(!aggiungiCuore)
    {
        aggiungiCuore=true;
        Sprite cuore("cuoricino.bmp", Point(640/2-50,480/2));
        cuore.setScaleWidth(0.20f);
        cuore.setScaleHeight(0.20f);
       
        it = backgroundLayer.add(cuore);
    }
    else
    {
        Sprite* cuore = dynamic_cast<Sprite*> (*it);
        cuore->setScaleWidth(cuore->getScaleWidth()+0.01f);
        cuore->setScaleHeight(cuore->getScaleHeight()+0.01f);
        cuore->setLeftTopCorner(Point(cuore->getLeftTopCorner().getX()-1, cuore->getLeftTopCorner().getY()-1));
    }
}
void MyAllegro::cuoreEndLevel1()
{
    static bool aggiungiCuore=false;
    static CompositeBitmap::iterator it;
    
    if(!aggiungiCuore)
    {
        aggiungiCuore=true;
        Sprite cuore("cuoricino.bmp", Point(640/2-50,480/2));
        cuore.setScaleWidth(0.20f);
        cuore.setScaleHeight(0.20f);
       
        it = backgroundLayer.add(cuore);
    }
    else
    {
        Sprite* cuore = dynamic_cast<Sprite*> (*it);
        cuore->setScaleWidth(cuore->getScaleWidth()+0.01f);
        cuore->setScaleHeight(cuore->getScaleHeight()+0.01f);
        cuore->setLeftTopCorner(Point(cuore->getLeftTopCorner().getX()-1, cuore->getLeftTopCorner().getY()-1));
    }
}

void MyAllegro::cuoreFinale()
{
    static bool aggiungiCuore=false;
    static CompositeBitmap::iterator it;
    
    if(!aggiungiCuore)
    {
        aggiungiCuore=true;
        Sprite cuore("cuoricino.bmp", Point(640/2-50,480/2));
        cuore.setScaleWidth(0.20f);
        cuore.setScaleHeight(0.20f);
       
        it = backgroundLayer.add(cuore);
    }
    else
    {
        Sprite* cuore = dynamic_cast<Sprite*> (*it);
        cuore->setScaleWidth(cuore->getScaleWidth()+0.01f);
        cuore->setScaleHeight(cuore->getScaleHeight()+0.01f);
        cuore->setLeftTopCorner(Point(cuore->getLeftTopCorner().getX()-1, cuore->getLeftTopCorner().getY()-1));
    }
}


void MyAllegro::scena3()
{
    
    static bool fineScena=false;

   // cout << "tick:"<<tick<<endl;
    if(tick==SCENA3+1)
    {
        
        conversationHandlerScena3.playCurrentSentence(tick);
        
    }


    if(tick%5==0 )
    {
        
        if(conversationHandlerScena3.inPause(tick))
        {
            
            if(!conversationHandlerScena3.wait(tick))
            {
                if(conversationHandlerScena3.hasNext())
                {
                   // conversationHandlerScena1.popFrontSentence();
                    conversationHandlerScena3.playCurrentSentence(tick);

                }
            }
        }
        else if(conversationHandlerScena3.postSentence())
        {
            if(!conversationHandlerScena3.inPause(tick))
            {
                switch(conversationHandlerScena3.getFrasiCounter())
                {
                    case 0:
                        conversationHandlerScena3.setPause(80);
                        conversationHandlerScena3.setLatenzaFrase(70);
                        break;
                    case 1:
                        conversationHandlerScena3.setPause(60);
                        conversationHandlerScena3.setLatenzaFrase(50);
                        break;
                    case 2:
                        conversationHandlerScena3.setPause(60);
                        conversationHandlerScena3.setLatenzaFrase(50);
                        break;
                    case 6:
                        conversationHandlerScena3.setPause(60);
                        conversationHandlerScena3.setLatenzaFrase(60);
                        break;
                    case 7:
                        conversationHandlerScena3.setPause(60);
                        conversationHandlerScena3.setLatenzaFrase(60);
                        fineScena = true;
                        break;
                    default:
                        conversationHandlerScena3.setPause(30);
                        break;
                }

                if(conversationHandlerScena3.getLatenzaFrase()<=0)
                        conversationHandlerScena3.setLatenzaFrase(30);
                //cout<<conversationHandlerScena1.getFrasiCounter() <<" ->" <<conversationHandlerScena1.getPause() <<endl;
            }
        }
       
        
    }
    
      /* Animazione personaggi quando parlano*/
    if(tick%10==0)
    {
        string character = conversationHandlerScena3.getCharacter(tick);

//        cout << character <<" - "<<conversationHandlerScena1.qualcunoParla(tick)<< " - "<< conversationHandlerScena1.getFrasiCounter() << " - " << conversationHandlerScena1.getPause() << " - " << conversationHandlerScena1.getLatenzaFrase() <<endl;

        if(character!="idle" && character!="story" )
        {
            Sprite* characterSprite = dynamic_cast<Sprite*> (*(spriteScena3[character]));

            int pointX = characterSprite->getLeftTopCorner().getX();
            int pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));

        }
        
      
    }
    
    //TINITI A FOTIA!!!
    if((tick> SCENA3 + 1250 && tick< SCENA3 + 1451) || (tick> SCENA3 + 1550 && tick< SCENA3 + 1751))
    {
        Sprite* characterSprite = dynamic_cast<Sprite*> (*(spriteScena3["fotia"]));

        int angle= characterSprite->getAngle();

        characterSprite->setAngle(0);
        if(tick%2==0)
            angle+=2;
        else
            angle-=2;

        characterSprite->setAngle(angle);
        
        if(tick%10==0)
        {
            //Luca
            characterSprite = dynamic_cast<Sprite*> (*(spriteScena3["luca"]));

            int pointX = characterSprite->getLeftTopCorner().getX();
            int pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));
                
            //Aligi    
            characterSprite = dynamic_cast<Sprite*> (*(spriteScena3["aligi"]));

            pointX = characterSprite->getLeftTopCorner().getX();
            pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));
                
            //Savio
            characterSprite = dynamic_cast<Sprite*> (*(spriteScena3["savio"]));

            pointX = characterSprite->getLeftTopCorner().getX();
            pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));
                
            //Riks
            characterSprite = dynamic_cast<Sprite*> (*(spriteScena3["riks"]));

            pointX = characterSprite->getLeftTopCorner().getX();
            pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));
                
                
            //Cardo
            characterSprite = dynamic_cast<Sprite*> (*(spriteScena3["cardo"]));

            pointX = characterSprite->getLeftTopCorner().getX();
            pointY = characterSprite->getLeftTopCorner().getY();


            if(tick%(20)==0)
                characterSprite->setLeftTopCorner(Point(pointX, pointY+3));
            else
                characterSprite->setLeftTopCorner(Point(pointX, pointY-3));

        }
        
        
    }
    
    
    
    /** FINALE, SCHERMO DIVENTA NERO*/
    
    static bool sipario=false;
    static CompositeBitmap::iterator it;
    static int alpha=0;
    
    if(!sipario)
    {
        sipario = true;
        it = backgroundLayer.add(Sipario(0,0,640,480,ColorAlpha(0,0,0,0)));
    }
        
  
    if(fineScena)
    {
        if(tick%3==0)
            if(alpha<255)
            {
                Sipario* sp = dynamic_cast<Sipario*> ((*it));
                sp->setColor(ColorAlpha(0,0,0,alpha));

               alpha++;
            }
    }
    
}


void MyAllegro::scena4()
{
    static bool removed=false;


    Sprite* characterSprite;
    
    if(!removed)
        characterSprite = dynamic_cast<Sprite*> (*(spriteScena4["aligiApe"]));
    else
        characterSprite = dynamic_cast<Sprite*> (*(spriteScena4["aligiValeApe"]));

    int pointX = characterSprite->getLeftTopCorner().getX();
    int pointY = characterSprite->getLeftTopCorner().getY();
    
    if(tick%2==0)
    {
        pointX+=2;
    }
    
    if(tick%(2)==0)
        characterSprite->setLeftTopCorner(Point(pointX, pointY+1));
    else
        characterSprite->setLeftTopCorner(Point(pointX, pointY-1));
    
    
    if(!removed)
    {
        Sprite* vale = dynamic_cast<Sprite*> (*(spriteScena4["valentina"]));
        Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScena4["vincenzo"]));
        if(tick%30==0)
        {
            int pointX = vinc->getLeftTopCorner().getX()+5;
            int pointY = vinc->getLeftTopCorner().getY();

            vinc->setLeftTopCorner(Point(pointX,pointY));

            int angle = 0;

            switch(tick%(60))
            {
                case 0:
                    angle=1;
                    break;
                case 30:
                    angle=0;
                    break;
                default:
                    angle=-1;
                    break;
            }

            vinc->setAngle(angle);

            //FINE MOVIMENTO VINCENZO

            //MOVIMENTO VALENTINA
            pointX = vale->getLeftTopCorner().getX()+5;
            pointY = vale->getLeftTopCorner().getY();

            vale->setLeftTopCorner(Point(pointX,pointY));

            vale->setAngle(angle);
        }
        if(characterSprite->getLeftTopCorner().getX() +50 >= vale->getLeftTopCorner().getX())
        {
            backgroundLayer.remove(spriteScena4["valentina"]);
            backgroundLayer.remove(spriteScena4["aligiApe"]);
            
            Sprite apeAligiVale("apeAligiVale.bmp", Point(characterSprite->getLeftTopCorner().getX(),characterSprite->getLeftTopCorner().getY()));
            apeAligiVale.setScaleHeight(0.60f);
            apeAligiVale.setScaleWidth(0.60f);
            string apeAligiValeName="aligiValeApe";


            spriteScena4.insert(pair<string,CompositeBitmap::iterator>(apeAligiValeName,backgroundLayer.add(apeAligiVale)));

            removed=true;
        }
    }
    static int jumped=0;
    
    if(removed && tick%10==0)
    {
        Sprite* vinc = dynamic_cast<Sprite*> (*(spriteScena4["vincenzo"]));
        
        
        pointX = vinc->getLeftTopCorner().getX();
        pointY = vinc->getLeftTopCorner().getY();

        if(jumped < 13 )
        {
            if(tick%(20)==0)
                vinc->setLeftTopCorner(Point(pointX, pointY+3));
            else
            {
                vinc->setLeftTopCorner(Point(pointX, pointY-3));
                jumped++;
            }
        }
        else
        {
            vinc->setLeftTopCorner(Point(pointX+5, pointY));
            
            int angle = 0;

            switch(tick%(20))
            {
                case 0:
                    angle=1;
                    break;
                case 20:
                    angle=0;
                    break;
                default:
                    angle=-1;
                    break;
            }

            vinc->setAngle(angle);
        }
    }
    
    
    if(tick == SCENA4+400)
    {
        backgroundLayer.add(Sipario(0,0,640,200,ColorAlpha(255,255,255,128)));
        conversationHandlerScena4.playCurrentSentence(tick);
        
    }


    if(tick%5==0 && tick > SCENA4+400)
    {
        
        if(conversationHandlerScena4.inPause(tick))
        {
            
            if(!conversationHandlerScena4.wait(tick))
            {
                if(conversationHandlerScena4.hasNext())
                {
                   // conversationHandlerScena1.popFrontSentence();
                    conversationHandlerScena4.playCurrentSentence(tick);

                }
            }
        }
        else if(conversationHandlerScena4.postSentence())
        {
            if(!conversationHandlerScena4.inPause(tick))
            {
                switch(conversationHandlerScena4.getFrasiCounter())
                {
                    case 0:
                        conversationHandlerScena4.setPause(40);
                        conversationHandlerScena4.setLatenzaFrase(40);
                        break;
                    default:
                        conversationHandlerScena4.setPause(30);
                        break;
                }

                if(conversationHandlerScena4.getLatenzaFrase()<=0)
                        conversationHandlerScena4.setLatenzaFrase(30);
                //cout<<conversationHandlerScena1.getFrasiCounter() <<" ->" <<conversationHandlerScena1.getPause() <<endl;
            }
        }
       
        
    }
    
    
}
