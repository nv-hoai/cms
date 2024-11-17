#ifndef SERVICEFILTERMODEL_H
#define SERVICEFILTERMODEL_H

#include <QSortFilterProxyModel>
#include "ServiceModel.h"

class ServiceFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
public:
    explicit ServiceFilterModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    QString filterText() const;
    void setFilterText(const QString &text);

signals:
    void filterTextChanged();

private:
    QString m_filterText;
};

#endif // SERVICEFILTERMODEL_H
