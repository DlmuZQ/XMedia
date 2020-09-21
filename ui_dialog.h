/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_out_file_dir;
    QPushButton *pushButton_open_file_out;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_open_file_in;
    QLineEdit *lineEdit_file_path_in;
    QLineEdit *lineEdit_file_path_out;
    QProgressBar *progressBar_wait;
    QLabel *label_file_path;
    QLabel *label_start_time;
    QLabel *label_end_time;
    QLineEdit *lineEdit_time_start;
    QLineEdit *lineEdit_time_end;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 600);
        gridLayoutWidget = new QWidget(Dialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 351, 271));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_out_file_dir = new QLabel(gridLayoutWidget);
        label_out_file_dir->setObjectName(QString::fromUtf8("label_out_file_dir"));

        gridLayout->addWidget(label_out_file_dir, 1, 1, 1, 1);

        pushButton_open_file_out = new QPushButton(gridLayoutWidget);
        pushButton_open_file_out->setObjectName(QString::fromUtf8("pushButton_open_file_out"));

        gridLayout->addWidget(pushButton_open_file_out, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_ok = new QPushButton(gridLayoutWidget);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_cancel = new QPushButton(gridLayoutWidget);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 5, 1, 1, 3);

        pushButton_open_file_in = new QPushButton(gridLayoutWidget);
        pushButton_open_file_in->setObjectName(QString::fromUtf8("pushButton_open_file_in"));

        gridLayout->addWidget(pushButton_open_file_in, 0, 3, 1, 1);

        lineEdit_file_path_in = new QLineEdit(gridLayoutWidget);
        lineEdit_file_path_in->setObjectName(QString::fromUtf8("lineEdit_file_path_in"));

        gridLayout->addWidget(lineEdit_file_path_in, 0, 2, 1, 1);

        lineEdit_file_path_out = new QLineEdit(gridLayoutWidget);
        lineEdit_file_path_out->setObjectName(QString::fromUtf8("lineEdit_file_path_out"));

        gridLayout->addWidget(lineEdit_file_path_out, 1, 2, 1, 1);

        progressBar_wait = new QProgressBar(gridLayoutWidget);
        progressBar_wait->setObjectName(QString::fromUtf8("progressBar_wait"));
        progressBar_wait->setValue(24);

        gridLayout->addWidget(progressBar_wait, 4, 1, 1, 3);

        label_file_path = new QLabel(gridLayoutWidget);
        label_file_path->setObjectName(QString::fromUtf8("label_file_path"));

        gridLayout->addWidget(label_file_path, 0, 1, 1, 1);

        label_start_time = new QLabel(gridLayoutWidget);
        label_start_time->setObjectName(QString::fromUtf8("label_start_time"));

        gridLayout->addWidget(label_start_time, 2, 1, 1, 1);

        label_end_time = new QLabel(gridLayoutWidget);
        label_end_time->setObjectName(QString::fromUtf8("label_end_time"));

        gridLayout->addWidget(label_end_time, 3, 1, 1, 1);

        lineEdit_time_start = new QLineEdit(gridLayoutWidget);
        lineEdit_time_start->setObjectName(QString::fromUtf8("lineEdit_time_start"));

        gridLayout->addWidget(lineEdit_time_start, 2, 2, 1, 1);

        lineEdit_time_end = new QLineEdit(gridLayoutWidget);
        lineEdit_time_end->setObjectName(QString::fromUtf8("lineEdit_time_end"));

        gridLayout->addWidget(lineEdit_time_end, 3, 2, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label_out_file_dir->setText(QApplication::translate("Dialog", "TextLabel", nullptr));
        pushButton_open_file_out->setText(QApplication::translate("Dialog", "PushButton", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog", "\345\274\200\345\247\213", nullptr));
        pushButton_cancel->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", nullptr));
        pushButton_open_file_in->setText(QApplication::translate("Dialog", "PushButton", nullptr));
        label_file_path->setText(QApplication::translate("Dialog", "TextLabel", nullptr));
        label_start_time->setText(QApplication::translate("Dialog", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\210\347\247\222\357\274\211", nullptr));
        label_end_time->setText(QApplication::translate("Dialog", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\210\347\247\222\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
