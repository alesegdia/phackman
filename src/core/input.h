#pragma once

#include <allegro5/allegro.h>

class Input
{
public:
	friend class AllegroApp;

	// singleton interface
	static Input* instance;
	static void Initialize();
	static void Dispose();

	static bool IsKeyDown( int key );

private:
	Input();
	void notifyKeyDown( int key );
	void notifyKeyUp( int key );

	bool m_keyStates[ALLEGRO_KEY_MAX];
};
