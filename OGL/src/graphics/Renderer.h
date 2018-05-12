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
private:
	///Methods
	void InitGLEW() const;
	void SetGLOptions() const;
};