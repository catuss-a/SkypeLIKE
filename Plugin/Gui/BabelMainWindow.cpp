//
// BabelMainWindow.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:02:43 2011 Chanh Allaux
// Last update Sun Dec  4 22:57:56 2011 alexandre champion
//

#include <QScrollBar>
#include <QTextCursor>
#include "QSingletonApplication.hpp"
#include "BabelMainWindow.hpp"
#include "ui_babelmainwindow.h"
#include "ui_babelconversation.h"

BabelMainWindow::BabelMainWindow(const QString& login, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::BabelMainWindow),
  mEmoticon(0),
  mShowing(false),
  mLogin(login),
  mDisconnect(false)
{
  ui->setupUi(this);
  ui->retranslateUi(this);
  ui->loginLabel->setText(login);
  connect(ui->actionAbout_Qt, SIGNAL(activated()), QSingletonApplication::getSingletonPtr(), SLOT(aboutQt()));
  deactivateTab();
  initStatusMenu();
}

BabelMainWindow::~BabelMainWindow()
{
  delete ui;
}

void BabelMainWindow::initStatusMenu()
{
  QMenu* menu = new QMenu(ui->statusToolButton);

  QAction* busyAction = new QAction(QIcon(":/images/icon/Resources/babel_icon_b_busy.png"), "Busy", menu);
  QAction* idleAction = new QAction(QIcon(":/images/icon/Resources/babel_icon_b_idle.png"), "Idle", menu);
  QAction* connectedAction = new QAction(QIcon(":/images/icon/Resources/babel_icon_b_connected.png"), "Connected", menu);

  busyAction->setIconVisibleInMenu(true);
  idleAction->setIconVisibleInMenu(true);
  connectedAction->setIconVisibleInMenu(true);

  connect(busyAction, SIGNAL(activated()), this, SLOT(setStatusBusy()));
  connect(idleAction, SIGNAL(activated()), this, SLOT(setStatusIdle()));
  connect(connectedAction, SIGNAL(activated()), this, SLOT(setStatusConnected()));

  menu->addAction(connectedAction);
  menu->addAction(idleAction);
  menu->addAction(busyAction);

  ui->statusToolButton->setMenu(menu);
}

void BabelMainWindow::openEmoticonFrame()
{
  mEmoticon = new EmoticonFrame(this);
  mEmoticon->setWindowFlags(Qt::Popup);
  mEmoticon->show();
  mEmoticon->setGeometry(this->x() + this->width() - mEmoticon->width(),
			 this->y() + this->height() - mEmoticon->height(),
			 mEmoticon->width(), mEmoticon->height());
}

void BabelMainWindow::tryHangUp(const QString& login)
{
  BabelConversation* bc;
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
            bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
            if (bc->ui->callPushButton->objectName() == "hang up")
	    {
	      Babe::CommandManager::getSingletonPtr()->execute("hangupcall " + login.toStdString());
              bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("is disconnected") + "***</b><br />");
              setCallButtonCall(bc);
              setSuspendButtonDisabled(bc);
	    }
	}
    }
}

void BabelMainWindow::addContactAction(const QString& login, const QString& status)
{
  QList<QListWidgetItem*> itemList;
  QListWidgetItem* item;

  if (login == ui->loginLabel->text())
    {
      return ;
    }
  itemList = ui->contactListWidget->findItems(login, Qt::MatchExactly);
  if (!itemList.empty())
    {
      itemList.front()->setIcon(QIcon(":/images/icon/Resources/babel_icon_b_" + status + ".png"));
      itemList.front()->setStatusTip(status);
      if (status == "disconnected")
	tryHangUp(login);
    }
  else
    {
      item = new QListWidgetItem(login);
      item->setIcon(QIcon(":/images/icon/Resources/babel_icon_b_" + status + ".png"));
      item->setStatusTip(status);
      ui->contactListWidget->addItem(item);
    }
}

void BabelMainWindow::deactivateTab()
{
  ui->contactTabWidget->setHidden(true);
  this->setMaximumSize(318, 16777215);
}

