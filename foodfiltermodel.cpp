#include "foodfiltermodel.h"

FoodFilterModel::FoodFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool FoodFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString data = "ID: " + sourceModel()->data(index, FoodModel::IdRole).toString();
    data += " Name: " + sourceModel()->data(index, FoodModel::NameRole).toString();
    data += " Remain: " + sourceModel()->data(index, FoodModel::RemainRole).toString();
    data += " Cost: " + sourceModel()->data(index, FoodModel::CostRole).toString();

    if (data.contains(filterRegularExpression())) {
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
