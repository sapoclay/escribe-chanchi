#include <QApplication>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include "markdow_editor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Configurar información de la aplicación para QSettings
    app.setOrganizationName("EscribeChanchi");
    app.setApplicationName("Escribe Chanchi");
    app.setApplicationVersion("1.0");
    
    // Configurar icono de la aplicación
    app.setWindowIcon(QIcon(":/img/logo_escribe_chanchi.png"));
    
    // Verificar si el sistema soporta la bandeja del sistema
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, "Escribe Chanchi",
                             "No se detectó soporte para la bandeja del sistema en este sistema.");
    }
    
    MarkdownEditor editor;
    editor.showMaximized(); // Abrir maximizada (permite desmaximizar)
    
    return app.exec();
}
