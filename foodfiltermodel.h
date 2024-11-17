#ifndef FOODFILTERMODEL_H
#define FOODFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "FoodModel.h"

class FoodFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
public:
    explicit FoodFilterModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    QString filterText() const;
    void setFilterText(const QString &text);

signals:
    void filterTextChanged();

private:
    QString m_filterText;
};

#endif // FOODFILTERMODEL_H
