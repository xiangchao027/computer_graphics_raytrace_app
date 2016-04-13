#ifndef CG_CANVAS_H
#define CG_CANVAS_H

#include <iostream>
#include "string.h"
#include "cg_math.hpp"
#include "cg_material.hpp"
#include "cg_bitmap.hpp"

namespace cg
{

using namespace std;

class Canvas
{
	enum
	{
		OWNER = 1
	};

public:
	// constructor / destructors
	Canvas( int a_Width, int a_Height ) :
		m_Width( a_Width ),
		m_Height( a_Height )
	{
		m_Buffer = new Pixel[a_Width * a_Height];
	}
	Canvas( const char * a_File )
	{
		int fnn = strlen(a_File);
		bool legal = false;
		if (a_File[fnn-4]=='.')
			if(a_File[fnn-3]=='b')
				if(a_File[fnn-2]=='m')
					if(a_File[fnn-1]=='p')
						legal = true;
		if ( !legal )
		{
			printf("ERROR: BAD FILE NAME OR BAD FILE FORMAT! \n");
			return;
		}
		GetImageInfo(a_File, m_Width, m_Height);
		m_Buffer = new Pixel[m_Width * m_Height];
	}
	~Canvas()
	{
		delete [] m_Buffer;
	}

	// member data access
    Pixel* GetBuffer() 
    { 
    	return m_Buffer; 
    }
	int GetWidth() 
	{ 
		return m_Width; 
	}
	int GetHeight() 
	{ 
		return m_Height; 
	}

