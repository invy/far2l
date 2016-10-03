#pragma once

#include "MountOptions.h"
#include "KeyBarTitlesHelper.h"

#include "plugin.hpp"
#include <windows.h>

#include <vector>
#include <memory>
#include <map>

class Options
{
public:
    bool AddToDisksMenu;
    bool AddToPluginsMenu;
    int CommonPanel;
    int SafeModePanel;
    int AnyInPanel;
    int CopyContents;
    int Mode;
    int MenuForFilelist;
    int NewPanelForSearchResults;
    int FullScreenPanel;
    int LastSearchResultsPanel;
    int SelectedCopyContents;
    wchar_t ColumnTypes[64];
    wchar_t ColumnWidths[64];
    wchar_t StatusColumnTypes[64];
    wchar_t StatusColumnWidths[64];
    wchar_t Mask[512];
    wchar_t Prefix[16];
};

class Plugin {
public:
    static Plugin& getInstance();

public:
    Plugin();
public:
    int getVersion();
    void setStartupInfo(const struct PluginStartupInfo * m_pPsi);
    void exitFar();
    void getPluginInfo(PluginInfo * pi);
    int configure(int item);
    HANDLE openPlugin(int openFrom, intptr_t item);
    void closePlugin(HANDLE Plugin);
    void getOpenPluginInfo(HANDLE Plugin, OpenPluginInfo * pluginInfo);
    int getFindData(HANDLE Plugin, PluginPanelItem ** PanelItem, int * itemsNumber, int OpMode);
    void freeFindData(HANDLE Plugin, PluginPanelItem * PanelItem, int itemsNumber);
    int processHostFile(HANDLE Plugin, struct PluginPanelItem * PanelItem, int ItemsNumber, int OpMode);
    int processKey(HANDLE Plugin, int key, unsigned int controlState);
    int processEvent(HANDLE Plugin, int Event, void * Param);
    int setDirectory(HANDLE Plugin, const wchar_t * Dir, int OpMode);
    int makeDirectory(HANDLE Plugin, const wchar_t ** Name, int OpMode);
    int deleteFiles(HANDLE Plugin, PluginPanelItem * PanelItem, int itemsNumber, int OpMode);
    int getFiles(HANDLE Plugin, PluginPanelItem * PanelItem, int itemsNumber, int Move, const wchar_t ** destPath, int OpMode);
    int putFiles(HANDLE Plugin, PluginPanelItem * PanelItem, int itemsNumber, int Move, const wchar_t * SrcPath, int OpMode);
    int processEditorEvent(int Event, void * Param);
    int processEditorInput(const INPUT_RECORD * Rec);
private:
    void updatePanelItems();

private:
    Options Opt;
    KeyBarTitlesHelper m_keyBar;
    PluginStartupInfo m_pPsi;
    std::vector<PluginPanelItem> m_items;
    std::map<std::wstring, MountPoint> m_mountPoints;
};
