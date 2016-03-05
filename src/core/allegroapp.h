#include <allegro5/allegro.h>

class AllegroApp {
public:
	AllegroApp ( int screen_width, int screen_height );
	virtual ~AllegroApp ();

	int Exec();
	ALLEGRO_DISPLAY* display();

private:

	int Init();

protected:

	enum Keys
	{
		KEY_UP = 0,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,

		KEY_SLEFT,
		KEY_SRIGHT
	};

	void handleEvent(ALLEGRO_EVENT& ev);
	virtual void draw();
	virtual void update(float delta);
	virtual void ready();
	virtual void handleKeyInput();

	int m_screenWidth, m_screenHeight;

	const int FPS = 60;

	ALLEGRO_DISPLAY* m_display = NULL;
	ALLEGRO_EVENT_QUEUE* m_eventQueue = NULL;
	ALLEGRO_TIMER* m_timer = NULL;

	bool m_redraw = true;
	bool m_doexit = false;

	bool key[6] = { false, false, false, false, false, false };

};

