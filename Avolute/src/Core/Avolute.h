#pragma once
#include "Entity.h"

class Avolute : Entity
{
public:

	enum Avolutes
	{
		TEST1,
		TEST2,
		TEST3,
		TEST4
	};

	Avolute(const std::string& name, SDL_Texture* tex, Vector2f pos);
	std::string GetName();
	void SpawnAvolute(Avolutes avolute);

private:
	std::string m_name;
	SDL_Texture* m_tex = Entity::m_tex;
	Vector2f m_pos = Entity::m_pos;
};