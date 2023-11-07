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

#ifndef QLTHEMECOMBOBOXITEMDELEGATE_H
#define QLTHEMECOMBOBOXITEMDELEGATE_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlcomboboxitemdelegate.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLThemeComboBoxItemDelegate : public QLComboBoxItemDelegate
{
	Q_OBJECT

signals:
	void mouse_moved(QPoint cursor_pos);

public:
	virtual bool editorEvent(QEvent* event,
		QAbstractItemModel* model,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) override;

	virtual void paint(QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

private:
	QImage m_caution_image{ QImage(":/images/caution.png") };
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMECOMBOBOXITEMDELEGATE_H
