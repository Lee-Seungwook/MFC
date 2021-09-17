#pragma once

typedef enum figuretype_ { BORDERONLY, BORDERFILL, NOBORDERFILL} FIGURETYPE;
typedef enum tooltype_ { DEFAULT, PENCIL, FILL, BEELINE, CIRCLE, RECTANGLE, POLYGON, TEXT } TOOLTYPE;

class DrawObject
{
public:
	DrawObject(void);
	virtual ~DrawObject(void);
	virtual void draw(CDC* pDc) = 0;
	virtual int drawType(void) = 0;
	virtual void serialize(CArchive& ar) = 0;
	virtual void deserialize(CArchive& ar) = 0;
};
