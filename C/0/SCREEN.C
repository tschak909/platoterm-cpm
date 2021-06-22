/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * screen.c - Display output functions
 */

#include <stdlib.h>
#include "screen.h"
#include "protocol.h"
#include "font.h"

unsigned char CharHigh=16;
unsigned char CharWide=8;
padPt TTYLoc;

/* SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
extern SDL_Surface *surface; */
unsigned char fontm23[2048];
padRGB backgroundColor={0,0,0};
padRGB foregroundColor={255,255,255};

short max(short a, short b) { return ( a > b ) ? a : b; }
short min(short a, short b) { return ( a < b ) ? a : b; }

#define true 1
#define false 0

extern padBool FastText;

/**
 * screen_init() - Set up the screen
 */
void screen_init(void)
{
  /* canvas_init(); */
  /* SDL_Init(SDL_INIT_VIDEO); */
  /* SDL_CreateWindowAndRenderer(512,512,0,&window,&renderer); */
  /* screen_clear(); */
}

/**
 * screen_main() - render/preserve screen
 */
void screen_main(void)
{
  /* texture = SDL_CreateTextureFromSurface(renderer,surface); */
  /* SDL_RenderCopy(renderer,texture,NULL,NULL); */
  /* SDL_RenderPresent(renderer); */
  /* SDL_DestroyTexture(texture); */
}

/**
 * screen_wait(void) - Sleep for approx 16.67ms
 */
void screen_wait(void)
{
}

/**
 * screen_beep(void) - Beep the terminal
 */
void screen_beep(void)
{
}

/**
 * screen_clear - Clear the screen
 */
void screen_clear(void)
{
  /* canvas_clear(SDL_MapRGB(surface->format,backgroundColor.red,backgroundColor.green,backgroundColor.blue)); */
}

/**
 * screen_set_pen_mode(void) - Set pen mode
 */
void screen_set_pen_mode(void)
{
}

/**
 * screen_block_draw(Coord1, Coord2) - Perform a block fill from Coord1 to Coord2
 */
void screen_block_draw(padPt* Coord1, padPt* Coord2)
{
  /* SDL_Rect rect; */
  /* short x1; */
  /* short y1; */
  /* short x2; */
  /* short y2; */

  /* x1=min(Coord1->x,Coord2->x); */
  /* x2=max(Coord1->x,Coord2->x); */
  /* y1=min((Coord1->y^0x1FF)&0x1FF,(Coord2->y^0x1FF)&0x1FF); */
  /* y2=max((Coord1->y^0x1FF)&0x1FF,(Coord2->y^0x1FF)&0x1FF); */

  /* if ((CurMode==ModeErase)||(CurMode==ModeInverse)) */
  /*   canvas_block_fill(x1,y1,x2,y2,SDL_MapRGB(surface->format,backgroundColor.red,backgroundColor.green,backgroundColor.blue)); */
  /* else */
  /*   canvas_block_fill(x1,y1,x2,y2,SDL_MapRGB(surface->format,foregroundColor.red,foregroundColor.green,foregroundColor.blue));     */
}

/**
 * screen_dot_draw(Coord) - Plot a mode 0 pixel
 */
void screen_dot_draw(padPt* Coord)
{
  /* if ((CurMode==ModeErase)||(CurMode==ModeInverse)) */
  /*   canvas_set_pixel(Coord->x,(Coord->y^0x1FF)&0x1FF,SDL_MapRGB(surface->format,backgroundColor.red,backgroundColor.green,backgroundColor.blue)); */
  /* else */
  /*   canvas_set_pixel(Coord->x,(Coord->y^0x1FF)&0x1FF,SDL_MapRGB(surface->format,foregroundColor.red,foregroundColor.green,foregroundColor.blue));       */
}

/**
 * screen_line_draw(Coord1, Coord2) - Draw a mode 1 line
 */
void screen_line_draw(padPt* Coord1, padPt* Coord2)
{
  /* short x1; */
  /* short y1; */
  /* short x2; */
  /* short y2; */

  /* x1=Coord1->x; */
  /* x2=Coord2->x; */
  /* y1=(Coord1->y^0x1FF)&0x1FF; */
  /* y2=(Coord2->y^0x1FF)&0x1FF; */
  
  /* if ((CurMode==ModeErase)||(CurMode==ModeInverse)) */
  /*   canvas_line(x1,y1,x2,y2,SDL_MapRGB(surface->format,backgroundColor.red,backgroundColor.green,backgroundColor.blue)); */
  /* else */
  /*   canvas_line(x1,y1,x2,y2,SDL_MapRGB(surface->format,foregroundColor.red,foregroundColor.green,foregroundColor.blue));       */
}

