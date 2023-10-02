#ifndef BUTTONS_H
#define BUTTONS_H

#include <QToolButton>

class Buttons : public QToolButton
{
    Q_OBJECT
public:
    explicit Buttons(const QString &text,QWidget *parent = nullptr);

    QSize sizeHint() const;
};

#endif // BUTTONS_H
