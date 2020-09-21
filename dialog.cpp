#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <QProcess>

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
    canbtnUse(false);
}

void Dialog::canbtnUse(bool use)
{
    ui->pushButton_open_file_out->setEnabled(use);
    ui->pushButton_ok->setEnabled(use);
}


void Dialog::on_pushButton_ok_clicked()
{
    ui->progressBar_wait->setHidden(false);
    canbtnUse(false);

    m_fileOut = ui->lineEdit_file_path_out->text().trimmed();
    //输入参数检查
    double startTime = ui->lineEdit_time_start->text().toDouble();
    double endTime = ui->lineEdit_time_end->text().toDouble();
    if(endTime <= startTime)
    {
        QString errorInfo = "时间点错误 >_<";
        QMessageBox::critical(nullptr, "error", errorInfo, QMessageBox::Yes);
        return;
    }

    //ffmpeg 处理
    WorkThreadParams paras;
    paras.startTime = startTime;
    paras.endTime = endTime - startTime;
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
