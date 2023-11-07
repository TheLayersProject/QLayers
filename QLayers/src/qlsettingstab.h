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

#ifndef QLSETTINGSTAB_H
#define QLSETTINGSTAB_H

#include <QHBoxLayout>

#include <QLayers/qlayers_global.h>

#include <QLayers/qlwidget.h>

QLAYERS_NAMESPACE_BEGIN
class QLLabel;
class QLThemesWidget;

class QLSettingsTab : public QLWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	QLSettingsTab(const QLGraphic& icon, const QString& label_text, QWidget* parent = nullptr);

	int recommended_minimum_width();

	QLStatePool* select_states() const;

	void set_disabled(bool cond = true);

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

	void init_attributes();

	//void resizeEvent(QResizeEvent* event);

private:
	void init_layout();

	QHBoxLayout* main_layout{ new QHBoxLayout };

	bool m_disabled{ false };

	QLLabel* m_icon_label;

	QLLabel* m_text_label;

	QLStatePool* m_select_states{
		new QLStatePool("Select", { "Selected", "Unselected" }) };
};
QLAYERS_NAMESPACE_END

#endif // QLSETTINGSTAB_H
