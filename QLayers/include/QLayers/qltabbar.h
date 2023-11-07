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

#ifndef QLTABBAR_H
#define QLTABBAR_H

#include <QHBoxLayout>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qltab.h"
#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLTabBar : public QLWidget
{
	Q_OBJECT

signals:
	void index_changed(int old_index, int new_index);

	void tab_closed(int index);

public:
	QLTabBar(QWidget* parent = nullptr);

	void add_tab(const QLGraphic& icon, const QString& text);

	void add_tab(const QString& text);

	int current_index() const;

	void set_current_index(int index);

	QList<QLTab*> tabs() const;

private:
	void _add_tab(QLTab* tab);

	void init_layout();

	int m_current_index{ -1 };

	QList<QLTab*> m_tabs;

	QHBoxLayout* m_tab_layout{ new QHBoxLayout };
};
QLAYERS_NAMESPACE_END

#endif // QLTABBAR_H
