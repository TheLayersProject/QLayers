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

#ifndef QLSLIDER_H
#define QLSLIDER_H

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLSlider : public QLWidget
{
	Q_OBJECT

public:
	QLSlider(QWidget* parent = nullptr);

	QLSlider(int limit, QWidget* parent = nullptr);

	void set_limit(int limit);

	Layers::LAttribute* value();

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();

	void init_attributes();

	void init_layout();

	void update_handle_pos();

	Layers::LAttribute* m_value
		{ new Layers::LAttribute("value", 0.0, this) };

	QLWidget* m_bar{ new QLWidget };
	QLWidget* m_handle{ new QLWidget(this) };

	int m_limit{ 99 };
	double m_value_on_click{ 0.0 };

	bool m_dragging_handle{ false };

	bool m_is_decimal_slider;

	QPoint m_mouse_click_position{ QPoint() };
};
QLAYERS_NAMESPACE_END

#endif // QLSLIDER_H
