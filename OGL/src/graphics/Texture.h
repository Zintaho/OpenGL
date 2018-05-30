#pragma once
#include <string>

struct TextureData
{
	std::string filePath;
	std::string extension;

	unsigned int fileSize;
	unsigned int offset;
	unsigned int width;
	unsigned int height;
	unsigned int dataSize;

	unsigned char *imageData;
};

class Texture
{
public:
	Texture(std::string path, std::string ext);
	virtual ~Texture();

	inline std::string GetFilePath() { return fileData.filePath; }
	inline std::string GetExtension() { return fileData.extension; }
	inline TextureData *GetData() { return &fileData; }
private:
	void ReadSource();
	TextureData fileData;
};

