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

#include <QLayers/qlthemeeditordialog.h>

#include <Layers/lalgorithms.h>
#include <Layers/lstring.h>

#include <QLayers/qlapplication.h>

using Layers::LString;
using Layers::LThemeItem;

using QLayers::QLThemeable;
using QLayers::QLThemeEditorDialog;

QLThemeEditorDialog::QLThemeEditorDialog(QWidget* parent) :
	QLDialog("Theme Editor", parent)
{
	init_layout();
	m_attr_editors_widget->installEventFilter(this);
	resize(800, 600);
	set_icon(QLGraphic(":/images/customize_theme.svg", QSize(24, 24)));
	set_object_name("Theme Editor Dialog");;

	m_path_label->set_object_name("Path Label");
	m_path_label->setFixedHeight(40);

	//m_theme_view->set_object_name("Theme View");
	m_theme_view->setFixedWidth(298);

	connect(m_theme_view, &QLThemeView::selected_theme_item_changed,
		[this](LThemeItem* theme_item)
		{
			edit_theme_item(theme_item);
		});

	//connect(m_theme_view, SIGNAL(selected_theme_item_changed(LThemeItem*)),
	//	this, SLOT(edit_theme_item(LThemeItem*)));

	m_divider->set_object_name("Divider");
	m_divider->setFixedWidth(4);

	m_attr_editors_widget->setSizePolicy(
		QSizePolicy::Minimum, QSizePolicy::Minimum);

	m_attr_editors_scroll_area->set_object_name("Attribute Editors Scroll Area");
	m_attr_editors_scroll_area->setHorizontalScrollBarPolicy(
		Qt::ScrollBarAlwaysOff);
	m_attr_editors_scroll_area->setWidget(m_attr_editors_widget);

	connect(m_save_progress_indicator, &QLGrowingDotProgressIndicator::timeout,
		[this]
	{
		activeTheme()->save();

		m_save_progress_indicator->hide();

		m_check_label->show();
		m_status_label->show();
	});

	m_status_bar->setFixedHeight(40);
	m_status_bar->set_object_name("Status Bar");

	m_check_label->set_object_name("Check Label");
	m_check_label->hide();

	m_status_label->set_object_name("Status Label");
	m_status_label->hide();

	m_save_progress_indicator->set_object_name("Save Progress Indicator");
	m_save_progress_indicator->hide();
}

void QLThemeEditorDialog::apply_theme_item(LThemeItem* theme_item)
{
	clear_attr_editors();
	m_check_label->hide();
	m_status_label->hide();
	m_path_text = "";
	update_path_label();

	LThemeable::apply_theme_item(theme_item);
}

bool QLThemeEditorDialog::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Resize)
	{
		update_attr_editors_max_width();
		return true;
	}

	return QLDialog::eventFilter(object, event);
}

void QLThemeEditorDialog::edit_theme_item(LThemeItem* theme_item)
{
	clear_attr_editors();

	QMap<QString, QWidget*> organized_widgets;
	QMap<QString, QLAttributeEditorGroup*> attr_editor_groups;

	for (auto group_name : theme_item->attribute_group_names())
	{
		QString q_group_name = QString::fromStdString(group_name.c_str());

		QLAttributeEditorGroup* attr_editor_group =
			new QLAttributeEditorGroup(q_group_name);
		attr_editor_group->set_object_name("Attribute Editor Groups");

		if (current_theme_item())
			attr_editor_group->apply_theme_item(
				current_theme_item()->find_item(
					attr_editor_group->objectName().toStdString().c_str()));

		attr_editor_groups[q_group_name] = attr_editor_group;
		organized_widgets[q_group_name] = attr_editor_group;
	}

	for (const auto& [key, attr] : theme_item->attributes())
	{
		QLAttributeEditor* attr_editor = new QLAttributeEditor(attr);
		attr_editor->set_object_name("Attribute Editors");

		if (current_theme_item())
			attr_editor->apply_theme_item(
				current_theme_item()->find_item(
					attr_editor->objectName().toStdString().c_str()));

		attr_editor->fill_control()->fill()->on_change(
			[this] {
				reset_save_timer();
			});

		attr_editor->slider()->value()->on_change(
			[this] {
				reset_save_timer();
			});

		LString attr_name = attr->object_name();

		if (std::find(attr_name.begin(), attr_name.end(),
			'.') != attr_name.end())
		{
			auto group_name = Layers::split<std::vector<LString>>(
				attr_name, '.').front();

			attr_editor_groups[QString::fromStdString(group_name.c_str())]->
				add_attribute_editor(attr_editor);
		}
		else
			organized_widgets[QString::fromStdString(attr_name.c_str())] = attr_editor;
	}

	for (QWidget* widget : organized_widgets)
	{
		widget->setMaximumWidth(m_attr_editors_scroll_area->width());

		m_attr_editors_layout->insertWidget(
			m_attr_editors_layout->count() - 1, widget);
	}

	update_attr_editors_max_width();

	m_path_text = QString::fromStdString(theme_item->path().c_str());
	update_path_label();
}

