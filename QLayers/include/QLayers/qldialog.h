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

#ifndef QLDIALOG_H
#define QLDIALOG_H

#include <QDialog>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlbutton.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLDialog : public QDialog, public QLThemeableBox
{
	Q_OBJECT

public:
	QLDialog(const QString& title = "Dialog", QWidget* parent = nullptr);

	void set_icon(const QLGraphic& icon);

	void setLayout(QLayout* layout);

	virtual void update() override;

protected:
	virtual bool nativeEvent(
		const QByteArray& eventType, void* message, qintptr* result) override;

	virtual void paintEvent(QPaintEvent* event) override;

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

private:
	void init_attributes();
	void init_layout();
	void init_titlebar();

	bool m_hovering{ false };

	QHBoxLayout* m_titlebar_layout = new QHBoxLayout;

	QLWidget* m_titlebar{ new QLWidget };

	QLLabel* m_icon_label{ nullptr };

	QLLabel* m_title_label{ nullptr };

	QLButton* m_exit_button = new QLButton(
		QLGraphic(":/images/exit.svg", QSize(20, 20)));
};

/*!
	Moves *upper_widget* to the center of *lower_widget*.
*/
QLAYERS_EXPORT void center(QWidget* upper_widget, QWidget* lower_widget);

QLAYERS_NAMESPACE_END

#endif // QLDIALOG_H
