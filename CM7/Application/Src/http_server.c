/**
 ******************************************************************************
 * @file           : httpserver.c
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2018-present Reso-nance Numerique.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <http_server.h>
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include <stdio.h>
#include "cmsis_os.h"

#include "file_manager.h"

#include "shared.h"

TaskHandle_t http_ThreadHandle = NULL;

char colour;
int indx = 0;

static void http_server(struct netconn *conn)
{
	struct netbuf *inbuf;
	err_t recv_err;
	char* buf;
	u16_t buflen;
	struct fs_file file;

	/* Read the data from the port, blocking if nothing yet there */
	recv_err = netconn_recv(conn, &inbuf);

	if (recv_err == ERR_OK)
	{
		if (netconn_err(conn) == ERR_OK)
		{
			/* Get the data pointer and length of the data inside a netbuf */
			netbuf_data(inbuf, (void**)&buf, &buflen);

			/* Check for various paths and handle GET requests */
			if (strncmp((char const *)buf, "GET /config.html", 16) == 0)
			{
				fs_open(&file, "/config.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

			/* Send an image file for requests to '/img/CISYNTH.png' */
			else if (strncmp((char const *)buf, "GET /img/CISYNTH.png", 20) == 0)
			{
				fs_open(&file, "/img/CISYNTH.png");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

			/* Send a favicon for requests to '/img/favicon.ico' */
			else if (strncmp((char const *)buf, "GET /img/favicon.ico", 20) == 0)
			{
				fs_open(&file, "/img/favicon.ico");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

			/* Get frequency data and send response */
			else if (strncmp((char const *)buf, "GET /getFreq", 12) == 0)
			{
			    char response[128];
			    int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", (int)shared_var.cis_freq);
			    netconn_write(conn, response, len, NETCONN_COPY);
			}

			/* Get DPI data and send response */
			else if (strncmp((char const *)buf, "GET /getDPI", 11) == 0)
			{
			    char response[100];
			    int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", (int)shared_config.cis_dpi);

			    netconn_write(conn, response, len, NETCONN_COPY);
			}

			/* Process POST request to set DPI */
			else if (strncmp((char const *)buf, "POST /setDPI", 12) == 0)
			{
			    char *dpiValue = strstr(buf, "dpi=") + 4;  // Point to the first character of the value

			    if (dpiValue) {
			         shared_config.cis_dpi = atoi(dpiValue);
				     shared_config.cis_dpi  = shared_config.cis_dpi  < 200 ? 200 : shared_config.cis_dpi  > 200 ? 400 : shared_config.cis_dpi ;
				     file_writeConfig(CONFIG_FILE_PATH, &shared_config);

			        char response[100];
			        int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", (int) shared_config.cis_dpi);
			        netconn_write(conn, response, len, NETCONN_COPY);
			    } else {
			        char *errorResponse = "Error: DPI value not found";
			        netconn_write(conn, errorResponse, strlen(errorResponse), NETCONN_NOCOPY);
			    }
			}

			/* Get and set oversampling settings */
			else if (strncmp((char const *)buf, "GET /getOversampling", 20) == 0)
			{
			    char response[100];
			    int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", (int)shared_config.cis_oversampling);

			    netconn_write(conn, response, len, NETCONN_COPY);
			}

			/* Process POST request to set oversampling */
			else if (strncmp((char const *)buf, "POST /setOversampling", 21) == 0)
			{
			    char *oversamplingValue = strstr(buf, "oversampling=") + 13;

			    if (oversamplingValue) {
			        shared_config.cis_oversampling = atoi(oversamplingValue);
			        shared_config.cis_oversampling  = shared_config.cis_oversampling  < 0 ? 0 : shared_config.cis_oversampling  > 32 ? 32 : shared_config.cis_oversampling ;
			        file_writeConfig(CONFIG_FILE_PATH, &shared_config);

			        char response[100];
			        int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOversampling set to %d", (int)shared_config.cis_oversampling);
			        netconn_write(conn, response, len, NETCONN_COPY);
			    } else {
			        char *errorResponse = "Error: Oversampling value not found";
			        netconn_write(conn, errorResponse, strlen(errorResponse), NETCONN_NOCOPY);
			    }
			}

			/* Get hand settings */
			else if (strncmp((char const *)buf, "GET /getHand", 12) == 0)
			{
			    char response[100];
			    int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", (int)shared_config.cis_handedness);

			    netconn_write(conn, response, len, NETCONN_COPY);
			}

			/* Process POST request to set hand settings */
			else if (strncmp((char const *)buf, "POST /setHand", 13) == 0)
			{
			    char *handValue = strstr(buf, "hand=") + 5;

			    if (handValue) {
			        shared_config.cis_handedness = atoi(handValue);
			        shared_config.cis_handedness =  shared_config.cis_handedness < 0 ? 0 :  shared_config.cis_handedness > 1 ? 1 :  shared_config.cis_handedness;
			        file_writeConfig(CONFIG_FILE_PATH, &shared_config);

			        char response[100];
			        int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%d", (int) shared_config.cis_handedness);
			        netconn_write(conn, response, len, NETCONN_COPY);
			    } else {
			        char *errorResponse = "Error: Hand value not found";
			        netconn_write(conn, errorResponse, strlen(errorResponse), NETCONN_NOCOPY);
			    }
			}

			/* Process calibration start command */
			else if (strncmp((char const *)buf, "POST /startCalibration", 22) == 0)
			{
			    char *body = strstr(buf, "\r\n\r\n");
			    if (body && strstr(body, "CIS_CAL_START")) {
			        shared_var.cis_cal_state = CIS_CAL_REQUESTED;
			        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nCalibration started";
			        netconn_write(conn, response, strlen(response), NETCONN_COPY);
			    }
			}




			/* Get network settings */
			else if (strncmp((char const *)buf, "GET /getNetworkConfig", 21) == 0)
			{
			    char response[300];
			    int len = sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n"
			                                "{"
			                                "\"ip\":\"%d.%d.%d.%d\","
			                                "\"mask\":\"%d.%d.%d.%d\","
			                                "\"gateway\":\"%d.%d.%d.%d\","
			                                "\"dest_ip\":\"%d.%d.%d.%d\","
			                                "\"udp_port\":%d,"
			                                "\"broadcast\":%d"
			                                "}",
			                                shared_config.network_ip[0], shared_config.network_ip[1], shared_config.network_ip[2], shared_config.network_ip[3],
			                                shared_config.network_netmask[0], shared_config.network_netmask[1], shared_config.network_netmask[2], shared_config.network_netmask[3],
			                                shared_config.network_gw[0], shared_config.network_gw[1], shared_config.network_gw[2], shared_config.network_gw[3],
			                                shared_config.network_dest_ip[0], shared_config.network_dest_ip[1], shared_config.network_dest_ip[2], shared_config.network_dest_ip[3],
			                                shared_config.network_udp_port,
			                                shared_config.network_broadcast);

			    netconn_write(conn, response, len, NETCONN_COPY);
			}



			/* Send 404 if no route matches */
			else
			{
				fs_open(&file, "/404.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

		}
	}
	/* Close the connection (server closes in HTTP) */
	netconn_close(conn);

	/* Free the buffer */
	netbuf_delete(inbuf);
}

static void http_thread(void *arg)
{
	printf("----- HTTP THREAD SARTED ------\n");
	                                          //

	struct netconn *conn, *newconn;
	err_t err, accept_err;

	/* Create a new TCP connection handle */
	conn = netconn_new(NETCONN_TCP);

	if (conn != NULL)
	{
		/* Bind to port 80 (HTTP) with default IP address */
		err = netconn_bind(conn, IP_ADDR_ANY, 80);

		if (err == ERR_OK)
		{
			/* Listen for incoming connections */
			netconn_listen(conn);

			while (1)
			{
				/* Accept any incoming connection */
				accept_err = netconn_accept(conn, &newconn);
				if (accept_err == ERR_OK)
				{
					/* Serve the connection */
					http_server(newconn);

					/* Delete the connection */
					netconn_delete(newconn);

				}
			}
		}
	}
}

void http_serverInit()
{
	printf("----- HTTP INITIALIZATIONS ----\n");
	                                          //
    if (xTaskCreate(http_thread, "http_thread", 2048, NULL, osPriorityNormal, &http_ThreadHandle) == pdPASS) {
        printf("http task created successfully.\n");
    } else {
        printf("Failed to create http task.\n");
    }
}