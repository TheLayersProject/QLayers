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

#ifndef QLTAB_H
#define QLTAB_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlbutton.h"
#include "qllabel.h"
#include "qlstatepool.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLTab : public QLWidget
{
	Q_OBJECT

signals:
	void clicked();

	void closed();

public:
	QLTab(const QLGraphic& icon, const QString& text, QWidget* parent = nullptr);

	QLTab(const QString& text, QWidget* parent = nullptr);

	QLButton* close_button() const;

	QLLabel* icon_label() const;

	QLStatePool* status_states() const;

	QLLabel* text_label() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();
	void init_attributes();
	void init_layout();

	QHBoxLayout* main_layout = new QHBoxLayout;

	QLButton* m_close_button
		{ new QLButton(QLGraphic(":/images/tab_exit.svg", QSize(16, 17))) };

	QLLabel* m_icon_label{ nullptr };

	QLLabel* m_text_label{ nullptr };

	QLStatePool* m_status_states
		{ new QLStatePool("Status", { "Active", "Inactive" })};
};
QLAYERS_NAMESPACE_END

#endif // QLTAB_H
