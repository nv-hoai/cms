#include "hirecomputer.h"
#include <cmath>

HireComputer::HireComputer(QObject *parent)
    : Service(parent), m_computer(nullptr)
{}

int HireComputer::timeUse() const
{
    return m_timeUse;
}

void HireComputer::setTimeUse(int newTimeUse)
{
    if (m_timeUse == newTimeUse)
        return;
    m_timeUse = newTimeUse;
    emit timeUseChanged();
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
    return ceil((cost()*(m_timeUse/60)));
}
