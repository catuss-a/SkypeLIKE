#include "EmoticonFrame.hpp"
#include "ui_emoticonframe.h"

EmoticonFrame::EmoticonFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmoticonFrame)
{
    ui->setupUi(this);
}

EmoticonFrame::~EmoticonFrame()
{
    delete ui;
}
