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

#ifndef QLGRADIENTEDITORITEM
#define QLGRADIENTEDITORITEM

#include <QGradientStop>

#include <QLayers/qlayers_global.h>

#include <QLayers/qlcolorcontrol.h>

QLAYERS_NAMESPACE_BEGIN

struct QLGradientEditorItem
{
	QGradientStop stop;
	QLColorControl* control;
};

inline bool compare_items(
	QLGradientEditorItem* left, QLGradientEditorItem* right)
{
	return left->control->x() < right->control->x();
}

QLAYERS_NAMESPACE_END

#endif // QLGRADIENTEDITORITEM
