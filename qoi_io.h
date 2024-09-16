/*

Copyright (c) 2021, Dominic Szablewski - https://phoboslab.org
SPDX-License-Identifier: MIT

QOI - The "Quite OK Image" format for fast, lossless image compression

Spec - spec.md

*/


/* -----------------------------------------------------------------------------
Header - Public functions */

#ifndef QOI_IO_H
#define QOI_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qoi.h"

void qoi_io_set_memory_functions(qoi_malloc_fn malloc_fn, qoi_free_fn free_fn, qoi_zero_arr_fn zero_fn);

/* Encode raw RGB or RGBA pixels into a QOI image and write it to the file
system. The qoi_desc struct must be filled with the image width, height,
number of channels (3 = RGB, 4 = RGBA) and the colorspace.

The function returns 0 on failure (invalid parameters, or fopen or malloc
failed) or the number of bytes written on success. */

int qoi_write(const char *filename, const void *data, const qoi_desc *desc);


/* Read and decode a QOI image from the file system. If channels is 0, the
number of channels from the file header is used. If channels is 3 or 4 the
output format will be forced into this number of channels.

The function either returns NULL on failure (invalid data, or malloc or fopen
failed) or a pointer to the decoded pixels. On success, the qoi_desc struct
will be filled with the description from the file header.

The returned pixel data should be free()d after use. */

void *qoi_read(const char *filename, qoi_desc *desc, int channels);

#ifdef __cplusplus
}
#endif
 
#endif // QOI_IO_H
