/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * keyboard.c - Keyboard functions (apple2)
 */

#include <conio.h>
#include "screen.h"
#include "keyboard.h"
#include "protocol.h"
#include "key.h"

#define true 1
#define false 0

static unsigned char ch;
static unsigned char shift_lock=false;
static unsigned char is_escape=false;
extern unsigned char xoff_enabled;
extern padBool TTY;

/**
 * keyboard_out - If platoKey < 0x7f, pass off to protocol
 * directly. Otherwise, platoKey is an access key, and the
 * ACCESS key must be sent, followed by the particular
 * access key from PTAT_ACCESS.
 */
void keyboard_out(unsigned char platoKey)
{
  if (platoKey==0xff)
    return;
  
  if (platoKey>0x7F)
    {
      Key(ACCESS);
      Key(ACCESS_KEYS[platoKey-0x80]);
      return;
    }
  Key(platoKey);
  return;
}

/**
 * keyboard_out_tty - keyboard output to serial I/O in TTY mode
 */
void keyboard_out_tty(char ch)
{
  io_send_byte(ch);
}

/**
 * keyboard_main - Handle the keyboard presses
 */
void keyboard_main(void)
{
  if (kbhit())
    {
      /* ch=cgetc(); */
      if (is_escape==true && ch==0x1B) /* ESC */
	{
	  screen_beep();

	  if (shift_lock==true)
	    shift_lock=false;
	  else
	    shift_lock=true;
	  
	  is_escape=false;
	}
      else if (is_escape==false && ch==0x1B)
	is_escape=true;
      else if (TTY)
	{
	  keyboard_out_tty(ch);
	}
      else if (is_escape==true)
	{
	  keyboard_out(esc_key_to_pkey[ch]);
	  is_escape=false;
	}
      else if (shift_lock==true)
	{
	  keyboard_out(shiftlock_key_to_pkey[ch]);
	}
      else
	{
	  keyboard_out(key_to_pkey[ch]);
	}
    }
}

/**
 * keyboard_clear() - Clear the keyboard buffer
 */
void keyboard_clear(void)
{
}

