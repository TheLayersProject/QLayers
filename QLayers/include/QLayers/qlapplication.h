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

/*!
	An LApplication is a QApplication and a LThemeable that provides structure
	and functionality for a Layers app.

	## App ID

	Layers app developers will need to manually produce a UUID for their
	application. The app name and UUID are used together to produce an app ID
	which is used by themes to specify app-implementations. The UUID for an
	application should never be changed because things may stop working
	properly if it does.

	## Theme Management

	The application manages loaded themes. The application is responsible for
	applying themes to known top-level widgets.

	## Updating

	The application includes functionality capable of updating itself when an
	update is available.

	<b>For now, this only works for applications hosted on GitHub. In the
	future, there will be an option to enable updating from file servers.</b>

	To enable update checking, Layers app developers will need to include
	LVersion and QLGitHubRepo objects as arguments for LApplication
	construction. These objects are used during initialization to retrieve the
	latest version via GitHub's API and compare it with the current version to
	determine if an update is available.

	After the %LApplication has been initialized in the *main()* function, the
	developers can include the following code:

	~~~~~~~~~~~~~{.c}
	if (app.update_available())
		if (app.update_on_request())
			return 0;
	~~~~~~~~~~~~~

	In the code above, update_available() is called to check if an update is
	available. If so, update_on_request() is called to display an QLUpdateDialog
	to the user which alerts them and asks if they would like to update the
	application. If they choose 'Update', then update_on_request() will return
	true and cause the *main()* function to end, closing the application while
	the update takes place. If the user chooses not to update, then the *main()*
	function will proceed.

	It is recommended to perform this sequence before initializing the
	QLMainWindow.
*/
class QLAYERS_EXPORT QLApplication : public QApplication, public QLThemeable
{
	Q_OBJECT

signals:
	/*!
		This signal is emitted if the active theme changes.
	*/
	void active_theme_changed();

	/*!
		This signal is emitted when a new theme is added to the application.
	*/
	void theme_added(Layers::LTheme* theme);

public:
	/*!
		Constructs a Layers application.

		The *name* and *uuid* parameters are required.

		The *version* and *github_repo* parameters are only required if the
		Layers app developer decides to utilize the included updating
		functionality.
	*/
	QLApplication(int& argc, char** argv,
		const QString& name,
		const QUuid& uuid);

	~QLApplication();

	/*!
		Returns a pointer to the active theme.
	*/
	Layers::LTheme* active_theme();

	void add_theme(Layers::LTheme* theme);

	/*!
		Returns the application's display-ID.
	*/
	QString app_display_id() const;

	/*!
		Applies *theme* to the known top-level widgets.
	*/
	void apply_theme(Layers::LTheme* theme);

	/*!
		Returns a list of child themeables.

		This function overrides QLThemeable::q_child_themeables() to include the
		known top-level widgets.
	*/
	virtual QList<QLThemeable*> q_child_themeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	/*!
		Returns a pointer to a QFile of the application icon.

		If no icon was supplied during initialization, nullptr is returned.
	*/
	QFile* icon_file();

	void init();

	QString latest_version();

	/*!
		Returns the name of the application.
	*/
	QString name();

	Layers::LAttribute* primary() const;

	/*!
		Reapplies the active theme.
	*/
	void reapply_theme();

	void set_github_repo(const QString& github_repo_url);

	void set_publisher(const QString& publisher);

	static void set_version(const QString& version);

	/*!
		Returns the application's settings.
	*/
	QSettings& settings();

	/*!
		Returns a pointer to the theme specified by *theme_id*.
	*/
	Layers::LTheme* theme(const QString& theme_id);

	/*!
		Returns a reference to the QMap containing the application's
		themes.

		The QMap contains QString-LTheme* pairs where the QString matches the
		name of the associated theme.
	*/
	QMap<QString, Layers::LTheme*> themes();

	/*!
		Returns true if an application update is available.
	*/
	bool update_available();

	static QString version();

	/*!
		Prompts the user with an QLUpdateDialog asking if they would like to
		update the application.

		Returns true if the user decides to update. Otherwise, returns false.
	*/
	void download_and_install_update();

public slots:
	/*!
		Renames the theme specified by *old_name* to *new_name*.
	*/
	void rename_theme(const QString& old_name, const std::string& new_name);

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
