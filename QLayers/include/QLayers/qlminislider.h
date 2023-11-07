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

#ifndef QLMINISLIDER_H
#define QLMINISLIDER_H

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLMiniSlider : public QLWidget
{
	Q_OBJECT

public:
	QLMiniSlider(double limit = 99.0, QWidget* parent = nullptr);

	void set_limit(double limit);

	Layers::LAttribute* value();

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	double drag_increment() const;

	void init_attributes();

	void init_layout();

	void update_handle_pos();

	Layers::LAttribute* m_value
		{ new Layers::LAttribute("value", 0.0, this) };

	QLWidget* m_bar{ new QLWidget };
	QLWidget* m_handle{ new QLWidget(this) };

	double m_limit;

	int m_mouse_move_scale{ 5 };
	int m_value_on_click{ 0 };

	bool m_dragging_handle{ false };

	QPoint m_mouse_click_position;
};
QLAYERS_NAMESPACE_END

#endif // QLMINISLIDER_H
