#include "template_manager.h"

TemplateManager::TemplateManager(QObject *parent) 
    : QObject(parent), templateDialog(nullptr), createDialog(nullptr), currentEditor(nullptr) {
    setupTemplatesDirectory();
    loadPredefinedTemplates();
    loadCustomTemplates();
}

void TemplateManager::setupTemplatesDirectory() {
    templatesDir = QDir::currentPath() + "/templates";
    QDir dir;
    if (!dir.exists(templatesDir)) {
        dir.mkpath(templatesDir);
    }
}

void TemplateManager::loadPredefinedTemplates() {
    predefinedTemplates.clear();
    
    // README básico
    predefinedTemplates << createPredefinedTemplate(
        "README Básico",
        "Plantilla básica para archivos README de proyectos",
        "# Nombre del Proyecto\n\n"
        "## Descripción\n"
        "Breve descripción de lo que hace tu proyecto.\n\n"
        "## Instalación\n"
        "```bash\n"
        "# Instrucciones de instalación\n"
        "```\n\n"
        "## Uso\n"
        "```bash\n"
        "# Ejemplos de uso\n"
        "```\n\n"
        "## Contribución\n"
        "Las contribuciones son bienvenidas. Por favor:\n"
        "1. Fork el proyecto\n"
        "2. Crea una rama para tu feature\n"
        "3. Commit tus cambios\n"
        "4. Push a la rama\n"
        "5. Abre un Pull Request\n\n"
        "## Licencia\n"
        "Este proyecto está bajo la licencia MIT.",
        "Documentación"
    );
    
    // Documentación de API
    predefinedTemplates << createPredefinedTemplate(
        "Documentación API",
        "Plantilla para documentar APIs REST",
        "# API Documentation\n\n"
        "## Base URL\n"
        "`https://api.ejemplo.com/v1`\n\n"
        "## Autenticación\n"
        "```\n"
        "Authorization: Bearer <token>\n"
        "```\n\n"
        "## Endpoints\n\n"
        "### GET /usuarios\n"
        "Obtiene la lista de usuarios.\n\n"
        "**Parámetros:**\n"
        "- `page` (opcional): Número de página\n"
        "- `limit` (opcional): Elementos por página\n\n"
        "**Respuesta:**\n"
        "```json\n"
        "{\n"
        "  \"users\": [],\n"
        "  \"total\": 0,\n"
        "  \"page\": 1\n"
        "}\n"
        "```\n\n"
        "### POST /usuarios\n"
        "Crea un nuevo usuario.\n\n"
        "**Body:**\n"
        "```json\n"
        "{\n"
        "  \"nombre\": \"string\",\n"
        "  \"email\": \"string\"\n"
        "}\n"
        "```",
        "Documentación"
    );
    
    // Artículo/Blog
    predefinedTemplates << createPredefinedTemplate(
        "Artículo Blog",
        "Plantilla para artículos de blog o posts",
        "# Título del Artículo\n\n"
        "*Publicado el: [fecha]*\n"
        "*Por: [autor]*\n\n"
        "## Introducción\n"
        "Párrafo introductorio que engancha al lector...\n\n"
        "## Desarrollo\n\n"
        "### Subtema 1\n"
        "Contenido del primer subtema...\n\n"
        "### Subtema 2\n"
        "Contenido del segundo subtema...\n\n"
        "## Conclusión\n"
        "Resumen y conclusiones del artículo...\n\n"
        "---\n\n"
        "**Tags:** #tag1 #tag2 #tag3\n\n"
        "> 💡 **Tip:** Algún consejo útil para el lector.",
        "Contenido"
    );
    
    // Notas de reunión
    predefinedTemplates << createPredefinedTemplate(
        "Notas de Reunión",
        "Plantilla para actas y notas de reuniones",
        "# Notas de Reunión\n\n"
        "**Fecha:** [fecha]\n"
        "**Hora:** [hora]\n"
        "**Duración:** [duración]\n"
        "**Moderador:** [nombre]\n\n"
        "## Participantes\n"
        "- [ ] Persona 1\n"
        "- [ ] Persona 2\n"
        "- [ ] Persona 3\n\n"
        "## Agenda\n"
        "1. Punto 1\n"
        "2. Punto 2\n"
        "3. Punto 3\n\n"
        "## Discusión\n\n"
        "### Punto 1: [título]\n"
        "- Resumen de la discusión\n"
        "- Decisiones tomadas\n\n"
        "### Punto 2: [título]\n"
        "- Resumen de la discusión\n"
        "- Decisiones tomadas\n\n"
        "## Acciones a seguir\n"
        "- [ ] Acción 1 - Responsable: [nombre] - Fecha: [fecha]\n"
        "- [ ] Acción 2 - Responsable: [nombre] - Fecha: [fecha]\n\n"
        "## Próxima reunión\n"
        "**Fecha:** [fecha]\n"
        "**Temas:** [temas a tratar]",
        "Trabajo"
    );
    
    // Lista de tareas
    predefinedTemplates << createPredefinedTemplate(
        "Lista de Tareas",
        "Plantilla para listas de tareas y checklists",
        "# Lista de Tareas\n\n"
        "**Proyecto:** [nombre del proyecto]\n"
        "**Fecha:** [fecha]\n\n"
        "## Tareas Pendientes\n"
        "- [ ] Tarea importante 1\n"
        "  - [ ] Subtarea 1.1\n"
        "  - [ ] Subtarea 1.2\n"
        "- [ ] Tarea importante 2\n"
        "- [ ] Tarea importante 3\n\n"
        "## En Progreso\n"
        "- [ ] Tarea en desarrollo 1\n"
        "- [ ] Tarea en desarrollo 2\n\n"
        "## Completadas ✅\n"
        "- [x] Tarea completada 1\n"
        "- [x] Tarea completada 2\n\n"
        "## Notas\n"
        "- Nota importante 1\n"
        "- Nota importante 2\n\n"
        "---\n"
        "*Última actualización: [fecha]*",
        "Productividad"
    );
    
    // Tutorial paso a paso
    predefinedTemplates << createPredefinedTemplate(
        "Tutorial",
        "Plantilla para tutoriales paso a paso",
        "# Tutorial: [Título]\n\n"
        "## Requisitos previos\n"
        "- Requisito 1\n"
        "- Requisito 2\n"
        "- Requisito 3\n\n"
        "## Lo que aprenderás\n"
        "Al finalizar este tutorial, serás capaz de:\n"
        "- Objetivo 1\n"
        "- Objetivo 2\n"
        "- Objetivo 3\n\n"
        "## Paso 1: [Título del paso]\n"
        "Descripción detallada del primer paso...\n\n"
        "```bash\n"
        "# Código de ejemplo\n"
        "```\n\n"
        "## Paso 2: [Título del paso]\n"
        "Descripción detallada del segundo paso...\n\n"
        "```bash\n"
        "# Más código de ejemplo\n"
        "```\n\n"
        "## Paso 3: [Título del paso]\n"
        "Descripción detallada del tercer paso...\n\n"
        "## Conclusión\n"
        "Resumen de lo aprendido y próximos pasos...\n\n"
        "## Recursos adicionales\n"
        "- [Enlace 1](url)\n"
        "- [Enlace 2](url)\n"
        "- [Enlace 3](url)",
        "Educación"
    );
}

