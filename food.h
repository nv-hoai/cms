#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QQmlEngine>

class Food : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int  remain READ remain WRITE setRemain NOTIFY remainChanged)
    Q_PROPERTY(int cost READ cost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged FINAL)
public:
    explicit Food(QObject *parent = nullptr);

    int cost() const;
    void setCost(int newCost);

    int remain() const;
    void setRemain(int newRemain);

    QString name() const;
    void setName(const QString &newName);

    int id() const;

    QString imageSource() const;
    void setImageSource(const QString &newImageSource);

signals:
    void costChanged();
    void remainChanged();
    void nameChanged();
    void imageSourceChanged();

private:
    double m_cost;
    int m_remain;
    QString m_name;
    int m_id;
    QString m_imageSource;

    static int foodCount;
};

#endif // FOOD_H
