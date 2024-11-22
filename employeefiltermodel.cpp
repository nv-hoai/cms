#include "employeefiltermodel.h"

EmployeeFilterModel::EmployeeFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool EmployeeFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString data = "ID: " + sourceModel()->data(index, EmployeeModel::IdRole).toString();
    data += " First name: " + sourceModel()->data(index, EmployeeModel::FirstNameRole).toString();
    data += " Last name: " + sourceModel()->data(index, EmployeeModel::LastNameRole).toString();
    data += " Age: " + sourceModel()->data(index, EmployeeModel::AgeRole).toString();
    bool gender = sourceModel()->data(index, EmployeeModel::GenderRole).toBool();
    data += " Gender: ";
    data.append(((gender)?"Male":"Female"));
    data += " Position: " + sourceModel()->data(index, EmployeeModel::PositionRole).toString();
    data += " Worked days: " + sourceModel()->data(index, EmployeeModel::WorkedDaysRole).toString();
    data += " Time work: " + sourceModel()->data(index, EmployeeModel::TimeWorkRole).toString();
    data += " Base salary: " + sourceModel()->data(index, EmployeeModel::BaseSalaryRole).toString();

    if (data.contains(filterRegularExpression())) {
        return true;
    }

    return false;
}

QString EmployeeFilterModel::filterText() const {
    return m_filterText;
}

void EmployeeFilterModel::setFilterText(const QString &text) {
    if (m_filterText != text) {
        m_filterText = text;
        setFilterRegularExpression(text);
        emit filterTextChanged();
    }
}
