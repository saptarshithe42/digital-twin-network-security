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
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "static_model.h"

static int running = 0;
static IedServer iedServer = NULL;

void sigint_handler(int signalId)
{
    running = 0;
}

static void
connectionHandler(IedServer self, ClientConnection connection, bool connected, void *parameter)
{
    if (connected)
        printf("Connection opened\n");
    else
        printf("Connection closed\n");
}

static void
printAppTitle(ItuObjectIdentifier *oid)
{
    int i;

    for (i = 0; i < oid->arcCount; i++)
    {
        printf("%i", oid->arc[i]);

        if (i != (oid->arcCount - 1))
            printf(".");
    }
}

static bool
clientAuthenticator(void *parameter, AcseAuthenticationParameter authParameter, void **securityToken, IsoApplicationReference *appRef)
{
    printf("ACSE Authenticator:\n");
    printf("  client ap-title: ");
    printAppTitle(&(appRef->apTitle));
    printf("\n");
    printf("  client ae-qualifier: %i\n", appRef->aeQualifier);
    printf("  auth-mechanism: %i\n", authParameter->mechanism);

    if (authParameter->mechanism == ACSE_AUTH_TLS)
    {
        printf("  Has certificate with size: %i\n", authParameter->value.certificate.length);
    }

    return true;
}

static void
securityEventHandler(void *parameter, TLSEventLevel eventLevel, int eventCode, const char *msg, TLSConnection con)
{
    (void)parameter;

    char *peerAddr = TLSConnection_getPeerAddress(con, NULL);

    const char *tlsVersionStr = TLSConfigVersion_toString(TLSConnection_getTLSVersion(con));

    printf("[SECURITY EVENT - %s] %s (%s)(t: %i, c: %i)\n", tlsVersionStr, msg, peerAddr, eventLevel, eventCode);

    free(peerAddr);
}

int main(int argc, char **argv)
{
    int tcpPort = 102;

    if (argc > 1)
    {
        tcpPort = atoi(argv[1]);
    }

    printf("Using libIEC61850 version %s\n", LibIEC61850_getVersionString());

    TLSConfiguration tlsConfig = TLSConfiguration_create();

    TLSConfiguration_setChainValidation(tlsConfig, false);
    TLSConfiguration_setAllowOnlyKnownCertificates(tlsConfig, true);

    TLSConfiguration_setEventHandler(tlsConfig, securityEventHandler, NULL);

    if (!TLSConfiguration_setOwnKeyFromFile(tlsConfig, "server_CA1_1.key", NULL))
    {
        printf("Failed to load private key!\n");
        return 0;
    }

    if (!TLSConfiguration_setOwnCertificateFromFile(tlsConfig, "server_CA1_1.pem"))
    {
        printf("ERROR: Failed to load own certificate!\n");
        return 0;
    }

    if (!TLSConfiguration_addCACertificateFromFile(tlsConfig, "root_CA1.pem"))
    {
        printf("ERROR: Failed to load root certificate\n");
        return 0;
    }

    /**
     * Configure two allowed clients
     */

    if (!TLSConfiguration_addAllowedCertificateFromFile(tlsConfig, "client_CA1_1.pem"))
    {
        printf("ERROR: Failed to load allowed client certificate\n");
        return 0;
    }

    if (!TLSConfiguration_addAllowedCertificateFromFile(tlsConfig, "client_CA1_2.pem"))
    {
        printf("ERROR: Failed to load allowed client certificate\n");
        return 0;
    }

    iedServer = IedServer_createWithTlsSupport(&iedModel, tlsConfig);

    IedServer_setAuthenticator(iedServer, clientAuthenticator, NULL);

    IedServer_setConnectionIndicationHandler(iedServer, (IedConnectionIndicationHandler)connectionHandler, NULL);

    IedServer_start(iedServer, -1);

    /* set initial measurement and status values from process */

    /* MMS server will be instructed to start listening to client connections. */
    // IedServer_start(iedServer, tcpPort);

    if (!IedServer_isRunning(iedServer))
    {
        printf("Starting server failed! Exit.\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }

    running = 1;

    signal(SIGINT, sigint_handler);

    int16_t pressure = 1000;

    MmsValue *pressureValue = MmsValue_newIntegerFromInt16(pressure);

    while (running)
    {

        // read input from 'pressure_input.txt' file
        FILE *fptr = fopen("pressure_input.txt", "r");
        fscanf(fptr, "%hd", &pressure);
        fclose(fptr);

        // update pressure value in the IED
        IedServer_lockDataModel(iedServer);

        IedServer_updateAttributeValue(iedServer,
                                       IEDMODEL_LogicalDevice_GGIO1_CurrentPressure_mag_f, pressureValue);

        IedServer_unlockDataModel(iedServer);

        MmsValue_setInt16(pressureValue, pressure);

        Thread_sleep(100);
    }

    /* stop MMS server - close TCP server socket and all client sockets */
    IedServer_stop(iedServer);

    /* Cleanup - free all resources */
    IedServer_destroy(iedServer);

    return 0;
} /* main() */