Template TemplateManager::createPredefinedTemplate(const QString &name, const QString &desc, 
                                                  const QString &content, const QString &category) {
    Template tmpl;
    tmpl.name = name;
    tmpl.description = desc;
    tmpl.content = content;
    tmpl.category = category;
    tmpl.isCustom = false;
    return tmpl;
}

void TemplateManager::loadCustomTemplates() {
    customTemplates.clear();
    QDir dir(templatesDir);
    QStringList filters;
    filters << "*.md";
    
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);
    for (const QFileInfo &fileInfo : files) {
        QFile file(fileInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            
            Template tmpl;
            tmpl.name = fileInfo.baseName();
            tmpl.description = "Plantilla personalizada";
            tmpl.content = content;
            tmpl.category = "Personalizada";
            tmpl.isCustom = true;
            
            customTemplates << tmpl;
        }
    }
}

QList<Template> TemplateManager::getAvailableTemplates() {
    QList<Template> allTemplates;
    allTemplates << predefinedTemplates << customTemplates;
    return allTemplates;
}

void TemplateManager::showTemplateDialog(QTextEdit *editor) {
    currentEditor = editor;
    
    templateDialog = new QDialog();
    templateDialog->setWindowTitle("Seleccionar Plantilla");
    templateDialog->setMinimumSize(800, 600);
    
    QHBoxLayout *mainLayout = new QHBoxLayout(templateDialog);
    
    // Panel izquierdo - Lista de plantillas
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QLabel *listLabel = new QLabel("Plantillas disponibles:");
    templateList = new QListWidget();
    
    leftLayout->addWidget(listLabel);
    leftLayout->addWidget(templateList);
    
    // Panel derecho - Vista previa
    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *previewLabel = new QLabel("Vista previa:");
    previewArea = new QTextEdit();
    previewArea->setReadOnly(true);
    
    rightLayout->addWidget(previewLabel);
    rightLayout->addWidget(previewArea);
    
    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *useButton = new QPushButton("Usar Plantilla");
    QPushButton *createButton = new QPushButton("Crear Nueva");
    QPushButton *deleteButton = new QPushButton("Eliminar");
    QPushButton *cancelButton = new QPushButton("Cancelar");
    
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(useButton);
    buttonLayout->addWidget(cancelButton);
    
    // Layout principal
    QVBoxLayout *leftContainer = new QVBoxLayout();
    leftContainer->addLayout(leftLayout);
    leftContainer->addLayout(buttonLayout);
    
    QWidget *leftWidget = new QWidget();
    leftWidget->setLayout(leftContainer);
    leftWidget->setMaximumWidth(300);
    
    mainLayout->addWidget(leftWidget);
    mainLayout->addLayout(rightLayout);
    
    // Conectar señales
    connect(templateList, &QListWidget::currentItemChanged, this, &TemplateManager::onPreviewTemplate);
    connect(useButton, &QPushButton::clicked, this, &TemplateManager::onTemplateSelected);
    connect(createButton, &QPushButton::clicked, this, &TemplateManager::onCreateTemplate);
    connect(deleteButton, &QPushButton::clicked, this, &TemplateManager::onDeleteTemplate);
    connect(cancelButton, &QPushButton::clicked, templateDialog, &QDialog::reject);
    
    populateTemplateList();
    templateDialog->exec();
}

