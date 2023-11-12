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

#include <QLayers/qlapplication.h>

#include <QDirIterator>
#include <QFontDatabase>
#include <QGradientStops>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QProcess>
#include <QWidget>

#include <QLayers/qldownloader.h>
#include <QLayers/qlgithubrepo.h>

using Layers::LAttribute;
using Layers::LTheme;
using Layers::LThemeable;

using QLayers::QLApplication;
//using QLayers::QLMainWindow;
using QLayers::QLThemeable;

LTheme* QLayers::activeTheme()
{
	if (qLayersApp)
		return qLayersApp->active_theme();
	else
		return nullptr;
}

QLApplication::QLApplication(
	int& argc, char** argv,
	const QString& name,
	const QUuid& uuid) :
	m_name{ name },
	m_uuid{ uuid },
	m_settings{ QSettings(name, name) },
	m_downloader{ new QLDownloader(this) },
	QApplication(argc, argv)
{
	//LThemeable::init(nullptr);
}

QLApplication::~QLApplication()
{
	_clear_theme();

	if (m_github_repo)
		delete m_github_repo;

	for (LTheme* theme : m_themes)
		delete theme;

	m_themes.clear();
}

QString QLApplication::app_display_id() const
{
	return m_name + " (" + m_publisher + ")";
}

void QLApplication::apply_theme(LTheme* theme)
{
	if (m_active_theme != theme)
	{
		LTheme* previous_active_theme = m_active_theme;

		m_active_theme = theme;

		if (!m_active_theme->has_implementation(app_display_id().toStdString().c_str()))
		{
			// Iterate backwards through the lineage to determine last CAT.
			// TEMPORARILY DISABLED
			//for (int i = m_active_theme->lineage().size() - 1; i >= 0; i--)
			//{
			//	QString theme_id = m_active_theme->lineage()[i];

			//	QString theme_name = (theme_id.contains("_")) ?
			//		theme_id.left(theme_id.lastIndexOf("_")) : theme_id;

			//	if (LTheme* theme = qLayersApp->theme(theme_id))
			//		if (theme->has_implementation(app_display_id()))
			//		{
			//			QString app_file_name =
			//				qLayersApp->app_identifier() + ".json";

			//			QFile last_CAT_app_file(
			//				theme->path().filePath(app_file_name));
			//			
			//			if (last_CAT_app_file.exists())
			//			{
			//				last_CAT_app_file.copy(
			//					m_active_theme->path().filePath(app_file_name)
			//				);

			//				QFile::setPermissions(
			//					m_active_theme->path().filePath(app_file_name),
			//					QFileDevice::WriteUser);

			//				break;
			//			}
			//		}
			//}
		}

		m_active_theme->load(app_display_id().toStdString().c_str());

		_clear_theme();

		apply_theme_item(theme->find_item(path()));

		m_settings.setValue(
			"themes/active_theme",
			QString::fromStdString(theme->display_id().c_str()));

		emit active_theme_changed();

		if (previous_active_theme)
			previous_active_theme->clear();
	}
}

QList<QLThemeable*> QLApplication::child_qlthemeables(Qt::FindChildOptions options)
{
	QList<QLThemeable*> child_qlthemeables;

	for (QWidget* tl_widget : topLevelWidgets())
		if (QLThemeable* tl_themeable = dynamic_cast<QLThemeable*>(tl_widget))
			child_qlthemeables.append(tl_themeable);

	return child_qlthemeables;
}

LTheme* QLApplication::active_theme()
{
	return m_active_theme;
}

void QLApplication::add_theme(LTheme* theme)
{
	m_themes[QString::fromStdString(theme->display_id().c_str())] = theme;

	emit theme_added(theme);
}

QFile* QLApplication::icon_file()
{
	return m_icon_file;
}

void QLApplication::init()
{
	if (!m_initialized)
	{
		Q_INIT_RESOURCE(roboto_font);
		Q_INIT_RESOURCE(images);

		qRegisterMetaType<QGradientStops>("QGradientStops");

		init_directories();
		init_fonts();
		init_latest_version();
		setAttribute(Qt::AA_EnableHighDpiScaling);
		setEffectEnabled(Qt::UI_AnimateCombo, false);
		set_object_name("App");

		QStringList name_parts = m_name.split(' ', Qt::SkipEmptyParts);
		for (int i = 0; i < name_parts.size(); i++)
			name_parts[i].replace(0, 1, name_parts[i][0].toLower());
		m_name_underscored = name_parts.join("_");

		init_themes();

		m_initialized = true;
	}
}

QString QLApplication::latest_version()
{
	return m_latest_version;
}

QMap<QString, LTheme*> QLApplication::themes()
{
	return m_themes;
}

bool QLApplication::update_available()
{
	if (!m_latest_version.isEmpty() && !version().isEmpty())
		return m_latest_version != version();
	else
		return false;
}

QString QLApplication::version()
{
	return applicationVersion();
}

