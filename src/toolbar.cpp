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

#include "toolbar.h"

#include <QtGui/QIcon>
#include <QtGui/QHBoxLayout>

Toolbar::Toolbar() : QToolBar("toolbar") {
    addAction((QIcon)getIcon("add"), "Add new instance"); 
    addAction((QIcon)getIcon("duplicate"), "Duplicate instance"); 
    addAction((QIcon)getIcon("trash"), "Remove instance"); 
    addSeparator();
    addAction((QIcon)getIcon("import"), "Import instance"); 
    addAction((QIcon)getIcon("export"), "Export instance"); 
    addSeparator();
    addAction((QIcon)getIcon("search"), "Search"); 
}

QString Toolbar::getIcon(QString icon) {
#ifdef Q_WS_MAC
    return ":/img/toolbar-mac/"+icon+".png";
#else
    return ":/img/toolbar-misc/"+icon+".png";
#endif
}
