#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <buttons.h>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator();

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void doubleOperandClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void minMemory();
    void addToMemory();
private:
    Buttons* createButtons(const QString& text, const char* member);
    void abortOperation();
    bool calculate(double operand, const QString& operation);

    double m_sum_in_memory;
    double sumSoFar;

    QString m_pending_operation;

    QLineEdit* m_display_up;
    QLineEdit* m_display_down;
    QLabel*    m_sign;

    Buttons* m_digitButtons[10];

    QString m_squareRoot_sign = QChar(0x221A);
    QString m_power_sign = 'x' + QChar(0x000000b2);
    QString m_reciprocal_sign = "1/x";
    QString m_division_sign = QChar(0x000000F7);
    QString m_times_sign = QChar(0x000000D7);
    QString m_plus_sign = "+";
    QString m_minus_sign = "-";
    QString m_change_sign = "+/-";
    QString m_percent_sign = "%";
    QString m_natural_logarithm_sign = "0x000033D1";

};


#endif // CALCULATOR_H
