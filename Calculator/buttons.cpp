#include "buttons.h"

Buttons::Buttons(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    setText(text);
}

QSize Buttons::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
