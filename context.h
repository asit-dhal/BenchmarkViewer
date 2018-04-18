#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

class Context
{
public:
    Context() = default;
    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);
    int getCpuFrequency() const;
    void setCpuFrequency(int value);
    bool getCpuScalingEnabled() const;
    void setCpuScalingEnabled(bool value);
    QString getLibraryBuildType() const;
    void setLibraryBuildType(QString value);
    int getCpuCount() const;
    void setCpuCount(int value);

private:
    QDateTime timestamp;
    int cpuCount;
    int cpuFrequency;
    bool cpuScalingEnabled;
    QString libraryBuildType;
};

QDebug operator<< (QDebug d, const Context &ctx);

#endif // CONTEXT_H
