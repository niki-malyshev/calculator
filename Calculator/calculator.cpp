#include "calculator.h"

#include <QGridLayout>
#include <QToolButton>
#include <buttons.h>
#include <QDebug>
#include <QtMath>
#include <QDialog>
#include <QStyle>

Calculator::Calculator()
    :m_sum_in_memory(0.0), sumSoFar(0.0)
{
    m_display_up = new QLineEdit();
    m_display_down = new QLineEdit();
    m_sign = new QLabel();
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    m_display_down->setText("0");

    m_sign->setAlignment(Qt::AlignRight);

    m_display_up->setReadOnly(true);
    m_display_down->setReadOnly(true);

    m_display_up->setAlignment(Qt::AlignRight);
    m_display_down->setAlignment(Qt::AlignRight);

    m_display_up->setMaxLength(15);
    m_display_down->setMaxLength(15);

    QFont font = m_display_up->font();
    font.setPixelSize(font.pointSize()+10);
    m_display_up->setFont(font);
    m_display_down->setFont(font);
    m_sign->setFont(font);

    for (int i = 0; i < 10; ++i) {
        m_digitButtons[i] = createButtons(QString::number(i),    SLOT(digitClicked()));
        m_digitButtons[i]->setStyleSheet("color: white; background-color: rgb(0,0,0)");
    }

    Buttons *pointButton = createButtons(".",                    SLOT(pointClicked()));
    Buttons *changeSignButton = createButtons(m_change_sign,     SLOT(changeSignClicked()));

    Buttons *backspaceButton = createButtons("Backspace->",      SLOT(backspaceClicked()));
    Buttons *clearButton = createButtons("Clear",                SLOT(clear()));
    Buttons *clearAllButton = createButtons("Clear All",         SLOT(clearAll()));

    Buttons *clearMemoryButton = createButtons("MC",             SLOT(clearMemory()));
    Buttons *readMemoryButton = createButtons("MR",              SLOT(readMemory()));
    Buttons *setToMemoryButton = createButtons("M+",             SLOT(addToMemory()));
    Buttons *addMemoryButton = createButtons("M-",               SLOT(minMemory()));

    Buttons *divisionButton = createButtons(m_division_sign,     SLOT(doubleOperandClicked()));
    Buttons *timesButton = createButtons(m_times_sign,           SLOT(doubleOperandClicked()));
    Buttons *minusButton = createButtons(m_minus_sign,           SLOT(doubleOperandClicked()));
    Buttons *plusButton = createButtons(m_plus_sign,             SLOT(doubleOperandClicked()));

    Buttons *squareRootButton = createButtons(m_squareRoot_sign, SLOT(unaryOperatorClicked()));
    Buttons *powerButton = createButtons(m_power_sign,           SLOT(unaryOperatorClicked()));
    Buttons *reciprocalButton = createButtons(m_reciprocal_sign, SLOT(unaryOperatorClicked()));
    Buttons *equalButton = createButtons("=",                    SLOT(equalClicked()));
    Buttons *percentButton = createButtons(m_percent_sign,             SLOT(doubleOperandClicked()));

    pointButton->setStyleSheet("color: white; background-color: rgb(0,0,0)");
    changeSignButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    backspaceButton->setStyleSheet("color: white; background-color: rgb(70,70,70)");
    clearButton->setStyleSheet("color: white; background-color: rgb(70,70,70)");
    clearAllButton->setStyleSheet("color: white; background-color: rgb(70,70,70)");
    clearMemoryButton->setStyleSheet("color: white; background-color: rgb(87, 139, 189)");
    readMemoryButton->setStyleSheet("color: white; background-color: rgb(87, 139, 189)");
    setToMemoryButton->setStyleSheet("color: white; background-color: rgb(87, 139, 189)");
    addMemoryButton->setStyleSheet("color: white; background-color: rgb(87, 139, 189)");
    divisionButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    timesButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    minusButton->setStyleSheet("color: white; background-color:rgb(45, 74, 52)");
    plusButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    squareRootButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    powerButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    reciprocalButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    equalButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");
    percentButton->setStyleSheet("color: white; background-color: rgb(45, 74, 52)");

    mainLayout->addWidget(m_display_up,   0, 0, 1, 6);
    mainLayout->addWidget(m_sign,         1, 5, 1, 1);
    mainLayout->addWidget(m_display_down, 2, 0, 1, 6);

    mainLayout->addWidget(backspaceButton,  3, 0);
    mainLayout->addWidget(clearButton,      4, 0);
    mainLayout->addWidget(clearAllButton,   5, 0);

    mainLayout->addWidget(clearMemoryButton, 3, 1);
    mainLayout->addWidget(readMemoryButton,  3, 2);
    mainLayout->addWidget(addMemoryButton,   3, 3);
    mainLayout->addWidget(setToMemoryButton, 3, 4);

    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(m_digitButtons[i], row, column);
    }

    mainLayout->addWidget(m_digitButtons[0], 7, 1);
    mainLayout->addWidget(pointButton,       7, 2);
    mainLayout->addWidget(changeSignButton,  7, 3);

    mainLayout->addWidget(divisionButton,    4, 4);
    mainLayout->addWidget(timesButton,       5, 4);
    mainLayout->addWidget(minusButton,       6, 4);
    mainLayout->addWidget(plusButton,        7, 4);

    mainLayout->addWidget(squareRootButton,  3, 5);
    mainLayout->addWidget(powerButton,       4, 5);
    mainLayout->addWidget(reciprocalButton,  5, 5);
    mainLayout->addWidget(equalButton,       7, 5);
    mainLayout->addWidget(percentButton,     6, 5);

    setLayout(mainLayout);

    setWindowTitle("Калькулятор");

}


