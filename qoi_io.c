#include "./qoi_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void qoi_io_impl_zero_arr_fn(void* arr) {
  memset(arr, 0, sizeof(arr));
}

qoi_malloc_fn QOI_IO_MALLOC = malloc;
qoi_free_fn QOI_IO_FREE = free;
qoi_zero_arr_fn QOI_IO_ZEROARR = qoi_io_impl_zero_arr_fn;

void qoi_io_set_memory_functions(qoi_malloc_fn malloc_fn, qoi_free_fn free_fn, qoi_zero_arr_fn zero_fn)
{
  QOI_IO_MALLOC = malloc_fn;
  QOI_IO_FREE = free_fn;
  QOI_IO_ZEROARR = zero_fn;
}

int qoi_write(const char *filename, const void *data, const qoi_desc *desc) {
	FILE *f = fopen(filename, "wb");
	int size, err;
	void *encoded;

	if (!f) {
		return 0;
	}

	encoded = qoi_encode(data, desc, &size);
	if (!encoded) {
		fclose(f);
		return 0;
	}

	fwrite(encoded, 1, size, f);
	fflush(f);
	err = ferror(f);
	fclose(f);

	QOI_IO_FREE(encoded);
	return err ? 0 : size;
}

void *qoi_read(const char *filename, qoi_desc *desc, int channels) {
	FILE *f = fopen(filename, "rb");
	int size, bytes_read;
	void *pixels, *data;

	if (!f) {
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	if (size <= 0 || fseek(f, 0, SEEK_SET) != 0) {
		fclose(f);
		return NULL;
	}

	data = QOI_IO_MALLOC(size);
	if (!data) {
		fclose(f);
		return NULL;
	}

	bytes_read = fread(data, 1, size, f);
	fclose(f);
	pixels = (bytes_read != size) ? NULL : qoi_decode(data, bytes_read, desc, channels);
	QOI_IO_FREE(data);
	return pixels;
}


