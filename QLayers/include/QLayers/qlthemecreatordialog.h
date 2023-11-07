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

#ifndef QLCREATETHEMEDIALOG_H
#define QLCREATETHEMEDIALOG_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qldialog.h"
#include "qllineeditor.h"
#include "Qlthemecombobox.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT LThemeCreatorDialog : public QLDialog
{
	Q_OBJECT

public:
	LThemeCreatorDialog(QWidget* parent = nullptr);

public slots:
	virtual int	exec() override;

private slots:
	void create_theme();

private:
	void copy_directory(const QDir& copy_dir, const QDir& new_dir,
		const QList<QString>& filter_names);

	void init_attributes();
	void init_layout();

	QLLabel* m_name_label{ new QLLabel("Name") };

	QLLineEditor* m_name_editor{ new QLLineEditor };

	QLLabel* m_parent_theme_label{ new QLLabel("Parent Theme") };

	QLThemeComboBox* m_parent_theme_combobox{ new QLThemeComboBox };

	QLButton* m_create_button{
		new QLButton(QLGraphic(":/images/check.svg", QSize(16, 13)), "Create") };
};
QLAYERS_NAMESPACE_END

#endif // QLCREATETHEMEDIALOG_H
