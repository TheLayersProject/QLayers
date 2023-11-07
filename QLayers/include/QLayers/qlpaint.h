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

#ifndef QLPAINT_H
#define QLPAINT_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlcalculate.h"
#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN

QLAYERS_EXPORT constexpr QPoint lpoint(int p)
{
	return QPoint(p, p);
}

QLAYERS_EXPORT constexpr QSize lsize(int s)
{
	return QSize(s, s);
}

struct QLAYERS_EXPORT LCornerRadii
{
	int top_left{ 0 };
	int top_right{ 0 };
	int bottom_left{ 0 };
	int bottom_right{ 0 };
};

QLAYERS_NAMESPACE_END

#endif // QLPAINT_H
