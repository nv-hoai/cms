#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QAbstractListModel>
#include "doublelinkedlist.h"
#include "employee.h"

class EmployeeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole,
        FirstNameRole,
        LastNameRole,
        AgeRole,
        GenderRole,
        PositionRole,
        TimeWorkRole,
        WorkedDaysRole,
        BaseSalaryRole
    };

    explicit EmployeeModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
public slots:
    void add(const QString& firstName, const QString& lastName, const int& age, const bool& gender,
             const QString& position, const int& workedDays, const QString& timeWork, const int& baseSalary);
    void remove(const int& index);
    void setEmployeeFirstName(const int& index, const QString& firstName);
    void setEmployeeLastName(const int& index, const QString& lastName);
    void setEmployeeAge(const int& index, const int& age);
    void setEmployeeGender(const int& index, const bool& gender);
    void setPosition(const int& index, const QString& position);
    void setTimeWork(const int& index, const QString& timeWork);
    void setWorkedDays(const int& index, const int& workedDays);
    void setBaseSalary(const int& index, const int& baseSalary);

    int getIndexById(const int& id);

    void saveEmployeeData(const char* path);
private:
    DoubleLinkedList<Employee*> m_employeeList;

};

#endif // EMPLOYEEMODEL_H
