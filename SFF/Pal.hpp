//
//  Pal.hpp
//  
//
//  Created by Benny Franco Dennis on 19/12/17.
//

#pragma once
#include "types.h"

struct PalNodeHeader 
{
    short group_no;
    short item_no;
    short num_cols;
    short index_linked_palette;
    unsigned long offset;
    unsigned long palette_data_length;
};


// Every color is 4 bytes, 3 bytes for RGB and 1 byte unused.
struct Color
{
	byte r;
	byte g;
	byte b;
	byte u; // Unused
};

class Pal
{
private:
    PalNodeHeader	m_header;
	Color*			m_colors;
public:
    Pal();
    ~Pal();

    PalNodeHeader   GetHeader() { return m_header; }
	Color*			GetColors() { return m_colors; }

    void			SetHeader(PalNodeHeader p_header) { m_header = p_header; }
	void			SetColors(Color* p_colors) { m_colors = p_colors; }
};