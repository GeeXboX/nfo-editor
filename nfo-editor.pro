#
# GeeXboX NFO editor: GUI for media scanner application.
# Copyright (C) 2009 Fabien Brisset <fbrisset@geexbox.org>
#
# This file is part of nfo-editor.
#
# nfo-editor is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# nfo-editor is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with libvalhalla; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#
QT += network \
    xml \
    xmlpatterns \
    testlib
TARGET = nfo-editor
TEMPLATE = app
SOURCES += main.cpp \
    nfomain.cpp
HEADERS += nfomain.h
FORMS += nfomainwindow.ui
OTHER_FILES += icons/icon_enna_128.png
LIBS += -lnfo -lvalhalla
INCLUDEPATH += -I"/usr/include"
