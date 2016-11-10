#pragma once

class Room
{
public:
	virtual void createObjects() = 0;
	virtual void updateObjects() = 0;
	virtual void drawObjects() = 0;
	virtual void deleteObjects() = 0;
};