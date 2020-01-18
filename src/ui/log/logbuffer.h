#ifndef LOGBUFFER_H
#define LOGBUFFER_H

#include <QObject>
#include <QByteArray>

#include "logentry.h"

QT_FORWARD_DECLARE_CLASS(LogEntryBlocked)
QT_FORWARD_DECLARE_CLASS(LogEntryProcNew)
QT_FORWARD_DECLARE_CLASS(LogEntryStatTraf)

class LogBuffer : public QObject
{
    Q_OBJECT

public:
    explicit LogBuffer(int bufferSize = 0,
                       QObject *parent = nullptr);

    int top() const { return m_top; }
    int offset() const { return m_offset; }

    QByteArray &array() { return m_array; }

    LogEntry::LogType peekEntryType();

    void writeEntryBlocked(const LogEntryBlocked *logEntry);
    void readEntryBlocked(LogEntryBlocked *logEntry);

    void writeEntryProcNew(const LogEntryProcNew *logEntry);
    void readEntryProcNew(LogEntryProcNew *logEntry);

    void readEntryStatTraf(LogEntryStatTraf *logEntry);

public slots:
    void reset(int top = 0);

private:
    char *output();
    const char *input() const;

    void prepareFor(int len);

private:
    int m_top = 0;
    int m_offset = 0;

    QByteArray m_array;
};

#endif // LOGBUFFER_H
