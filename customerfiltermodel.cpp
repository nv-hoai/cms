#include "customerfiltermodel.h"

CustomerFilterModel::CustomerFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool CustomerFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString idData = "ID: " + sourceModel()->data(index, CustomerModel::IdRole).toString();
    QString firstNameData = "First name: " + sourceModel()->data(index, CustomerModel::FirstNameRole).toString();
    QString lastNameData = "Last name: " + sourceModel()->data(index, CustomerModel::LastNameRole).toString();
    QString ageData = "Age: " + sourceModel()->data(index, CustomerModel::AgeRole).toString();
    bool gender = sourceModel()->data(index, CustomerModel::GenderRole).toBool();
    QString genderData = "Gender: ";
    genderData.append(((gender)?"Male":"Female"));
    int status = sourceModel()->data(index, CustomerModel::StatusRole).toInt();
    QString statusData = "Status: ";
    statusData.append(((!status)?"Not using any service":(status==1)?"Using service":"Registering"));

    if (idData.contains(filterRegularExpression()) ||
        firstNameData.contains(filterRegularExpression()) ||
        lastNameData.contains(filterRegularExpression()) ||
        ageData.contains(filterRegularExpression()) ||
        genderData.contains(filterRegularExpression()) ||
        statusData.contains(filterRegularExpression())) {
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
