#include"pcolorer.h"
#include"tools.h"
#include"FarEditorSet.h"

FarEditorSet *editorSet = NULL;
PluginStartupInfo Info;
FarStandardFunctions FSF;
StringBuffer *PluginPath =NULL;

SHAREDSYMBOL void WINPORT_DllStartup(const char *path)
{
      DString module(path, 0);
      int pos = module.lastIndexOf('/');
      pos = module.lastIndexOf('/',pos);
      PluginPath=new StringBuffer(DString(module, 0, pos));	
	  printf("Colorer startup: %s\n", path);
}
//todo:
/**
  Returns message from FAR current language.
*/
const wchar_t *GetMsg(int msg)
{
  return(Info.GetMsg(Info.ModuleNumber, msg));
};

/**
  Plugin initialization and creation of editor set support class.
*/
SHAREDSYMBOL void WINAPI SetStartupInfoW(const struct PluginStartupInfo *fei)
{
  Info = *fei;
  FSF = *fei->FSF;
  Info.FSF = &FSF;
};

/**
  Plugin strings in FAR interface.
*/
SHAREDSYMBOL void WINAPI GetPluginInfoW(struct PluginInfo *nInfo)
{
  static wchar_t* PluginMenuStrings;
  memset(nInfo, 0, sizeof(*nInfo));
  nInfo->Flags = PF_EDITOR | PF_DISABLEPANELS;
  nInfo->StructSize = sizeof(*nInfo);
  nInfo->PluginConfigStringsNumber = 1;
  nInfo->PluginMenuStringsNumber = 1;
  PluginMenuStrings = (wchar_t*)GetMsg(mName);
  nInfo->PluginConfigStrings = &PluginMenuStrings;
  nInfo->PluginMenuStrings = &PluginMenuStrings;
  nInfo->CommandPrefix = L"clr";
};

/**
  On FAR exit. Destroys all internal structures.
*/
SHAREDSYMBOL void WINAPI ExitFARW()
{
  if (editorSet){
    delete editorSet;
  }
};

/**
  Open plugin configuration of actions dialog.
*/
SHAREDSYMBOL HANDLE WINAPI OpenPluginW(int OpenFrom, INT_PTR Item)
{
  if (OpenFrom == OPEN_EDITOR){
    editorSet->openMenu();
  }
  else
    if (OpenFrom == OPEN_COMMANDLINE){
      //file name, which we received
      wchar_t *file = (wchar_t*)Item;

      wchar_t *nfile = PathToFull(file,true);
      if (nfile){
        if (!editorSet){
          editorSet = new FarEditorSet();
        }
        editorSet->viewFile(DString(nfile));
      }

      delete[] nfile;
    }

  return INVALID_HANDLE_VALUE;
};

/**
  Configures plugin.
*/
SHAREDSYMBOL int WINAPI ConfigureW(int ItemNumber)
{
  if (!editorSet){
    editorSet = new FarEditorSet();
  }else{
  // ReadSettings need for plugin off mode
		editorSet->ReadSettings();
	}
  editorSet->configure(false);
  return 1;
};

/**
  Processes FAR editor events and
  makes text colorizing here.
*/
SHAREDSYMBOL int WINAPI ProcessEditorEventW(int Event, void *Param)
{
  if (!editorSet){
    editorSet = new FarEditorSet();
  }
  return editorSet->editorEvent(Event, Param);
};

SHAREDSYMBOL int WINAPI ProcessEditorInputW(const INPUT_RECORD *ir)
{
  return editorSet->editorInput(ir);
}

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */