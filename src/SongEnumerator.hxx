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

#ifndef MPD_SONG_ENUMERATOR_HXX
#define MPD_SONG_ENUMERATOR_HXX

struct Song;

/**
 * An object which provides serial access to a number of #Song
 * objects.  It is used to enumerate the contents of a playlist file.
 */
class SongEnumerator {
public:
	virtual ~SongEnumerator() {}

	/**
	 * Obtain the next song.  The caller is responsible for
	 * freeing the returned #Song object.  Returns nullptr if
	 * there are no more songs.
	 */
	virtual Song *NextSong() = 0;
};

#endif
