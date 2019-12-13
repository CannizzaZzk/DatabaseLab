#ifndef ADMINWELCOME_H
#define ADMINWELCOME_H

#include <QMainWindow>

namespace Ui {
class AdminWelcome;
}

class AdminWelcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWelcome(QWidget *parent = 0);
    ~AdminWelcome();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AdminWelcome *ui;
    void upDate();
    void Delete(QString fid);
};

#endif // ADMINWELCOME_H