void QLThemeEditorDialog::reset_save_timer()
{
	m_check_label->hide();
	m_status_label->hide();

	m_save_progress_indicator->show();

	m_save_progress_indicator->start(3000);
}

void QLThemeEditorDialog::init_layout()
{
	QHBoxLayout* path_label_layout = new QHBoxLayout;
	path_label_layout->addWidget(m_path_label);
	path_label_layout->setSpacing(0);
	path_label_layout->setContentsMargins(8, 0, 8, 0);

	QVBoxLayout* right_vbox = new QVBoxLayout;
	right_vbox->addLayout(path_label_layout);
	right_vbox->addWidget(m_attr_editors_scroll_area);

	m_attr_editors_layout->addStretch();
	m_attr_editors_widget->setLayout(m_attr_editors_layout);

	m_hbox_layout->addWidget(m_theme_view);
	m_hbox_layout->addWidget(m_divider);
	m_hbox_layout->addLayout(right_vbox);
	m_hbox_layout->setContentsMargins(0, 0, 0, 0);
	m_hbox_layout->setSpacing(0);

	m_status_bar_layout->addWidget(m_save_progress_indicator);
	m_status_bar_layout->addWidget(m_check_label);
	m_status_bar_layout->addWidget(m_status_label);
	m_status_bar_layout->addStretch();
	m_status_bar_layout->setContentsMargins(8, 0, 8, 0);
	m_status_bar_layout->setSpacing(8);
	m_status_bar->setLayout(m_status_bar_layout);

	m_main_layout->addLayout(m_hbox_layout);
	m_main_layout->addWidget(m_status_bar);
	m_main_layout->setContentsMargins(0, 0, 0, 0);
	m_main_layout->setSpacing(0);

	setLayout(m_main_layout);
	m_main_layout->activate();
}

void QLThemeEditorDialog::clear_attr_editors()
{
	for (QObject* child_object : m_attr_editors_widget->children())
		if (QWidget* child_widget = dynamic_cast<QWidget*>(child_object))
			child_widget->deleteLater();
}

void QLThemeEditorDialog::update_attr_editors_max_width()
{
	QMargins margins = m_attr_editors_layout->contentsMargins();

	int scroll_bar_width =
		(m_attr_editors_scroll_area->height() < m_attr_editors_widget->height()) ?
		m_attr_editors_scroll_area->verticalScrollBar()->width() : 0;

	for (QObject* child_object : m_attr_editors_widget->children())
		if (QWidget* child_widget = dynamic_cast<QWidget*>(child_object))
			child_widget->setMaximumWidth(
				m_attr_editors_scroll_area->width() -
				(margins.left() + margins.right() + scroll_bar_width)
			);
}

void QLThemeEditorDialog::update_path_label()
{
	QFontMetrics font_metrics = QFontMetrics(m_path_label->font());

	m_path_label->setText(
		font_metrics.elidedText(
			m_path_text, Qt::ElideLeft, m_path_label->width()));
}
