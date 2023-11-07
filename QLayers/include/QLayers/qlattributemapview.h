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

#ifndef QLATTRIBUTEMAPVIEW_H
#define QLATTRIBUTEMAPVIEW_H

#include <QTreeView>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlscrollbar.h"
#include "qlthemeable.h"
#include "qlattributemapmodel.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLAttributeMapView :
	public QTreeView, public QLThemeable
{
	Q_OBJECT

signals:
	void selected_map_item_changed(Layers::LAttribute* attr);

public:
	QLAttributeMapView(QWidget* parent = nullptr);

	//~QLAttributeMapView();

	virtual QList<QLThemeable*> q_child_themeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	void set_attributes(
		Layers::LAttributeMap attributes, const QStringList& filter_paths);

	virtual void update() override;

protected:
	virtual void selectionChanged(
		const QItemSelection& selected,
		const QItemSelection& deselected) override;

private:
	Layers::LAttribute* m_fill{
		new Layers::LAttribute("Fill", "#ffffff", this) };

	Layers::LAttribute* m_text_color{
		new Layers::LAttribute("Text Color", "#000000", this) };

	QLScrollBar* m_horizontal_scrollbar{ new QLScrollBar };
	QLScrollBar* m_vertical_scrollbar{ new QLScrollBar };

	QLAttributeMapModel* m_model{ new QLAttributeMapModel };

	//QMetaObject::Connection m_model_update_connection;
};
QLAYERS_NAMESPACE_END

#endif // QLATTRIBUTEMAPVIEW_H  
