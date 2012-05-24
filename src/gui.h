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

#ifndef MMM_GUI_H_
#define MMM_GUI_H_

#include <QtGui/QListWidget>

class Instance;

class Gui : public QListWidget {
    Q_OBJECT
public:
    Gui(QWidget* parent = 0); 

    bool containsInstance(const QString&) const;

    bool addInstance();
    Instance* insertInstance(const QString&);
    bool checkInstanceName(const QString&) const;

public slots:
    bool removeInstance(Instance*);

private slots:
    void onItemClick(QListWidgetItem* item);
    void onItemActivate(QListWidgetItem* item);
    void onDeleteKey();
    void onOpenInstance() const;
    void onContextMenu(const QPoint&);

private:
    QListWidgetItem* mAddButton;
};

#endif /* MMM_GUI_H_ */

