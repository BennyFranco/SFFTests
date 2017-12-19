#pragma once

typedef unsigned char byte;

typedef struct 
{
	short Xmin;
	short Ymin;
	short Xmax;
	short Ymax;
} Window;

typedef struct 
{
	byte			manufacturer;			// Constant Flag  10 = ZSoft .PCX
	byte			version;				// Version information:
											/*	0 = Version 2.5
											2 = Version 2.8 w / palette information
											3 = Version 2.8 w / o palette information
											5 = Version 3.0
											*/
	byte			encoding;				// 1 = .PCX run length encoding
	byte			bitsPerPixel;			// Number of bits/pixel per plane
	Window			window;					// Picture Dimensions (Xmin, Ymin) - (Xmax - Ymax) in pixels, inclusive
	short			hres;					// Horizontal Resolution of creating device
	short			vres;					// Vertical Resolution of creating device
	byte			colorMap[48];			// Color palette setting
	byte			reserved;
	byte			nPlanes;				// Number of color planes
	short			bytesPerLine;			// Number of bytes per scan line per color plane (always even for .PCX files)
	short			paletteInf;				// How to interpret palette 
											//		1 = color/BW
											//		2 = grayscale
	byte			filler[58];				// Blank to fill out 128 byte header
} PCXHeader;

class PCXImage
{
private:
	PCXHeader		m_header;
	char *		m_memblock;
	int				m_size;
public:
	PCXImage(PCXHeader p_header, char * p_memblock, int p_size);
	PCXImage();
	~PCXImage();

	PCXHeader	GetHeader() { return m_header; }
	char *		GetMemblock() { return m_memblock; }
	int			GetMemSize() { return m_size; }
};

