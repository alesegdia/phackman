#include <allegro5/allegro.h>

#include "input.h"

class AllegroApp {
public:
	AllegroApp ( int screen_width, int screen_height );
	virtual ~AllegroApp ();

	int Exec();
	ALLEGRO_DISPLAY* display();

private:

	int Init();

protected:

	void handleEvent(ALLEGRO_EVENT& ev);
	virtual void draw() = 0 ;
	virtual void update(double delta) = 0 ;
	virtual void ready() = 0 ;
	virtual void dispose() = 0 ;

	int m_screenWidth, m_screenHeight;

	const int FPS = 60;

	ALLEGRO_DISPLAY* m_display = NULL;
	ALLEGRO_EVENT_QUEUE* m_eventQueue = NULL;
	ALLEGRO_TIMER* m_timer = NULL;

	bool m_redraw = true;
	bool m_doexit = false;


};

