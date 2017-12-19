//
//  ReadSFF.cpp
//  
//
//  Created by Benny Franco Dennis on 19/12/17.
//

#include <iostream>
#include <fstream>

#include "libpcx/PCXImage.h"
#include "libpcx/PcxIO.h"
#include "types.h"

#include "SFF/SFFv2.hpp"

using namespace std;

int main()
{
    streampos size;
    SFFHeader header;
    
    ifstream file ("kfm.sff", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        file.seekg (0, ios::beg);

        file.read(reinterpret_cast<char *>(&header), sizeof(header));
        
        cout << "Signature: " << header.signature
             << " " << static_cast<int>(header.verhi) 
             << "." << static_cast<int>(header.verlo1) 
             << "." << static_cast<int>(header.verlo2)
             << "." << static_cast<int>(header.verlo3) << endl;

        cout << "Minimum Version: " 
             << static_cast<int>(header.compat_verhi) 
             << "." << static_cast<int>(header.compat_verlo1) 
             << "." << static_cast<int>(header.compat_verlo2)
             << "." << static_cast<int>(header.compat_verlo3) << endl;

        cout << "Sprites: " << header.sprite_number << " images" << endl
             << "Palettes: " << header.palette_number << endl;

        cout << "Sprite node Offset: " << static_cast<int>(header.sprite_offset) << endl
             << "Palette node offset: " << static_cast<int>(header.palette_offset) << endl;

// ---- Palette nodes reading
        file.seekg (header.palette_offset, ios::beg);
        PalNodeHeader* palNodes = new PalNodeHeader[static_cast<int>(header.palette_number)];

        cout << "---------- Reading palettes nodes ----------" << endl;

        for(unsigned long i = 0; i < header.palette_number; i++)
        {
            PalNodeHeader palHeader;
            file.read (reinterpret_cast<char *>(&palHeader), sizeof(palHeader));
            palNodes[i] = palHeader;
        }     

        cout<< static_cast<int>(palNodes[6].offset) <<endl;
// ---- Sprite nodes reading
        file.seekg (header.sprite_offset, ios::beg);

        SpriteNodeHeader* spriteNodes = new SpriteNodeHeader[static_cast<int>(header.sprite_number)];

        cout << "---------- Reading sprites nodes ----------" << endl;

        for(unsigned long i = 0; i < header.sprite_number; i++)
        {
            SpriteNodeHeader spriteHeader;
            file.read (reinterpret_cast<char *>(&spriteHeader), sizeof(spriteHeader));
            spriteNodes[i] = spriteHeader;
        }  
        
        cout << "---------- Creating images buffer ----------" << endl;
        SpriteNodeHeader portraitNode = spriteNodes[0];
        
        int64_t imgOffset = 0;
        
        if(portraitNode.flags == 0) imgOffset = header.ldata_offset;
        else if(portraitNode.flags != 0) imgOffset = header.tdata_offset;

        imgOffset += portraitNode.offset;

        cout << "Portrait Offset: " << static_cast<int>(imgOffset) << endl
             << "Length: " << static_cast<int>(portraitNode.sprite_data_length) << endl
             << "Compression: " << static_cast<int>(portraitNode.fmt)  << endl
             << "Width: " << static_cast<int>(portraitNode.width)  << endl
             << "Height: " << static_cast<int>(portraitNode.height)  << endl
             << "Palette index: " << static_cast<int>(portraitNode.palette_index)  << endl;       
        
// ------ RLE 8 Decode
       unsigned int pLength;

        file.seekg (imgOffset, ios::beg);
        file.read(reinterpret_cast<char *>(&pLength), sizeof(pLength));

        cout<<pLength<<endl;

        PCXHeader pcx_header;        
        char * copy_memblock = new char[pLength];
        
        byte one_byte;
        byte color;

        unsigned int i = 0;

        while(i < pLength)
        {
             file.read(reinterpret_cast<char *>(&one_byte), sizeof(one_byte));

            if((one_byte & 0xC0) == 0x40)
            {
                file.read(reinterpret_cast<char *>(&color), sizeof(color));
                for(int run_count = 0; run_count < (one_byte & 0x3f) ; run_count++)
                {
                    copy_memblock[i++] = color;
                }
            }
            else
            {
                copy_memblock[i++] = one_byte;
            }
        }
// -------

        memcpy(&pcx_header, copy_memblock, sizeof(pcx_header));

        cout << static_cast<int>(pcx_header.version) << endl;
                
        file.close();

        }
        else cout << "Unable to open file";

		getchar();
    return 0;
}