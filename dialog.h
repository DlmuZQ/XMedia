#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class WorkThread;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_open_file_in_clicked();

    void on_pushButton_open_file_out_clicked();

    void progerBarTimeOut();
    void myComplete(QString result);

private:
    void            initUI();
    void            canbtnUse(bool use);


private:
    Ui::Dialog *ui;
    QString     m_fileIn;
    QString     m_fileOut;

    int         m_progress = 0;
    QTimer      m_progressTime;

    WorkThread  *m_workThread = nullptr;
};
#endif // DIALOG_H
