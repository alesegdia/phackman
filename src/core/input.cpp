#include "input.h"

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

}

void Input::notifyKeyDown(int key)
{
	m_keyStates[key] = true;
}

void Input::notifyKeyUp(int key)
{
	m_keyStates[key] = false;
}
