#include "context.h"


QDateTime Context::getTimestamp() const
{
    return timestamp;
}

void Context::setTimestamp(const QDateTime &value)
{
    timestamp = value;
}

int Context::getCpuFrequency() const
{
    return cpuFrequency;
}

void Context::setCpuFrequency(int value)
{
    cpuFrequency = value;
}

bool Context::getCpuScalingEnabled() const
{
    return cpuScalingEnabled;
}

void Context::setCpuScalingEnabled(bool value)
{
    cpuScalingEnabled = value;
}

QString Context::getLibraryBuildType() const
{
    return libraryBuildType;
}

void Context::setLibraryBuildType(QString value)
{
    libraryBuildType = value;
}

int Context::getCpuCount() const
{
    return cpuCount;
}

void Context::setCpuCount(int value)
{
    cpuCount = value;
}

QDebug operator<< (QDebug d, const Context &ctx)
{
    d << "timestamp: " << ctx.getTimestamp()
        << " cpu_count: " << ctx.getCpuCount()
        << " cpu_frequency: " << ctx.getCpuFrequency()
        << " cpu_scaling_enabled: " << ctx.getCpuScalingEnabled()
        << " library_build_type: " << ctx.getLibraryBuildType();
    return d;
}
