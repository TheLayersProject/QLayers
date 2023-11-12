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

#ifndef QLTHEMEVIEW_H
#define QLTHEMEVIEW_H

#include <QTreeView>

#include <Layers/lattribute.h>
#include <Layers/lthemeitem.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlscrollbar.h"
#include "qlthemeable.h"
#include "qlthememodel.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLThemeView : public QTreeView, public QLThemeable
{
	Q_OBJECT

signals:
	void selected_theme_item_changed(Layers::LThemeItem* theme_item);

public:
	QLThemeView(QWidget* parent = nullptr);

	~QLThemeView();

	virtual QList<QLThemeable*> child_qlthemeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	virtual void update() override;

protected:
	virtual void selectionChanged(
		const QItemSelection& selected,
		const QItemSelection& deselected) override;

private:
	Layers::LAttribute* m_fill
		{ new Layers::LAttribute("Fill", "#ffffff", this) };

	Layers::LAttribute* m_text_color
		{ new Layers::LAttribute("Text Color", "#000000", this) };

	QLScrollBar* m_horizontal_scrollbar{ new QLScrollBar };
	QLScrollBar* m_vertical_scrollbar{ new QLScrollBar };

	QLThemeModel* m_model{ new QLThemeModel };

	QMetaObject::Connection m_model_update_connection;
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMEVIEW_H  
