/*
 *  server_example_simple.c
 *
 *  Copyright 2013 Michael Zillgith
 *
 *	This file is part of libIEC61850.
 *
 *	libIEC61850 is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	libIEC61850 is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with libIEC61850.  If not, see <http://www.gnu.org/licenses/>.
 *
 *	See COPYING file for the complete license text.
 */

#include "iec61850_server.h"
#include "iec61850_client.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "static_model.h"

static int running = 0;

void sigint_handler(int signalId)
{
    running = 0;
}

int main(int argc, char **argv)
{
    char *hostname;
    int tcpPort = 102;

    if (argc > 1)
        hostname = argv[1];
    else
        hostname = "h2.com";

    if (argc > 2)
    {
        tcpPort = atoi(argv[2]);
    }

    IedServer iedServer = IedServer_create(&iedModel);

    /* set initial measurement and status values from process */

    /* MMS server will be instructed to start listening to client connections. */
    IedServer_start(iedServer, tcpPort);

    if (!IedServer_isRunning(iedServer))
    {
        printf("Starting server failed! Exit.\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    running = 1;

    signal(SIGINT, sigint_handler);

    while (running)
    {
        int16_t currentPressure = -1;
        int16_t openingPressure = -1;

        // read input from 'opening_pressure_input.txt' file
        FILE *fptr1 = fopen("opening_pressure_input.txt", "r");
        fscanf(fptr1, "%hd", &openingPressure);
        fclose(fptr1);

        // read input from 'current_pressure_input.txt' file
        FILE *fptr2 = fopen("current_pressure_input.txt", "r");
        fscanf(fptr2, "%hd", &currentPressure);
        fclose(fptr2);

        if (currentPressure == -1 || openingPressure == -1)
        {
            continue;
        }

        bool coilStatus = false; // false is close, true is open

        if (currentPressure >= openingPressure)
        {
            coilStatus = true;
        }
        else
        {
            coilStatus = false;
        }

        printf("\n\nCurrent Pressure = %d", currentPressure);
        printf("\nOpening Pressure = %d", openingPressure);
        printf("\nCoil Status = %d", coilStatus);

        MmsValue *currentPressureMMSVal = MmsValue_newIntegerFromInt16(currentPressure);
        MmsValue *openingPressureMMSVal = MmsValue_newIntegerFromInt16(openingPressure);
        MmsValue *coilStatusMMSVal = MmsValue_newBoolean(coilStatus);

        // update opening pressure value in the PLC
        IedServer_lockDataModel(iedServer);

        IedServer_updateAttributeValue(iedServer,
                                       IEDMODEL_LogicalDevice_GGIO1_OpeningPressure_mag_f, openingPressureMMSVal);
        IedServer_updateAttributeValue(iedServer,
                                       IEDMODEL_LogicalDevice_GGIO1_CurrentPressure_mag_f, currentPressureMMSVal);
        IedServer_updateAttributeValue(iedServer,
                                       IEDMODEL_LogicalDevice_GGIO1_CoilStatus_mag_f, coilStatusMMSVal);

        IedServer_unlockDataModel(iedServer);

        MmsValue_delete(openingPressureMMSVal);
        MmsValue_delete(currentPressureMMSVal);
        MmsValue_delete(coilStatusMMSVal);

        Thread_sleep(100);
    }

    /* stop MMS server - close TCP server socket and all client sockets */
    IedServer_stop(iedServer);

    /* Cleanup - free all resources */
    IedServer_destroy(iedServer);

    return 0;
} /* main() */