void TemplateManager::populateTemplateList() {
    templateList->clear();
    
    // Añadir plantillas predefinidas
    for (const Template &tmpl : predefinedTemplates) {
        QListWidgetItem *item = new QListWidgetItem(QString("[%1] %2").arg(tmpl.category, tmpl.name));
        item->setData(Qt::UserRole, QVariant::fromValue(tmpl));
        item->setToolTip(tmpl.description);
        templateList->addItem(item);
    }
    
    // Añadir plantillas personalizadas
    for (const Template &tmpl : customTemplates) {
        QListWidgetItem *item = new QListWidgetItem(QString("[%1] %2").arg(tmpl.category, tmpl.name));
        item->setData(Qt::UserRole, QVariant::fromValue(tmpl));
        item->setToolTip(tmpl.description);
        item->setForeground(QBrush(QColor(0, 100, 200))); // Color azul para personalizadas
        templateList->addItem(item);
    }
}

void TemplateManager::onPreviewTemplate() {
    QListWidgetItem *item = templateList->currentItem();
    if (item) {
        Template tmpl = item->data(Qt::UserRole).value<Template>();
        previewArea->setPlainText(tmpl.content);
    }
}

void TemplateManager::onTemplateSelected() {
    QListWidgetItem *item = templateList->currentItem();
    if (item && currentEditor) {
        Template tmpl = item->data(Qt::UserRole).value<Template>();
        applyTemplate(tmpl, currentEditor);
        templateDialog->accept();
    }
}

void TemplateManager::onCreateTemplate() {
    templateDialog->hide();
    showCreateTemplateDialog(currentEditor);
}

