#pragma once
#include "ParticleFX.h"
#include "HUD.h"



class Editor
{
public:
	void RunEditor(int type);
private:
	void ParticleEditor();
	ParticleFX* CurrentFX = new ParticleFX();
	float FrameTime = 0.01; //runs at a controlled fps
	bool Running = false;

	

};

