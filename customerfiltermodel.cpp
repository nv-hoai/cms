#include "customerfiltermodel.h"

CustomerFilterModel::CustomerFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool CustomerFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString data = "ID: " + sourceModel()->data(index, CustomerModel::IdRole).toString();
    data += " First name: " + sourceModel()->data(index, CustomerModel::FirstNameRole).toString();
    data += " Last name: " + sourceModel()->data(index, CustomerModel::LastNameRole).toString();
    data += " Age: " + sourceModel()->data(index, CustomerModel::AgeRole).toString();
    bool gender = sourceModel()->data(index, CustomerModel::GenderRole).toBool();
    data += " Gender: ";
    data.append(((gender)?"Male":"Female"));
    int status = sourceModel()->data(index, CustomerModel::StatusRole).toInt();
    data += " Status: ";
    data.append(((!status)?"Not using any service":(status==1)?"Using service":"Registering"));

    if (data.contains(filterRegularExpression())) {
        return true;
    }

    return false;
}

QString CustomerFilterModel::filterText() const {
    return m_filterText;
}

void CustomerFilterModel::setFilterText(const QString &text) {
    if (m_filterText != text) {
        m_filterText = text;
        setFilterRegularExpression(text);
        emit filterTextChanged();
    }
}
