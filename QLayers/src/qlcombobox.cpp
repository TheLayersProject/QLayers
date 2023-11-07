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

#include <QLayers/qlcombobox.h>

#include <QEvent>
#include <QListView>
#include <QPainter>

#include <Layers/lalgorithms.h>
#include <Layers/lstring.h>

#include <QLayers/qlcalculate.h>
#include <QLayers/qlcomboboxitemdelegate.h>
#include <QLayers/qlconvert.h>
#include <QLayers/qlthemeablebox.h>

using Layers::LAttribute;
using Layers::LString;

using QLayers::QLComboBox;
using QLayers::QLThemeable;

QLComboBox::QLComboBox(QWidget* parent) : QComboBox(parent)
{
	setItemDelegate(new QLComboBoxItemDelegate);

	view()->window()->installEventFilter(this);
	view()->window()->setAttribute(Qt::WA_TranslucentBackground);
	view()->window()->setWindowFlags(
		Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	view()->setMouseTracking(true);

	update();
}

LAttribute* QLComboBox::border_fill() const
{
	return m_border_fill;
}

LAttribute* QLComboBox::border_thickness() const
{
	return m_border_thickness;
}

QList<QLThemeable*> QLComboBox::q_child_themeables(Qt::FindChildOptions options)
{
	QList<QLThemeable*> q_child_themeables =
		QLThemeable::q_child_themeables(options);

	if (QLThemeable* themeable_item_delegate =
		dynamic_cast<QLThemeable*>(itemDelegate()))
	{
		q_child_themeables.append(themeable_item_delegate);

		if (options == Qt::FindChildrenRecursively)
		{
			QList<QObject*> delegate_child_objects =
				itemDelegate()->findChildren<QObject*>(options);

			for (QObject* delegate_child_object : delegate_child_objects)
				if (QLThemeable* child_themeable =
					dynamic_cast<QLThemeable*>(delegate_child_object))
				{
					q_child_themeables.append(child_themeable);
				}
		}
	}

	return q_child_themeables;
}

LAttribute* QLComboBox::corner_radius() const
{
	return m_corner_radius;
}

LAttribute* QLComboBox::fill() const
{
	return m_fill;
}

bool QLComboBox::is_view_positioned_above() const
{
	return view()->window()->y() <= mapToGlobal(this->rect().topLeft()).y();
}

void QLComboBox::setFixedHeight(int h)
{
	QComboBox::setFixedHeight(h);

	update();
}

void QLComboBox::setFixedSize(int w, int h)
{
	QLComboBox::setFixedSize(QSize(w, h));
}

void QLComboBox::setFixedSize(const QSize& s)
{
	QComboBox::setFixedSize(s);

	update();
}

void QLComboBox::setFixedWidth(int w)
{
	QComboBox::setFixedWidth(w);

	update();
}

void QLComboBox::showPopup()
{
	QComboBox::showPopup();

	if (QLComboBoxItemDelegate* combobox_delegate =
		dynamic_cast<QLComboBoxItemDelegate*>(itemDelegate()))
	{
		combobox_delegate->set_is_above_control(is_view_positioned_above());
	}
}

LAttribute* QLComboBox::text_color() const
{
	return m_text_color;
}

void QLComboBox::update()
{
	QString style_sheet =
		"QComboBox::drop-down { "
		"width: 0px; "
		"}";

	setStyleSheet(style_sheet);

	view()->setStyleSheet(
		"QAbstractItemView {"
		"background: transparent;"
		"border: none;"
		"}"

		"QAbstractItemView::item {"
		"height: " + QString::number(height()) + "px;"
		"}"
	);

	QWidget::update();
}

bool QLComboBox::eventFilter(QObject* object, QEvent* event)
{
	if (object == view()->window())
		if (event->type() == QEvent::Show || event->type() == QEvent::Hide)
			update();

	return false;
}

void QLComboBox::paint_box(QPainter* painter)
{
	if (!painter)
		return;

	auto s = state_combo();

	int border_thickness = m_border_thickness->as<double>(s);

	LCornerRadii border_cr;
	LCornerRadii fill_cr;

	border_cr.top_left = m_corner_radius->as<double>(s);
	border_cr.top_right = border_cr.top_left;
	border_cr.bottom_left = border_cr.top_left;
	border_cr.bottom_right = border_cr.top_left;

	if (view()->window()->isVisible())
		if (is_view_positioned_above())
		{
			border_cr.top_left = 0;
			border_cr.top_right = 0;
		}
		else
		{
			border_cr.bottom_left = 0;
			border_cr.bottom_right = 0;
		}

	fill_cr.top_left = (border_thickness) ?
		inner_radius(border_cr.top_left, border_thickness) :
		border_cr.top_left;

	fill_cr.top_right = (border_thickness) ?
		inner_radius(border_cr.top_right, border_thickness) :
		border_cr.top_right;

	fill_cr.bottom_left = (border_thickness) ?
		inner_radius(border_cr.bottom_left, border_thickness) :
		border_cr.bottom_left;

	fill_cr.bottom_right = (border_thickness) ?
		inner_radius(border_cr.bottom_right, border_thickness) :
		border_cr.bottom_right;

	QRect border_rect = QRect(
		QPoint(0, 0),
		size() + lsize(1));

	QRect fill_rect = QRect(
		lpoint(border_thickness),
		size() + lsize(1) - lsize(border_thickness * 2));

	QPainterPath fill_path =
		QLThemeableBox::box_path(fill_rect, fill_cr);
	QPainterPath border_path =
		QLThemeableBox::box_path(border_rect, border_cr) - fill_path;

	/* Draw Border */
	if (border_thickness)
	{
		if (auto stops = m_border_fill->as_if<std::vector<LString>>(s))
		{
			QLinearGradient border_fill_grad;

			border_fill_grad.setStart(border_rect.left(), 0);
			border_fill_grad.setFinalStop(border_rect.right() + 1, 0);
			border_fill_grad.setStops(to_QGradientStops(*stops));

			painter->fillPath(border_path, border_fill_grad);
		}
		else
			painter->fillPath(border_path,
				QColor(QString::fromStdString(
						m_border_fill->as<LString>(s).c_str())));
	}

	/* Draw Fill */
	if (auto stops = m_fill->as_if<std::vector<LString>>(s))
	{
		QLinearGradient fill_gradient;

		fill_gradient.setStart(fill_rect.left(), 0);
		fill_gradient.setFinalStop(fill_rect.right() + 1, 0);
		fill_gradient.setStops(to_QGradientStops(*stops));

		painter->fillPath(fill_path, fill_gradient);
	}
	else
		painter->fillPath(fill_path,
			QColor(QString::fromStdString(m_fill->as<LString>(s).c_str())));
}

void QLComboBox::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	paint_box(&painter);

	QFont item_font = font();

	const QFontMetrics& item_font_metrics = QFontMetrics(item_font);

	QPainterPath item_text_path;

	QString item_text = currentData(Qt::DisplayRole).toString();

	item_text_path.addText(
		QPoint(10, rect().center().y() + (item_font_metrics.height() / 2) - 2),
		item_font,
		item_text
	);

	painter.fillPath(item_text_path,
		QColor(QString::fromStdString(m_text_color->as<LString>().c_str())));
}
