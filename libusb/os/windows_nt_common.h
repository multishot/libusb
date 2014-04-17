/*
 * Windows backend common header for libusb 1.0
 *
 * This file brings together header code common between
 * the desktop Windows backends.
 * Copyright © 2012-2013 RealVNC Ltd.
 * Copyright © 2009-2012 Pete Batard <pete@akeo.ie>
 * With contributions from Michael Plante, Orin Eman et al.
 * Parts of this code adapted from libusb-win32-v1 by Stephan Meyer
 * Major code testing contribution by Xiaofan Chen
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#pragma once

#include <stdbool.h>

typedef struct USB_CONFIGURATION_DESCRIPTOR {
  UCHAR  bLength;
  UCHAR  bDescriptorType;
  USHORT wTotalLength;
  UCHAR  bNumInterfaces;
  UCHAR  bConfigurationValue;
  UCHAR  iConfiguration;
  UCHAR  bmAttributes;
  UCHAR  MaxPower;
} USB_CONFIGURATION_DESCRIPTOR, *PUSB_CONFIGURATION_DESCRIPTOR;

typedef struct libusb_device_descriptor USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;

#define HTAB_SIZE                   1021

int htab_create(struct libusb_context *ctx, unsigned long nel);
void htab_destroy(void);
unsigned long htab_hash(char* str);

extern const uint64_t epoch_time;

bool win_nt_init_clock(struct libusb_context *ctx);
void win_nt_destroy_clock(void);
int win_nt_clock_gettime(int clk_id, struct timespec *tp);

void win_backend_clear_transfer_priv(struct usbi_transfer *itransfer);
int win_backend_copy_transfer_data(struct usbi_transfer *itransfer, uint32_t io_size);
struct winfd *win_backend_get_fd(struct usbi_transfer *transfer);
void win_backend_get_overlapped_result(struct usbi_transfer *transfer, struct winfd *pollable_fd, DWORD *io_result, DWORD *io_size);

void win_nt_handle_callback(struct usbi_transfer *itransfer, uint32_t io_result, uint32_t io_size);
void win_nt_transfer_callback(struct usbi_transfer *itransfer, uint32_t io_result, uint32_t io_size);
int win_nt_handle_events(struct libusb_context *ctx, struct pollfd *fds, POLL_NFDS_TYPE nfds, int num_ready);

#if defined(ENABLE_LOGGING)
char *windows_error_str(uint32_t retval);
#endif
