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

#include <QLayers/qlmainwindow.h>

#include <Windows.h>
#include <windowsx.h>

#include <QIcon>
#include <QPainterPath>

#include <Layers/lstring.h>

#include <QLayers/qlapplication.h>
#include <QLayers/qlcalculate.h>
#include <QLayers/qlthemecreatordialog.h>

#include "qlmainwindowtitlebar.h"
#include "qlsettingsmenu.h"
#include "qlthemeswidget.h"

using Layers::LString;

using QLayers::QLSettingsMenu;
using QLayers::LMainWindowTitlebar;
using QLayers::QLMainWindow;
//using QLayers::QLThemeable;

QLMainWindow::QLMainWindow(QWidget* parent) :
	m_titlebar{ new LMainWindowTitlebar },
	QLWidget(parent)
{
	init_attributes();
	init_layout();
	init_titlebar_connections();
	resize(1000, 700);
	set_object_name("Main Window");
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	connect(m_titlebar->menu_tab_bar(), &QLTabBar::index_changed,
		[this](int prev_index, int new_index)
		{
			if (QWidget* prev_widget = (prev_index != -1) ?
				m_central_widgets[prev_index] : nullptr)
			{
				prev_widget->hide();
			}

			if (QWidget* new_widget = (new_index != -1) ?
				m_central_widgets[new_index] : nullptr)
			{
				new_widget->show();
			}
		});

	connect(m_titlebar->menu_tab_bar(), &QLTabBar::tab_closed,
		[this](int i)
		{
			m_central_widgets.takeAt(i)->deleteLater();

			if (m_central_widgets.isEmpty())
				qApp->quit();
		});

	m_separator->set_object_name("Separator");
	m_separator->setFixedHeight(3);
}

void QLMainWindow::open_central_widget(QWidget* central_widget)
{
	m_titlebar->menu_tab_bar()->add_tab(central_widget->objectName());

	_open_central_widget(central_widget);
}

void QLMainWindow::open_central_widget(
	QWidget* central_widget, const QLGraphic& tab_icon_graphic)
{
	m_titlebar->menu_tab_bar()->add_tab(
		tab_icon_graphic, central_widget->objectName());

	_open_central_widget(central_widget);
}

void QLMainWindow::update()
{
	if (isMaximized())
		m_main_layout->setContentsMargins(0, 0, 0, 0);
	else
	{
		int border_thickness = m_border_thickness->as<double>();

		m_main_layout->setContentsMargins(
			border_thickness + m_margins_left->as<double>(),
			border_thickness + m_margins_top->as<double>(),
			border_thickness + m_margins_right->as<double>(),
			border_thickness + m_margins_bottom->as<double>());
	}

	QWidget::update();
}

bool QLMainWindow::nativeEvent(
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

void QLMainWindow::new_theme_clicked()
{
	LThemeCreatorDialog dialog;

	center(&dialog, this);

	dialog.exec();
}

void QLMainWindow::init_attributes()
{
	m_fill->set_link_attribute(qLayersApp->primary());

	m_border_thickness->set_value(15.0);
	m_border_fill->set_value(std::vector<LString>({ "0:#3a3c42", "1:#42454d" }));
	m_corner_radii_top_left->set_value(10.0);
	m_corner_radii_top_right->set_value(10.0);
	m_corner_radii_bottom_left->set_value(10.0);
	m_corner_radii_bottom_right->set_value(10.0);

	m_separator->fill()->set_value("#25272b");
}

void QLMainWindow::init_layout()
{
	int margin = border_thickness()->as<double>();

	m_main_layout->setContentsMargins(margin, margin, margin, margin);
	m_main_layout->setSpacing(0);
	m_main_layout->addWidget(m_titlebar);
	m_main_layout->addWidget(m_separator);

	setLayout(m_main_layout);
}

void QLMainWindow::init_titlebar_connections()
{
	connect(m_titlebar->settings_button(), &QLButton::clicked,
		[this]
		{
			QLSettingsMenu* settings_menu = new QLSettingsMenu;

			connect(settings_menu->themes_widget()->new_theme_button(),
				&QLButton::clicked,
				this, &QLMainWindow::new_theme_clicked);

			open_central_widget(settings_menu,
				QLGraphic(":/images/settings_animated.svg", QSize(24, 24)));
		});

	connect(m_titlebar->minimize_button(), &QLButton::clicked,
		[this]
		{
			showMinimized();
		});

	connect(m_titlebar->maximize_button(), &QLButton::clicked,
		[this]
		{
			if (isMaximized())
				showNormal();
			else
				showMaximized();

			update();
		});

	connect(m_titlebar->exit_button(), &QLButton::clicked,
		[this] { qApp->quit(); });
}

void QLMainWindow::_open_central_widget(QWidget* central_widget)
{
	if (LThemeable* central_themeable =
		dynamic_cast<LThemeable*>(central_widget))
	{
		if (current_theme_item())
			central_themeable->apply_theme_item(
				current_theme_item()->find_item(
					central_widget->objectName().toStdString().c_str()));
	}

	m_central_widgets.append(central_widget);
	m_main_layout->addWidget(central_widget);

	set_active_central_widget(central_widget);
}

void QLMainWindow::set_active_central_widget(QWidget* central_widget)
{
	if (m_central_widgets.contains(central_widget))
		m_titlebar->menu_tab_bar()->set_current_index(
			m_central_widgets.indexOf(central_widget));
}
