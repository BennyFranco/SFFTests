//
//  SFFv2.hpp
//  
//
//  Created by Benny Franco Dennis on 27/11/17.
//
#pragma once
#ifndef SFF_V2_HPP
#define SFF_V2_HPP

#include "types.h"
#include "Pal.hpp"

struct SFFHeader
{
    char signature [12];
    byte verlo3;
    byte verlo2;
    byte verlo1;
    byte verhi;
    unsigned long reserve_zero;
    unsigned long reserve_one;
    byte compat_verlo3;
    byte compat_verlo1;
    byte compat_verlo2;
    byte compat_verhi;
    unsigned long reserve_two;
    unsigned long reserve_three;
    unsigned long sprite_offset;
    unsigned long sprite_number;
    unsigned long palette_offset;
    unsigned long palette_number;
    unsigned long ldata_offset;
    unsigned long ldata_length;
    unsigned long tdata_offset;
    unsigned long tdata_length;
    unsigned long reserve_four;
    unsigned long reserve_five;
    byte unused [436];
};

struct SpriteNodeHeader
{
    short group_no;
    short item_no;
    short width;
    short height;
    short axisx;
    short axisy;
    short index_linked_sprite;
    byte fmt;
    byte coldepth;
    unsigned long offset;
    unsigned long sprite_data_length;
    short palette_index;
    short flags;
};

class SFFv2
{
private:
    SFFHeader           m_header;
    SpriteNodeHeader*   m_nodes;
    Pal*                m_palettes;

public:
    SFFv2();
    ~SFFv2();

    SFFHeader           GetHeader() { return m_header; }
    SpriteNodeHeader*   GetNodes() { return m_nodes; }
    Pal*                GetPalettes() { return m_palettes; }

    void                SetHeader(SFFHeader p_header) { m_header = p_header; }
    void                SetNodes(SpriteNodeHeader* p_nodes) { m_nodes = p_nodes; }
    void                SetPalettes(Pal* p_palettes) { m_palettes = p_palettes; }
};

#endif /* SFF_V2_HPP */