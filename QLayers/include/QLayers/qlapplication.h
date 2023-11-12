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

#ifndef QLAPPLICATION_H
#define QLAPPLICATION_H

#include <vector>

#include <QApplication>
#include <QDir>
#include <QGradientStops>
#include <QSettings>
#include <QUuid>

#include <Layers/ltheme.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlpaths.h"
#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN

QLAYERS_EXPORT Layers::LTheme* activeTheme();

class QLDownloader;
class QLGitHubRepo;
class QLMainWindow;

class QLAYERS_EXPORT QLApplication : public QApplication, public QLThemeable
{
	Q_OBJECT

signals:
	void active_theme_changed();

	void theme_added(Layers::LTheme* theme);

public:
	QLApplication(int& argc, char** argv,
		const QString& name,
		const QUuid& uuid);

	~QLApplication();

	Layers::LTheme* active_theme();

	void add_theme(Layers::LTheme* theme);

	QString app_display_id() const;

	void apply_theme(Layers::LTheme* theme);

	virtual QList<QLThemeable*> child_qlthemeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	void download_and_install_update();

	QFile* icon_file();

	void init();

	QString latest_version();

	QString name();

	Layers::LAttribute* primary() const;

	void reapply_theme();

	void set_github_repo(const QString& github_repo_url);

	void set_publisher(const QString& publisher);

	static void set_version(const QString& version);

	QSettings& settings();

	Layers::LTheme* theme(const QString& theme_id);

	QMap<QString, Layers::LTheme*> themes();

	bool update_available();

	static QString version();

public slots:
	void rename_theme(const QString& old_name, const QString& new_name);

private:
	void _clear_theme();

	void init_directories();
	void init_fonts();
	void init_themes();
	void init_latest_version();

	bool m_initialized{ false };

	Layers::LAttribute* m_foreground{
		new Layers::LAttribute("Foreground", "#e3e3e3", this) };

	Layers::LAttribute* m_gradient{
		new Layers::LAttribute("Gradient",
			std::vector<Layers::LString>({ Layers::LString("0:#3a3c42"), Layers::LString("1:#42454d") }), this) };

	Layers::LAttribute* m_primary{
		new Layers::LAttribute("Primary", "#36393f", this)};

	Layers::LAttribute* m_secondary{
		new Layers::LAttribute("Secondary", "#2f3136", this) };

	Layers::LAttribute* m_tertiary{
		new Layers::LAttribute("Tertiary", "#25272b", this) };

	Layers::LTheme* m_active_theme{ nullptr };

	QLDownloader* m_downloader{ nullptr };

	QString m_github_api_repos_url_base{ "https://api.github.com/repos" };

	QLGitHubRepo* m_github_repo{ nullptr };

	QFile* m_icon_file{ nullptr };

	QString m_latest_version;

	QString m_name;

	QString m_name_underscored;

	QString m_publisher;

	QSettings m_settings;

	QMap<QString, Layers::LTheme*> m_themes;

	QUuid m_uuid;
};
QLAYERS_NAMESPACE_END

#define qLayersApp (static_cast<QLApplication*>(qApp))

#endif // !QLAPPLICATION_H
