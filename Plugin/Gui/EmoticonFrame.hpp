#ifndef EMOTICONFRAME_HPP
#define EMOTICONFRAME_HPP

#include <QWidget>

namespace Ui {
    class EmoticonFrame;
}

class EmoticonFrame : public QWidget
{
    Q_OBJECT

public:
    explicit EmoticonFrame(QWidget *parent = 0);
    ~EmoticonFrame();

private:
    Ui::EmoticonFrame *ui;
};

#endif // EMOTICONFRAME_HPP
