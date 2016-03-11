#include "input.h"
#include <algorithm>

Input* Input::instance = nullptr;

void Input::Initialize()
{
	instance = new Input();
}

void Input::Dispose()
{
	delete instance;
}

bool Input::IsKeyDown(int key)
{
	return instance->m_keyStates[key];
}

Input::Input()
{
	std::fill(std::begin(m_keyStates), std::begin(m_keyStates) + ALLEGRO_KEY_MAX, false);
}

void Input::notifyKeyDown(int key)
{
	m_keyStates[key] = true;
}

void Input::notifyKeyUp(int key)
{
	m_keyStates[key] = false;
}
