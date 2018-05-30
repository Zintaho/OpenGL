#include "Texture.h"
#include <fstream>
#include <iterator>
#include <vector>

#include <iostream>

Texture::Texture(std::string path, std::string ext)
{
	this->fileData.filePath = path;
	this->fileData.extension = ext;

	ReadSource();
}

void Texture::ReadSource()
{
	const std::string pathHeader = ".\\model\\texture\\";
	const std::string pathFooter = "." + fileData.extension;

	std::string path;
	path = (pathHeader + fileData.filePath + pathFooter);
	
	if (fileData.extension == "bmp")
	{
		std::ifstream inputStream(path, std::ios::binary);
		std::vector<char> buffer((std::istreambuf_iterator<char>(inputStream)), (std::istreambuf_iterator<char>()));

		char bmpHeader[54];
		for (int i = 0; i < 54; ++i)
		{
			bmpHeader[i] = buffer[i];
		}
		if (bmpHeader[0] == 'B' && bmpHeader[1] == 'M')
		{///Assume that extension of this file is BMP
			fileData.fileSize = *(unsigned int *)(&bmpHeader[2]);
			fileData.offset = *(unsigned int *)(&bmpHeader[10]);
			fileData.width = *(unsigned int *)(&bmpHeader[18]);
			fileData.height = *(unsigned int *)(&bmpHeader[22]);
			fileData.dataSize = *(unsigned int *)(&bmpHeader[34]);

			fileData.imageData = new unsigned char[fileData.dataSize];
			for (unsigned int i = 0; i < fileData.dataSize; ++i)
			{
				fileData.imageData[i] = buffer[i + fileData.offset];
			}
		}
		else
		{
			std::cerr << "Not a Correct BMP" << std::endl;
		}

		inputStream.close();
	}

}

Texture::~Texture()
{
	if (fileData.imageData != NULL)
	{
		delete[] fileData.imageData;
	}
}
