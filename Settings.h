#ifndef SETTINGS_H
#define SETTINGS_H

#include <AntTweakBar.h>

class Settings
{
public:
	int velocityIteration;
	int positionIteration;
	int stepIteration;
	int frictionSwitch;
	double gravity;
	bool pause;
	int frameRate;
public:
	void Init();
	void InitAntTweakBar();
};

extern Settings settings;

#endif