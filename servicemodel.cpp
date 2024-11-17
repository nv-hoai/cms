#include "servicemodel.h"

ServiceModel::ServiceModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ServiceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_serviceList.getSize();
}

QVariant ServiceModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_serviceList.getSize()) {
        Service* sv = m_serviceList[index.row()];
        HireComputer* hc;
        OrderFood* of;
        if (sv->serviceName() == "Hire computer")
            hc = static_cast<HireComputer*>(sv);
        else
            of = static_cast<OrderFood*>(sv);

        switch((Role)role) {
        case IdRole:
            return sv->id();
        case ServiceNameRole:
            return sv->serviceName();
        case CostRole:
            return sv->cost();
        case StatusRole:
            return sv->status();
        case CustomerRole:
            return QVariant::fromValue(sv->customer());
        case ComputerRole:
            return QVariant::fromValue(hc->computer());
        case TimeUseRole:
            return hc->timeUse();
        case FoodRole:
            return QVariant::fromValue(of->food());
        case NumberOrderedRole:
            return of->numberOrdered();
        }
    }

    return QVariant(0);
}

bool ServiceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (m_serviceList.getSize() == 0)
        return false;
    Service* sv = m_serviceList[index.row()];
    HireComputer* hc;
    OrderFood* of;
    if (sv->serviceName() == "Hire computer")
        hc = static_cast<HireComputer*>(sv);
    else
        of = static_cast<OrderFood*>(sv);
    QVariant previousValue;

    switch((Role)role) {
    case IdRole:
        //never happen
        break;
    case ServiceNameRole:
        previousValue = sv->serviceName();
        sv->setServiceName(value.toString());
        break;
    case CustomerRole:
        previousValue = QVariant::fromValue(sv->customer());
        sv->setCustomer(value.value<Customer*>());
        break;
    case CostRole:
        previousValue = sv->cost();
        sv->setCost(value.toInt());
        break;
    case StatusRole:
        previousValue = sv->status();
        sv->setStatus(value.toBool());
        break;
    case ComputerRole:
        previousValue = QVariant::fromValue(hc->computer());
        hc->setComputer(value.value<Computer*>());
        break;
    case TimeUseRole:
        previousValue = hc->timeUse();
        hc->setTimeUse(value.toInt());
        break;
    case FoodRole:
        previousValue = QVariant::fromValue(of->food());
        of->setFood(value.value<Food*>());
        break;
    case NumberOrderedRole:
        previousValue = of->numberOrdered();
        of->setNumberOrdered(value.toInt());
        break;
    }

    if (data(index, role) != previousValue) {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ServiceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ServiceModel::roleNames() const
{
    QHash<int, QByteArray> result;

    result[IdRole] = "id";
    result[ServiceNameRole] = "serviceName";
    result[CustomerRole] = "customer";
    result[ComputerRole] = "computer";
    result[TimeUseRole] = "timeUse";
    result[FoodRole] = "food";
    result[NumberOrderedRole] = "numberOrdered";
    result[StatusRole] = "status";
    result[CostRole] = "cost";

    return result;
}

DoubleLinkedList<Service *> &ServiceModel::getServiceList()
{
    return m_serviceList;
}

Service *ServiceModel::getService(const int &id)
{
    for(auto it=m_serviceList.begin(); it!=m_serviceList.end(); ++it) {
        if (id == (*it)->id())
            return (*it);
    }
    return nullptr;
}

int ServiceModel::getIndexById(const int &id)
{
    int index = 0;
    for(auto it=m_serviceList.begin(); it!=m_serviceList.end(); ++it) {
        if (id == (*it)->id())
            return index;
        index++;
    }
    return 0;
}

void ServiceModel::saveServiceData(const char *path)
{

}

void ServiceModel::addHireComputer(const QString &serviceName, Customer* customer, Computer* computer, const int &timeUse, const int& status)
{
    beginInsertRows(QModelIndex(), m_serviceList.getSize(), m_serviceList.getSize());
    HireComputer* hc = new HireComputer(this);
    hc->setServiceName(serviceName);
    hc->setStatus(status);
    hc->setCustomer(customer);
    hc->setComputer(computer);
    hc->setTimeUse(timeUse);
    hc->setCost(computer->cost());
    m_serviceList.append(hc);
    endInsertRows();
}

void ServiceModel::addOrderFood(const QString &serviceName, Customer* customer, Food* food, const int &numberOredered, const int& status)
{
    beginInsertRows(QModelIndex(), m_serviceList.getSize(), m_serviceList.getSize());
    OrderFood* of = new OrderFood(this);
    of->setServiceName(serviceName);
    of->setStatus(status);
    of->setCustomer(customer);
    of->setFood(food);
    of->setNumberOrdered(numberOredered);
    of->setCost(food->cost());
    m_serviceList.append(of);
    endInsertRows();
}

void ServiceModel::remove(const int &index)
{
    if (index >= 0 && index < m_serviceList.getSize()) {
        beginRemoveRows(QModelIndex(), index, index);
        Service* toRemove = m_serviceList[index];
        m_serviceList.remove(toRemove);
        toRemove->deleteLater();
        endRemoveRows();
    }
}

void ServiceModel::setServiceName(const int &index, const QString &serviceName)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, serviceName, ServiceNameRole);
}

void ServiceModel::setCustomer(const int &index, Customer* customer)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, QVariant::fromValue(customer), CustomerRole);
}

void ServiceModel::setComputer(const int &index, Computer* computer)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, QVariant::fromValue(computer), ComputerRole);
}

void ServiceModel::setTimeUse(const int &index, const int &timeUse)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, timeUse, TimeUseRole);
}

void ServiceModel::setFood(const int &index, Food* food)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, QVariant::fromValue(food), FoodRole);
}

void ServiceModel::setNumberOrdered(const int &index, const int &numberOrdered)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, numberOrdered, NumberOrderedRole);
}

void ServiceModel::setStatus(const int &index, const bool &status)
{
    QModelIndex modelIndex = createIndex(index, 0);
    setData(modelIndex, status, StatusRole);
}