Buttons *Calculator::createButtons(const QString &text, const char *member)
{
    Buttons* btn = new Buttons(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;

}

void Calculator :: digitClicked(){
    Buttons*  btn = (Buttons*) sender();
    int digit = btn -> text().toUInt();

    if(m_display_down->text()=="0"){
        m_display_down->clear();
        m_display_up->clear();
    }

    m_display_down->setText(m_display_down->text() + QString::number(digit));
}

void Calculator :: unaryOperatorClicked(){
    Buttons*  btn = (Buttons*) sender();
    QString operation = btn -> text();

    double operand = m_display_down->text().toDouble();
    double result = 0.0;

    if (operation == m_squareRoot_sign) {
             if (operand < 0.0) {
                 abortOperation();
                 return;
             }
             result = std :: sqrt(operand);
         } else if (operation == m_power_sign) {
             result = std::pow(operand, 2.0);
         } else if (operation == m_reciprocal_sign) {
             if (operand == 0.0) {
                 abortOperation();
                 return;
             }
             result = 1.0 / operand;
         }
         m_display_down->setText(QString::number(result));

}

void Calculator :: doubleOperandClicked(){
    Buttons*  btn = (Buttons*) sender();
    QString operation = btn -> text();

    double operand = m_display_down->text().toDouble();

    if(m_display_down->text()=="0")
        return;

    m_sign->setText(operation);

    if(m_display_down->text()== "")
        return;

    m_display_down->clear();

    if (!m_pending_operation.isEmpty()) {
        if(!calculate(operand, m_pending_operation)){
            abortOperation();
            return;
        }
        m_pending_operation.clear();

    }else{
        m_display_up->setText(QString::number(operand));
    }

    m_pending_operation = operation;


}


void Calculator :: equalClicked(){
    double operand = m_display_down->text().toDouble();

    if (!m_pending_operation.isEmpty()) {
        if (!calculate(operand, m_pending_operation)) {
            abortOperation();
            return;
        }
        m_pending_operation.clear();
         }

    m_display_down->setText(m_display_up->text());
    m_display_up->clear();
    m_sign->clear();
}

void Calculator :: pointClicked(){
    if(!m_display_down->text().contains('.')){
        m_display_down->setText(m_display_down->text()+'.');
    }
}

void Calculator :: changeSignClicked(){
    QString text = m_display_down->text();
    double val = text.toDouble();

    if (val>0.0){
        text.prepend("-");
    }else if (val<0.0){
        text.remove(0, 1);
    }
    m_display_down->setText(text);
}

void Calculator :: backspaceClicked(){
    QString text = m_display_down->text();
    text.chop(1);

    if(text.isEmpty())
        text = "0";

    m_display_down->setText(text);
}

void Calculator :: clear(){
    m_display_down->setText("0");
}

void Calculator :: clearAll(){
    m_display_down->setText("0");
    m_display_up->setText("0");
}

void Calculator :: clearMemory(){
    m_sum_in_memory = 0.0;
}

void Calculator :: readMemory(){
    m_display_up->clear();
    m_sign->clear();
    m_display_down->setText(QString::number(m_sum_in_memory));
}

void Calculator :: minMemory(){
    equalClicked();
    m_sum_in_memory -= m_display_down->text().toDouble();
}

void Calculator :: addToMemory(){
    equalClicked();
    m_sum_in_memory += m_display_down->text().toDouble();
}

void Calculator ::  abortOperation(){
    m_display_up->setText("Error");
    m_display_down->setText("Error");
}

bool Calculator::calculate(double operand, const QString &operation)
{
    double temp_total = m_display_up->text().toDouble();


    if (operation == m_plus_sign){
        temp_total += operand;
    } else if (operation == m_minus_sign){
        temp_total -= operand;
    } else if (operation == m_times_sign){
        temp_total *= operand;
    } else if (operation == m_division_sign){
        if(operand == 0.0)
            return false;
        temp_total /= operand;
    }else if(operation == m_percent_sign){
        temp_total = temp_total * (operand / 100.0);
   }

    m_display_up->setText(QString::number(temp_total));
    return true;
}