/**
 * screen_char_draw(Coord, ch, count) - Output buffer from ch* of length count as PLATO characters
 */
void screen_char_draw(padPt* Coord, unsigned char* ch, unsigned char count)
{
  short offset; /* due to negative offsets */
  unsigned short x;      /* Current X and Y coordinates */
  unsigned short y;
  unsigned short* px;   /* Pointers to X and Y coordinates used for actual plotting */
  unsigned short* py;
  unsigned char i; /* current character counter */
  unsigned char a; /* current character byte */
  unsigned char j,k; /* loop counters */
  char b; /* current character row bit signed */
  char width=8;
  char height=16;
  short deltaX=1;
  short deltaY=1;
  unsigned char *p;
  unsigned char* curfont;
  padRGB mainColor;
  padRGB altColor;

  if (CurMode==ModeRewrite)
    {
      altColor.red=backgroundColor.red;
      altColor.green=backgroundColor.green;
      altColor.blue=backgroundColor.blue;
    }
  else if (CurMode==ModeInverse)
    {
      altColor.red=foregroundColor.red;
      altColor.green=foregroundColor.green;
      altColor.blue=foregroundColor.blue;
    }

  if (CurMode==ModeErase || CurMode==ModeInverse)
    {
      mainColor.red=backgroundColor.red;
      mainColor.green=backgroundColor.green;
      mainColor.blue=backgroundColor.blue;
    }
  else
    {
      mainColor.red=foregroundColor.red;
      mainColor.green=foregroundColor.green;
      mainColor.blue=foregroundColor.blue;
    }

  switch(CurMem)
    {
    case M0:
      curfont=font;
      offset=-32;
      break;
    case M1:
      curfont=font;
      offset=64;
      break;
    case M2:
      curfont=fontm23;
      offset=-32;
      break;
    case M3:
      curfont=fontm23;
      offset=32;      
      break;
    }

  x=Coord->x;
  if (ModeBold)    
    y=((Coord->y+30)^0x1FF)&0x1FF;
  else
    y=((Coord->y+15)^0x1FF)&0x1FF;
  
  if (FastText==padF)
    {
      goto chardraw_with_fries;
    }

  /* the diet chardraw routine - fast text output. */
  
  for (i=0;i<count;++i)
    {
      a=*ch;
      ++ch;
      a+=offset;
      p=&curfont[FONTPTR(a)];
      
      for (j=0;j<16;++j)
  	{
  	  b=*p;
	  
  	  for (k=0;k<8;++k)
  	    {
  	      if (b<0) /* check sign bit. */
		{
		  /* canvas_set_pixel(x,y,SDL_MapRGB(surface->format,mainColor.red,mainColor.green,mainColor.blue)); */
		}
	      ++x;
  	      b<<=1;
  	    }

	  ++y;
	  x-=width;
	  ++p;
  	}

      x+=width;
      y-=height;
    }

  return;

 chardraw_with_fries:
  if (Rotate)
    {
      deltaX=-abs(deltaX);
      width=-abs(width);
      px=&y;
      py=&x;
    }
    else
    {
      px=&x;
      py=&y;
    }
  
  if (ModeBold)
    {
      deltaX = deltaY = 2;
      width<<=1;
      height<<=1;
    }
  
  for (i=0;i<count;++i)
    {
      a=*ch;
      ++ch;
      a+=offset;
      p=&curfont[FONTPTR(a)];
      for (j=0;j<16;++j)
  	{
  	  b=*p;

	  if (Rotate)
	    {
	      px=&y;
	      py=&x;
	    }
	  else
	    {
	      px=&x;
	      py=&y;
	    }

  	  for (k=0;k<8;++k)
  	    {
  	      if (b<0) /* check sign bit. */
		{
		  if (ModeBold)
		    {
		      /* canvas_set_pixel(*px+1,*py,SDL_MapRGB(surface->format,mainColor.red,mainColor.green,mainColor.blue)); */
		      /* canvas_set_pixel(*px,*py+1,SDL_MapRGB(surface->format,mainColor.red,mainColor.green,mainColor.blue)); */
		      /* canvas_set_pixel(*px+1,*py+1,SDL_MapRGB(surface->format,mainColor.red,mainColor.green,mainColor.blue)); */
		    }
		  /* canvas_set_pixel(*px,*py,SDL_MapRGB(surface->format,mainColor.red,mainColor.green,mainColor.blue)); */
		}
	      else
		{
		  if (CurMode==ModeInverse || CurMode==ModeRewrite)
		    {
		      if (ModeBold)
			{
			  /* canvas_set_pixel(*px+1,*py,SDL_MapRGB(surface->format,altColor.red,altColor.green,altColor.blue)); */
			  /* canvas_set_pixel(*px,*py+1,SDL_MapRGB(surface->format,altColor.red,altColor.green,altColor.blue)); */
			  /* canvas_set_pixel(*px+1,*py+1,SDL_MapRGB(surface->format,altColor.red,altColor.green,altColor.blue)); */
			}
		      /* canvas_set_pixel(*px,*py,SDL_MapRGB(surface->format,altColor.red,altColor.green,altColor.blue)); */
		    }
		}

	      x += deltaX;
  	      b<<=1;
  	    }

	  y+=deltaY;
	  x-=width;
	  ++p;
  	}

      Coord->x+=width;
      x+=width;
      y-=height;
    }

  return;
}

