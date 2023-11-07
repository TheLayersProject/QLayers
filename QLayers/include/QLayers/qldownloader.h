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

#ifndef QLDOWNLOADER_H
#define QLDOWNLOADER_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLDownloader : public QObject
{
	Q_OBJECT

public:
	QLDownloader(QObject* parent = nullptr);

	QNetworkReply* download(const QUrl& file_url);

	QNetworkReply* download(const QUrl& file_url, const QDir& directory);

private:
	QNetworkAccessManager m_network_manager;
};
QLAYERS_NAMESPACE_END

#endif // QLDOWNLOADER_H
