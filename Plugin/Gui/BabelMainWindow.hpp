//
// BabelMainWindow.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:37 2011 Chanh Allaux
// Last update Sun Dec  4 19:47:56 2011 alexandre champion
//

#ifndef BABELMAINWINDOW_HPP
#define BABELMAINWINDOW_HPP

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QListWidget>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QTranslator>
#include <QMessageBox>
#include <QInputDialog>
#include <QMap>
#include "BabeCommands.hpp"
#include "BabelAboutDialog.hpp"
#include "BabelConsole.hpp"
#include "BabelAddContactDialog.hpp"
#include "BabelConversation.hpp"
#include "EmoticonFrame.hpp"
#include "BabeCommandManager.hpp"

namespace Ui
{
  class BabelMainWindow;
}

class BabelMainWindow : public QMainWindow
{
  Q_OBJECT

  friend class BabelAddContactDialog;
  friend class BabelConversation;

public:
  explicit BabelMainWindow(const QString& login, QWidget *parent = 0);
  ~BabelMainWindow();
  void addContactAction(const QString&, const QString&);
  void contactRequest(const QString&);
  void requestCall(const QString&);
  void requestCallFromTab();
  void callRequest(const QString&);
  void callAccepted(const QString&);
  void callRejected(const QString&);
  void callHungUp(const QString&);
  void suspendOrResume(BabelConversation*);
  void callResumed(const QString&);
  void callSuspended(const QString&);
  void unknownContact(const QString&);
  void connectionLost();
  void receiveText(const QString&, const QString&);

private:
  void initStatusMenu();
  void loadLanguage(const QString&, const QString&);
  void activateTab();
  void deactivateTab();
  void stopAllCall(const QString&);
  void tryHangUp(const QString&);
  void setSuspendButtonDisabled(BabelConversation*);
  void setSuspendButtonEnabledAndSuspend(BabelConversation*);
  void setSuspendButtonEnableAndResume(BabelConversation*);
  void setCallButtonCall(BabelConversation*);
  void setCallButtonHangUp(BabelConversation*);

private:
  Ui::BabelMainWindow *ui;
  EmoticonFrame *mEmoticon;
  bool mShowing;
  QString mLogin;
  QMap<QString, bool> mOpenedTab;
  bool mDisconnect;
  QString mCurrentCall;

public slots:
  void setLanguageToEnglish();
  void setLanguageToFrench();
  void setLanguageToSpanish();
  void setLanguageTo1337();
  void openEmoticonFrame();
  void setStatusDisconnected();
  void setStatusConnected();
  void setStatusBusy();
  void setStatusIdle();
  void customTreeViewMenu(const QPoint &);
  void openAboutWindow();
  void addContact();
  void removeContact();
  void doubleClickContact(QListWidgetItem*);
  void startChat();
  void startCall();
  void closeTab(int index);
  void disconnect();

protected:
  void closeEvent(QCloseEvent *);
  void keyPressEvent(QKeyEvent *);
};

#endif // BABELMAINWINDOW_HPP
