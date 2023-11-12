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

#ifndef QLATTRIBUTEEDITOR_H
#define QLATTRIBUTEEDITOR_H

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlbutton.h"
#include "qlfillcontrol.h"
#include "qlgraphic.h"
#include "qllabel.h"
#include "qllineeditor.h"
#include "qlminislider.h"
#include "qltabbar.h"
#include "qlthemeable.h"
#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLLinksView;
class QLNewLinkWidget;

class QLAYERS_EXPORT QLAttributeEditor : public QLWidget
{
	Q_OBJECT

public:
	QLAttributeEditor(Layers::LAttribute* attr, QWidget* parent = nullptr);

	~QLAttributeEditor();

	virtual QList<QLThemeable*> child_qlthemeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	QLFillControl* fill_control() const;

	QLLineEditor* line_editor() const;

	QLMiniSlider* slider() const;

private:
	void init_attributes();
	void init_layout();

	void update_icon_labels();

	Layers::LAttribute* m_attr;

	QHBoxLayout* m_controls_layout{ new QHBoxLayout };
	QHBoxLayout* m_icons_layout{ new QHBoxLayout };
	QHBoxLayout* m_links_buttons_layout{ new QHBoxLayout };
	QVBoxLayout* m_links_layout{ new QVBoxLayout };
	QVBoxLayout* m_overrides_layout{ new QVBoxLayout };

	QLFillControl* m_fill_control{ new QLFillControl };

	QLLabel* m_label{ new QLLabel };

	QLMiniSlider* m_slider{ new QLMiniSlider };

	QLLineEditor* m_line_editor{ new QLLineEditor };

	QLLabel* m_link_icon_label =
		new QLLabel(QLGraphic(":/images/chain_link.svg", QSize(8, 18)));

	QLLabel* m_overrides_icon_label =
		new QLLabel(QLGraphic(":/images/overrides_icon.svg", QSize(10, 18)));

	QLButton* m_collapse_button{
		new QLButton(
			QLGraphic(":/images/collapse_arrow_right.svg", QSize(8, 12)),
			QLGraphic(":/images/collapse_arrow_down.svg", QSize(12, 8))) };

	QLWidget* m_icons_widget{ new QLWidget };

	QLTabBar* m_features_tab_bar{ new QLTabBar };

	QWidget* m_features_widget{ new QWidget };

	QLLinksView* m_links_view;

	QLNewLinkWidget* m_new_link_widget{ nullptr };

	Layers::LConnectionID m_attr_link_changed_connection;
	QMetaObject::Connection m_new_link_widget_destroyed_connection;

	QLWidget* m_links_widget{ new QLWidget };

	QLWidget* m_overrides_widget{ new QLWidget };

	QLButton* m_new_link_button{
		new QLButton(
			QLGraphic(":/images/new_theme.svg", QSize(18, 18)), "New Link") };

	QLButton* m_break_link_button{
		new QLButton(
			QLGraphic(":/images/tab_exit.svg", QSize(16, 17)), "Break Link") };

	QLStatePool* m_status_states{
		new QLStatePool("Status", { "Active", "Inactive" }) };
};
QLAYERS_NAMESPACE_END

#endif // QLATTRIBUTEEDITOR_H
