/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <cryptoauthlib.h>

#define AES_CONFIG_ENABLE_BIT_MASK 0x01

int main(void)
{
	uint8_t revision[4] = {0};
	ATCA_STATUS status = atcab_info(revision);
	
	if(status == ATCA_SUCCESS)
	{
		for(uint8_t i=0;i<4;i++)
		{
			printf("%02X ", revision[i]);
		}
		printf("\r\n");
	}

	uint8_t aes_enable;

	status = atcab_read_bytes_zone(ATCA_ZONE_CONFIG, 0, 13, &aes_enable, 1);
	if ((aes_enable & AES_CONFIG_ENABLE_BIT_MASK) == 0)
	{
		printf("Ignoring the test, AES is not enabled in config zone");
	}

	printf("Hello World! %s\n", CONFIG_BOARD);

	return 0;
}
