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

#ifndef QLRADIOBUTTON_H
#define QLRADIOBUTTON_H

#include <QWidget>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLRadioButton : public QWidget, public QLThemeable
{
	Q_OBJECT

signals:
	void clicked();

public:
	QLRadioButton(QWidget* parent = nullptr);

	QLStatePool* status_states() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:
	void init_attributes();

	Layers::LAttribute* m_active_dot_fill
		{ new Layers::LAttribute("Active Dot Fill", "#000000", this) };

	Layers::LAttribute* m_border_fill
		{ new Layers::LAttribute("Border.Fill", "#a0a0a4", this) };

	Layers::LAttribute* m_border_thickness
		{ new Layers::LAttribute("Border.Thickness", 3.0, this) };

	Layers::LAttribute* m_fill
		{ new Layers::LAttribute("Fill", "#808080", this) };

	Layers::LAttribute* m_margin
		{ new Layers::LAttribute("Margin", 10.0, this) };

	//QLStatePool* m_select_states{
	//	new QLStatePool("Select", { "Selected", "Unselected" }) };

	QLStatePool* m_status_states{
		new QLStatePool("Status", { "Active", "Inactive" }) };
};
QLAYERS_NAMESPACE_END

#endif // QLRADIOBUTTON_H