void BabelMainWindow::activateTab()
{
  ui->contactTabWidget->setHidden(false);
  this->setMaximumSize(16777215, 16777215);
}

void BabelMainWindow::contactRequest(const QString &login)
{
  if (QMessageBox::question(this, "", login + " " + tr("wants to add you in his/her contact"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
      addContactAction(login, "disconnected");
      ui->statusbar->showMessage(login + " " + tr("has been added to your contact"));
      Babe::CommandManager::getSingletonPtr()->execute("acceptcontactrequest " + login.toStdString());
    }
  else
    {
      Babe::CommandManager::getSingletonPtr()->execute("rejectcontactrequest " + login.toStdString());
    }
}

void BabelMainWindow::requestCall(const QString& login)
{
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
	  stopAllCall(login);
	  BabelConversation* bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
          if (bc->ui->callPushButton->objectName() == "call")
            {
              setCallButtonHangUp(bc);
              setSuspendButtonEnabledAndSuspend(bc);
              bc->ui->textEdit->insertHtml("<b>***" + tr("You are calling ") + login + "***</b><br />");
	      Babe::CommandManager::getSingletonPtr()->execute("requestcall " + login.toStdString());
            }
	  else
            {
              setCallButtonCall(bc);
              setSuspendButtonDisabled(bc);
	      bc->ui->textEdit->insertHtml("<b>***" + tr("You hung up") + "***</b><br />");
	      Babe::CommandManager::getSingletonPtr()->execute("hangupcall " + login.toStdString());
            }
	  ui->contactTabWidget->setCurrentIndex(i);
	  break ;
        }
    }

}

void BabelMainWindow::callAccepted(const QString& login)
{
  BabelConversation* bc;
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
	  bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
	  ui->contactTabWidget->setCurrentIndex(i);
	  bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("has picked up your call") + "***</b><br />");
	  break ;
        }
    }
}

void BabelMainWindow::callRejected(const QString& login)
{
  BabelConversation* bc;
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
	  bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
	  ui->contactTabWidget->setCurrentIndex(i);
          setCallButtonCall(bc);
          setSuspendButtonDisabled(bc);
	  bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("has rejected your call") + "***</b><br />");
	  break ;
        }
    }
}

void BabelMainWindow::requestCallFromTab()
{
  QString login = ui->contactTabWidget->tabText(ui->contactTabWidget->currentIndex());
  QList<QListWidgetItem*> itemList = ui->contactListWidget->findItems(login, Qt::MatchExactly);
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
          stopAllCall(login);
          BabelConversation* bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
          if (itemList.front()->statusTip() != "disconnected")
              requestCall(login);
          else if (bc->ui->callPushButton->objectName() == "hang up")
              requestCall(login);
        }
    }
}

void BabelMainWindow::stopAllCall(const QString& login)
{
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
	continue ;
      BabelConversation* bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
      if (bc->ui->callPushButton->objectName() == "hang up")
        {
          setCallButtonCall(bc);
          setSuspendButtonDisabled(bc);
	  Babe::CommandManager::getSingletonPtr()->execute("hangupcall " + ui->contactTabWidget->tabText(i).toStdString());
        }
    }
}

void BabelMainWindow::callHungUp(const QString& login)
{
  BabelConversation* bc;
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
          bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
          ui->contactTabWidget->setCurrentIndex(i);
          setCallButtonCall(bc);
          setSuspendButtonDisabled(bc);
          bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("has hung up the call") + "***</b><br />");
          Babe::CommandManager::getSingletonPtr()->execute("endcall " + ui->contactTabWidget->tabText(i).toStdString());
          break ;
        }
    }
}

