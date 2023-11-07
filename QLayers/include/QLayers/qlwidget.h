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

#ifndef QLWIDGET_H
#define QLWIDGET_H

#include <QWidget>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeablebox.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLWidget : public QWidget, public QLThemeableBox
{
	Q_OBJECT

public:
	QLWidget(QWidget* parent = nullptr);

protected:
	virtual void paintEvent(QPaintEvent* event) override;
};
QLAYERS_NAMESPACE_END

#endif // QLWIDGET_H  
