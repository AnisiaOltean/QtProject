#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10Qt.h"

class Lab10Qt : public QMainWindow
{
    Q_OBJECT

public:
    Lab10Qt(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab10QtClass ui;
};