void BabelMainWindow::callRequest(const QString& login)
{
  QList<QListWidgetItem*> item = ui->contactListWidget->findItems(login, Qt::MatchExactly);
  if (item.length() == 0)
    return ;
  if (QMessageBox::question(this, tr("Call"), login + " " + tr("is calling you, do you want to pick up ?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
      stopAllCall(login);
      doubleClickContact(item.front());
      BabelConversation* bc = 0;
      for (int i = 0; i < ui->contactTabWidget->count(); ++i)
        {
	  if (ui->contactTabWidget->tabText(i) == login)
            {
	      bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
	      break;
            }
        }
      bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("is calling you") + "***</b><br />");
      setCallButtonHangUp(bc);
      setSuspendButtonEnabledAndSuspend(bc);
      Babe::CommandManager::getSingletonPtr()->execute("acceptcall " + login.toStdString());
    }
  else
    {
      Babe::CommandManager::getSingletonPtr()->execute("rejectcall " + login.toStdString());
    }
}

void BabelMainWindow::suspendOrResume(BabelConversation* bc)
{
  QString login = ui->contactTabWidget->tabText(ui->contactTabWidget->currentIndex());
  if (bc->ui->suspendPushButton->objectName() == "suspend")
    {
      setSuspendButtonEnableAndResume(bc);
      bc->ui->textEdit->insertHtml("<b>***" + tr("You suspended the call") + "***</b><br />");
      Babe::CommandManager::getSingletonPtr()->execute("suspendcall " + login.toStdString());
    }
  else
    {
      setSuspendButtonEnabledAndSuspend(bc);
      bc->ui->textEdit->insertHtml("<b>***" + tr("You resumed the call") + "***</b><br />");
      Babe::CommandManager::getSingletonPtr()->execute("resumecall " + login.toStdString());
    }
}

void BabelMainWindow::callResumed(const QString& login)
{
  BabelConversation* bc;
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
	  bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
	  ui->contactTabWidget->setCurrentIndex(i);
          bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("has resumed the call") + "***</b><br />");
          setSuspendButtonEnabledAndSuspend(bc);
	  break ;
        }
    }
}

void BabelMainWindow::callSuspended(const QString& login)
{
  BabelConversation* bc;
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
	  bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
	  ui->contactTabWidget->setCurrentIndex(i);
	  bc->ui->textEdit->insertHtml("<b>***" + login + " " + tr("has suspended the call") + "***</b><br />");
          setSuspendButtonDisabled(bc);
	  break ;
        }
    }
}

void BabelMainWindow::unknownContact(const QString& message)
{
  QMessageBox::critical(this, tr("tr"), message);
}

void BabelMainWindow::connectionLost()
{
  disconnect();
}

void BabelMainWindow::receiveText(const QString& login, const QString& message)
{
  doubleClickContact(ui->contactListWidget->findItems(login, Qt::MatchExactly).front());
  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
    {
      if (ui->contactTabWidget->tabText(i) == login)
        {
	  BabelConversation* bc;
	  bc = dynamic_cast<BabelConversation*>(ui->contactTabWidget->widget(i));
	  bc->ui->textEdit->verticalScrollBar()->setValue(bc->ui->textEdit->verticalScrollBar()->maximum());
	  QTextCursor c = bc->ui->textEdit->textCursor();
	  c.movePosition(QTextCursor::End);
	  bc->ui->textEdit->setTextCursor(c);
	  bc->ui->textEdit->insertHtml("<b>" + login + " : </b>" + message + "<br />");
	  ui->contactTabWidget->setCurrentIndex(i);
	  break ;
	}
    }
}

void BabelMainWindow::setSuspendButtonDisabled(BabelConversation* bc)
{
    bc->ui->suspendPushButton->setEnabled(false);
    bc->ui->suspendPushButton->setObjectName("suspend");
    bc->ui->suspendPushButton->setText(tr("Suspend"));
    bc->ui->suspendPushButton->setIcon(QIcon(":/images/icon/Resources/pause_icon.png"));
}

void BabelMainWindow::setSuspendButtonEnableAndResume(BabelConversation* bc)
{
    bc->ui->suspendPushButton->setEnabled(true);
    bc->ui->suspendPushButton->setObjectName("resume");
    bc->ui->suspendPushButton->setText(tr("Resume"));
    bc->ui->suspendPushButton->setIcon(QIcon(":/images/icon/Resources/play_icon.png"));
}

