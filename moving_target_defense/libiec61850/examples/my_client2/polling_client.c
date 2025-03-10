/*
 * client_example1.c
 *
 * This example is intended to be used with server_example_basic_io or server_example_goose.
 */

#include "iec61850_client.h"

#include <stdlib.h>
#include <stdio.h>

#include "hal_thread.h"

int main(int argc, char **argv)
{

    char *hostname;
    int tcpPort = 102;
    const char *localIp = NULL;
    int localTcpPort = -1;

    if (argc > 1)
        hostname = argv[1];
    else
        // hostname = "192.168.0.108";
        hostname = "h2.com";

    if (argc > 2)
        tcpPort = atoi(argv[2]);

    if (argc > 3)
        localIp = argv[3];

    if (argc > 4)
        localTcpPort = atoi(argv[4]);

    while (1)
    {
        IedClientError error;
        IedConnection con = IedConnection_create();

        /* Optional bind to local IP address/interface */
        if (localIp)
        {
            IedConnection_setLocalAddress(con, localIp, localTcpPort);
            printf("Bound to Local Address: %s:%i\n", localIp, localTcpPort);
        }

        IedConnection_connect(con, &error, hostname, tcpPort);
        printf("Connecting to %s:%i\n", hostname, tcpPort);

        if (error == IED_ERROR_OK)
        {
            printf("Connected\n");

            /* read an analog measurement value from server */

            // Current Pressure
            MmsValue *CurrentPressure = IedConnection_readObject(con, &error, "IED01LogicalDevice/GGIO1.CurrentPressure.mag.f", IEC61850_FC_MX);

            if (CurrentPressure != NULL)
            {
                if (MmsValue_getType(CurrentPressure) == MMS_INTEGER)
                {
                    int fval = MmsValue_toInt32(CurrentPressure);
                    printf("Current Pressure Value : %d\n", fval);
                }
                else if (MmsValue_getType(CurrentPressure) == MMS_DATA_ACCESS_ERROR)
                {
                    printf("Failed to read value (error code: %i)\n", MmsValue_getDataAccessError(CurrentPressure));
                }

                MmsValue_delete(CurrentPressure);
            }

        close_connection:

            IedConnection_close(con);
        }
        else
        {
            printf("Failed to connect to %s:%i\n", hostname, tcpPort);
            Thread_sleep(5);
        }

        IedConnection_destroy(con);
        sleep(5);
    }

    return 0;
}
