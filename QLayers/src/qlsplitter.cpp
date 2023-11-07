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

#include <QLayers/qlsplitter.h>

using QLayers::QLSplitter;

QLSplitter::QLSplitter(QWidget* parent) :
	QSplitter(parent)
{
	init();
}

QLSplitter::QLSplitter(Qt::Orientation orientation, QWidget* parent) :
	QSplitter(orientation, parent)
{
	init();
}

void QLSplitter::init()
{
	set_object_name("Splitter");
	setHandleWidth(20);
}
