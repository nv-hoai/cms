#include "servicefiltermodel.h"

ServiceFilterModel::ServiceFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool ServiceFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString idData = "ID: " + sourceModel()->data(index, ServiceModel::IdRole).toString();
    QString serviceName = sourceModel()->data(index, ServiceModel::ServiceNameRole).toString();
    QString serviceNameData = "Service name: " + serviceName;
    Customer* customer = sourceModel()->data(index, ServiceModel::CustomerRole).value<Customer*>();
    QString customerIdData = "Customer's ID: " + QString::number(customer->id());
    QString customerNameData = "Customer's name: " + customer->firstName() + " " + customer->lastName();
    QString computerIdData, timeUseData;
    computerIdData = timeUseData = "";
    if (serviceName == "Hire computer") {
        Computer* computer = sourceModel()->data(index, ServiceModel::ComputerRole).value<Computer*>();
        computerIdData = "Computer's ID: " + QString::number(computer->id());
        timeUseData = "Time use: " + sourceModel()->data(index, ServiceModel::TimeUseRole).toString();
    }
    QString foodNameData, numberOrderedData;
    foodNameData = numberOrderedData = "";
    if (serviceName == "Order food") {
        Food* food = sourceModel()->data(index, ServiceModel::FoodRole).value<Food*>();
        foodNameData = "Food's name: " + food->name();
        numberOrderedData = "Number ordered: " + sourceModel()->data(index, ServiceModel::NumberOrderedRole).toString();
    }

    if (idData.contains(filterRegularExpression()) ||
        serviceNameData.contains(filterRegularExpression()) ||
        customerIdData.contains(filterRegularExpression()) ||
        customerNameData.contains(filterRegularExpression()) ||
        computerIdData.contains(filterRegularExpression()) ||
        timeUseData.contains(filterRegularExpression()) ||
        foodNameData.contains(filterRegularExpression()) ||
        numberOrderedData.contains(filterRegularExpression())) {
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
