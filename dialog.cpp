#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <QProcess>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>
#include <QVector>

#include "dialog.h"
#include "ui_dialog.h"
#include "workthread.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    this->resize(600,100);
    this->setWindowTitle("XMedia");
    QIcon icon("./XMedia.icon");
    this->setWindowIcon(QIcon(":icon_1/XMedia.ico"));

    initUI();

    m_workThread = new WorkThread();

    connect(m_workThread, &WorkThread::complete, this, &Dialog::myComplete);
    connect(&m_progressTime, &QTimer::timeout, this, &Dialog::progerBarTimeOut);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::initUI()
{
    ui->label_file_path->setText("视频/音频:");
    ui->label_out_file_dir->setText("输出目录:");
    ui->pushButton_open_file_in->setText("选择");
    ui->pushButton_open_file_out->setText("选择");

    ui->progressBar_wait->setHidden(true);
    ui->progressBar_wait->setValue(0);
    ui->progressBar_wait->setMinimum(0);
    ui->progressBar_wait->setMaximum(100);

    ui->lineEdit_time_start->setText("00:00:00.000");
    ui->lineEdit_time_end->setText("00:00:00.000");

    QRegExp regx("[0-9.:]+$");
    QValidator *v1 = new QRegExpValidator(regx, ui->lineEdit_time_start);
    ui->lineEdit_time_start->setValidator(v1);

    QValidator *v2 = new QRegExpValidator(regx, ui->lineEdit_time_end);
    ui->lineEdit_time_end->setValidator(v2);

    canbtnUse(false);
}

void Dialog::canbtnUse(bool use)
{
    ui->pushButton_open_file_out->setEnabled(use);
    ui->pushButton_ok->setEnabled(use);
}

QString Dialog::parseTime(QString timeStr, double &seconds)
{
    int ruleIndex = 3;
    QString hourStr, minuteStr, secondStr, msStr;
    int curIndex = timeStr.trimmed().size() - 1;
    timeStr = timeStr.trimmed();

    for(; curIndex >= 0; curIndex --)
    {
        if(timeStr[curIndex] == "." || timeStr[curIndex] == ":")
        {
            ruleIndex --;
            continue;
        }
        if(ruleIndex == 3)
        {
            if(msStr.size() != 3)
                msStr = QString(timeStr[curIndex]) + msStr;
            else
            {
                ruleIndex --;
                secondStr = QString(timeStr[curIndex]) + secondStr;
            }
        }
        else if(ruleIndex == 2)
        {
            if(secondStr.size() != 2)
                secondStr = QString(timeStr[curIndex]) + secondStr;
            else
            {
                ruleIndex --;
                minuteStr = QString(timeStr[curIndex]) + minuteStr;
            }
        }
        else if(ruleIndex == 1)
        {
            if(minuteStr.size() != 2)
                minuteStr = QString(timeStr[curIndex]) + minuteStr;
            else
            {
                ruleIndex --;
                hourStr = QString(timeStr[curIndex]) + hourStr;
            }
        }
        else
        {
            if(hourStr.size() != 2)
                hourStr = QString(timeStr[curIndex]) + hourStr;
        }
    }

    seconds = hourStr.toInt() * 60 * 60 + minuteStr.toInt() * 60 + secondStr.toInt();
    double tmpMs = msStr.toDouble();
    for(int i = 0; i < msStr.size(); i++)
        tmpMs = tmpMs / 10;
    seconds += tmpMs;
    auto addTime = [](QString str, int s) -> QString {
        QString ret;
        if(str.size() == s) return str;
        for(int i = s; i > str.size(); i--)
        {
            ret = "0" + ret + str;
        }
        return ret;
    };
    QString outText = addTime(hourStr, 2) + ":" + addTime(minuteStr, 2) + ":" + addTime(secondStr, 2) + "." + (msStr.size() == 0 ? "0" : msStr);
    return outText;
}


void Dialog::on_pushButton_ok_clicked()
{
    ui->progressBar_wait->setHidden(false);
    canbtnUse(false);

    m_fileOut = ui->lineEdit_file_path_out->text().trimmed();
    if(m_endTime <= m_startTime)
    {
        QString errorInfo = "时间点错误 >_<";
        QMessageBox::critical(nullptr, "error", errorInfo, QMessageBox::Yes);
        return;
    }

    //ffmpeg 处理
    WorkThreadParams paras;
    paras.startTime = m_startTime;
    paras.endTime = m_endTime - m_startTime;
    paras.inFiles = QStringList(m_fileIn);
    paras.outFile = m_fileOut;
    m_workThread->paramers(paras);
    m_workThread->start();
    m_progressTime.stop();
    m_progressTime.start(2000);
}

void Dialog::on_pushButton_cancel_clicked()
{
	QProcess myprocess;
	QString cmd = "taskkill /im ffmpeg.exe";
	myprocess.start(cmd);
	myprocess.waitForFinished();

	ui->progressBar_wait->setValue(0);
	ui->progressBar_wait->setHidden(true);
	m_progress = 0;
}

void Dialog::on_pushButton_open_file_in_clicked()
{
    QFileDialog dialog;
    dialog.setWindowTitle("选择音频/视频");
    if(dialog.exec())
    {
        auto ret = dialog.selectedFiles();
        if(ret.size() > 0)
        {
            m_fileIn = ret[0];
            ui->lineEdit_file_path_in->setText(m_fileIn);
            QFileInfo fileInfo(m_fileIn);
            QString timeStr = QString::number(QDateTime::currentSecsSinceEpoch());
            m_fileOut = fileInfo.dir().path() + "/" + timeStr + "." + fileInfo.suffix();
            ui->lineEdit_file_path_out->setText(m_fileOut);

            canbtnUse(true);
        }
    }
}

void Dialog::on_pushButton_open_file_out_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
    QFileInfo fileInfo(m_fileIn);
    QString timeStr = QString::number(QDateTime::currentSecsSinceEpoch());
    m_fileOut = dirpath + "/" + timeStr + "." + fileInfo.suffix();
    ui->lineEdit_file_path_out->setText(m_fileOut);
}

void Dialog::progerBarTimeOut()
{
    if(m_progress < 99)
    {
        m_progress ++;
        ui->progressBar_wait->setValue(m_progress);
    }
}

void Dialog::myComplete(QString result)
{
	m_progressTime.stop();
    ui->progressBar_wait->setValue(100);
	QFileInfo fileInfo(m_fileOut);
	if (fileInfo.exists())
	{
		QMessageBox::information(nullptr, "ok", "完成");
	}
	else
	{
		QMessageBox::critical(nullptr, "error", "失败", QMessageBox::Yes);
	}
	ui->progressBar_wait->setValue(0);
	ui->progressBar_wait->setHidden(true);
	m_progress = 0;
}
void Dialog::on_lineEdit_time_start_editingFinished()
{
    QString outText = parseTime(ui->lineEdit_time_start->text(), m_startTime);
    ui->lineEdit_time_start->setText(outText);
    qDebug() << m_startTime;
}

void Dialog::on_lineEdit_time_end_editingFinished()
{
    QString outText = parseTime(ui->lineEdit_time_end->text(), m_endTime);
    ui->lineEdit_time_end->setText(outText);
    qDebug() << m_endTime;
}
