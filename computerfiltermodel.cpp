#include "ComputerFilterModel.h"
#include <QRegularExpression>

ComputerFilterModel::ComputerFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool ComputerFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString data = "ID: " + sourceModel()->data(index, ComputerModel::IdRole).toString();
    data += " CPU: " + sourceModel()->data(index, ComputerModel::CpuRole).toString();
    data += " RAM: " + sourceModel()->data(index, ComputerModel::RamRole).toString();
    data += " Position: " + sourceModel()->data(index, ComputerModel::PositionRole).toString();
    int status = sourceModel()->data(index, ComputerModel::StatusRole).toInt();
    data += " Status: ";
    data.append(((status == 1)?"Busy":(status == 0)?"Idle":(status==2)?"Being registered":"Cracked"));
    data += " Cost per hour: " + sourceModel()->data(index, ComputerModel::CostRole).toString();

    if (data.contains(filterRegularExpression())) {
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
        QRegularExpression regex(text, QRegularExpression::CaseInsensitiveOption);
        setFilterRegularExpression(regex);
        emit filterTextChanged();
    }
}
