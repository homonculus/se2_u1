#include "memory_param_window.h"
#include <iostream>
#include <QtWidgets>


const int IdRole = Qt::UserRole;

MemoryParamWindow::MemoryParamWindow()
{
    setWindowTitle(tr("Memory Parameters"));

    // callibrationArea = new MemoryCallibrationArea;



    rowComboBox = new QComboBox;
    rowComboBox->addItem(tr("2"),0);
    rowComboBox->addItem(tr("3"),1);
    rowComboBox->addItem(tr("4"),2);
    rowComboBox->addItem(tr("5"),2);
    rowLabel = new QLabel(tr("&Anzahl Reien:"));
    rowLabel->setBuddy(rowComboBox);



    colComboBox = new QComboBox;
    colComboBox->addItem(tr("2"),0);
    colComboBox->addItem(tr("3"),1);
    colComboBox->addItem(tr("4"),2);
    colComboBox->addItem(tr("5"),2);
    colLabel = new QLabel(tr("&Anzahl Spalten:"));
    colLabel->setBuddy(colComboBox);

    connect(rowComboBox, SIGNAL(activated(int)), this, SLOT(rowChanged()));
    connect(colComboBox, SIGNAL(activated(int)), this, SLOT(colChanged()));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(rowLabel,0,0,Qt::AlignRight);// row column
    mainLayout->addWidget(rowComboBox,0,1);

    mainLayout->addWidget(colLabel,1,0,Qt::AlignRight);
    mainLayout->addWidget(colComboBox,1,1);


    // mainLayout->addWidget(callibrationArea, 3, 0, 1, 4); // fromrow fromcolumn nrows ncols

    setLayout(mainLayout);

}

void MemoryParamWindow::rowChanged(){
    std::cout << "ROW CHANGED : " << rowComboBox->itemData(rowComboBox->currentIndex(), IdRole).toInt() << "\n";
}

void MemoryParamWindow::colChanged(){
    std::cout << "ROW CHANGED : " << rowComboBox->itemData(rowComboBox->currentIndex(), IdRole).toInt() << "\n";
}


