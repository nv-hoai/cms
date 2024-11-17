#include "ComputerFilterModel.h"

ComputerFilterModel::ComputerFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool ComputerFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString idData = "ID: " + sourceModel()->data(index, ComputerModel::IdRole).toString();
    QString cpuData = "CPU: " + sourceModel()->data(index, ComputerModel::CpuRole).toString();
    QString ramData = "RAM: " + sourceModel()->data(index, ComputerModel::RamRole).toString();
    QString positionData = "Position: " + sourceModel()->data(index, ComputerModel::PositionRole).toString();
    int status = sourceModel()->data(index, ComputerModel::StatusRole).toInt();
    QString statusData = "Status: ";
    statusData.append(((status == 1)?"Busy":(status == 0)?"Idle":"Cracked"));
    QString costData = "Cost per hour: " + sourceModel()->data(index, ComputerModel::CostRole).toString();

    if (idData.contains(filterRegularExpression()) ||
        cpuData.contains(filterRegularExpression()) ||
        ramData.contains(filterRegularExpression()) ||
        positionData.contains(filterRegularExpression()) ||
        statusData.contains(filterRegularExpression()) ||
        costData.contains(filterRegularExpression())) {
        return true;
    }

    return false;
}

QString ComputerFilterModel::filterText() const {
    return m_filterText;
}

void ComputerFilterModel::setFilterText(const QString &text) {
    if (m_filterText != text) {
        m_filterText = text;
        setFilterRegularExpression(text);
        emit filterTextChanged();
    }
}
