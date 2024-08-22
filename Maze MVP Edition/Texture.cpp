#include "Texture.h"

 std::vector<std::wstring> split(const std::wstring& s, wchar_t delimiter) {
     std::vector<std::wstring> tokens;
     std::wstringstream wss(s);
     std::wstring token;
     while (std::getline(wss, token, delimiter)) {
         tokens.push_back(token);
     }
     return tokens;
 }


 Texture Texture::getTexture(std::string textureName) {
     // Go to the folder with textures
     std::string filePath = "Textures\\" + textureName + ".txt";
     // Checking for file availability
     std::wifstream wif(filePath.c_str());
     if (!wif.is_open()) {
         throw std::runtime_error("The file was not found: " + filePath);
     }
     //wif.close();
     // Setting the UTF 8 locale
     wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
     // Record each character
     std::wstringstream wss;
     wss << wif.rdbuf();
     std::vector<std::wstring> splitFile = split(wss.str(), ':');
     std::vector<std::wstring> textureFullSize = split(splitFile[0], 'x');

     Texture texture;

     texture.textureSize.x = std::stoi(textureFullSize[0]);
     texture.textureSize.y = std::stoi(textureFullSize[1]);

     texture.texture = splitFile[1];

     // Return wstring
     return texture;
 }