void BabelMainWindow::setSuspendButtonEnabledAndSuspend(BabelConversation* bc)
{
    bc->ui->suspendPushButton->setEnabled(true);
    bc->ui->suspendPushButton->setObjectName("suspend");
    bc->ui->suspendPushButton->setText(tr("Suspend"));
    bc->ui->suspendPushButton->setIcon(QIcon(":/images/icon/Resources/pause_icon.png"));
}

void BabelMainWindow::setCallButtonCall(BabelConversation* bc)
{
    bc->ui->callPushButton->setText(tr("Call"));
    bc->ui->callPushButton->setObjectName("call");
    bc->ui->callPushButton->setIcon(QIcon(":/images/icon/Resources/call_icon.png"));
}

void BabelMainWindow::setCallButtonHangUp(BabelConversation* bc)
{
    bc->ui->callPushButton->setText(tr("Hang Up"));
    bc->ui->callPushButton->setObjectName("hang up");
    bc->ui->callPushButton->setIcon(QIcon(":/images/icon/Resources/hangup_icon.png"));
}

//-------------------------------------slot----------------------------------------//

// slot
void BabelMainWindow::removeContact()
{
  if (ui->contactListWidget->selectedItems().length() == 0)
    {
      QMessageBox::warning(this, tr("Warning"), tr("No contact selected"));
    }
  else
    {
      if (QMessageBox::question(this, tr("Warning"), tr("Are you sure you want to remove this contact ?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
	  QListWidgetItem* item = ui->contactListWidget->selectedItems().front();
	  Babe::CommandManager::getSingletonPtr()->execute("deletecontact " + item->text().toStdString());
	  for (int i = 0; i < ui->contactTabWidget->count(); ++i)
            {
	      if (ui->contactTabWidget->tabText(i) == item->text())
                {
		  ui->contactTabWidget->removeTab(i);
		  if (ui->contactTabWidget->count() == 0)
		    deactivateTab();
                }
            }
	  int row = ui->contactListWidget->row(item);
	  ui->contactListWidget->takeItem(row);
        }
    }
}

// slot
void BabelMainWindow::doubleClickContact(QListWidgetItem* item)
{
  if (mOpenedTab.find(item->text()) != mOpenedTab.end())
    return ;
  if (ui->contactTabWidget->count() == 0)
    activateTab();
  BabelConversation* conversation = new BabelConversation(ui->contactTabWidget);
  conversation->ui->callPushButton->setObjectName("call");
  conversation->ui->suspendPushButton->setObjectName("suspend");
  ui->contactTabWidget->addTab(conversation, QIcon(":/images/icon/Resources/babel_icon_b.png"), item->text());
  mOpenedTab[item->text()] = true;
}

// slot
void BabelMainWindow::startChat()
{
  if (ui->contactListWidget->selectedItems().length() == 0)
    {
      QMessageBox::warning(this, tr("Warning"), tr("No contact selected"));
    }
  else
    {
      QListWidgetItem* item = ui->contactListWidget->selectedItems().front();
      doubleClickContact(item);
    }
}

// slot
void BabelMainWindow::startCall()
{
  if (ui->contactListWidget->selectedItems().length() == 0)
    {
      QMessageBox::warning(this, tr("Warning"), tr("No contact selected"));
    }
  else
    {
      QListWidgetItem* item = ui->contactListWidget->selectedItems().front();
      if (item->statusTip() == "disconnected")
      {
          ui->statusbar->showMessage(item->text() + " " + tr("is disconnected"), 5000);
          return ;
      }
      doubleClickContact(item);
      requestCall(item->text());
    }
}

// slot
void BabelMainWindow::closeTab(int index)
{
  callHungUp(ui->contactTabWidget->tabText(index));
  mOpenedTab.remove(ui->contactTabWidget->tabText(index));
  ui->contactTabWidget->removeTab(index);
  if (ui->contactTabWidget->count() == 0)
    deactivateTab();
}

// slot
void BabelMainWindow::setLanguageToEnglish()
{
  loadLanguage("Plugin/Gui/babel_en", "Language set to english");
}

// slot
void BabelMainWindow::setLanguageToFrench()
{
  loadLanguage("Plugin/Gui/babel_fr", "La langue a ete changer en francais");
}

// slot
void BabelMainWindow::setLanguageToSpanish()
{
  loadLanguage("Plugin/Gui/babel_es", "La idioma es espanol");
}

// slot
void BabelMainWindow::setLanguageTo1337()
{
  loadLanguage("Plugin/Gui/babel_1337", "lAn9uA93 537 70 1337");
}

// slot
void BabelMainWindow::customTreeViewMenu(const QPoint &pos)
{
  QMenu* menu = new QMenu(this);

  if (ui->contactListWidget->selectedItems().length() > 0)
    {
      menu->addAction(ui->actionStart_Call);
      menu->addAction(ui->actionStart_Chat);
      menu->addSeparator();
      menu->addAction(ui->actionRemove);
      menu->addSeparator();
      menu->addAction(ui->actionAdd_Contact);
    }
  else
    {
      menu->addAction(ui->actionAdd_Contact);
    }
  menu->exec(ui->contactListWidget->mapToGlobal(pos));
}

// slot
void BabelMainWindow::openAboutWindow()
{
  BabelAboutDialog* about = new BabelAboutDialog(this);
  about->exec();
}

// slot
void BabelMainWindow::addContact()
{
  BabelAddContactDialog* addContact = new BabelAddContactDialog(this);
  addContact->exec();
}

// slot
void BabelMainWindow::setStatusBusy()
{
  ui->statusToolButton->setIcon(QIcon(":/images/icon/Resources/babel_icon_b_busy.png"));
  Babe::CommandManager::getSingletonPtr()->execute("updateuserstatus busy");
}

// slot
void BabelMainWindow::setStatusConnected()
{
  ui->statusToolButton->setIcon(QIcon(":/images/icon/Resources/babel_icon_b_connected.png"));
  Babe::CommandManager::getSingletonPtr()->execute("updateuserstatus connected");
}

// slot
void BabelMainWindow::setStatusDisconnected()
{
  ui->statusToolButton->setIcon(QIcon(":/images/icon/Resources/babel_icon_b_disconnected.png"));
  Babe::CommandManager::getSingletonPtr()->execute("updateuserstatus disconnected");
}

// slot
void BabelMainWindow::setStatusIdle()
{
  ui->statusToolButton->setIcon(QIcon(":/images/icon/Resources/babel_icon_b_idle.png"));
  Babe::CommandManager::getSingletonPtr()->execute("updateuserstatus idle");
}

void BabelMainWindow::loadLanguage(const QString &language, const QString &comment)
{
  if (!QSingletonApplication::getSingletonPtr()->translator.load(language))
    ui->statusbar->showMessage("Could not load language", 5000);
  else
    {
      QSingletonApplication::getSingletonPtr()->installTranslator(&QSingletonApplication::getSingletonPtr()->translator);
      ui->statusbar->showMessage(comment, 5000);
    }
  ui->retranslateUi(this);
}

// slot
void BabelMainWindow::disconnect()
{
  Babe::CommandManager::getSingletonPtr()->execute("updateuserstatus disconnected");
  mDisconnect = true;
  QSingletonApplication::getSingletonPtr()->loginWindow->show();
  this->close();
}

//-------------------------------------Event---------------------------------------//

// event
void BabelMainWindow::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_F1 && (e->modifiers() & Qt::ShiftModifier) && (e->modifiers() & Qt::ControlModifier))
    QSingletonApplication::getSingletonPtr()->console(this);
  else if (e->key() == Qt::Key_F2 && (e->modifiers() & Qt::ShiftModifier) && (e->modifiers() & Qt::ControlModifier))
    QSingletonApplication::getSingletonPtr()->helpConsole(this);
}

// event
void BabelMainWindow::closeEvent(QCloseEvent *)
{
  if (!mDisconnect)
    Babe::CommandManager::getSingletonPtr()->execute("quit");
}
