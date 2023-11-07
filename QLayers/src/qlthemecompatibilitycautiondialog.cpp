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

#include <QLayers/qlthemecompatibilitycautiondialog.h>

#include <QHeaderView>
#include <QSizePolicy>

#include <Layers/ltheme.h>

#include <QLayers/qlapplication.h>
#include <QLayers/qlthemecompatibilityitemdelegate.h>

using Layers::LTheme;

using QLayers::QLThemeCompatibilityCautionDialog;
using QLayers::QLThemeLineageData;

QLThemeCompatibilityCautionDialog::QLThemeCompatibilityCautionDialog(QWidget* parent) :
	QLDialog("Theme Compatibility Caution", parent)
{
	init_attributes();
	init_layout();

	setAttribute(Qt::WA_ShowWithoutActivating);
	setFixedWidth(520);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	setWindowFlags(windowFlags() | Qt::Tool | Qt::WindowStaysOnTopHint);
	set_icon(QLGraphic(":/images/caution.png"));
	set_object_name("Theme Compatibility Caution Dialog");

	m_message_label->set_font_size(14);
	m_message_label->set_object_name("Message Label");
	m_message_label->setText(
		qLayersApp->name() + " has not been implemented in this theme. An "
		"implementation will be inherited from the last compatible ancestor "
		"theme.");
	m_message_label->setWordWrap(true);

	m_table_label->set_font_size(14);
	m_table_label->set_object_name("Table Label");
	m_table_label->setText("Lineage");

	init_lineage_table();
}

void QLThemeCompatibilityCautionDialog::set_lineage_table_data(
	const QStringList& lineage_list)
{
	QList<QLThemeLineageData> lineage_table_data;

	for (const QString& theme_id : lineage_list)
	{
		QLThemeLineageData lineage_data;

		if (theme_id.contains("_"))
		{
			lineage_data.name = theme_id.left(theme_id.lastIndexOf("_"));
			lineage_data.uuid =
				theme_id.right(theme_id.size() - 1 - theme_id.lastIndexOf("_"));
		}
		else
			lineage_data.name = theme_id;

		if (LTheme* theme = qLayersApp->theme(theme_id))
			lineage_data.has_app_implementation_available =
				theme->has_implementation(qLayersApp->app_display_id().toStdString().c_str());

		lineage_table_data.append(lineage_data);
	}

	m_theme_lineage_model.clear();

	for (const QLThemeLineageData& lineage_data : lineage_table_data)
		m_theme_lineage_model.append(lineage_data);

	m_lineage_table->verticalHeader()->resizeSection(
		m_lineage_table->verticalHeader()->count() - 1, 40);

	m_lineage_table->update_height();
}

void QLThemeCompatibilityCautionDialog::set_theme_name(const QString& theme_name)
{
	m_table_label->setText(theme_name + "'s Lineage");
}

void QLThemeCompatibilityCautionDialog::init_attributes()
{
	m_border_thickness->set_value(3.0);

	m_corner_radii_top_left->set_value(10.0);
	m_corner_radii_top_right->set_value(10.0);
	m_corner_radii_bottom_left->set_value(10.0);
	m_corner_radii_bottom_right->set_value(10.0);
}

void QLThemeCompatibilityCautionDialog::init_layout()
{
	QVBoxLayout* layout = new QVBoxLayout;

	layout->addWidget(m_message_label);
	layout->addSpacing(15);
	layout->addWidget(m_table_label);
	layout->addWidget(m_lineage_table);
	layout->setAlignment(m_table_label, Qt::AlignHCenter);
	layout->setContentsMargins(12, 12, 12, 12);
	layout->setSpacing(5);

	setLayout(layout);
}

void QLThemeCompatibilityCautionDialog::init_lineage_table()
{
	QLThemeCompatibilityItemDelegate* item_delegate =
		new QLThemeCompatibilityItemDelegate;

	m_lineage_table->setItemDelegate(item_delegate);

	m_lineage_table->set_object_name("Theme Lineage Table");
	m_lineage_table->setModel(&m_theme_lineage_model);

	// Set 'Theme' column to fized size:
	m_lineage_table->horizontalHeader()->resizeSection(0, 370);
}
