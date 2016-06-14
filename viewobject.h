#ifndef VIEWOBJECT_H
#define VIEWOBJECT_H

#include <QObject>

class ViewObject : public QObject
{
    Q_OBJECT
public:
    explicit ViewObject(QObject *parent = 0);

signals:

public slots:
};

#endif // VIEWOBJECT_H