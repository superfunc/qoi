CC ?= gcc
CFLAGS_BENCH ?= -std=gnu99 -O3
LFLAGS_BENCH ?= -lpng $(LDFLAGS)
CFLAGS_CONV ?= -std=c99 -O3
LFLAGS_CONV ?= $(LDFLAGS)

TARGET_BENCH ?= qoibench
TARGET_CONV ?= qoiconv

all: $(TARGET_BENCH) $(TARGET_CONV)

bench: $(TARGET_BENCH)
$(TARGET_BENCH):$(TARGET_BENCH).c qoi.c qoi_io.c qoi.h qoi_io.h
	$(CC) $(CFLAGS_BENCH) $(CFLAGS) qoi.c qoi_io.c $(TARGET_BENCH).c -o $(TARGET_BENCH) $(LFLAGS_BENCH)

conv: $(TARGET_CONV)
$(TARGET_CONV):$(TARGET_CONV).c qoi.c qoi_io.c qoi.h qoi_io.h
	$(CC) $(CFLAGS_CONV) $(CFLAGS) qoi.c qoi_io.c $(TARGET_CONV).c -o $(TARGET_CONV) $(LFLAGS_CONV)

.PHONY: clean
clean:
	$(RM) $(TARGET_BENCH) $(TARGET_CONV)
