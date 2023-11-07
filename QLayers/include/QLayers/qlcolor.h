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

#ifndef QLCOLOR_H
#define QLCOLOR_H

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN

enum class QLAYERS_EXPORT HSV { Hue, Saturation, Value };

QLAYERS_EXPORT extern const int MAX_H;
QLAYERS_EXPORT extern const int MAX_SV;
QLAYERS_EXPORT extern const int MAX_RGB;

QLAYERS_NAMESPACE_END

#endif // QLCOLOR_H
