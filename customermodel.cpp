#include <QFile>
#include <QTextStream>
#include "customermodel.h"

CustomerModel::CustomerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int CustomerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_customerList.getSize();
}

QVariant CustomerModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_customerList.getSize()) {
        Customer* customer = m_customerList[index.row()];

        switch((Role)role) {
        case IdRole:
            return customer->id();
        case FirstNameRole:
            return customer->firstName();
        case LastNameRole:
            return customer->lastName();
        case AgeRole:
            return customer->age();
        case GenderRole:
            return customer->gender();
        case StatusRole:
            return customer->status();
        }
    }

    return {};
}

bool CustomerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (m_customerList.getSize() == 0)
        return false;

    Customer* customer = m_customerList[index.row()];
    QVariant previousValue;

    switch((Role)role) {
    case IdRole:
        //never happen
        break;
    case FirstNameRole:
        previousValue = customer->firstName();
        customer->setFirstName(value.toString());
        break;
    case LastNameRole:
        previousValue = customer->lastName();
        customer->setLastName(value.toString());
        break;
    case AgeRole:
        previousValue = customer->age();
        customer->setAge(value.toInt());
        break;
    case GenderRole:
        previousValue = customer->gender();
        customer->setGender(value.toBool());
        break;
    case StatusRole:
        previousValue = customer->status();
        customer->setStatus(value.toInt());
        break;
    }

    if (data(index, role) != previousValue) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags CustomerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> CustomerModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[IdRole] = "id";
    result[FirstNameRole] = "firstName";
    result[LastNameRole] = "lastName";
    result[AgeRole] = "age";
    result[GenderRole] = "gender";
    result[StatusRole] = "status";

    return result;
}

Customer *CustomerModel::getCustomer(const int &id)
{
    for(auto it=m_customerList.begin(); it!=m_customerList.end(); ++it) {
        if (id == (*it)->id())
            return (*it);
    }
    return nullptr;
}

int CustomerModel::getIndexById(const int &id)
{
    int index = 0;
    for(auto it=m_customerList.begin(); it!=m_customerList.end(); ++it) {
        if (id == (*it)->id())
            return index;
        index++;
    }
    return 0;
}

void CustomerModel::saveCustomerData(const char *path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: " << file.errorString().toStdString() << std::endl;
        return;
    }

    QTextStream out(&file);
    for (auto it=m_customerList.begin(); it!=m_customerList.end(); ++it) {
        out << (*it)->firstName() << ";";
        out << (*it)->lastName() << ";";
        out << (*it)->age() << ";";
        out << int((*it)->gender()); Qt::endl(out);
    }

    file.close();
}

void CustomerModel::add(const QString& firstName, const QString& lastName, const int& age, const bool& gender)
{
    beginInsertRows(QModelIndex(), m_customerList.getSize(), m_customerList.getSize());
    Customer* customer = new Customer(this);
    customer->setFirstName(firstName);
    customer->setLastName(lastName);
    customer->setAge(age);
    customer->setGender(gender);
    m_customerList.append(customer);
    endInsertRows();
}

void CustomerModel::remove(const int &index)
{
    if (index >= 0 && index < m_customerList.getSize()) {
        beginRemoveRows(QModelIndex(), index, index);
        Customer* toRemove = m_customerList[index];
        m_customerList.remove(toRemove);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

void CustomerModel::setCustomerFirstName(const int &index, const QString &firstName)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, firstName, FirstNameRole);
}

void CustomerModel::setCustomerLastName(const int &index, const QString &lastName)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, lastName, LastNameRole);
}

void CustomerModel::setCustomerAge(const int &index, const int &age)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, age, AgeRole);
}

void CustomerModel::setCustomerGender(const int &index, const bool &gender)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, gender, GenderRole);
}

void CustomerModel::setStatus(const int &index, const int &status)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, status, StatusRole);
}
