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

#ifndef QLCOLORCONTROL_H
#define QLCOLORCONTROL_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLColorControl : public QLWidget
{
	Q_OBJECT

signals:
	void color_changed();

public:
	QLColorControl(QWidget* parent = nullptr);

	~QLColorControl();

	void click();

	void disable_clicking(bool cond = true);

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_attributes();

	bool clicking_disabled{ false };
	bool open_on_release{ false };

	QStringList m_attribute_states;
};
QLAYERS_NAMESPACE_END

#endif // QLCOLORCONTROL_H
