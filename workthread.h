#ifndef WORKTHREAD_H
#define WORKTHREAD_H
#include <QThread>

struct WorkThreadParams
{
    QStringList inFiles;
    QString     outFile;
    double      startTime;
    double      endTime;
};

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();

    void paramers(WorkThreadParams params);

signals:
    void complete(QString result);

protected:
    void run() override;

private:
    WorkThreadParams m_params;
};

#endif // WORKTHREAD_H
