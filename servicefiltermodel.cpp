#include "servicefiltermodel.h"

ServiceFilterModel::ServiceFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool ServiceFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString data = "ID: " + sourceModel()->data(index, ServiceModel::IdRole).toString();
    QString serviceName = sourceModel()->data(index, ServiceModel::ServiceNameRole).toString();
    data += " Service name: " + serviceName;
    Customer* customer = sourceModel()->data(index, ServiceModel::CustomerRole).value<Customer*>();
    data += " Customer's ID: " + QString::number(customer->id());
    data += " Customer's name: " + customer->firstName() + " " + customer->lastName();
    if (serviceName == "Hire computer") {
        Computer* computer = sourceModel()->data(index, ServiceModel::ComputerRole).value<Computer*>();
        data += " Computer's ID: " + QString::number(computer->id());
        data += " Time used: " + sourceModel()->data(index, ServiceModel::TimeUsedRole).toString();
    }
    if (serviceName == " Order food") {
        Food* food = sourceModel()->data(index, ServiceModel::FoodRole).value<Food*>();
        data += " Food's name: " + food->name();
        data += " Number ordered: " + sourceModel()->data(index, ServiceModel::NumberOrderedRole).toString();
    }

    bool status = sourceModel()->data(index, ServiceModel::StatusRole).toBool();
    data += " Status: ";
    data.append(((status)?"Confirmed":"Unconfirmed"));

    if (data.contains(filterRegularExpression())) {
        return true;
    }

    return false;
}

QString ServiceFilterModel::filterText() const {
    return m_filterText;
}

void ServiceFilterModel::setFilterText(const QString &text) {
    if (m_filterText != text) {
        m_filterText = text;
        setFilterRegularExpression(text);
        emit filterTextChanged();
    }
}
