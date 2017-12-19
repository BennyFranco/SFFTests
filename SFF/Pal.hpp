//
//  Pal.hpp
//  
//
//  Created by Benny Franco Dennis on 19/12/17.
//

struct PalNodeHeader 
{
    short group_no;
    short item_no;
    short num_cols;
    short index_linked_palette;
    unsigned long offset;
    unsigned long palette_data_length;
};

class Pal
{
private:
    PalNodeHeader       m_header;
public:
    Pal();
    ~Pal();

    PalNodeHeader       GetHeader() { return m_header; }

    void                SetHeader(PalNodeHeader p_header) { m_header = p_header; }

};