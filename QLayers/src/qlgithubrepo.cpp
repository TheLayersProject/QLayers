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

#include <QLayers/qlgithubrepo.h>

#include <QList>

using QLayers::QLGitHubRepo;

QLGitHubRepo::QLGitHubRepo(const QString& repo_url)
{
	QStringList url_strings = repo_url.split("/");

	if (url_strings.size() >= 2)
	{
		m_user_name = url_strings[url_strings.size() - 2];
		m_repo_name = url_strings[url_strings.size() - 1];
	}
}

QString QLGitHubRepo::to_string() const
{
	return QString(m_user_name + "/" + m_repo_name);
}