/**
 * screen_tty_char - Called to plot chars when in tty mode
 */
void screen_tty_char(padByte theChar)
{
  if ((theChar >= 0x20) && (theChar < 0x7F)) {
    screen_char_draw(&TTYLoc, &theChar, 1);
    TTYLoc.x += CharWide;
  }
  else if (theChar == 0x0b) /* Vertical Tab */
    {
      TTYLoc.y += CharHigh;
    }
  else if ((theChar == 0x08) && (TTYLoc.x > 7))/* backspace */
    {
      TTYLoc.x -= CharWide;
      /* screen_block_draw(&scalex[TTYLoc.x],&scaley[TTYLoc.y],&scalex[TTYLoc.x+CharWide],&scaley[TTYLoc.y+CharHigh]); */
    }
  else if (theChar == 0x0A)/* line feed */
    TTYLoc.y -= CharHigh;
  else if (theChar == 0x0D)/* carriage return */
    TTYLoc.x = 0;

  if (TTYLoc.x + CharWide > 511) {/* wrap at right side */
    TTYLoc.x = 0;
    TTYLoc.y -= CharHigh;
  }

  if (TTYLoc.y < 0) {
    screen_clear();
    TTYLoc.y=495;
  }
  
}

/**
 * screen_foreground - Called to set foreground color.
 */
void screen_foreground(padRGB* theColor)
{
  foregroundColor.red = theColor->red;
  foregroundColor.green = theColor->green;
  foregroundColor.blue = theColor->blue;
}

/**
 * screen_background - Called to set foreground color.
 */
void screen_background(padRGB* theColor)
{
  backgroundColor.red = theColor->red;
  backgroundColor.green = theColor->green;
  backgroundColor.blue = theColor->blue;
}

/**
 * screen_paint_get_pixel - Get pixel at x,y
 */
unsigned char screen_paint_get_pixel(int x, int y)
{
  return 0;
}

/**
 * screen_paint - Called to paint at location.
 */
void screen_paint(padPt* Coord)
{
  static unsigned short xStack[512];
  static unsigned short yStack[512];
  unsigned char stackentry = 1;
  unsigned char spanAbove, spanBelow;
  int x = Coord->x;
  int y = (Coord->y^0x1FF)&0x1FF;
  unsigned char oldColor;
  unsigned char foregroundColorPixel;

  oldColor = screen_paint_get_pixel(x,y);
  /* foregroundColorPixel = SDL_MapRGB(surface->format,foregroundColor.red,foregroundColor.green,foregroundColor.blue); */

  if (oldColor == foregroundColorPixel)
    return;

  do
    {
      unsigned short startx;
      while (x > 0 && screen_paint_get_pixel(x-1,y) == oldColor)
        --x;

      spanAbove = spanBelow = false;
      startx=x;

      while(screen_paint_get_pixel(x,y) == oldColor)
        {
          if (y < (511))
            {
              unsigned char belowColor = screen_paint_get_pixel(x, y+1);
              if (!spanBelow  && belowColor == oldColor)
                {
                  xStack[stackentry]  = x;
                  yStack[stackentry]  = y+1;
                  ++stackentry;
                  spanBelow = true;
                }
              else if (spanBelow && belowColor != oldColor)
                spanBelow = false;
            }

          if (y > 0)
            {
              unsigned char aboveColor = screen_paint_get_pixel(x, y-1);
              if (!spanAbove  && aboveColor == oldColor)
                {
                  xStack[stackentry]  = x;
                  yStack[stackentry]  = y-1;
                  ++stackentry;
                  spanAbove = true;
                }
              else if (spanAbove && aboveColor != oldColor)
                spanAbove = false;
            }

          ++x;
        }
      /* canvas_line(startx,y,x-1,y,foregroundColorPixel); */
      --stackentry;
      x = xStack[stackentry];
      y = yStack[stackentry];
    }
  while (stackentry);  
}

/**
 * screen_done()
 * Close down TGI
 */
void screen_done(void)
{
}

