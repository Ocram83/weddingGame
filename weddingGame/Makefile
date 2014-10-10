BINARY=VForVincenzo
GCC=g++
CXX=$(GCC)
CXXFLAGS=-Wall
LINK=$(GCC)
LINKFLAGS=-lalleg
DEBUGFLAGS=-g

SRCS = \
 Allegro.cpp\
 Bitmap.cpp\
 Circle.cpp\
 Color.cpp\
 ColorAlpha.cpp\
 CompositeBitmap.cpp\
 CompositeSprite.cpp\
 ConversationHandler.cpp\
 DrawablePointer.cpp\
 Ellipse.cpp\
 Eroe.cpp\
 Font.cpp\
 Keyboard.cpp\
 Line.cpp\
 Mouse.cpp\
 Munizione.cpp\
 MyAllegro.cpp\
 Nemico.cpp\
 Personaggio.cpp\
 Pixel.cpp\
 Point.cpp\
 Polygon.cpp\
 Rectangle.cpp\
 SampleSound.cpp\
 Sipario.cpp\
 Text.cpp\
 TextPlotter.cpp\
 Triangle.cpp\
 main.cpp\
 

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(BINARY) 
	
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -M $< >$@
	
$(BINARY): $(OBJS)
	$(LINK)  $(LIBS) $(OBJS) $(LINKFLAGS) -o $(BINARY)

debug: $(OBJS)
	$(LINK) $(LIBS) $(OBJS) $(LINKFLAGS) $(DEBUGFLAGS) -o $(BINARY)
	

static: $(OBJS)
	$(LINK)  $(LIBS) $(OBJS) $(LINKFLAGS) -static -o $(BINARY)

########## Clean

clean:
	rm -f *.o a.out
	rm -f gmon.out

distclean: clean
	rm -f $(BINARY)
	rm -f *.d

-include $(DEPS)

