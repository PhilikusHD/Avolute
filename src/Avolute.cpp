#include "Avolute.h"

Avolute::Avolute(const std::string& name, SDL_Texture* tex, Vector2f pos)
    : m_name(name), m_tex(tex), m_pos(pos)
{
}

std::string Avolute::GetName()
{
    return m_name;
}

void Avolute::SpawnAvolute(Avolutes avolute)
{
}
