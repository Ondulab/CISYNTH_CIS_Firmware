/**
 ******************************************************************************
 * @file           : httpserver.h
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

#ifndef __HTTP_SERVER_NETCONN_H__
#define __HTTP_SERVER_NETCONN_H__

#include "lwip/api.h"

/* Custom return type for HTTP server -----------------------------*/
typedef enum {
	HTTPSERVER_OK = 0,
	HTTPSERVER_ERROR = 1
} HTTPSERVER_StatusTypeDef;

extern TaskHandle_t http_ThreadHandle;

HTTPSERVER_StatusTypeDef http_serverInit(void);

#endif /* __HTTP_SERVER_NETCONN_H__ */
