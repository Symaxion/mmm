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

#include <QtGui/QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QPushButton;

class Gui : public QWidget {
    Q_OBJECT
public:
    Gui(QWidget* parent = 0); 

    bool addInstance(const QString&);
    bool removeInstance(const QString&);
    void launchInstance(QString);
    void openInstance(const QString&);

    bool containsInstance(const QString&) const;

private:
    bool checkInstanceName(const QString&);

private slots:
    void addButtonEvent();
    void removeButtonEvent();
    void openButtonEvent();
    void launchButtonEvent();

private:
    QVBoxLayout* mLayout;
    QListWidget* mListWidget;
    QWidget* mButtonContainer;
    QHBoxLayout* mButtonLayout;
    QPushButton* mAddButton;
    QPushButton* mRemoveButton;
    QPushButton* mOpenButton;
    QPushButton* mLaunchButton;
};
