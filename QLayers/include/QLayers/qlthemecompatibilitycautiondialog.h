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

#ifndef QLTHEMECOMPATIBILITYCAUTIONDIALOG_H
#define QLTHEMECOMPATIBILITYCAUTIONDIALOG_H

#include <QTableView>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qldialog.h"
#include "qltableview.h"
#include "qlthemelineagemodel.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLThemeCompatibilityCautionDialog : public QLDialog
{
	Q_OBJECT

public:
	QLThemeCompatibilityCautionDialog(QWidget* parent = nullptr);

	void set_lineage_table_data(const QStringList& lineage_list);

	void set_theme_name(const QString& theme_name);

private:
	void init_attributes();

	void init_layout();

	void init_lineage_table();

	QLLabel* m_message_label{ new QLLabel };
	QLLabel* m_table_label{ new QLLabel };

	QLTableView* m_lineage_table{ new QLTableView };

	QLThemeLineageModel m_theme_lineage_model;
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMECOMPATIBILITYCAUTIONDIALOG_H  
