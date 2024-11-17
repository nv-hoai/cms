#include "foodfiltermodel.h"

FoodFilterModel::FoodFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool FoodFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString idData = "ID: " + sourceModel()->data(index, FoodModel::IdRole).toString();
    QString nameData = "Name: " + sourceModel()->data(index, FoodModel::NameRole).toString();
    QString remainData = "Remain: " + sourceModel()->data(index, FoodModel::RemainRole).toString();
    QString costData = "Cost: " + sourceModel()->data(index, FoodModel::CostRole).toString();

    if (idData.contains(filterRegularExpression()) ||
        nameData.contains(filterRegularExpression()) ||
        remainData.contains(filterRegularExpression()) ||
        costData.contains(filterRegularExpression())) {
        return true;
    }

    return false;
}

QString FoodFilterModel::filterText() const {
    return m_filterText;
}

void FoodFilterModel::setFilterText(const QString &text) {
    if (m_filterText != text) {
        m_filterText = text;
        setFilterRegularExpression(text);
        emit filterTextChanged();
    }
}
