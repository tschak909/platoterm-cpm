/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * io.h - Input/output functions (serial/ethernet)
 */

/* #include <SDL.h> */
/* #include <SDL_net.h> */
#include "io.h"
#include "protocol.h"

#define true 1
#define false 0

/* IPaddress ip; */
/* TCPsocket sock; */
/* int len; */
/* SDLNet_SocketSet set; */
/* int numReady; */
/* unsigned char d; */
/* unsigned char DoNotSend=true; */
/* unsigned char buffer[4096]; */

/**
 * io_init() - Set-up the I/O
 */
void io_init(void)
{
/*  SDLNet_Init();
  SDLNet_ResolveHost(&ip,"irata.online",8005);
  sock=SDLNet_TCP_Open(&ip);
  set=SDLNet_AllocSocketSet(1);
  SDLNet_TCP_AddSocket(set,sock); */
}

/**
 * io_send_byte(b) - Send specified byte out
 */
void io_send_byte(unsigned char b)
{
  /* if (DoNotSend==1) */
  /*   return; */
  /* SDLNet_TCP_Send(sock,&b,1); */
}

/**
 * io_main() - The IO main loop
 */
void io_main(void)
{
  /* numReady=SDLNet_CheckSockets(set,0); */
  /* if (numReady) */
  /*   { */
  /*     len=SDLNet_TCP_Recv(sock,&buffer,4096); */
  /*     ShowPLATO(buffer,len); */
  /*   } */
}

/**
 * io_done() - Called to close I/O
 */
void io_done(void)
{
  /* SDLNet_TCP_Close(sock); */
  /* SDLNet_FreeSocketSet(set); */
  /* SDLNet_Quit(); */
}
