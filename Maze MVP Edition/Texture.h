#ifndef _Texture_H_
#pragma once

#include <iostream>
#include "Point.h"
#include <string>
#include <sstream>	
#include <fstream>
#include <codecvt>
#include <vector>

class Texture
{
public:
	Texture getTexture(std::string textureName);

	Point textureSize;
	std::wstring texture;
};


#endif // !_Texture_H_




