# Archivo de proyecto optimizado para Windows
# Usar este archivo si tienes problemas con libcmark en Windows

QT += core widgets gui printsupport

CONFIG += c++11

TARGET = markdown_editor
TEMPLATE = app

SOURCES += main.cpp \
           markdow_editor.cpp \
           markdown_formatter.cpp \
           template_manager.cpp

HEADERS += markdow_editor.h \
           markdown_formatter.h \
           template_manager.h

# Configuración específica para Windows
win32 {
    # Intentar usar libcmark si está disponible
    CONFIG += link_pkgconfig
    
    # Si libcmark no está disponible, comentar la línea siguiente
    LIBS += -lcmark
    
    # Configuración para distribución
    CONFIG += static
    
    # Icono de la aplicación (opcional)
    # RC_ICONS = icon.ico
    
    # Información de versión
    VERSION = 1.0.0
    QMAKE_TARGET_COMPANY = "EscribeChanchi"
    QMAKE_TARGET_PRODUCT = "Editor de Markdown"
    QMAKE_TARGET_DESCRIPTION = "Editor de Markdown Avanzado"
    QMAKE_TARGET_COPYRIGHT = "Copyright 2025"
}

# Configuración específica para Linux
unix:!mac {
    LIBS += -lcmark
}

# Configuración específica para macOS
mac {
    LIBS += -lcmark
}

# Fallback si libcmark no está disponible
# Uncomment this section if you want to build without cmark
# DEFINES += NO_CMARK_SUPPORT
