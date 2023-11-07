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

#ifndef QLMAINWINDOW_H
#define QLMAINWINDOW_H

#include <QVBoxLayout>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLSettingsMenu;
class LMainWindowTitlebar;

class QLAYERS_EXPORT QLMainWindow : public QLWidget
{
	Q_OBJECT

public:
	QLMainWindow(QWidget* parent = nullptr);

	void open_central_widget(QWidget* central_widget);

	void open_central_widget(
		QWidget* central_widget, const QLGraphic& tab_icon_graphic);

	virtual void update() override;

protected:
	virtual bool nativeEvent(
		const QByteArray& eventType, void* message, qintptr* result) override;

private slots:
	void new_theme_clicked();

private:
	void init_attributes();
	void init_layout();
	void init_titlebar_connections();

	void _open_central_widget(QWidget* central_widget);

	void set_active_central_widget(QWidget* central_widget);

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	LMainWindowTitlebar* m_titlebar;

	QLWidget* m_separator{ new QLWidget };

	QList<QWidget*> m_central_widgets;
};
QLAYERS_NAMESPACE_END

#endif // QLMAINWINDOW_H
