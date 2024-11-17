#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QQmlEngine>
#include "human.h"

class Employee : public Human
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString timeWork READ timeWork WRITE setTimeWork NOTIFY timeWorkChange)
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int workedDays READ workedDays WRITE setWorkedDays NOTIFY workedDaysChanged)
    Q_PROPERTY(int baseSalary READ baseSalary WRITE setBaseSalary NOTIFY baseSalaryChanged)
public:
    explicit Employee(QObject *parent = nullptr);

    int id() const;

    QString position() const;
    void setPosition(const QString &newPosition);

    int baseSalary() const;
    void setBaseSalary(int newBaseSalary);

    int workedDays() const;
    void setWorkedDays(int newWorkedDays);

    QString timeWork() const;
    void setTimeWork(const QString &newTimeWork);

signals:
    void positionChanged();
    void baseSalaryChanged();
    void workedDaysChanged();

    void timeWorkChange();

private:
    int m_id;
    QString m_position;
    int m_baseSalary;

    static int employeeCount;
    int m_workedDays;
    QString m_timeWork;
};

#endif // EMPLOYEE_H
