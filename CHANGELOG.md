# Changelog

All notable changes to this project will be documented in this file.

## [0.1.0] - 2023-11-12

Introducing QLayers, a C++ library for integrating Layers with Qt applications. All facilities in this library were previously maintained directory within Layers. The following are changes made to these facilities since **Layers 0.16**:

### Added

- Implemented QLThemeView which significantly improves navigation of theme-item hierarchies.
- Implemented QLResizer which is an interactive widget that can resize another widget.
- Implemented QLSplitter which can contain and resize multiple other widgets.
- Implemented QLGrowingDotProgressIndicator which shows progress by expanding a dot within a circle outline. The dots fills the outline once the progress is 100%.
- Added a status bar to the bottom of the theme editor dialog.
- Implemented automatic theme saving. The theme editor saves the active theme after a 3-second delay from when the last change was made. A growing-dot progress indicator has been added to the theme editor's status bar to represent the delay.

### Changed

- All class names are now prefixed with "QL".
- QLMainWindow::open_central_Widget() replaces set_central_widget(). The idea now is that the main window can have multiple central widgets open and the user switches between them using tabs in the titlebar.
- QLThemeEditor is now QLThemeEditorDialog. Instead of being embedded in QLMainWindow, QLThemeEditorDialog is a separate window. It updates the actual widgets directly instead of copies of them.
- The theme editor now uses the theme and its associated theme items directly instead of the themeable widgets.
- Redesigned the QLAttributeEditor to be capable of handling new Layers attribute features.
- The links widget in QLAttributeEditor displays the attribute's linking chain alongside dots and arrows for improved visual experience.
- Redesigned QLGradientDialog.
- QLThemeable subclasses no longer have to manually populate a list of child attributes for QLThemeable to have access to them.

### Removed

- Removed QLStateEditor since it has been replaced with the new QLAttributeEditor.
- Removed QLNavigator, QLWidgetButton, QLWidgetButtonGroup, QLWidgetEditor
- Removed QLThemeable::assign_tag_prefixes().
- Removed dialogs from QLApplication.
- Removed QLVersion.