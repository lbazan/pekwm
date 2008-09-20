//
// CmdDialog.hh for pekwm
// Copyright © 2008 Claes Nästén <me@pekdon.net>
//
// This program is licensed under the GNU GPL.
// See the LICENSE file for more information.
//

#ifndef _INPUT_DIALOG_HH_
#define _INPUT_DIALOG_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "PWinObj.hh"
#include "PDecor.hh"
#include "Util.hh"

/**
 * Base for windows handling text input.
 */
class InputDialog : public PDecor {
public:
  InputDialog(Display *dpy, Theme *theme, const std::wstring &title);
  virtual ~InputDialog(void);

  // BEGIN - PWinObj interface
  virtual void mapWindow(void);

  // PWinObj event interface
  ActionEvent *handleButtonPress(XButtonEvent *ev);
  ActionEvent *handleKeyPress(XKeyEvent *ev);
  ActionEvent *handleExposeEvent(XExposeEvent *ev);
  // END - PWinObj interface

  void setTitle(const std::wstring &title);

  void loadTheme(void);
  void unloadTheme(void);
  void render(void);

  virtual void mapCentered(const std::string &buf, bool focus, PWinObj *wo_ref = NULL);
  virtual void moveCentered(PWinObj *wo);

protected:
  virtual ActionEvent *close(void);
  virtual ActionEvent *exec(void) { return 0; }

  void bufAdd(XKeyEvent *ev);
  void bufRemove(void);
  void bufClear(void);
  void bufKill(void);
  void bufChangePos(int off);

  virtual void bufChanged(void); // recalculates buf position

  void histNext(void);
  void histPrev(void);

  void updateSize(void);
  void updatePixmapSize(void);

protected:
  Theme::TextDialogData *_data;

  ActionEvent _ae; //!< Action event for event handling
  PWinObj *_text_wo;
  PDecor::TitleItem _title;

  Pixmap _pixmap_bg;

  // content related
  std::wstring _buf;
  uint _pos, _buf_off, _buf_chars; // position, start and num display

  // history
  std::wstring _hist_new; // the one we started editing on
  Util::file_backed_list _hist_list;
  Util::file_backed_list::iterator _hist_it;
};

#endif // _INPUT_DIALOG_HH_
