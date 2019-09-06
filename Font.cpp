#include "DXUT.h"
#include "Font.h"


Font* Font::Load(const string& fontKey, int size)
{
	return RESOURCE.InsertFont(fontKey, size);
}

Font* Font::Find(const string& fontKey, int size)
{
	return RESOURCE.FindFont(fontKey, size);
}
