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

#ifndef QLGRADIENTDIALOG_H
#define QLGRADIENTDIALOG_H

#include <QTimer>

#include <Layers/lstring.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlbutton.h"
#include "qlcolorcontrol.h"
#include "qldialog.h"
#include "qlgradienteditor.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLGradientDialog : public QLDialog
{
	Q_OBJECT

public:
	QLGradientDialog(std::vector<Layers::LString> stops, QWidget* parent = nullptr);

	std::vector<Layers::LString> stops() const;

private:
	void init_layout();

	QLGradientEditor* m_gradient_editor;

	QLButton* m_apply_button{
		new QLButton(QLGraphic(":/images/check.svg", QSize(16, 13)), "Apply") };
};
QLAYERS_NAMESPACE_END

#endif // QLGRADIENTDIALOG_H
