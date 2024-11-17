#include "employeefiltermodel.h"

EmployeeFilterModel::EmployeeFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool EmployeeFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString idData = "ID: " + sourceModel()->data(index, EmployeeModel::IdRole).toString();
    QString firstNameData = "First name: " + sourceModel()->data(index, EmployeeModel::FirstNameRole).toString();
    QString lastNameData = "Last name: " + sourceModel()->data(index, EmployeeModel::LastNameRole).toString();
    QString ageData = "Age: " + sourceModel()->data(index, EmployeeModel::AgeRole).toString();
    bool gender = sourceModel()->data(index, EmployeeModel::GenderRole).toBool();
    QString genderData = "Gender: ";
    genderData.append(((gender)?"Male":"Female"));
    QString positionData = "Position: " + sourceModel()->data(index, EmployeeModel::PositionRole).toString();
    QString workedDaysData = "Worked days: " + sourceModel()->data(index, EmployeeModel::WorkedDaysRole).toString();
    QString timeWorkData = "Time work: " + sourceModel()->data(index, EmployeeModel::TimeWorkRole).toString();
    QString baseSalaryData = "Base salary: " + sourceModel()->data(index, EmployeeModel::BaseSalaryRole).toString();

    if (idData.contains(filterRegularExpression()) ||
        firstNameData.contains(filterRegularExpression()) ||
        lastNameData.contains(filterRegularExpression()) ||
        ageData.contains(filterRegularExpression()) ||
        genderData.contains(filterRegularExpression()) ||
        positionData.contains(filterRegularExpression()) ||
        workedDaysData.contains(filterRegularExpression()) ||
        timeWorkData.contains(filterRegularExpression()) ||
        baseSalaryData.contains(filterRegularExpression())) {
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