void QLApplication::download_and_install_update()
{
	QUrl repo_releases_json_download_url(m_github_api_repos_url_base + "/" + m_github_repo->to_string() + "/releases");

	QNetworkReply* repo_releases_json_download = m_downloader->download(repo_releases_json_download_url);

	QEventLoop loop;
	connect(repo_releases_json_download, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	if (repo_releases_json_download->error() == QNetworkReply::NoError)
	{
		QJsonArray repo_releases_json_array = QJsonDocument::fromJson(repo_releases_json_download->readAll()).array();

		QJsonArray release_assets_array = repo_releases_json_array.first().toObject()["assets"].toArray();

		for (QJsonValueRef release_asset : release_assets_array)
		{
			QString release_asset_name = release_asset.toObject()["name"].toString();

			if (release_asset_name.endsWith(".exe") || release_asset_name.endsWith(".msi"))
			{
				QDir temp_dir = local_app_data_path() / "Temp\\";

				QUrl latest_version_download_url = QUrl(release_asset.toObject()["browser_download_url"].toString());

				if (!QFile::exists(latest_version_download_url.fileName()))
				{
					QNetworkReply* update_download = m_downloader->download(latest_version_download_url, temp_dir);

					QEventLoop loop;
					connect(update_download, SIGNAL(finished()), &loop, SLOT(quit()));
					loop.exec();
				}

				QStringList args = { "/SILENT" };

				QProcess update_process;
				update_process.startDetached(temp_dir.filePath(latest_version_download_url.fileName()), args);
			}
		}
	}
}

void QLApplication::rename_theme(const QString& theme_id, const QString& new_name)
{
	if (m_themes.contains(theme_id))
	{
		LTheme* theme = m_themes[theme_id];
		QDir old_theme_dir = theme->directory();

		theme->set_name(new_name.toStdString().c_str());

		old_theme_dir.rename(
			old_theme_dir.absoluteFilePath("."),
			QString::fromStdString(
				(latest_T_version_path() / theme->display_id().c_str()).string()));

		// TEMP
		//theme->set_dir();

		//old_theme_dir.removeRecursively();

		//m_themes.insert(new_name, m_themes.take(old_name));

		//m_themes[new_name]->set_name(new_name);

		//apply_theme(*m_themes[new_name]);
		//save_theme(*m_themes[new_name]);
	}
}

QString QLApplication::name()
{
	return m_name;
}

LAttribute* QLApplication::primary() const
{
	return m_primary;
}

void QLApplication::reapply_theme()
{
	apply_theme(m_active_theme);
}

void QLApplication::set_github_repo(const QString& github_repo_url)
{
	if (m_github_repo)
		delete m_github_repo;

	m_github_repo = new QLGitHubRepo(github_repo_url);
}

void QLApplication::set_publisher(const QString& publisher)
{
	m_publisher = publisher;
}

void QLApplication::set_version(const QString& version)
{
	setApplicationVersion(version);
}

QSettings& QLApplication::settings()
{
	return m_settings;
}

LTheme* QLApplication::theme(const QString& theme_id)
{
	if (m_themes.contains(theme_id))
		return m_themes[theme_id];

	return nullptr;
}

void QLApplication::_clear_theme()
{
	if (current_theme_item())
		apply_theme_item(nullptr);
}

void QLApplication::init_directories()
{
	QDir app_dir = app_path(m_name.toStdString());
	QDir layers_dir = layers_path();
	QDir themes_dir = themes_path();
	QDir latest_T_version_dir = latest_T_version_path();

	if (!app_dir.exists())
		app_dir.mkdir(".");

	if (!layers_dir.exists())
		layers_dir.mkdir(".");

	if (!themes_dir.exists())
		themes_dir.mkdir(".");

	if (!latest_T_version_dir.exists())
		latest_T_version_dir.mkdir(".");
}

void QLApplication::init_fonts()
{
	QDirIterator fonts_iterator(
		":/fonts",
		{ "*.ttf", "*.otf" },
		QDir::Files, QDirIterator::Subdirectories);

	while (fonts_iterator.hasNext())
		QFontDatabase::addApplicationFont(fonts_iterator.next());

	QFont font("Roboto", 12, QFont::Normal);
	font.setStyleStrategy(QFont::PreferAntialias);
	setFont(font);
}

void QLApplication::init_themes()
{
	/*
		TODO: Might need to handle case where theme files labeled "dark" or
		"light" appear in the custom themes directory.
	*/

	// Load prebuilt theme files
	m_themes["Dark"] = new LTheme(std::filesystem::path("./themes/Dark"));
	m_themes["Light"] = new LTheme(std::filesystem::path("./themes/Light"));

	std::filesystem::path latest_path = latest_T_version_path();

	for (const auto& dir_entry :
		std::filesystem::directory_iterator(latest_path))
	{
		if (dir_entry.is_directory())
		{
			LTheme* loaded_theme = new LTheme(dir_entry.path());

			m_themes[QString::fromStdString(loaded_theme->display_id().c_str())] = loaded_theme;
		}
	}

	QString active_theme_id =
		m_settings.value("themes/active_theme").value<QString>();

	if (m_themes.contains(active_theme_id))
		apply_theme(m_themes[active_theme_id]);
	else
		apply_theme(m_themes["Dark"]);
}

void QLApplication::init_latest_version()
{
	if (m_github_repo)
	{
		QUrl url(m_github_api_repos_url_base + "/" + m_github_repo->to_string() + "/tags");

		QNetworkReply* download = m_downloader->download(url);

		QEventLoop loop;
		connect(download, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		loop.exec();

		if (download->error() == QNetworkReply::NoError)
		{
			QJsonDocument json_doc =
				QJsonDocument::fromJson(download->readAll());

			if (!json_doc.array().isEmpty())
				m_latest_version =
				json_doc.array().first().toObject()["name"].toString();
		}
	}
}
