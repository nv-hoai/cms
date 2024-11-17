#include "employee.h"

int Employee::employeeCount = 1;

Employee::Employee(QObject *parent)
    : Human(parent)
{
    m_id = employeeCount++;
}

int Employee::id() const
{
    return m_id;
}

QString Employee::position() const
{
    return m_position;
}

void Employee::setPosition(const QString &newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}

int Employee::baseSalary() const
{
    return m_baseSalary;
}

void Employee::setBaseSalary(int newBaseSalary)
{
    if (m_baseSalary ==  newBaseSalary)
        return;
    m_baseSalary = newBaseSalary;
    emit baseSalaryChanged();
}


int Employee::workedDays() const
{
    return m_workedDays;
}

void Employee::setWorkedDays(int newWorkedDays)
{
    if (m_workedDays == newWorkedDays)
        return;
    m_workedDays = newWorkedDays;
    emit workedDaysChanged();
}

QString Employee::timeWork() const
{
    return m_timeWork;
}

void Employee::setTimeWork(const QString &newTimeWork)
{
    if (m_timeWork == newTimeWork)
        return;
    m_timeWork = newTimeWork;
    emit timeWorkChange();
}
