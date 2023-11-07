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

#include <QLayers/qlthemecombobox.h>

#include <QAbstractItemView>
#include <QEvent>
#include <QMouseEvent>

#include <Layers/lstring.h>

#include <QLayers/qlapplication.h>
#include <QLayers/qlthemecomboboxitemdelegate.h>
#include <QLayers/qlthemecomboboxitemmodel.h>

using Layers::LString;
using Layers::LTheme;

using QLayers::QLThemeComboBox;

QLThemeComboBox::QLThemeComboBox(QWidget* parent) :
	m_model{ new QLThemeComboBoxItemModel }, QLComboBox(parent)
{
	init_item_delegate();
	setFixedSize(250, 60);
	setModel(m_model);

	m_compatibility_dialog->apply_theme_item(
		activeTheme()->find_item(m_compatibility_dialog->path()));

	connect(this, &QComboBox::highlighted, [this](int index)
	{
		m_highlighted_index = index;

		LTheme* theme = itemData(index).value<LTheme*>();

		if (!theme->has_implementation(qLayersApp->app_display_id().toStdString().c_str()))
		{
			QStringList lineage_str_list;

			for (const LString& lineage_id : theme->lineage())
				lineage_str_list.append(QString::fromStdString(lineage_id.c_str()));

			m_compatibility_dialog->set_lineage_table_data(lineage_str_list);
			m_compatibility_dialog->set_theme_name(
				QString::fromStdString(theme->name().c_str()));

			if (!m_compatibility_dialog->isVisible())
			{
				m_compatibility_dialog->show();
				m_compatibility_dialog->raise();
			}
		}
		else
		{
			m_compatibility_dialog->hide();
		}
	});
}

void QLThemeComboBox::clear()
{
	m_model->clear();
}

void QLThemeComboBox::add_theme(LTheme* theme, bool set_as_current_index)
{
	m_model->append(theme);

	if (set_as_current_index)
	{
		for (int i = 0; i < count(); i++)
			if (itemData(i).value<LTheme*>()->display_id() == theme->display_id())
			{
				setCurrentIndex(i);
				break;
			}
	}
}

bool QLThemeComboBox::eventFilter(QObject* object, QEvent* event)
{
	QLComboBox::eventFilter(object, event);

	if (object == view()->window())
		if (event->type() == QEvent::Leave && m_compatibility_dialog)
			m_compatibility_dialog->hide();

	return false;
}

void QLThemeComboBox::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	LTheme* current_theme = currentData().value<LTheme*>();

	paint_box(&painter);

	QFont item_font = font();
	QFont secondary_font(item_font.family(), 8);

	const QFontMetrics& item_font_metrics = QFontMetrics(item_font);
	const QFontMetrics& secondary_font_metrics = QFontMetrics(secondary_font);

	QPainterPath item_text_path;
	QPainterPath secondary_text_path;

	QString item_text = QString::fromStdString(current_theme->name().c_str());
	QString secondary_text;

	if (!current_theme->publisher().empty())
	{
		secondary_text = QString::fromStdString(
			current_theme->publisher().c_str());
	}
	else if (!current_theme->uuid().empty())
	{
		secondary_text = QString::fromStdString(
			current_theme->uuid().c_str());
	}

	if (!secondary_text.isEmpty())
	{
		// Draw item text and uuid text

		item_text_path.addText(
			QPoint(10, rect().center().y() + (item_font_metrics.height() / 2) - 12),
			item_font,
			item_text
		);

		secondary_text_path.addText(
			QPoint(10, rect().center().y() + (secondary_font_metrics.height() / 2) + 8),
			secondary_font,
			secondary_text
		);
	}
	else
	{
		// Draw item text only

		item_text_path.addText(
			QPoint(10, rect().center().y() + (item_font_metrics.height() / 2) - 2),
			item_font,
			item_text
		);
	}

	QColor text_color =
		QColor(QString::fromStdString(m_text_color->as<LString>().c_str()));

	painter.fillPath(item_text_path, text_color);
	painter.fillPath(secondary_text_path, text_color);
}

void QLThemeComboBox::init_item_delegate()
{
	QLThemeComboBoxItemDelegate* item_delegate = new QLThemeComboBoxItemDelegate;

	connect(item_delegate, &QLThemeComboBoxItemDelegate::mouse_moved,
		[this](QPoint mouse_cursor)
	{
		if (m_highlighted_index > -1)
		{
			LTheme* theme = itemData(m_highlighted_index).value<LTheme*>();

			if (!theme->has_implementation(
				qLayersApp->app_display_id().toStdString().c_str()))
			{
				if (!m_compatibility_dialog->isVisible())
				{
					m_compatibility_dialog->show();
					m_compatibility_dialog->raise();
				}
			}	
		}

		m_compatibility_dialog->move(QCursor::pos() + QPoint(20, 20));
	});

	setItemDelegate(item_delegate);
}
