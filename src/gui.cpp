#include "gui.h"

#include "os.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

#include <iostream>

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

    mListWidget->addItem("Default");
    mListWidget->setSortingEnabled(true);

    // Connections
    connect(mOpenButton, SIGNAL(clicked()), this, SLOT(openButtonEvent())); 

} 

bool Gui::addInstance(const QString& name) {
    if(!checkInstanceName(name)) {
        // Name invalid
        return false;
    }

    if(containsInstance(name)) {
        // Duplicate item
        return false;
    }

    mListWidget->addItem(name);

    OS::prepareInstance(name);

    return true;
}

bool Gui::removeInstance(const QString& name) {
    if(!containsInstance(name)) {
        // Item does not exist
        return false;
    }

    QListWidgetItem* toRemove = mListWidget->findItems(name, 
            Qt::MatchFixedString).at(0);

    delete mListWidget->takeItem(mListWidget->row(toRemove));

    return true;
}

void Gui::launchInstance(const QString& name) {

}

void Gui::openInstance(const QString& name) {
    if(name == "Default") {
        OS::openFolder(OS::kDefaultInstanceMcPath);
    } else {
        OS::openFolder(OS::instanceMcPath(name));
    }
}

bool Gui::containsInstance(const QString& name) const {
    return mListWidget->findItems(name, Qt::MatchFixedString).size() != 0;

}


bool Gui::checkInstanceName(const QString& name) {
    return name.contains(QRegExp("^[a-zA-Z0-9 -_.()]+$"));
}

void Gui::addButtonEvent() {
    // TODO
}

void Gui::removeButtonEvent() {
    // TODO
}

void Gui::openButtonEvent() {
    QString selected = mListWidget->currentItem()->text();
    std::cerr << "Debug: " << qPrintable(selected) << std::endl;
    openInstance(selected);
}

void Gui::launchButtonEvent() {
    // TODO
}




