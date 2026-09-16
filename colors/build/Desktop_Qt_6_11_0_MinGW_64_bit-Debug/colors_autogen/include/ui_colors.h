/********************************************************************************
** Form generated from reading UI file 'colors.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORS_H
#define UI_COLORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_colors
{
public:

    void setupUi(QWidget *colors)
    {
        if (colors->objectName().isEmpty())
            colors->setObjectName("colors");
        colors->resize(800, 600);

        retranslateUi(colors);

        QMetaObject::connectSlotsByName(colors);
    } // setupUi

    void retranslateUi(QWidget *colors)
    {
        colors->setWindowTitle(QCoreApplication::translate("colors", "colors", nullptr));
    } // retranslateUi

};

namespace Ui {
    class colors: public Ui_colors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORS_H
