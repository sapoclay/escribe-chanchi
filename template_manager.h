#ifndef TEMPLATE_MANAGER_H
#define TEMPLATE_MANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDialog>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QMetaType>

struct Template {
    QString name;
    QString description;
    QString content;
    QString category;
    bool isCustom;
};

Q_DECLARE_METATYPE(Template)

class TemplateManager : public QObject {
    Q_OBJECT

public:
    explicit TemplateManager(QObject *parent = nullptr);
    
    // Métodos principales
    void showTemplateDialog(QTextEdit *editor);
    void showCreateTemplateDialog(QTextEdit *editor = nullptr);
    
    // Gestión de plantillas
    QList<Template> getAvailableTemplates();
    void loadPredefinedTemplates();
    void loadCustomTemplates();
    void saveCustomTemplate(const Template &tmpl);
    void deleteCustomTemplate(const QString &name);
    
    // Aplicar plantilla
    void applyTemplate(const Template &tmpl, QTextEdit *editor);

private slots:
    void onTemplateSelected();
    void onCreateTemplate();
    void onDeleteTemplate();
    void onPreviewTemplate();

private:
    QList<Template> predefinedTemplates;
    QList<Template> customTemplates;
    QString templatesDir;
    
    // UI
    QDialog *templateDialog;
    QDialog *createDialog;
    QListWidget *templateList;
    QTextEdit *previewArea;
    QTextEdit *currentEditor;
    
    // Métodos auxiliares
    void setupTemplatesDirectory();
    void populateTemplateList();
    Template createPredefinedTemplate(const QString &name, const QString &desc, 
                                    const QString &content, const QString &category);
};

#endif // TEMPLATE_MANAGER_H
