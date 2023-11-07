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

#ifndef QLFILLCONTROL_H
#define QLFILLCONTROL_H

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLFillDialog;

class QLAYERS_EXPORT QLFillControl : public QLWidget
{
	Q_OBJECT

public:
	QLFillControl(QWidget* parent = nullptr);

	~QLFillControl();

	void set_attribute(Layers::LAttribute* attribute);

protected:
	bool eventFilter(QObject* object, QEvent* event);

private:
	void init_attributes();
};
QLAYERS_NAMESPACE_END

#endif // QLFILLCONTROL_H
