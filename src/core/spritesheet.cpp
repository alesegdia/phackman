#include "spritesheet.h"




Spritesheet::Spritesheet(size_t width, size_t height, ALLEGRO_BITMAP *bitmap)
{
	reset( width, height, bitmap );
}

ALLEGRO_BITMAP *Spritesheet::getFrame(int num_frame)
{
	assert( num_frame >= 0 && num_frame < m_frames.size() );
	return m_frames[num_frame];
}

void Spritesheet::reset(size_t width, size_t height, ALLEGRO_BITMAP *bitmap)
{
	m_width = width;
	m_height = height;

	size_t num_frames = width * height;
	size_t tw = al_get_bitmap_width(bitmap) / width;
	size_t th = al_get_bitmap_height(bitmap) / height;

	m_frames.clear();
	m_frames.reserve(num_frames);

	for( size_t i = 0; i < height; i++ )
	{
		for( size_t j = 0; j < width; j++ )
		{
			ALLEGRO_BITMAP* frame = al_create_sub_bitmap( bitmap, j * tw, i * th, tw, th );
			m_frames.push_back(frame);
		}
	}
}

int Spritesheet::coordToIndex(int x, int y)
{
	return y * m_width + x;
}
