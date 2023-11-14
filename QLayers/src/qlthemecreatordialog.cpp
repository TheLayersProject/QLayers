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

#include <QLayers/qlthemecreatordialog.h>

#include <Layers/lstring.h>
#include <Layers/ltheme.h>

#include <QLayers/qlapplication.h>
#include <QLayers/qlsystem.h>

using Layers::LString;
using Layers::LTheme;

using QLayers::QLThemeCreatorDialog;
//using QLayers::QLThemeable;

QLThemeCreatorDialog::QLThemeCreatorDialog(QWidget* parent) :
	QLDialog("Create Theme", parent)
{
	init_attributes();
	init_layout();

	set_icon(QLGraphic(":/images/new_theme.svg", QSize(20, 20)));
	set_object_name("Theme Creator Dialog");
	setFixedSize(290, 300);
	setModal(true);

	m_name_label->set_object_name("Name Label");
	m_name_label->set_font_size(15);

	m_name_editor->set_object_name("Name Editor");
	m_name_editor->setFixedSize(250, 50);
	m_name_editor->set_margin(0);
	m_name_editor->set_font_size(15);
	connect(m_name_editor, &QLLineEditor::text_edited,
		[this] 
		{
			bool has_char_other_than_space = false;

			QString text = QString::fromStdString(
				m_name_editor->text()->as<LString>().c_str());

			for (const QChar& character : text)
			{
				if (character != ' ')
					has_char_other_than_space = true;
			}

			if (!has_char_other_than_space)
			{
				m_create_button->set_disabled();
				return;
			}

			if (text == "")
			{
				m_create_button->set_disabled();
				return;
			}

			if (m_create_button->disabled())
				m_create_button->set_disabled(false);
		});

	m_parent_theme_label->set_object_name("Parent Theme Label");
	m_parent_theme_label->set_font_size(15);

	m_parent_theme_combobox->set_object_name("Parent Theme Combobox");

	for (LTheme* theme : qLayersApp->themes())
		if (theme->has_implementation(qLayersApp->app_display_id().toStdString().c_str()))
		{
			if (theme == activeTheme())
				m_parent_theme_combobox->add_theme(theme, true);
			else
				m_parent_theme_combobox->add_theme(theme);
		}

	m_create_button->set_object_name("Create Button");
	m_create_button->set_disabled();
	m_create_button->set_font_size_f(10.5);
	m_create_button->set_padding(6);
	m_create_button->setFixedHeight(30);
	connect(m_create_button, &QLButton::clicked,
		this, &QLThemeCreatorDialog::create_theme);

	apply_theme_item(activeTheme()->find_item(path()));
}

int QLThemeCreatorDialog::exec()
{
	m_name_editor->setFocus();

	return QDialog::exec();
}

void QLThemeCreatorDialog::create_theme()
{
	LTheme* copy_theme =
		m_parent_theme_combobox->currentData().value<LTheme*>();
	LTheme* new_theme =
		new LTheme(m_name_editor->text()->as<LString>());

	new_theme->set_publisher(get_current_username().c_str());

	std::filesystem::path new_theme_dir =
		latest_T_version_path() / new_theme->display_id().c_str();
	std::filesystem::path copy_theme_dir = copy_theme->directory();

	new_theme->set_dir(new_theme_dir);

	copy_directory(copy_theme_dir, new_theme_dir, {".theme", "meta.json"});

	for (const LString& theme_id : copy_theme->lineage())
		new_theme->append_to_lineage(theme_id);

	new_theme->append_to_lineage(copy_theme->display_id());
	new_theme->save_meta_file();

	qLayersApp->add_theme(new_theme);
	qLayersApp->apply_theme(new_theme);

	done(QDialog::Accepted);
}

void QLThemeCreatorDialog::copy_directory(
	const QDir& copy_dir, const QDir& new_dir,
	const QList<QString>& filter_names)
{
	if (!new_dir.exists())
		new_dir.mkdir(".");

	for (const QString& file_name : copy_dir.entryList(QDir::Files))
		if (!filter_names.contains(file_name))
		{
			QFile::copy(
				copy_dir.filePath(file_name),
				new_dir.filePath(file_name));

			QFile::setPermissions(
				new_dir.filePath(file_name),
				QFileDevice::WriteUser);
		}

	for (const QString& dir_name :
		copy_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		if (!filter_names.contains(dir_name))
		{
			copy_directory(
				copy_dir.filePath(dir_name), new_dir.filePath(dir_name),
				filter_names);
		}
	}
}

void QLThemeCreatorDialog::init_attributes()
{
	m_name_editor->border_thickness()->set_value(3.0);
	m_name_editor->corner_radii_top_left()->set_value(5.0);
	m_name_editor->corner_radii_top_right()->set_value(5.0);
	m_name_editor->corner_radii_bottom_left()->set_value(5.0);
	m_name_editor->corner_radii_bottom_right()->set_value(5.0);
	m_name_editor->left_padding()->set_value(10.0);
}

void QLThemeCreatorDialog::init_layout()
{
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(m_name_label);
	layout->addWidget(m_name_editor);
	layout->addSpacing(20);
	layout->addWidget(m_parent_theme_label);
	layout->addWidget(m_parent_theme_combobox);
	layout->addStretch();
	layout->addWidget(m_create_button);
	layout->setAlignment(m_create_button, Qt::AlignRight);
	layout->setContentsMargins(15, 20, 7, 7);
	setLayout(layout);
}
