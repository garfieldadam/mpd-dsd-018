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

/** \file
 *
 * Internal stuff for the filter core and filter plugins.
 */

#ifndef MPD_FILTER_INTERNAL_HXX
#define MPD_FILTER_INTERNAL_HXX

#include <stddef.h>

struct AudioFormat;
class Error;

class Filter {
public:
	virtual ~Filter() {}

	/**
	 * Opens the filter, preparing it for FilterPCM().
	 *
	 * @param filter the filter object
	 * @param audio_format the audio format of incoming data; the
	 * plugin may modify the object to enforce another input
	 * format
	 * @param error location to store the error occurring, or nullptr
	 * to ignore errors.
	 * @return the format of outgoing data or
	 * AudioFormat::Undefined() on error
	 */
	virtual AudioFormat Open(AudioFormat &af, Error &error) = 0;

	/**
	 * Closes the filter.  After that, you may call Open() again.
	 */
	virtual void Close() = 0;

	/**
	 * Filters a block of PCM data.
	 *
	 * @param filter the filter object
	 * @param src the input buffer
	 * @param src_size the size of #src_buffer in bytes
	 * @param dest_size_r the size of the returned buffer
	 * @param error location to store the error occurring, or nullptr
	 * to ignore errors.
	 * @return the destination buffer on success (will be
	 * invalidated by filter_close() or filter_filter()), nullptr on
	 * error
	 */
	virtual const void *FilterPCM(const void *src, size_t src_size,
				      size_t *dest_size_r,
				      Error &error) = 0;
};

#endif
