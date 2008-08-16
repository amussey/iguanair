/****************************************************************************
 ** pipes.h *****************************************************************
 ****************************************************************************
 *
 * Header for the Unix/Named pipe interfaces.
 *
 * Copyright (C) 2007, IguanaWorks Incorporated (http://iguanaworks.net)
 * Author: Joseph Dunn <jdunn@iguanaworks.net>
 *
 * Distributed under the GPL version 2.
 * See LICENSE for license details.
 */

#ifndef _PIPES_
#define _PIPES_

#ifdef WIN32
  IGUANAIR_API bool createPipePair(PIPE_PTR *pair);
  IGUANAIR_API int readPipe(PIPE_PTR fd, void *buf, int count);
  IGUANAIR_API int writePipe(PIPE_PTR fd, const void *buf, int count);
  #define closePipe CloseHandle
  PIPE_PTR acceptClient(PIPE_PTR *server);

  #define IGSOCK_NAME "\\\\.\\pipe\\iguanaIR-"
#else
  #include <sys/un.h>
  #include <sys/socket.h>

  #define createPipePair(a) (pipe(a) == 0)
  #define readPipe read
  #define writePipe write
  #define closePipe close
  #define acceptClient(a) accept((a), NULL, NULL);

  #ifdef __APPLE__
    #define IGSOCK_NAME "/tmp/iguanaIR"
  #else
    #define IGSOCK_NAME "/dev/iguanaIR"
  #endif
#endif

/* functions dealing with the server sockets */
void socketName(const char *name, char *buffer, unsigned int length);
PIPE_PTR connectToPipe(const char *name);

/* reads with timeouts */
int readPipeTimed(PIPE_PTR fd, char *buffer, int size, int timeout);

/* used for notification of packet arrival */
int notified(PIPE_PTR fd, int timeout);
bool notify(PIPE_PTR fd);

#endif
