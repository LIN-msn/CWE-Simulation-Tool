#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>
#include <QApplication>
#include <QFile>

namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QString versionText, QWidget *parent = nullptr);
    ~DialogAbout();

private slots:
    void on_btn_backToTop_clicked();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
