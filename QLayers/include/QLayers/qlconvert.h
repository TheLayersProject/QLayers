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

#ifndef QLCONVERT_H
#define QLCONVERT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <QGradientStops>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include <Layers/lalgorithms.h>
#include <Layers/lstring.h>

QLAYERS_NAMESPACE_BEGIN

inline QLAYERS_EXPORT
QGradientStops to_QGradientStops(const std::vector<Layers::LString>& stops)
{
	QGradientStops q_gradient_stops;

	for (const auto& stop : stops)
	{
		auto stop_parts =
			Layers::split<std::vector<Layers::LString>>(stop, ':');

		q_gradient_stops.append(QGradientStop(
			std::stod(stop_parts[0].c_str()),
			QString::fromStdString(stop_parts[1].c_str())));
	}

	return q_gradient_stops;
}

QLAYERS_NAMESPACE_END

#endif // !QLCONVERT_H
