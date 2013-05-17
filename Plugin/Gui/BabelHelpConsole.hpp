#ifndef BABELHELPCONSOLE_HPP
#define BABELHELPCONSOLE_HPP

#include <QDialog>

namespace Ui
{
    class BabelHelpConsole;
}

class QSingletonApplication;

class BabelHelpConsole : public QDialog
{
    Q_OBJECT

    friend class QSingletonApplication;

public:
    explicit BabelHelpConsole(QWidget *parent = 0);
    ~BabelHelpConsole();

private:
    Ui::BabelHelpConsole *ui;
};

#endif // BABELHELPCONSOLE_HPP
