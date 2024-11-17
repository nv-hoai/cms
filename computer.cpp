#include "computer.h"

int Computer::computerCount = 1;


Computer::Computer(QObject *parent):
    QObject{parent}
{
    m_id = computerCount++;
}

int Computer::ram() const
{
    return m_ram;
}

void Computer::setRam(int newRam)
{
    if (m_ram == newRam)
        return;
    m_ram = newRam;
    emit ramChanged();
}

QString Computer::cpu() const
{
    return m_cpu;
}

void Computer::setCpu(const QString &newCpu)
{
    if (m_cpu == newCpu)
        return;
    m_cpu = newCpu;
    emit cpuChanged();
}

int Computer::position() const
{
    return m_position;
}

void Computer::setPosition(int newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}

int Computer::cost() const
{
    return m_cost;
}

void Computer::setCost(int newCost)
{
    if (m_cost == newCost)
        return;
    m_cost = newCost;
    emit costChanged();
}

int Computer::status() const
{
    return m_status;
}

void Computer::setStatus(int newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

int Computer::id() const
{
    return m_id;
}
