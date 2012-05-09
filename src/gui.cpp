/*
 * Multi Minecraft Manager (MMM)
 * Copyright (c) Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

#include "gui.h"

#include "os.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QInputDialog>
#include <QtGui/QErrorMessage>

#include <iostream>

void errorMessage(QWidget* parent, const QString& s) {
    QErrorMessage m(parent);
    m.showMessage(s);
    m.exec();
} 

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

    foreach(QString s, OS::listInstances()) {
        mListWidget->addItem(s);
    }

    // Connections
    connect(mAddButton   , SIGNAL(clicked()), this, SLOT(addButtonEvent())   ); 
    connect(mRemoveButton, SIGNAL(clicked()), this, SLOT(removeButtonEvent())); 
    connect(mOpenButton  , SIGNAL(clicked()), this, SLOT(openButtonEvent())  ); 
    connect(mLaunchButton, SIGNAL(clicked()), this, SLOT(launchButtonEvent())); 

} 

bool Gui::addInstance(const QString& name) {
    if(!checkInstanceName(name)) {
        // Name invalid
        errorMessage(this, "That name contains invalid characters.\n"
                "You can only use a-z, A-Z, 0-9, '-', '_', '.', '(', ')' and "
                "spaces.");
        return false;
    }

    if(containsInstance(name)) {
        // Duplicate item
        errorMessage(this, 
                "You already have an instance with that name.");
        return false;
    }

    mListWidget->addItem(name);

    OS::prepareInstance(name);

    return true;
}

bool Gui::removeInstance(const QString& name) {
    if(name == "Default") {
        // Can't remove default!
        errorMessage(this, "You cannot remove the default instance!");
        return false;
    }

    if(!containsInstance(name)) {
        // Item does not exist
        errorMessage(this, "That instance does not exist.");
        return false;
    }

    QListWidgetItem* toRemove = mListWidget->findItems(name, 
            Qt::MatchFixedString).at(0);

    delete mListWidget->takeItem(mListWidget->row(toRemove));

    OS::removeInstance(name);

    return true;
}

void Gui::launchInstance(QString name) {
    if(name == "Default") {
        name = OS::kDefaultInstance;
    } else {
        name = OS::instancePath(name);
    }

    OS::launchInstance(name);
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
    return QRegExp("^[a-zA-Z0-9 -_.()]+$").exactMatch(name);
}

void Gui::addButtonEvent() {
    QString name = QInputDialog::getText(this, "Name your new instance", 
            "Please give a name to the new instance: ");

    addInstance(name);
}

void Gui::removeButtonEvent() {
    QString selected = mListWidget->currentItem()->text();
    removeInstance(selected);
}

void Gui::openButtonEvent() {
    QString selected = mListWidget->currentItem()->text();
    openInstance(selected);
}

void Gui::launchButtonEvent() {
    QString selected = mListWidget->currentItem()->text();
    launchInstance(selected);
}




