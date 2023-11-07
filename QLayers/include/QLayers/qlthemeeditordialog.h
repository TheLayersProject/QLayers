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

#ifndef QLTHEMEEDITORDIALOG_H
#define QLTHEMEEDITORDIALOG_H

#include <Layers/lthemeitem.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlattributeeditor.h"
#include "qlattributeeditorgroup.h"
#include "qldialog.h"
#include "qlgrowingdotprogressindicator.h"
#include "qlscrollarea.h"
#include "qlthemeview.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLThemeEditorDialog : public QLDialog
{
	Q_OBJECT

public:
	QLThemeEditorDialog(QWidget* parent = nullptr);

	virtual void apply_theme_item(Layers::LThemeItem* theme_item) override;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

public slots:
	void edit_theme_item(Layers::LThemeItem* theme_item);

	void reset_save_timer();

private:
	void init_layout();

	void clear_attr_editors();

	void update_attr_editors_max_width();

	void update_path_label();

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	QHBoxLayout* m_hbox_layout{ new QHBoxLayout };

	QVBoxLayout* m_attr_editors_layout{ new QVBoxLayout };

	QHBoxLayout* m_status_bar_layout{ new QHBoxLayout };

	QLThemeView* m_theme_view{ new QLThemeView };

	QLWidget* m_divider{ new QLWidget };

	QString m_path_text;

	QLLabel* m_path_label{ new QLLabel };

	QLScrollArea* m_attr_editors_scroll_area{ new QLScrollArea };

	QWidget* m_attr_editors_widget{ new QWidget };

	QLWidget* m_status_bar{ new QLWidget };

	QLLabel* m_check_label{
		new QLLabel(QLGraphic(":/images/check.svg", QSize(16, 13))) };

	QLLabel* m_status_label{ new QLLabel("Saved") };

	QLGrowingDotProgressIndicator* m_save_progress_indicator{
		new QLGrowingDotProgressIndicator };
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMEEDITORDIALOG_H  
