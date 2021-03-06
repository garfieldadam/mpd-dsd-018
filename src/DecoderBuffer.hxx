/*
 * Copyright (C) 2003-2013 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_DECODER_BUFFER_HXX
#define MPD_DECODER_BUFFER_HXX

#include "Compiler.h"

#include <stddef.h>

/**
 * This objects handles buffered reads in decoder plugins easily.  You
 * create a buffer object, and use its high-level methods to fill and
 * read it.  It will automatically handle shifting the buffer.
 */
struct DecoderBuffer;

struct Decoder;
struct InputStream;

/**
 * Creates a new buffer.
 *
 * @param decoder the decoder object, used for decoder_read(), may be nullptr
 * @param is the input stream object where we should read from
 * @param size the maximum size of the buffer
 * @return the new decoder_buffer object
 */
DecoderBuffer *
decoder_buffer_new(Decoder *decoder, InputStream &is,
		   size_t size);

/**
 * Frees resources used by the decoder_buffer object.
 */
void
decoder_buffer_free(DecoderBuffer *buffer);

gcc_pure
const InputStream &
decoder_buffer_get_stream(const DecoderBuffer *buffer);

gcc_pure
bool
decoder_buffer_is_empty(const DecoderBuffer *buffer);

gcc_pure
bool
decoder_buffer_is_full(const DecoderBuffer *buffer);

void
decoder_buffer_clear(DecoderBuffer *buffer);

/**
 * Read data from the input_stream and append it to the buffer.
 *
 * @return true if data was appended; false if there is no data
 * available (yet), end of file, I/O error or a decoder command was
 * received
 */
bool
decoder_buffer_fill(DecoderBuffer *buffer);

/**
 * How many bytes are stored in the buffer?
 */
gcc_pure
size_t
decoder_buffer_available(const DecoderBuffer *buffer);

/**
 * Reads data from the buffer.  This data is not yet consumed, you
 * have to call decoder_buffer_consume() to do that.  The returned
 * buffer becomes invalid after a decoder_buffer_fill() or a
 * decoder_buffer_consume() call.
 *
 * @param buffer the decoder_buffer object
 * @param length_r pointer to a size_t where you will receive the
 * number of bytes available
 * @return a pointer to the read buffer, or nullptr if there is no data
 * available
 */
const void *
decoder_buffer_read(const DecoderBuffer *buffer, size_t *length_r);

/**
 * Consume (delete, invalidate) a part of the buffer.  The "nbytes"
 * parameter must not be larger than the length returned by
 * decoder_buffer_read().
 *
 * @param buffer the decoder_buffer object
 * @param nbytes the number of bytes to consume
 */
void
decoder_buffer_consume(DecoderBuffer *buffer, size_t nbytes);

/**
 * Skips the specified number of bytes, discarding its data.
 *
 * @param buffer the decoder_buffer object
 * @param nbytes the number of bytes to skip
 * @return true on success, false on error
 */
bool
decoder_buffer_skip(DecoderBuffer *buffer, size_t nbytes);

#endif
