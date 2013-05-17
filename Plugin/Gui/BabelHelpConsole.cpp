#include "BabelHelpConsole.hpp"
#include "ui_babelhelpconsole.h"

BabelHelpConsole::BabelHelpConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BabelHelpConsole)
{
    ui->setupUi(this);
}

BabelHelpConsole::~BabelHelpConsole()
{
    delete ui;
}
