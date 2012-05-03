#include "gui.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

Gui::Gui(QWidget* parent) : QWidget(parent) {
    this->setWindowTitle("Multi Minecraft Manager");
    this->resize(384, 420);

    mLayout = new QVBoxLayout(this);
    #ifndef Q_OS_MAC
    mLayout->setSpacing(6);
    #endif
    mLayout->setContentsMargins(6, 6, 6, 6);

    mListWidget = new QListWidget(this);
    mLayout->addWidget(mListWidget);

    mButtonContainer = new QWidget(this);

    mButtonLayout = new QHBoxLayout(mButtonContainer);
    mButtonLayout->setSpacing(1);
    mButtonLayout->setContentsMargins(1, 1, 1, 1);

    mAddButton = new QPushButton(mButtonContainer);
    mAddButton->setText("Add...");
    mButtonLayout->addWidget(mAddButton);

    mRemoveButton = new QPushButton(mButtonContainer);
    mRemoveButton->setText("Remove");
    mButtonLayout->addWidget(mRemoveButton);

    mOpenButton = new QPushButton(mButtonContainer);
    mOpenButton->setText("Open Folder");
    mButtonLayout->addWidget(mOpenButton);

    mLaunchButton = new QPushButton(mButtonContainer);
    mLaunchButton->setText("Launch");
    mButtonLayout->addWidget(mLaunchButton);

    mLayout->addWidget(mButtonContainer);
} 
