#ifndef VIOLET_TEXTOBJECT_H_
#define VIOLET_TEXTOBJECT_H_

#include "../Texture.h"
#include "../../Object.h"

namespace violet {

struct Label {
    std::string id;
    std::string text;
    public:
	Label(std::string id, std::string text):
	    id(id), text(text) {}
};

class TextObject: public Object {
private:
	Texture* m_texture;
	void drawQuad();
public:
	TextObject(float x, float y, int w, int h, Texture *texture);
	void draw(bool outlined, float x, float y);
	virtual ~TextObject();
};
}

#endif /* VIOLET_TEXTOBJECT_H_ */
