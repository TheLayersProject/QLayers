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

#ifndef QLGRADIENTEDITOR
#define QLGRADIENTEDITOR

#include <Layers/lstring.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlbutton.h"
#include "qlcolorcontrol.h"
#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLGradientEditorItem;

class QLAYERS_EXPORT QLGradientEditor : public QLWidget
{
	Q_OBJECT

public:
	QLGradientEditor(std::vector<Layers::LString> stops, QWidget* parent = nullptr);

	~QLGradientEditor();

	std::vector<Layers::LString> stops() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	QLGradientEditorItem* create_item(const Layers::LString& stop);

	void init_attributes(const std::vector<Layers::LString>& stops);
	void init_items(const std::vector<Layers::LString>& stops);
	void init_add_stop_buttons();

	void update_gradient();
	void update_indexes();
	void update_positions();

	QList<QLGradientEditorItem*> m_items;
	QList<QLButton*> m_add_stop_buttons;

	QLGradientEditorItem* m_drag_item{ nullptr };
	QLGradientEditorItem* m_replace_item{ nullptr };

	int m_drag_ctrl_initial_x{ 0 };
	QPoint m_click_pos;
};
QLAYERS_NAMESPACE_END

#endif // QLGRADIENTEDITOR
