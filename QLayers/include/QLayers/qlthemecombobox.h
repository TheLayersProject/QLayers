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

#ifndef QLTHEMECOMBOBOX_H
#define QLTHEMECOMBOBOX_H

#include <Layers/ltheme.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlcombobox.h"
#include "qlthemecompatibilitycautiondialog.h"

QLAYERS_NAMESPACE_BEGIN
class QLThemeComboBoxItemModel;

class QLAYERS_EXPORT QLThemeComboBox : public QLComboBox
{
	Q_OBJECT

public:
	QLThemeComboBox(QWidget* parent = nullptr);

	void add_theme(Layers::LTheme* theme, bool set_as_current_index = false);

	void clear();

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

	virtual void paintEvent(QPaintEvent* event) override;

private:
	void init_item_delegate();

	QLThemeComboBoxItemModel* m_model;

	QLThemeCompatibilityCautionDialog* m_compatibility_dialog{
		new QLThemeCompatibilityCautionDialog };

	int m_highlighted_index = -1;
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMECOMBOBOX_H
