STD_CFLAGS := \
	-std=c11 \
	-O2 \
	-Wall \
	-Wextra \
	-funsigned-char \
	-D_POSIX_C_SOURCE=200809L \
	-D_XOPEN_SOURCE=700

LIBS := -lm

hexterm: hexterm.c
	$(CC) $(STD_CFLAGS) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f hexterm