	// DISPLAY TEXT INFORMATION ON HEAD BAR
	void InitCharset()
	{
		SetChar( 0, ":ooo:", "o:::o", "ooooo", "o:::o", "o:::o" );
		SetChar( 1, "oooo:", "o:::o", "oooo:", "o:::o", "oooo:" );
		SetChar( 2, ":oooo", "o::::", "o::::", "o::::", ":oooo" );
		SetChar( 3, "oooo:", "o:::o", "o:::o", "o:::o", "oooo:" );
		SetChar( 4, "ooooo", "o::::", "oooo:", "o::::", "ooooo" );
		SetChar( 5, "ooooo", "o::::", "ooo::", "o::::", "o::::" );
		SetChar( 6, ":oooo", "o::::", "o:ooo", "o:::o", ":ooo:" );
		SetChar( 7, "o:::o", "o:::o", "ooooo", "o:::o", "o:::o" );
		SetChar( 8, "::o::", "::o::", "::o::", "::o::", "::o::" );
		SetChar( 9, ":::o:", ":::o:", ":::o:", ":::o:", "ooo::" );
		SetChar(10, "o::o:", "o:o::", "oo:::", "o:o::", "o::o:" );
		SetChar(11, "o::::", "o::::", "o::::", "o::::", "ooooo" );
		SetChar(12, "oo:o:", "o:o:o", "o:o:o", "o:::o", "o:::o" );
		SetChar(13, "o:::o", "oo::o", "o:o:o", "o::oo", "o:::o" );
		SetChar(14, ":ooo:", "o:::o", "o:::o", "o:::o", ":ooo:" );
		SetChar(15, "oooo:", "o:::o", "oooo:", "o::::", "o::::" );
		SetChar(16, ":ooo:", "o:::o", "o:::o", "o::oo", ":oooo" );
		SetChar(17, "oooo:", "o:::o", "oooo:", "o:o::", "o::o:" );
		SetChar(18, ":oooo", "o::::", ":ooo:", "::::o", "oooo:" );
		SetChar(19, "ooooo", "::o::", "::o::", "::o::", "::o::" );
		SetChar(20, "o:::o", "o:::o", "o:::o", "o:::o", ":oooo" );
		SetChar(21, "o:::o", "o:::o", ":o:o:", ":o:o:", "::o::" );
		SetChar(22, "o:::o", "o:::o", "o:o:o", "o:o:o", ":o:o:" );
		SetChar(23, "o:::o", ":o:o:", "::o::", ":o:o:", "o:::o" );
		SetChar(24, "o:::o", "o:::o", ":oooo", "::::o", ":ooo:" );
		SetChar(25, "ooooo", ":::o:", "::o::", ":o:::", "ooooo" );
		SetChar(26, ":ooo:", "o::oo", "o:o:o", "oo::o", ":ooo:" );
		SetChar(27, "::o::", ":oo::", "::o::", "::o::", ":ooo:" );
		SetChar(28, ":ooo:", "o:::o", "::oo:", ":o:::", "ooooo" );
		SetChar(29, "oooo:", "::::o", "::oo:", "::::o", "oooo:" );
		SetChar(30, "o::::", "o::o:", "ooooo", ":::o:", ":::o:" );
		SetChar(31, "ooooo", "o::::", "oooo:", "::::o", "oooo:" );
		SetChar(32, ":oooo", "o::::", "oooo:", "o:::o", ":ooo:" );
		SetChar(33, "ooooo", "::::o", ":::o:", "::o::", "::o::" );
		SetChar(34, ":ooo:", "o:::o", ":ooo:", "o:::o", ":ooo:" );
		SetChar(35, ":ooo:", "o:::o", ":oooo", "::::o", ":ooo:" );
		SetChar(36, "::o::", "::o::", "::o::", ":::::", "::o::" );
		SetChar(37, ":ooo:", "::::o", ":::o:", ":::::", "::o::" );
		SetChar(38, ":::::", ":::::", "::o::", ":::::", "::o::" );
		SetChar(39, ":::::", ":::::", ":ooo:", ":::::", ":ooo:" );
		SetChar(40, ":::::", ":::::", ":::::", ":::o:", "::o::" );
		SetChar(41, ":::::", ":::::", ":::::", ":::::", "::o::" );
		SetChar(42, ":::::", ":::::", ":ooo:", ":::::", ":::::" );
		SetChar(43, ":::o:", "::o::", "::o::", "::o::", ":::o:" );
		SetChar(44, "::o::", ":::o:", ":::o:", ":::o:", "::o::" );
		SetChar(45, ":::::", ":::::", ":::::", ":::::", ":::::" );
		SetChar(46, "ooooo", "ooooo", "ooooo", "ooooo", "ooooo" );
		SetChar(47, "::o::", "::o::", ":::::", ":::::", ":::::" );
		SetChar(48, "o:o:o", ":ooo:", "ooooo", ":ooo:", "o:o:o" );
		SetChar(49, "::::o", ":::o:", "::o::", ":o:::", "o::::" );
		char c[] = "abcdefghijklmnopqrstuvwxyz0123456789!?:=,.-() #'*/";
		int i;
		for ( i = 0; i < 256; i++ ) 
			s_Transl[i] = 45;
		for ( i = 0; i < 50; i++ ) 
			s_Transl[(unsigned char)c[i]] = i;
	}
	void SetChar( 
		int c, 
		const char * c1, 
		const char * c2, 
		const char * c3, 
		const char * c4, 
		const char * c5 
	)
	{
		strcpy( s_Font[c][0], c1 );
		strcpy( s_Font[c][1], c2 );
		strcpy( s_Font[c][2], c3 );
		strcpy( s_Font[c][3], c4 );
		strcpy( s_Font[c][4], c5 );
	}
	void Print( 
		const char * a_String, 
		int x1, 
		int y1, 
		Pixel color 
	)
	{
		Pixel* t = m_Buffer + x1 + y1 * m_Width;
		int i;
		for ( i = 0; i < (int)(strlen( a_String )); i++ )
		{	
			long pos = 0;
			if ((a_String[i] >= 'A') && (a_String[i] <= 'Z')) 
				pos = s_Transl[a_String[i] - ('A' - 'a')];
			else 
				pos = s_Transl[a_String[i]];
			Pixel* a = t;
			char* c = (char*)s_Font[pos];
			int h, v;
			for ( v = 0; v < 5; v++ ) 
			{
				for ( h = 0; h < 5; h++ ) 
					if (*c++ == 'o') 
						*(a + h) = color;
				a += m_Width;
			}
			t += 6;
		}
	}
	void Clear( Pixel a_Color )
	{
		int s = m_Width * m_Height;
		for ( int i = 0; i < s; i++ ) 
			m_Buffer[i] = a_Color;
	}

private:
	// Attributes
	Pixel* m_Buffer;	
	int m_Width, m_Height;	
	
	// Static attributes for the buildin font
	char s_Font[51][5][5];	
	int s_Transl[256];		
};


};

#endif
