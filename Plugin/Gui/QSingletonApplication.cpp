#include "QSingletonApplication.hpp"
#include "BabelHelpConsole.hpp"
#include "BabelConsole.hpp"
#include "ui_babelhelpconsole.h"

QSingletonApplication* QSingletonApplication::getSingletonPtr()
{
  return msSingleton;
}

QSingletonApplication& QSingletonApplication::getSingleton()
{
  ASSERT_SINGLETON( msSingleton, "QSingletonApplication", "getSingleton()" );  return ( *msSingleton );
}

QSingletonApplication::QSingletonApplication(int& argc, char** argv)
    : QApplication(argc, argv),
      mainWindow(0),
      settings(0)
{
}

void QSingletonApplication::helpConsole(QWidget* parent)
{
    BabelHelpConsole* hc = new BabelHelpConsole(parent);
    hc->show();
    std::map<std::string, std::string> commandMans = Babe::Commands::getSingletonPtr()->getCommandMans();
    for (std::map<std::string, std::string>::iterator i = commandMans.begin(); i != commandMans.end(); ++i)
      {
          QString line("");
          line += "<b>";
          line += (*i).first.c_str();
          line += " :</b><br />usage : ";
          hc->ui->textEdit->insertHtml(line);
          line = (*i).second.c_str();
          line.replace("\n", "<br />");
          hc->ui->textEdit->insertHtml(line);
          hc->ui->textEdit->insertHtml("<br /><br /> ---------------------------------------------- <br /><br />");
      }
}

void QSingletonApplication::console(QWidget* parent)
{
    BabelConsole* console = new BabelConsole(parent);
    console->show();
}
