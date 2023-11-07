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

#include <QLayers/qldialog.h>

#include <Windows.h>
#include <windowsx.h>

#include <QApplication>
#include <QMouseEvent>
#include <QPainterPath>

#include <Layers/lstring.h>

#include <QLayers/qlcalculate.h>

using Layers::LString;

using QLayers::QLDialog;

QLDialog::QLDialog(const QString& title, QWidget* parent) :
	m_title_label{ new QLLabel(title) }, QDialog(parent)
{
	init_attributes();
	init_layout();
	init_titlebar();
	resize(420, 275);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	update();
}

void QLDialog::set_icon(const QLGraphic& icon)
{
	m_icon_label = new QLLabel(icon);
	m_icon_label->set_object_name("Icon Label");
	m_icon_label->setAlignment(Qt::AlignCenter);
	m_icon_label->setMinimumWidth(40);

	m_titlebar_layout->insertWidget(0, m_icon_label);
}

void QLDialog::setLayout(QLayout* layout)
{
	m_main_layout->addLayout(layout);
}

void QLDialog::update()
{
	int border_thickness = m_border_thickness->as<double>();

	m_main_layout->setContentsMargins(
		border_thickness + m_margins_left->as<double>(),
		border_thickness + m_margins_top->as<double>(),
		border_thickness + m_margins_right->as<double>(),
		border_thickness + m_margins_bottom->as<double>());

	QWidget::update();
}

bool QLDialog::nativeEvent(
	const QByteArray& eventType, void* message, qintptr* result)
{
	MSG* msg = static_cast<MSG*>(message);

	if (msg->message == WM_NCHITTEST)
	{
		if (isMaximized())
			return false;

		*result = 0;
		const LONG borderWidth =
			border_thickness()->as<qreal>() * devicePixelRatio();
		RECT winrect;
		GetWindowRect(reinterpret_cast<HWND>(winId()), &winrect);

		// must be short to correctly work with multiple monitors
		short x = msg->lParam & 0x0000FFFF;
		short y = (msg->lParam & 0xFFFF0000) >> 16;

		bool resizeWidth = minimumWidth() != maximumWidth();
		bool resizeHeight = minimumHeight() != maximumHeight();

		if (resizeWidth)
		{
			//left border
			if (x >= winrect.left && x < winrect.left + borderWidth)
			{
				*result = HTLEFT;
			}
			//right border
			if (x < winrect.right && x >= winrect.right - borderWidth)
			{
				*result = HTRIGHT;
			}
		}
		if (resizeHeight)
		{
			//bottom border
			if (y < winrect.bottom && y >= winrect.bottom - borderWidth)
			{
				*result = HTBOTTOM;
			}
			//top border
			if (y >= winrect.top && y < winrect.top + borderWidth)
			{
				*result = HTTOP;
			}
		}
		if (resizeWidth && resizeHeight)
		{
			//bottom left corner
			if (x >= winrect.left && x < winrect.left + borderWidth &&
				y < winrect.bottom && y >= winrect.bottom - borderWidth)
			{
				*result = HTBOTTOMLEFT;
			}
			//bottom right corner
			if (x < winrect.right && x >= winrect.right - borderWidth &&
				y < winrect.bottom && y >= winrect.bottom - borderWidth)
			{
				*result = HTBOTTOMRIGHT;
			}
			//top left corner
			if (x >= winrect.left && x < winrect.left + borderWidth &&
				y >= winrect.top && y < winrect.top + borderWidth)
			{
				*result = HTTOPLEFT;
			}
			//top right corner
			if (x < winrect.right && x >= winrect.right - borderWidth &&
				y >= winrect.top && y < winrect.top + borderWidth)
			{
				*result = HTTOPRIGHT;
			}
		}

		if (m_titlebar == QApplication::widgetAt(QCursor::pos()))
		{
			*result = HTCAPTION;
			return true;
		}

		if (*result != 0)
			return true;
	}

	return false;
}

void QLDialog::paintEvent(QPaintEvent* event)
{
	paint(this);
}

void QLDialog::init_attributes()
{
	QLThemeableBox::init_attributes();

	m_border_fill->set_value(std::vector<LString>({ "0:#3a3c42", "1:#42454d" }));
	m_border_thickness->set_value(5.0);
	m_corner_radii_top_left->set_value(12.0);
	m_corner_radii_top_right->set_value(12.0);
	m_corner_radii_bottom_left->set_value(12.0);
	m_corner_radii_bottom_right->set_value(12.0);
	m_fill->set_value("#36393f");

	m_titlebar->corner_radii_top_left()->set_value(7.0);
	m_titlebar->corner_radii_top_right()->set_value(7.0);
	m_titlebar->fill()->set_value("#25272b");

	m_title_label->text_color()->set_value("#e3e3e3");

	m_exit_button->corner_radii_top_right()->set_value(7.0);
	m_exit_button->fill()->set_value("#25272b");
}

void QLDialog::init_layout()
{
	// Main Layout
	m_main_layout->setSpacing(0);
	m_main_layout->addWidget(m_titlebar);
	m_main_layout->setAlignment(m_titlebar, Qt::AlignTop);
	QWidget::setLayout(m_main_layout);
	m_main_layout->activate();
}

void QLDialog::init_titlebar()
{
	m_titlebar->set_object_name("Titlebar");
	m_titlebar->setFixedHeight(40);

	m_title_label->set_object_name("Title Label");
	m_title_label->set_font_size(14);
	m_title_label->setAttribute(Qt::WA_TransparentForMouseEvents);

	connect(m_exit_button, &QLButton::clicked,
		[this] { done(QDialog::Rejected); });

	m_exit_button->set_object_name("Exit Button");

	// Setup Titlebar Layout
	m_titlebar_layout->setContentsMargins(5, 0, 0, 0);
	m_titlebar_layout->setSpacing(0);
	m_titlebar_layout->addWidget(m_title_label);
	m_titlebar_layout->addStretch();
	m_titlebar_layout->addWidget(m_exit_button);
	m_titlebar->setLayout(m_titlebar_layout);
}

void QLayers::center(QWidget* upper_widget, QWidget* lower_widget)
{
	upper_widget->move(
		lower_widget->x() + (lower_widget->width() - upper_widget->width()) / 2,
		lower_widget->y() + (lower_widget->height() - upper_widget->height()) / 2);
}
