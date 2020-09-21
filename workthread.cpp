#include <QProcess>
#include "workthread.h"

WorkThread::WorkThread()
{

}

void WorkThread::paramers(WorkThreadParams params)
{
    m_params = params;
}

void WorkThread::run()
{
    QProcess myProcess;
    QString cmd = "ffmpeg -ss " + QString::number(m_params.startTime) + " -t " + QString::number(m_params.endTime)
            + " -i \"" + m_params.inFiles[0] + "\" -c:v copy -y \"" + m_params.outFile + "\"";
    myProcess.start(cmd);
    myProcess.waitForFinished();
    auto ret = QString::fromLocal8Bit(myProcess.readAllStandardOutput());
    emit complete(ret);
}
