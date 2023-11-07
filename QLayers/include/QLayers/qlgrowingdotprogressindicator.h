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

#ifndef QLGROWINGDOTPROGRESSINDICATOR_H
#define QLGROWINGDOTPROGRESSINDICATOR_H

#include <QTimer>
#include <QWidget>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLGrowingDotProgressIndicator :
	public QWidget, public QLThemeable
{
	Q_OBJECT

signals:
	void timeout();

public:
	QLGrowingDotProgressIndicator(QWidget* parent = nullptr);

	~QLGrowingDotProgressIndicator();

	void start(int msec);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QTimer* m_progress_timer{ new QTimer };
	QTimer* m_update_timer{ new QTimer };

	QMetaObject::Connection m_progress_timer_timeout_connection;
	QMetaObject::Connection m_update_timer_timeout_connection;

	Layers::LAttribute* m_color{
		new Layers::LAttribute("Color", "#c0c0c0", this)};
};
QLAYERS_NAMESPACE_END

#endif // QLGROWINGDOTPROGRESSINDICATOR_H
