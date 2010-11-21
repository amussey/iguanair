/****************************************************************************
 ** igdaemon.h **************************************************************
 ****************************************************************************
 *
 * A couple functions used to interface with Iguanaworks USB devices.
 *
 * Copyright (C) 2007, IguanaWorks Incorporated (http://iguanaworks.net)
 * Author: Joseph Dunn <jdunn@iguanaworks.net>
 *
 * Distributed under the GPL version 2.
 * See LICENSE for license details.
 */
#ifndef _IGDAEMON_
#define _IGDAEMON_

typedef struct client
{
    /* we keep a list of clients for each device */
    itemHeader header;

    /* which iguana device is this associated with? */
    iguanaDev *idev;

    /* for communication with the client */
    PIPE_PTR fd;

    /* whether recv messages should be returned to this client */
    int receiving;

    /* protocol version that should be used with this client */
    uint16_t version;

    /* true name of the device */
    const char *name;

#ifdef WIN32
    /* used in the win32 driver to keep track of overlapped actions */
    HANDLE listenData;
#endif
} client;

typedef bool (*handleReaderFunc)(iguanaDev *idev);
typedef void (*clientConnectedFunc)(const char *name,
                                    PIPE_PTR who, iguanaDev *idev);
typedef bool (*handleClientFunc)(client *me);

void listenToClients(const char *name, iguanaDev *idev,
                     handleReaderFunc handleReader,
                     clientConnectedFunc clientConnected,
                     handleClientFunc handleClient);
void setAlias(const char *name, const char *alias);

/* the worker thread has to check the id at startup */
void getID(const char *name, iguanaDev *idev);
/* start a thread to handle a single device instance */
void startWorker(deviceInfo *info);
/* terminate and join with each child thread */
bool reapAllChildren(deviceList *list, deviceSettings *settings);

extern bool readLabels;
#ifdef LIBUSB_NO_THREADS_OPTION
extern bool noThreads;
#endif

#endif
