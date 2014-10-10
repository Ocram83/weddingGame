#include "Font.h"

list<pair<string, FONT*> > Font::instances;

Font::Font() {
    data = font;
}

Font::Font(const string& filename) {
    for(list<pair<string, FONT*> >::const_iterator it = instances.begin(); it != instances.end(); ++it) {
        if(it->first == filename) {
            data = it->second;
            return;
        }
    }
    
    data = load_font(filename.c_str(), NULL, NULL); 
    assert(data != NULL);
    instances.push_back(pair<string, FONT*>(filename, data));
}

Font::Font(const Font& init) : data(init.data) {

}

Font::~Font() {
}
