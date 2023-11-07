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

#ifndef QLSPLITTER_H
#define QLSPLITTER_H

#include <QSplitter>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLSplitter : public QSplitter, public QLThemeable
{
	Q_OBJECT

public:
	QLSplitter(QWidget* parent = nullptr);

	QLSplitter(Qt::Orientation orientation, QWidget* parent = nullptr);

private:
	void init();
};
QLAYERS_NAMESPACE_END

#endif // QLSPLITTER_H
