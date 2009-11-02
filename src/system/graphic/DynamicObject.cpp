#include "DynamicObject.h"

DynamicObject::DynamicObject(float x, float y, Sprite *sprite) :
	Object(x, y, 128, 128) {
	m_sprite = sprite;
	Speed = 0;
	Frame = 0;
	m_lastFrameRollTime = SDL_GetTicks();
}

void DynamicObject::rollFrame(bool forward) {
	if (m_sprite->getFramesCount() == 1)
		return;

	int now = SDL_GetTicks();

	if (now - m_lastFrameRollTime > 40) {
		if (forward)
			Frame++;
		else
			Frame--;

		m_lastFrameRollTime = now;
	}

	if (Frame == m_sprite->getFramesCount())
		Frame = 0;
	if (Frame < 0)
		Frame = m_sprite->getFramesCount();
}

void DynamicObject::process(int deltaTime) {
	Object::move(deltaTime);
}

void DynamicObject::drawQuad()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(m_left, m_top, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(m_right, m_top, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(m_right, m_bottom, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(m_left, m_bottom, 0.0f);
	glEnd();
}

void DynamicObject::draw(float x, float y, float angle, float scale, float rMask, float gMask, float bMask, float aMask) {
	Texture* frameTex = m_sprite->getFrame(Frame);

	glBindTexture(frameTex->getType(), frameTex->getTextureId());

	glPushMatrix();

	glScalef(scale, scale, scale);
	glNormal3f(0.0f, 0.0f, 1.0f);

	glPushMatrix();

	glTranslatef(x + 15.0f, y + 15.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor4f(0.0f, 0.0f, 0.0f, aMask / 3.0f);

	drawQuad();

	glPopMatrix();

	glTranslatef(x, y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor4f(rMask, gMask, bMask, aMask);

	drawQuad();

	glPopMatrix();
}

void DynamicObject::draw() {
	DynamicObject::draw(X, Y, Angle, Scale, RMask, GMask, BMask, AMask);
}

DynamicObject::~DynamicObject() {
	//nothing
}