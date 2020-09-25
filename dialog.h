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

    void on_lineEdit_time_start_editingFinished();

    void on_lineEdit_time_end_editingFinished();

private:
    void            initUI();
    void            canbtnUse(bool use);
    QString         parseTime(QString timeStr, double& seconds);


private:
    Ui::Dialog *ui;
    QString     m_fileIn;
    QString     m_fileOut;

    double      m_startTime;
    double      m_endTime;

    int         m_progress = 0;
    QTimer      m_progressTime;

    WorkThread  *m_workThread = nullptr;
};
#endif // DIALOG_H
