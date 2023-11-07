/*
 * Copyright (C) 2023 The Layers Project
 *
 * This file is part of QLayers.
 *
 * QLayers is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QLayers is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with QLayers. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef QLCALCULATE_H
#define QLCALCULATE_H

#include <cmath>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN

QLAYERS_EXPORT inline double round(double d)
{
	return floor(d + 0.5);
}

QLAYERS_EXPORT inline bool is_even(int i)
{
	if (i % 2) return false;

	return true;
}

QLAYERS_EXPORT inline double inner_radius(int outer_radius, int thickness)
{
	double value = outer_radius - thickness;

	if (value < 0.0)
		return 0.0;

	return value;
}

QLAYERS_NAMESPACE_END

#endif // QLCALCULATE_H
