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

#ifndef QLRESIZER_H
#define QLRESIZER_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qllabel.h"

QLAYERS_NAMESPACE_BEGIN
enum class QLAYERS_EXPORT QLSizeDimension { Width, Height };

class QLAYERS_EXPORT QLResizer : public QWidget, public QLThemeable
{
	Q_OBJECT

public:
	QLResizer(QLSizeDimension resize_dimension, QWidget* parent = nullptr);

	void set_widget(QWidget* widget, int lower_limit, int upper_limit);

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

	virtual void paintEvent(QPaintEvent* event) override;

private:
	QLSizeDimension m_resize_dimension;

	QLSvgRenderer* m_icon_svg{ nullptr };

	QSize m_icon_size;

	QLStatePool* m_select_states
		{ new QLStatePool("Select", { "Selected", "Unselected" }) };

	QPoint m_click_pos;
	QSize m_click_size;

	QWidget* m_widget{ nullptr };

	int m_lower_limit{ 0 };
	int m_upper_limit{ 1000 };
};
QLAYERS_NAMESPACE_END

#endif // QLRESIZER_H
