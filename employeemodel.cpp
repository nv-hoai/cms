#include <QFile>
#include <QTextStream>
#include "employeemodel.h"

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int EmployeeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_employeeList.getSize();
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_employeeList.getSize()) {
        Employee* employee = m_employeeList[index.row()];

        switch((Role)role) {
        case IdRole:
            return employee->id();
        case FirstNameRole:
            return employee->firstName();
        case LastNameRole:
            return employee->lastName();
        case AgeRole:
            return employee->age();
        case GenderRole:
            return employee->gender();
        case PositionRole:
            return employee->position();
        case WorkedDaysRole:
            return employee->workedDays();
        case TimeWorkRole:
            return employee->timeWork();
        case BaseSalaryRole:
            return employee->baseSalary();
        }
    }

    return {};
}

bool EmployeeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (m_employeeList.getSize() == 0)
        return false;

    Employee* employee = m_employeeList[index.row()];
    QVariant previousValue;

    switch((Role)role) {
    case IdRole:
        //never happen
        break;
    case FirstNameRole:
        previousValue = employee->firstName();
        employee->setFirstName(value.toString());
        break;
    case LastNameRole:
        previousValue = employee->lastName();
        employee->setLastName(value.toString());
        break;
    case AgeRole:
        previousValue = employee->age();
        employee->setAge(value.toInt());
        break;
    case GenderRole:
        previousValue = employee->gender();
        employee->setGender(value.toBool());
        break;
    case PositionRole:
        previousValue = employee->position();
        employee->setPosition(value.toString());
        break;
    case WorkedDaysRole:
        previousValue = employee->workedDays();
        employee->setWorkedDays(value.toInt());
        break;
    case TimeWorkRole:
        previousValue = employee->timeWork();
        employee->setTimeWork(value.toString());
        break;
    case BaseSalaryRole:
        previousValue = employee->baseSalary();
        employee->setBaseSalary(value.toDouble());
        break;
    }

    if (data(index, role) != previousValue) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags EmployeeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> EmployeeModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[IdRole] = "id";
    result[FirstNameRole] = "firstName";
    result[LastNameRole] = "lastName";
    result[AgeRole] = "age";
    result[GenderRole] = "gender";
    result[PositionRole] = "position";
    result[WorkedDaysRole] = "workedDays";
    result[TimeWorkRole] = "timeWork";
    result[BaseSalaryRole] = "baseSalary";

    return result;
}

void EmployeeModel::add(const QString& firstName, const QString& lastName, const int& age, const bool& gender,
                        const QString& position, const int& workedDays, const QString& timeWork, const int& baseSalary)
{
    beginInsertRows(QModelIndex(), m_employeeList.getSize(), m_employeeList.getSize());
    Employee* employee = new Employee(this);
    employee->setFirstName(firstName);
    employee->setLastName(lastName);
    employee->setAge(age);
    employee->setGender(gender);
    employee->setPosition(position);
    employee->setWorkedDays(workedDays);
    employee->setTimeWork(timeWork);
    employee->setBaseSalary(baseSalary);
    m_employeeList.append(employee);
    endInsertRows();
}

void EmployeeModel::remove(const int &index)
{
    if (index >= 0 && index < m_employeeList.getSize()) {
        beginRemoveRows(QModelIndex(), index, index);
        Employee* toRemove = m_employeeList[index];
        m_employeeList.remove(toRemove);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

void EmployeeModel::setEmployeeFirstName(const int &index, const QString &firstName)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, firstName, FirstNameRole);
}

void EmployeeModel::setEmployeeLastName(const int &index, const QString &lastName)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, lastName, LastNameRole);
}

void EmployeeModel::setEmployeeAge(const int &index, const int &age)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, age, AgeRole);
}

void EmployeeModel::setEmployeeGender(const int &index, const bool &gender)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, gender, GenderRole);
}

void EmployeeModel::setPosition(const int &index, const QString &position)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, position, PositionRole);
}

void EmployeeModel::setTimeWork(const int &index, const QString&timeWork)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, timeWork, TimeWorkRole);
}

void EmployeeModel::setWorkedDays(const int &index, const int &workedDays)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, workedDays, WorkedDaysRole);
}

void EmployeeModel::setBaseSalary(const int &index, const int &baseSalary)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, baseSalary, BaseSalaryRole);
}

int EmployeeModel::getIndexById(const int &id)
{
    int index = 0;
    for(auto it=m_employeeList.begin(); it!=m_employeeList.end(); ++it) {
        if (id == (*it)->id())
            return index;
        index++;
    }
    return 0;
}

void EmployeeModel::saveEmployeeData(const char *path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream out(&file);
    for (auto it=m_employeeList.begin(); it!=m_employeeList.end(); ++it) {
        out << (*it)->firstName() << ";";
        out << (*it)->lastName() << ";";
        out << (*it)->age() << ";";
        out << int((*it)->gender()) << ";";
        out << (*it)->position() << ";";
        out << (*it)->workedDays() << ";";
        out << (*it)->timeWork() << ";";
        out << (*it)->baseSalary(); Qt::endl(out);
    }

    file.close();
}
