#include "hirecomputer.h"
#include <cmath>

HireComputer::HireComputer(QObject *parent)
    : Service(parent), m_computer(nullptr), m_timeUsed(0)
{}

int HireComputer::timeUsed() const
{
    return m_timeUsed;
}

void HireComputer::setTimeUsed(int newTimeUsed)
{
    if (m_timeUsed == newTimeUsed)
        return;
    m_timeUsed = newTimeUsed;
    emit timeUsedChanged();
}

Computer *HireComputer::computer() const
{
    return m_computer;
}

void HireComputer::setComputer(Computer *newComputer)
{
    if (m_computer == newComputer)
        return;
    m_computer = newComputer;
    emit computerChanged();
}

int HireComputer::totalCost() const
{
    return ceil((cost()*(m_timeUsed/3600)));
}
