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

#ifndef QLUPDATEDIALOG_H
#define QLUPDATEDIALOG_H

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qldialog.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLUpdateDialog : public QLDialog
{
	Q_OBJECT

public:
	QLUpdateDialog(const QString& version, const QString& latest_version,
		QWidget* parent = nullptr);

private:
	void init_layout();

	QLButton* m_remind_me_later_button{ new QLButton("Remind Me Later") };
	QLButton* m_update_button{ new QLButton("Update") };

	QLLabel* m_message_label;
};
QLAYERS_NAMESPACE_END

#endif // QLUPDATEDIALOG_H
