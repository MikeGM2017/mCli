/********************************************************************************
** Form generated from reading UI file 'Cli_Output_Form_QTextEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLI_OUTPUT_FORM_QTEXTEDIT_H
#define UI_CLI_OUTPUT_FORM_QTEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <cli_qtextedit.h>

QT_BEGIN_NAMESPACE

class Ui_Cli_Output_Form_QTextEdit
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_1;
    QHBoxLayout *horizontalLayout;
    Cli_QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_1;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Cli_Output_Form_QTextEdit)
    {
        if (Cli_Output_Form_QTextEdit->objectName().isEmpty())
            Cli_Output_Form_QTextEdit->setObjectName(QStringLiteral("Cli_Output_Form_QTextEdit"));
        Cli_Output_Form_QTextEdit->resize(320, 240);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Cli_Output_Form_QTextEdit->sizePolicy().hasHeightForWidth());
        Cli_Output_Form_QTextEdit->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Cli_Output_Form_QTextEdit);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        horizontalSpacer_2 = new QSpacerItem(3, 3, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer_1 = new QSpacerItem(3, 3, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_1, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textEdit = new Cli_QTextEdit(Cli_Output_Form_QTextEdit);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout->addWidget(textEdit);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        verticalSpacer_1 = new QSpacerItem(3, 3, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_1, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(3, 3, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(Cli_Output_Form_QTextEdit);

        QMetaObject::connectSlotsByName(Cli_Output_Form_QTextEdit);
    } // setupUi

    void retranslateUi(QWidget *Cli_Output_Form_QTextEdit)
    {
        Cli_Output_Form_QTextEdit->setWindowTitle(QApplication::translate("Cli_Output_Form_QTextEdit", "Cli Test Key Codes", 0));
        textEdit->setPlaceholderText(QApplication::translate("Cli_Output_Form_QTextEdit", "Test Cli Input Qt V0.01", 0));
    } // retranslateUi

};

namespace Ui {
    class Cli_Output_Form_QTextEdit: public Ui_Cli_Output_Form_QTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLI_OUTPUT_FORM_QTEXTEDIT_H
