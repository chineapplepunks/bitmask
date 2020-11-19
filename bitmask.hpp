/**
 * Bitmask - A pixel-perfect collision detection library (C++ port).
 * 
 * Copyright (C) 2020 Adam Brooke. 
 * 
 * This library is based around Danny van Bruggen's Java port of 
 * Ulf Ekstrom's C Bitmask library, which is Copyright (C) 2002-2005 
 * Ulf Ekstrom except for the bitcount function which is 
 * copyright (C) Donald W. Gillies, 1992.
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * Original C bitmask library can be found at:
 * https://github.com/matozoid/rudl
 * 
 * Danny van Bruggen's Java port can be found at:
 * https://github.com/laamella-gad/bitmask
 *
 * @file bitmask.hpp
 * @author Adam Brooke
 * @version 1.0
 * @date 2020
 * @copyright Lesser GNU Public License, version 2.1
 * @brief Contains class declaration for bitmasks.
 * 
 * This file contains a class declaration for bitmasks, which in this application
 * will be used for quick pixel-perfect collision detection between two bitmasks.
 * 
 * Bitmasks store the state of a single pixel in a single bit in an integer.
 * If there is a fully transparent pixel, the bit will be 0. An opaque pixel will
 * be 1.
 * 
 * You can therefore compare 32 pixels in the same time it would take to compare a single
 * pixel (if a pixel is represented as 4 bytes), simply by using bitwise operators.
 * 
 * It is still a good idea to use more general collision detection routines before using 
 * the overlaps function of this class, such as AABB checks and Quad Tree partitioning.
 * 
 * I'd like to acknowledge Ulf Ekstrom, who was the author of the original bitmask C library.
 * I'd also like to acknowledge Danny van Bruggen, who ported the C bitmask library to Java.
 * This library is derived from these code bases.
 */

#ifndef BITMASK_HPP
#define BITMASK_HPP

#include <vector>
#include <cmath>

/**
 * @class Bitmask
 * @brief Class Bitmask is used to store bitmasks.
 * 
 * This class is used to store bitmasks. Bitmasks are used to represent the state
 * of a pixel in a single bit of an integer. This allows us to do pixel perfect
 * collision detections more effectively and efficiently.
 */
class Bitmask
{
private:
	std::vector<int> bitmask_;
	int height_;
	int width_;
	
	const static int BIT_LENGTH_ = sizeof(int);
	const static int BIT_MASK_ = BIT_LENGTH_ - 1;
	
	int mask(int n) const;
public:
	/**
	 * @brief Constructor.
	 * 
	 * Constructs a new Bitmask.
	 */
	Bitmask();
	/**
	 * @brief Constructor.
	 * @param w The width of the bitmask.
	 * @param h The height of the bitmask.
	 * 
	 * Constructs a new Bitmask with the given dimensions.
	 */
	Bitmask(int w, int h);
	
	/**
	 * @brief Turns a bit on.
	 * @param x The x coordinate of the bit you want to turn on.
	 * @param y The y coordinate of the bit you want to turn on.
	 *
	 * Turns on the bit located at the position (x,y).
	 */
	void set_bit(int x, int y);
	/**
	 * @brief Returns a bit.
	 * @param x The x coordinate of the bit to retrieve.
	 * @param y The y coordinate of the bit to retrieve.
	 * @return The bit.
	 * 
	 * If the bit located at (x,y) has been previously set, it will
	 * return true. Otherwise, return false.
	 */
	bool get_bit(int x, int y) const;
	/**
	 * @brief Checks whether this bitmask overlaps another.
	 * @param b The bitmask to compare against.
	 * @param x_offset The x offset.
	 * @param y_offset The y offset
	 * @return True if one or more pixels overlap.
	 * 
	 * The overlap test uses the following offsets (which may be negative):
     *
	 *   +----+----------..
	 *   |this| yoffset   
	 *   |  +-+----------..
	 *   +--|B        
	 *   |xoffset      
	 *   |  |
	 *   :  : 
	 *
	 * And tests to see if a set pixel exists in the same place in both bitmasks. 
	 */
	bool overlaps(Bitmask& b, int x_offset, int y_offset);
};

#endif