void TemplateManager::onDeleteTemplate() {
    QListWidgetItem *item = templateList->currentItem();
    if (item) {
        Template tmpl = item->data(Qt::UserRole).value<Template>();
        if (tmpl.isCustom) {
            int ret = QMessageBox::question(templateDialog, "Confirmar eliminación",
                                          QString("¿Estás seguro de que quieres eliminar la plantilla '%1'?").arg(tmpl.name),
                                          QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                deleteCustomTemplate(tmpl.name);
                loadCustomTemplates();
                populateTemplateList();
            }
        } else {
            QMessageBox::information(templateDialog, "No se puede eliminar", 
                                   "No puedes eliminar plantillas predefinidas.");
        }
    }
}

void TemplateManager::showCreateTemplateDialog(QTextEdit *editor) {
    createDialog = new QDialog();
    createDialog->setWindowTitle("Crear Nueva Plantilla");
    createDialog->setMinimumSize(600, 500);
    
    QVBoxLayout *layout = new QVBoxLayout(createDialog);
    
    // Campos de entrada
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel("Nombre:");
    QLineEdit *nameEdit = new QLineEdit();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    
    QHBoxLayout *descLayout = new QHBoxLayout();
    QLabel *descLabel = new QLabel("Descripción:");
    QLineEdit *descEdit = new QLineEdit();
    descLayout->addWidget(descLabel);
    descLayout->addWidget(descEdit);
    
    // Área de contenido
    QLabel *contentLabel = new QLabel("Contenido de la plantilla:");
    QTextEdit *contentEdit = new QTextEdit();
    
    // Si hay un editor activo, usar su contenido como base
    if (editor && !editor->toPlainText().isEmpty()) {
        contentEdit->setPlainText(editor->toPlainText());
    } else {
        contentEdit->setPlainText("# Nueva Plantilla\n\nEscribe aquí el contenido de tu plantilla...\n");
    }
    
    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *saveButton = new QPushButton("Guardar");
    QPushButton *cancelButton = new QPushButton("Cancelar");
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    
    layout->addLayout(nameLayout);
    layout->addLayout(descLayout);
    layout->addWidget(contentLabel);
    layout->addWidget(contentEdit);
    layout->addLayout(buttonLayout);
    
    // Conectar botones
    connect(saveButton, &QPushButton::clicked, [=]() {
        QString name = nameEdit->text().trimmed();
        QString description = descEdit->text().trimmed();
        QString content = contentEdit->toPlainText();
        
        if (name.isEmpty()) {
            QMessageBox::warning(createDialog, "Error", "Debes especificar un nombre para la plantilla.");
            return;
        }
        
        if (content.isEmpty()) {
            QMessageBox::warning(createDialog, "Error", "El contenido de la plantilla no puede estar vacío.");
            return;
        }
        
        Template newTemplate;
        newTemplate.name = name;
        newTemplate.description = description.isEmpty() ? "Plantilla personalizada" : description;
        newTemplate.content = content;
        newTemplate.category = "Personalizada";
        newTemplate.isCustom = true;
        
        saveCustomTemplate(newTemplate);
        loadCustomTemplates();
        
        QMessageBox::information(createDialog, "Éxito", 
                               QString("Plantilla '%1' guardada correctamente.").arg(name));
        createDialog->accept();
    });
    
    connect(cancelButton, &QPushButton::clicked, createDialog, &QDialog::reject);
    
    createDialog->exec();
    createDialog->deleteLater();
}

void TemplateManager::saveCustomTemplate(const Template &tmpl) {
    QString fileName = templatesDir + "/" + tmpl.name + ".md";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << tmpl.content;
    }
}

void TemplateManager::deleteCustomTemplate(const QString &name) {
    QString fileName = templatesDir + "/" + name + ".md";
    QFile::remove(fileName);
}

void TemplateManager::applyTemplate(const Template &tmpl, QTextEdit *editor) {
    if (editor) {
        editor->setPlainText(tmpl.content);
        editor->moveCursor(QTextCursor::Start);
    }
}
