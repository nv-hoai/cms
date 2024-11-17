#ifndef CUSTOMERFILTERMODEL_H
#define CUSTOMERFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "CustomerModel.h"

class CustomerFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
public:
    explicit CustomerFilterModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    QString filterText() const;
    void setFilterText(const QString &text);

signals:
    void filterTextChanged();

private:
    QString m_filterText;
};

#endif // CUSTOMERFILTERMODEL_H
