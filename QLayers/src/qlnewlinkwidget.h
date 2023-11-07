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

#ifndef QLNEWLINKWIDGET
#define QLNEWLINKWIDGET

#include <Layers/lattribute.h>

#include <QLayers/qlayers_global.h>

#include <QLayers/qlattributemapview.h>
#include <QLayers/qlbutton.h>
#include <QLayers/qllineeditor.h>
#include <QLayers/qlresizer.h>
#include <QLayers/qlsplitter.h>
#include <QLayers/qlthemeview.h>
#include <QLayers/qlwidget.h>

QLAYERS_NAMESPACE_BEGIN
class QLNewLinkWidget : public QLWidget
{
	Q_OBJECT

signals:
	void visibility_changed(bool is_visible);

public:
	QLNewLinkWidget(Layers::LAttribute* attr, QWidget* parent = nullptr);

private:
	void init_layout();

	Layers::LAttribute* m_attr;

	Layers::LAttribute* m_selected_link_attr;

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QLSplitter* m_splitter{ new QLSplitter };

	QLThemeView* m_theme_view{ new QLThemeView };

	QLAttributeMapView* m_attr_map_view{ new QLAttributeMapView };

	QLLineEditor* m_path_editor{ new QLLineEditor };

	QLButton* m_apply_link_button{
		new QLButton(
			QLGraphic(":/images/check.svg", QSize(16, 13)), "Apply Link") };

	QLButton* m_cancel_button{
		new QLButton(
			QLGraphic(":/images/tab_exit.svg", QSize(16, 17)), "Cancel") };

	QLResizer* m_resizer{ new QLResizer(QLSizeDimension::Height) };
};
QLAYERS_NAMESPACE_END

#endif // QLNEWLINKWIDGET
