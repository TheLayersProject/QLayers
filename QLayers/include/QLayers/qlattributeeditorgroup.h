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

#ifndef QLATTRIBUTEEDITORGROUP_H
#define QLATTRIBUTEEDITORGROUP_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlattributeeditor.h"
#include "qlbutton.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLAttributeEditorGroup : public QLWidget
{
	Q_OBJECT

public:
	QLAttributeEditorGroup(const QString& name, QWidget* parent = nullptr);

	void add_attribute_editor(QLAttributeEditor* attribute_editor);

private:
	void init_layout();

	void set_collapsed(bool collapsed = true);

	QLButton* m_collapse_button{
		new QLButton(
			QLGraphic(":/images/collapse_arrow_right.svg", QSize(8, 12)),
			QLGraphic(":/images/collapse_arrow_down.svg", QSize(12, 8))) };

	bool m_collapsed{ true };

	QLLabel* m_label{ new QLLabel };

	QList<QLAttributeEditor*> m_attribute_editors;

	QVBoxLayout* m_widgets_vbox{ new QVBoxLayout };
};
QLAYERS_NAMESPACE_END

#endif // QLATTRIBUTEEDITORGROUP_H
