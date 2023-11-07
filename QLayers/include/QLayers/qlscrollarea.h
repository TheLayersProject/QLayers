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

#ifndef QLSCROLLAREA_H
#define QLSCROLLAREA_H

#include <QScrollArea>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlscrollbar.h"
#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLScrollArea : public QScrollArea, public QLThemeable
{
	Q_OBJECT

public:
	QLScrollArea(QWidget* parent = nullptr);

	virtual QList<QLThemeable*> q_child_themeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	void setWidget(QWidget* widget);

private:
	QLScrollBar* m_horizontal_scrollbar{ new QLScrollBar };
	QLScrollBar* m_vertical_scrollbar{ new QLScrollBar };
};
QLAYERS_NAMESPACE_END

#endif // QLSCROLLAREA_H
