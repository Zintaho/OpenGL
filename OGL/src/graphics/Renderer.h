#pragma once
#include <../../include/GL/glew.h>

class Renderer
{
public:
	///Constructor, Destructor
	Renderer();
	virtual ~Renderer();
	///Methods
	void Clear();

	void DrawTriangle();
private:
	///Methods
	void InitGLEW() const;
	void SetGLOptions() const;
};