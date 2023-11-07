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

#ifndef QLFILLDIALOG_H
#define QLFILLDIALOG_H

#include <QGraphicsOpacityEffect>

#include <Layers/lattribute.h>
#include <Layers/lstring.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlcolorcontrol.h"
#include "qldialog.h"
#include "qlgradientcontrol.h"
#include "qltoggleswitch.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLFillDialog : public QLDialog
{
	Q_OBJECT

public:
	QLFillDialog(QWidget* parent = nullptr);

	void set_attribute(Layers::LAttribute* attribute);

private:
	void init_attributes();
	void init_layout();

	LToggleSwitch* m_fill_type_toggle{ new LToggleSwitch(true) };

	QGraphicsOpacityEffect* m_color_label_opacity
		{ new QGraphicsOpacityEffect };
	QGraphicsOpacityEffect* m_gradient_label_opacity
		{ new QGraphicsOpacityEffect };

	QLLabel* m_color_label{ new QLLabel("Color") };
	QLLabel* m_gradient_label{ new QLLabel("Gradient") };

	QLColorControl* m_color_control{ new QLColorControl };
	QLGradientControl* m_gradient_control{ new QLGradientControl };

	Layers::LString m_previous_color{ "#f0f0f0" };
	std::vector<Layers::LString> m_previous_gradient{ "0:#f0f0f0", "0:#0f0f0f" };
};
QLAYERS_NAMESPACE_END

#endif // QLFILLDIALOG_H
