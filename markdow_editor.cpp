#include "markdow_editor.h"
#include <QPalette>
#include <QFont>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QPrinter>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QFileDialog>
#include <QTextStream>
#include <QPrinter>
#include <QPainter>
#include <QFile>
#include <QMenu>
#include <QKeySequence>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>
#include <cmark.h>

MarkdownEditor::MarkdownEditor(QWidget *parent) 
    : QMainWindow(parent), darkMode(false), showLineNumbers(false), untitledCounter(1),
      isFullScreenMode(false), formatter(nullptr), editor(nullptr), browser(nullptr), 
      splitter(nullptr), trayIcon(nullptr), trayIconMenu(nullptr) {
    
    // Crear el widget central
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Crear el widget de pestañas
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    
    // Layout principal para el widget central
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(tabWidget);
    centralWidget->setLayout(layout);

    setWindowTitle("EscribeChanchi");
    
    // Configurar icono de la ventana
    setWindowIcon(QIcon(":/img/logo_escribe_chanchi.png"));

    // Inicializar template manager
    templateManager = new TemplateManager(this);

    // Configurar la barra de menús
    setupMenuBar();
    
    // Configurar la barra de herramientas
    setupToolBar();
    
    // Configurar la bandeja del sistema
    setupSystemTray();

    // Conectar señales del tab widget
    connect(tabWidget, &QTabWidget::currentChanged, this, &MarkdownEditor::tabChanged);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MarkdownEditor::closeTab);

    // Crear la primera pestaña
    newTab();

    // Configuración inicial del modo claro
    setLightMode();
    
    // Configurar el tamaño y estado inicial de la ventana
    resize(1200, 800);  // Tamaño inicial razonable
    
    // Asegurar que la ventana no esté en modo pantalla completa al inicio
    isFullScreenMode = false;
}

void MarkdownEditor::setupMenuBar() {
    // Menú Archivo
    QMenu* fileMenu = this->menuBar()->addMenu("Archivo");
    
    QAction* newTabAction = new QAction("Nueva pestaña", this);
    newTabAction->setShortcut(QKeySequence::New);
    connect(newTabAction, &QAction::triggered, this, &MarkdownEditor::newTab);
    fileMenu->addAction(newTabAction);
    
    QAction* openAction = new QAction("Abrir", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MarkdownEditor::openFileInNewTab);
    fileMenu->addAction(openAction);
    
    fileMenu->addSeparator();
    
    QAction* saveAction = new QAction("Guardar", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MarkdownEditor::saveCurrentFile);
    fileMenu->addAction(saveAction);
    
    QAction* saveAsAction = new QAction("Guardar como...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MarkdownEditor::saveFileAs);
    fileMenu->addAction(saveAsAction);
    
    fileMenu->addSeparator();
    
    QAction* closeTabAction = new QAction("Cerrar pestaña", this);
    closeTabAction->setShortcut(QKeySequence::Close);
    connect(closeTabAction, &QAction::triggered, this, &MarkdownEditor::closeCurrentTab);
    fileMenu->addAction(closeTabAction);
    
    fileMenu->addSeparator();
    
    QAction* exportHtmlAction = new QAction("Exportar a HTML", this);
    connect(exportHtmlAction, &QAction::triggered, this, &MarkdownEditor::exportToHTML);
    fileMenu->addAction(exportHtmlAction);
    
    QAction* exportPdfAction = new QAction("Exportar a PDF", this);
    connect(exportPdfAction, &QAction::triggered, this, &MarkdownEditor::exportToPDF);
    fileMenu->addAction(exportPdfAction);
    
    fileMenu->addSeparator();
    
    QAction* exitAction = new QAction("Salir", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    // Menú Formato
    QMenu* formatMenu = this->menuBar()->addMenu("Formato");
    
    // Formato básico de texto
    QAction* boldAction = new QAction("&Negrita", this);
    boldAction->setShortcut(QKeySequence::Bold);
    connect(boldAction, &QAction::triggered, this, &MarkdownEditor::setBold);
    formatMenu->addAction(boldAction);
    
    QAction* italicAction = new QAction("&Cursiva", this);
    italicAction->setShortcut(QKeySequence::Italic);
    connect(italicAction, &QAction::triggered, this, &MarkdownEditor::setItalic);
    formatMenu->addAction(italicAction);
    
    QAction* strikethroughAction = new QAction("&Tachado", this);
    strikethroughAction->setShortcut(QKeySequence("Ctrl+Shift+X"));
    connect(strikethroughAction, &QAction::triggered, this, &MarkdownEditor::setStrikethrough);
    formatMenu->addAction(strikethroughAction);
    
    formatMenu->addSeparator();
    
    // Código
    QAction* codeAction = new QAction("Código en &línea", this);
    codeAction->setShortcut(QKeySequence("Ctrl+`"));
    connect(codeAction, &QAction::triggered, this, &MarkdownEditor::setCode);
    formatMenu->addAction(codeAction);
    
    QAction* codeBlockAction = new QAction("&Bloque de código", this);
    codeBlockAction->setShortcut(QKeySequence("Ctrl+Shift+`"));
    connect(codeBlockAction, &QAction::triggered, this, &MarkdownEditor::setCodeBlock);
    formatMenu->addAction(codeBlockAction);
    
    formatMenu->addSeparator();
    
    // Encabezados
    QAction* headerAction = new QAction("&Encabezado", this);
    headerAction->setShortcut(QKeySequence("Ctrl+H"));
    connect(headerAction, &QAction::triggered, this, &MarkdownEditor::setHeader);
    formatMenu->addAction(headerAction);
    
    formatMenu->addSeparator();
    
    // Listas
    QAction* unorderedListAction = new QAction("Lista con &viñetas", this);
    unorderedListAction->setShortcut(QKeySequence("Ctrl+U"));
    connect(unorderedListAction, &QAction::triggered, this, &MarkdownEditor::setUnorderedList);
    formatMenu->addAction(unorderedListAction);
    
    QAction* orderedListAction = new QAction("Lista &numerada", this);
    orderedListAction->setShortcut(QKeySequence("Ctrl+Shift+O"));
    connect(orderedListAction, &QAction::triggered, this, &MarkdownEditor::setOrderedList);
    formatMenu->addAction(orderedListAction);
    
    formatMenu->addSeparator();
    
    // Enlaces e imágenes
    QAction* linkAction = new QAction("Insertar en&lace", this);
    linkAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(linkAction, &QAction::triggered, this, &MarkdownEditor::setLink);
    formatMenu->addAction(linkAction);
    
    QAction* imageAction = new QAction("Insertar &imagen", this);
    imageAction->setShortcut(QKeySequence("Ctrl+Shift+I"));
    connect(imageAction, &QAction::triggered, this, &MarkdownEditor::setImage);
    formatMenu->addAction(imageAction);
    
    QAction* tableAction = new QAction("Insertar &tabla", this);
    tableAction->setShortcut(QKeySequence("Ctrl+T"));
    connect(tableAction, &QAction::triggered, this, &MarkdownEditor::insertTable);
    formatMenu->addAction(tableAction);
    
    formatMenu->addSeparator();
    
    // Otros elementos
    QAction* blockquoteAction = new QAction("&Cita", this);
    blockquoteAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(blockquoteAction, &QAction::triggered, this, &MarkdownEditor::setBlockquote);
    formatMenu->addAction(blockquoteAction);
    
    QAction* horizontalRuleAction = new QAction("Línea &horizontal", this);
    horizontalRuleAction->setShortcut(QKeySequence("Ctrl+Shift+H"));
    connect(horizontalRuleAction, &QAction::triggered, this, &MarkdownEditor::setHorizontalRule);
    formatMenu->addAction(horizontalRuleAction);

    // Menú Plantillas
    QMenu* templatesMenu = this->menuBar()->addMenu("Plantillas");
    
    QAction* showTemplatesAction = new QAction("Usar plantilla...", this);
    showTemplatesAction->setShortcut(QKeySequence("Ctrl+Shift+T"));
    connect(showTemplatesAction, &QAction::triggered, this, &MarkdownEditor::showTemplates);
    templatesMenu->addAction(showTemplatesAction);
    
    QAction* createTemplateAction = new QAction("Crear plantilla...", this);
    createTemplateAction->setShortcut(QKeySequence("Ctrl+Shift+N"));
    connect(createTemplateAction, &QAction::triggered, this, &MarkdownEditor::createTemplate);
    templatesMenu->addAction(createTemplateAction);

    // Menú Ver
    QMenu* viewMenu = this->menuBar()->addMenu("Ver");
    
    QAction* toggleModeAction = new QAction("Alternar Modo Oscuro", this);
    connect(toggleModeAction, &QAction::triggered, this, &MarkdownEditor::toggleDarkMode);
    viewMenu->addAction(toggleModeAction);
    
    QAction* toggleLineNumbersAction = new QAction("Mostrar números de línea", this);
    toggleLineNumbersAction->setCheckable(true);
    toggleLineNumbersAction->setShortcut(QKeySequence("Ctrl+Shift+L"));
    connect(toggleLineNumbersAction, &QAction::triggered, this, &MarkdownEditor::toggleLineNumbers);
    viewMenu->addAction(toggleLineNumbersAction);
    
    QAction* toggleFullScreenMenuAction = new QAction("Pantalla completa", this);
    toggleFullScreenMenuAction->setCheckable(true);
    toggleFullScreenMenuAction->setShortcut(QKeySequence("F11"));
    connect(toggleFullScreenMenuAction, &QAction::triggered, this, &MarkdownEditor::toggleFullScreen);
    viewMenu->addAction(toggleFullScreenMenuAction);

    // Menú Ayuda
    QMenu* helpMenu = this->menuBar()->addMenu("Ayuda");
    
    QAction* manualAction = new QAction("Manual", this);
    connect(manualAction, &QAction::triggered, this, &MarkdownEditor::showManual);
    helpMenu->addAction(manualAction);
    
    QAction* aboutAction = new QAction("Acerca de EscribeChanchi", this);
    connect(aboutAction, &QAction::triggered, this, &MarkdownEditor::showAbout);
    helpMenu->addAction(aboutAction);
}

void MarkdownEditor::setupToolBar() {
    // Crear la barra de herramientas principal
    mainToolBar = addToolBar("Formato");
    mainToolBar->setMovable(true);
    mainToolBar->setFloatable(true);
    mainToolBar->setIconSize(QSize(32, 32));
    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    
    // Función auxiliar para crear iconos de texto
    auto createTextIcon = [](const QString &text, const QFont &font = QFont(), const QColor &textColor = Qt::black, bool highlighted = false) -> QIcon {
        QPixmap pixmap(32, 32);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::TextAntialiasing);
        
        // Fondo con gradiente
        QLinearGradient gradient(0, 0, 0, 32);
        if (highlighted) {
            gradient.setColorAt(0, QColor(180, 200, 255, 200));
            gradient.setColorAt(1, QColor(150, 170, 230, 200));
        } else {
            gradient.setColorAt(0, QColor(245, 245, 245, 200));
            gradient.setColorAt(1, QColor(230, 230, 230, 200));
        }
        
        painter.setBrush(QBrush(gradient));
        painter.setPen(QPen(QColor(180, 180, 180), 1));
        painter.drawRoundedRect(2, 2, 28, 28, 6, 6);
        
        // Sombra de texto
        painter.setPen(QColor(0, 0, 0, 60));
        QFont shadowFont = font.family().isEmpty() ? QFont("Arial", 9, QFont::Bold) : font;
        painter.setFont(shadowFont);
        painter.drawText(pixmap.rect().adjusted(1, 1, 1, 1), Qt::AlignCenter, text);
        
        // Texto principal
        painter.setPen(textColor);
        painter.drawText(pixmap.rect(), Qt::AlignCenter, text);
        
        return QIcon(pixmap);
    };
    
    // Sección de pestañas
    QAction* newTabAction = mainToolBar->addAction(createTextIcon("+", QFont("Arial", 14, QFont::Bold), QColor(50, 150, 50)), "Nueva");
    newTabAction->setToolTip("Nueva pestaña (Ctrl+N)");
    newTabAction->setShortcut(QKeySequence::New);
    connect(newTabAction, &QAction::triggered, this, &MarkdownEditor::newTab);
    
    QAction* openTabAction = mainToolBar->addAction(createTextIcon("📁", QFont("Arial", 12), QColor(80, 120, 200)), "Abrir");
    openTabAction->setToolTip("Abrir archivo (Ctrl+O)");
    openTabAction->setShortcut(QKeySequence::Open);
    connect(openTabAction, &QAction::triggered, this, &MarkdownEditor::openFileInNewTab);
    
    QAction* saveTabAction = mainToolBar->addAction(createTextIcon("💾", QFont("Arial", 12), QColor(100, 100, 200)), "Guardar");
    saveTabAction->setToolTip("Guardar archivo (Ctrl+S)");
    saveTabAction->setShortcut(QKeySequence::Save);
    connect(saveTabAction, &QAction::triggered, this, &MarkdownEditor::saveCurrentFile);
    
    mainToolBar->addSeparator();
    
    // Sección de formato de texto
    QAction* boldAction = mainToolBar->addAction(createTextIcon("B", QFont("Arial", 10, QFont::Bold), QColor(60, 60, 60)), "Negrita");
    boldAction->setToolTip("Negrita (Ctrl+B)");
    boldAction->setShortcut(QKeySequence::Bold);
    connect(boldAction, &QAction::triggered, this, &MarkdownEditor::setBold);
    
    QFont italicFont("Arial", 10);
    italicFont.setItalic(true);
    QAction* italicAction = mainToolBar->addAction(createTextIcon("I", italicFont, QColor(80, 80, 80)), "Cursiva");
    italicAction->setToolTip("Cursiva (Ctrl+I)");
    italicAction->setShortcut(QKeySequence::Italic);
    connect(italicAction, &QAction::triggered, this, &MarkdownEditor::setItalic);
    
    QAction* codeAction = mainToolBar->addAction(createTextIcon("</\\>", QFont("Courier", 7), QColor(120, 80, 120)), "Código");
    codeAction->setToolTip("Código inline (Ctrl+`)");
    codeAction->setShortcut(QKeySequence("Ctrl+`"));
    connect(codeAction, &QAction::triggered, this, &MarkdownEditor::setCode);
    
    QFont strikeFont("Arial", 10);
    strikeFont.setStrikeOut(true);
    QAction* strikeAction = mainToolBar->addAction(createTextIcon("S", strikeFont, QColor(150, 80, 80)), "Tachado");
    strikeAction->setToolTip("Tachado (Ctrl+Shift+S)");
    strikeAction->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(strikeAction, &QAction::triggered, this, &MarkdownEditor::setStrikethrough);
    
    mainToolBar->addSeparator();
    
    // Sección de encabezados y estructura
    QAction* headerAction = mainToolBar->addAction(createTextIcon("H1", QFont("Arial", 8, QFont::Bold), QColor(50, 100, 200)), "Título");
    headerAction->setToolTip("Encabezado (Ctrl+H)");
    headerAction->setShortcut(QKeySequence("Ctrl+H"));
    connect(headerAction, &QAction::triggered, this, &MarkdownEditor::setHeader);
    
    QAction* quoteAction = mainToolBar->addAction(createTextIcon("❝", QFont("Arial", 14), QColor(100, 150, 100)), "Cita");
    quoteAction->setToolTip("Cita (Ctrl+Q)");
    quoteAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(quoteAction, &QAction::triggered, this, &MarkdownEditor::setBlockquote);
    
    QAction* codeBlockAction = mainToolBar->addAction(createTextIcon("{ }", QFont("Courier", 8), QColor(120, 80, 120)), "Bloque");
    codeBlockAction->setToolTip("Bloque de código (Ctrl+Shift+C)");
    codeBlockAction->setShortcut(QKeySequence("Ctrl+Shift+C"));
    connect(codeBlockAction, &QAction::triggered, this, &MarkdownEditor::setCodeBlock);
    
    mainToolBar->addSeparator();
    
    // Sección de listas
    QAction* unorderedListAction = mainToolBar->addAction(createTextIcon("•", QFont("Arial", 16)), "Lista");
    unorderedListAction->setToolTip("Lista sin ordenar (Ctrl+U)");
    unorderedListAction->setShortcut(QKeySequence("Ctrl+U"));
    connect(unorderedListAction, &QAction::triggered, this, &MarkdownEditor::setUnorderedList);
    
    QAction* orderedListAction = mainToolBar->addAction(createTextIcon("1.", QFont("Arial", 10, QFont::Bold)), "Números");
    orderedListAction->setToolTip("Lista numerada (Ctrl+Shift+U)");
    orderedListAction->setShortcut(QKeySequence("Ctrl+Shift+U"));
    connect(orderedListAction, &QAction::triggered, this, &MarkdownEditor::setOrderedList);
    
    mainToolBar->addSeparator();
    
    // Sección de enlaces y medios
    QAction* linkAction = mainToolBar->addAction(createTextIcon("🔗", QFont("Arial", 12)), "Enlace");
    linkAction->setToolTip("Insertar enlace (Ctrl+L)");
    linkAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(linkAction, &QAction::triggered, this, &MarkdownEditor::setLink);
    
    QAction* imageAction = mainToolBar->addAction(createTextIcon("🖼", QFont("Arial", 12)), "Imagen");
    imageAction->setToolTip("Insertar imagen (Ctrl+Shift+I)");
    imageAction->setShortcut(QKeySequence("Ctrl+Shift+I"));
    connect(imageAction, &QAction::triggered, this, &MarkdownEditor::setImage);
    
    QAction* tableAction = mainToolBar->addAction(createTextIcon("⊞", QFont("Arial", 14)), "Tabla");
    tableAction->setToolTip("Insertar tabla (Ctrl+T)");
    tableAction->setShortcut(QKeySequence("Ctrl+T"));
    connect(tableAction, &QAction::triggered, this, &MarkdownEditor::insertTable);
    
    QAction* hrAction = mainToolBar->addAction(createTextIcon("───", QFont("Arial", 8)), "Línea");
    hrAction->setToolTip("Línea horizontal (Ctrl+Shift+H)");
    hrAction->setShortcut(QKeySequence("Ctrl+Shift+H"));
    connect(hrAction, &QAction::triggered, this, &MarkdownEditor::setHorizontalRule);
    
    mainToolBar->addSeparator();
    
    // Sección de plantillas
    QAction* templatesAction = mainToolBar->addAction(createTextIcon("📋", QFont("Arial", 12)), "Plantilla");
    templatesAction->setToolTip("Usar plantilla (Ctrl+Shift+T)");
    templatesAction->setShortcut(QKeySequence("Ctrl+Shift+T"));
    connect(templatesAction, &QAction::triggered, this, &MarkdownEditor::showTemplates);
    
    QAction* newTemplateAction = mainToolBar->addAction(createTextIcon("📝", QFont("Arial", 12)), "Nueva");
    newTemplateAction->setToolTip("Crear plantilla (Ctrl+Shift+N)");
    newTemplateAction->setShortcut(QKeySequence("Ctrl+Shift+N"));
    connect(newTemplateAction, &QAction::triggered, this, &MarkdownEditor::createTemplate);
    
    mainToolBar->addSeparator();
    
    // Sección de vista
    QAction* darkModeAction = mainToolBar->addAction(createTextIcon("🌙", QFont("Arial", 12)), "Oscuro");
    darkModeAction->setToolTip("Alternar modo oscuro");
    connect(darkModeAction, &QAction::triggered, this, &MarkdownEditor::toggleDarkMode);
    
    QAction* lineNumbersAction = mainToolBar->addAction(createTextIcon("#", QFont("Arial", 12, QFont::Bold)), "Números");
    lineNumbersAction->setToolTip("Mostrar números de línea (Ctrl+Shift+L)");
    lineNumbersAction->setShortcut(QKeySequence("Ctrl+Shift+L"));
    lineNumbersAction->setCheckable(true);
    connect(lineNumbersAction, &QAction::triggered, this, &MarkdownEditor::toggleLineNumbers);
    
    QAction* fullScreenAction = mainToolBar->addAction(createTextIcon("⛶", QFont("Arial", 16)), "Pantalla");
    fullScreenAction->setToolTip("Alternar pantalla completa (F11)");
    fullScreenAction->setShortcut(QKeySequence("F11"));
    fullScreenAction->setCheckable(true);
    connect(fullScreenAction, &QAction::triggered, this, &MarkdownEditor::toggleFullScreen);
}

void MarkdownEditor::setBold() {
    if (formatter) {
        formatter->setBold();
    }
}

void MarkdownEditor::setItalic() {
    if (formatter) {
        formatter->setItalic();
    }
}

void MarkdownEditor::setCode() {
    if (formatter) {
        formatter->setCode();
    }
}

void MarkdownEditor::setHeader() {
    if (formatter) {
        formatter->setHeader();
    }
}

void MarkdownEditor::setStrikethrough() {
    if (formatter) {
        formatter->setStrikethrough();
    }
}

void MarkdownEditor::setBlockquote() {
    if (formatter) {
        formatter->setBlockquote();
    }
}

void MarkdownEditor::setUnorderedList() {
    if (formatter) {
        formatter->setUnorderedList();
    }
}

void MarkdownEditor::setOrderedList() {
    if (formatter) {
        formatter->setOrderedList();
    }
}

void MarkdownEditor::setLink() {
    if (formatter) {
        formatter->setLink();
    }
}

void MarkdownEditor::setImage() {
    if (formatter) {
        formatter->setImage();
    }
}

void MarkdownEditor::setHorizontalRule() {
    if (formatter) {
        formatter->setHorizontalRule();
    }
}

void MarkdownEditor::setCodeBlock() {
    if (formatter) {
        formatter->setCodeBlock();
    }
}

// Función para cambiar al modo oscuro
void MarkdownEditor::toggleDarkMode() {
    if (darkMode) {
        setLightMode();  // Si está en modo oscuro, cambiar a claro
    } else {
        setDarkMode();  // Si está en modo claro, cambiar a oscuro
    }
    darkMode = !darkMode;  // Alternar el valor de darkMode
}

// Función para aplicar el modo oscuro
void MarkdownEditor::setDarkMode() {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, Qt::black);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, Qt::darkGray);
    darkPalette.setColor(QPalette::AlternateBase, Qt::black);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, Qt::gray);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Highlight, Qt::blue);
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    setPalette(darkPalette);  // Aplicar el esquema de colores

    // Cambiar el color del texto en el editor
    TabDocument* doc = getCurrentDocument();
    if (doc) {
        if (doc->editor) {
            doc->editor->setStyleSheet("background-color: black; color: white;");
        }
        if (doc->browser) {
            doc->browser->setStyleSheet("background-color: black; color: white;");
        }
    }
}

// Función para aplicar el modo claro
void MarkdownEditor::setLightMode() {
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::AlternateBase, Qt::lightGray);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, Qt::lightGray);
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::Highlight, Qt::blue);
    lightPalette.setColor(QPalette::HighlightedText, Qt::black);
    setPalette(lightPalette);  // Aplicar el esquema de colores

    // Cambiar el color del texto en el editor
    TabDocument* doc = getCurrentDocument();
    if (doc) {
        if (doc->editor) {
            doc->editor->setStyleSheet("background-color: white; color: black;");
        }
        if (doc->browser) {
            doc->browser->setStyleSheet("background-color: white; color: black;");
        }
    }
}

void MarkdownEditor::renderMarkdown() {
    TabDocument* doc = getCurrentDocument();
    if (!doc || !doc->editor || !doc->browser) {
        return;
    }
    
    // Solo renderizar si es un archivo que debe mostrar vista previa
    if (!shouldRenderPreview(doc->filePath)) {
        return;
    }
    
    // Obtener el texto en Markdown desde el QTextEdit
    QString markdownText = doc->editor->toPlainText();
    
    // Verificar si hay tablas en el texto
    QRegularExpression tableRegex("\\|.*\\|");
    if (markdownText.contains(tableRegex)) {
        // Si hay tablas, procesar todo como HTML personalizado
        QString htmlContent = processMarkdownWithTables(markdownText);
        doc->browser->setHtml(htmlContent);
    } else {
        // Si no hay tablas, usar cmark normal
        QByteArray markdownByteArray = markdownText.toUtf8();
        int options = CMARK_OPT_HARDBREAKS;
        
        cmark_node *root = cmark_parse_document(markdownByteArray.constData(), markdownByteArray.size(), options);
        char *html = cmark_render_html(root, options);
        
        doc->browser->setHtml(QString::fromUtf8(html));
        
        free(html);
        cmark_node_free(root);
    }
}


// Implementación de exportToHTML
void MarkdownEditor::exportToHTML() {
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar como", "", "HTML files (*.html)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << browser->toHtml();  // Guardamos el contenido HTML del QTextBrowser
        }
    }
}

// Implementación de exportToPDF
void MarkdownEditor::exportToPDF() {
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar como PDF", "", "PDF files (*.pdf)");
    if (!fileName.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        
        QPainter painter;
        if (painter.begin(&printer)) {
            browser->document()->drawContents(&painter);
            painter.end();
        }
    }
}

void MarkdownEditor::saveToFile() {
    // Mostrar un cuadro de diálogo para elegir el archivo de destino
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "", 
        tr("Archivos Markdown (*.md);;Archivos de texto (*.txt);;Listas M3U (*.m3u);;Archivos de código (*.cpp *.h *.js *.py);;Todos los archivos (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    // Abrir el archivo en modo escritura
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // Escribir el contenido del editor al archivo
        out << editor->toPlainText();
        file.close();
    }
}

void MarkdownEditor::loadFromFile() {
    // Mostrar un cuadro de diálogo para elegir el archivo a cargar
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), "", 
        tr("Archivos Markdown (*.md);;Archivos de texto (*.txt);;Listas M3U (*.m3u);;Archivos de código (*.cpp *.h *.js *.py);;Todos los archivos (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    // Abrir el archivo en modo lectura
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        // Cargar el contenido del archivo en el editor
        editor->setPlainText(in.readAll());
        file.close();
    }
}

void MarkdownEditor::showManual() {
    QDialog* manualDialog = new QDialog(this);
    manualDialog->setWindowTitle("Manual de Markdown");
    manualDialog->setMinimumSize(600, 500);
    
    QVBoxLayout* layout = new QVBoxLayout(manualDialog);
    
    QScrollArea* scrollArea = new QScrollArea(manualDialog);
    QLabel* manualLabel = new QLabel();
    
    QString manualText = "<h1>Manual de Markdown</h1>"
                        "<h2>Encabezados</h2>"
                        "<p><strong># Encabezado 1</strong><br>"
                        "<strong>## Encabezado 2</strong><br>"
                        "<strong>### Encabezado 3</strong></p>"
                        
                        "<h2>Formato de Texto</h2>"
                        "<p><strong>**Texto en negrita**</strong><br>"
                        "<em>*Texto en cursiva*</em><br>"
                        "<code>`Código en línea`</code></p>"
                        
                        "<h2>Listas</h2>"
                        "<p><strong>Lista con viñetas:</strong><br>"
                        "- Elemento 1<br>"
                        "- Elemento 2<br>"
                        "- Elemento 3</p>"
                        
                        "<p><strong>Lista numerada:</strong><br>"
                        "1. Primer elemento<br>"
                        "2. Segundo elemento<br>"
                        "3. Tercer elemento</p>"
                        
                        "<h2>Enlaces</h2>"
                        "<p><strong>[Texto del enlace](https://ejemplo.com)</strong></p>"
                        
                        "<h2>Imágenes</h2>"
                        "<p><strong>![Texto alternativo](ruta/imagen.jpg)</strong></p>"
                        
                        "<h2>Código</h2>"
                        "<p><strong>Bloque de código:</strong><br>"
                        "```<br>"
                        "código aquí<br>"
                        "```</p>"
                        
                        "<h2>Citas</h2>"
                        "<p><strong>&gt; Esto es una cita</strong></p>"
                        
                        "<h2>Líneas Horizontales</h2>"
                        "<p><strong>---</strong> o <strong>***</strong></p>";
    
    manualLabel->setText(manualText);
    manualLabel->setWordWrap(true);
    manualLabel->setMargin(20);
    
    scrollArea->setWidget(manualLabel);
    scrollArea->setWidgetResizable(true);
    
    layout->addWidget(scrollArea);
    
    manualDialog->exec();
}

void MarkdownEditor::showAbout() {
    QDialog* aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle("Acerca de EscribeChanchi");
    aboutDialog->setFixedSize(500, 450);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(aboutDialog);
    
    // Crear un área de scroll
    QScrollArea* scrollArea = new QScrollArea(aboutDialog);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    // Widget contenedor para el contenido
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15);
    
    // Título del programa
    QLabel* titleLabel = new QLabel("<h1>EscribeChanchi</h1>");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    
    // Logo - usar recurso integrado
    QLabel* logoLabel = new QLabel();
    QPixmap logo(":/img/logo.png");  // Usar el logo original para la ventana About
    if (!logo.isNull()) {
        logoLabel->setPixmap(logo.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        logoLabel->setText("<p style='color: gray;'>[Logo no encontrado]</p>");
    }
    logoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(logoLabel);
    
    // Descripción completa
    QLabel* descLabel = new QLabel("<div style='text-align: center;'>"
                                  "<p><strong>EscribeChanchi</strong> es un editor de Markdown moderno y fácil de usar.</p>"
                                  "<p>Permite escribir y previsualizar documentos Markdown en tiempo real.</p>"
                                  "<br>"
                                  "<p><strong>Características principales:</strong></p>"
                                  "<p>✓ Vista previa en tiempo real</p>"
                                  "<p>✓ Modo oscuro y modo claro</p>"
                                  "<p>✓ Exportación a HTML y PDF</p>"
                                  "<p>✓ Interfaz intuitiva con menús</p>"
                                  "<p>✓ Manual de Markdown integrado</p>"
                                  "<p>✓ Atajos de teclado</p>"
                                  "<p>✓ Guardado y apertura de archivos</p>"
                                  "<p>✓ Resaltado de sintaxis Markdown</p>"
                                  "<br>"
                                  "<p><strong>Uso:</strong></p>"
                                  "<p>• Escribe Markdown en el panel izquierdo</p>"
                                  "<p>• Ve la vista previa en el panel derecho</p>"
                                  "<p>• Usa los menús para formatear y exportar</p>"
                                  "<p>• Consulta el Manual en Ayuda → Manual</p>"
                                  "<br>"
                                  "<p><em>Versión 1.0</em></p>"
                                  "</div>");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    descLabel->setMargin(20);
    layout->addWidget(descLabel);
    
    // Configurar el scroll area
    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);
    
    // Agregar botón de cerrar
    QPushButton* closeButton = new QPushButton("Cerrar");
    connect(closeButton, &QPushButton::clicked, aboutDialog, &QDialog::accept);
    mainLayout->addWidget(closeButton);
    
    aboutDialog->exec();
}

void MarkdownEditor::insertTable() {
    if (formatter) {
        formatter->insertTable();
    }
}

void MarkdownEditor::toggleLineNumbers() {
    TabDocument* doc = getCurrentDocument();
    if (!doc || !doc->editor) {
        return;
    }
    
    showLineNumbers = !showLineNumbers;
    
    if (showLineNumbers) {
        // Crear un estilo más visible para los números de línea
        QString lineNumberStyle = QString(
            "QTextEdit { "
            "   border-left: 40px solid %1; "
            "   padding-left: 10px; "
            "   background-color: %2; "
            "} "
        ).arg(darkMode ? "#3c3c3c" : "#f0f0f0", darkMode ? "#2b2b2b" : "#ffffff");
        
        doc->editor->setStyleSheet(lineNumberStyle);
        
        // Añadir números visualmente en el contenido
        QString content = doc->editor->toPlainText();
        if (!content.contains("│")) {  // Solo si no tiene ya números
            QStringList lines = content.split('\n');
            QString numberedContent;
            for (int i = 0; i < lines.size(); i++) {
                numberedContent += QString("%1 │ %2\n").arg(i + 1, 3).arg(lines[i]);
            }
            
            // Desconectar temporalmente para evitar recursión
            disconnect(doc->editor, &QTextEdit::textChanged, this, &MarkdownEditor::renderMarkdown);
            doc->editor->setPlainText(numberedContent);
            connect(doc->editor, &QTextEdit::textChanged, this, &MarkdownEditor::renderMarkdown);
        }
    } else {
        // Remover números de línea
        doc->editor->setStyleSheet(darkMode ? 
            "background-color: #2b2b2b; color: white;" : 
            "background-color: white; color: black;");
        
        // Remover números del contenido
        QString content = doc->editor->toPlainText();
        if (content.contains("│")) {
            QStringList lines = content.split('\n');
            QString cleanContent;
            for (const QString &line : lines) {
                int separatorIndex = line.indexOf("│");
                if (separatorIndex > 0) {
                    cleanContent += line.mid(separatorIndex + 2) + '\n';
                } else {
                    cleanContent += line + '\n';
                }
            }
            
            // Desconectar temporalmente para evitar recursión
            disconnect(doc->editor, &QTextEdit::textChanged, this, &MarkdownEditor::renderMarkdown);
            doc->editor->setPlainText(cleanContent.trimmed());
            connect(doc->editor, &QTextEdit::textChanged, this, &MarkdownEditor::renderMarkdown);
        }
    }
}

void MarkdownEditor::updateLineNumbers() {
    if (!showLineNumbers) return;
    
    // Esta es una implementación básica usando tooltip
    // Para una implementación completa se necesitaría un widget personalizado
    QTextCursor cursor = editor->textCursor();
    int currentLine = cursor.blockNumber() + 1;
    int totalLines = editor->document()->blockCount();
    
    // Mostrar información de línea en la barra de estado (si la tuviéramos)
    // Por ahora, cambiaremos el color del borde para indicar actividad
    QString lineStyle = QString(
        "QTextEdit { "
        "   padding-left: 50px; "
        "   border-left: 3px solid %1; "
        "} "
    ).arg(darkMode ? "#555555" : "#cccccc");
    
    // Aplicar el estilo manteniendo el estilo existente
    QString currentStyle = editor->styleSheet();
    QRegularExpression borderRegex("border-left:\\s*[^;]+;");
    currentStyle.replace(borderRegex, QString("border-left: 3px solid %1;").arg(darkMode ? "#555555" : "#cccccc"));
    
    editor->setStyleSheet(currentStyle);
}

QString MarkdownEditor::processTablesManually(const QString &text) {
    QString result = text;
    QStringList lines = result.split('\n');
    QString processedText;
    
    for (int i = 0; i < lines.size(); i++) {
        QString line = lines[i].trimmed();
        
        // Detectar si es una línea de tabla (contiene |)
        if (line.contains('|') && !line.isEmpty()) {
            // Buscar el encabezado, separador y filas de datos
            QStringList tableLines;
            int startIndex = i;
            
            // Recopilar todas las líneas de la tabla
            while (i < lines.size() && lines[i].trimmed().contains('|') && !lines[i].trimmed().isEmpty()) {
                tableLines.append(lines[i].trimmed());
                i++;
            }
            i--; // Ajustar porque el bucle for incrementará i
            
            if (tableLines.size() >= 2) {
                // Convertir a HTML
                QString tableHtml = "<table border='1' style='border-collapse: collapse; margin: 10px 0;'>";
                
                // Primera fila como encabezado
                if (tableLines.size() > 0) {
                    QString headerRow = tableLines[0];
                    QStringList headers = headerRow.split('|');
                    tableHtml += "<tr style='background-color: #f0f0f0; font-weight: bold;'>";
                    for (const QString &header : headers) {
                        QString cleanHeader = header.trimmed();
                        if (!cleanHeader.isEmpty()) {
                            tableHtml += "<td style='padding: 8px; border: 1px solid #ddd;'>" + cleanHeader + "</td>";
                        }
                    }
                    tableHtml += "</tr>";
                }
                
                // Saltar la línea separadora (segunda línea con ---)
                for (int j = 2; j < tableLines.size(); j++) {
                    QString dataRow = tableLines[j];
                    QStringList cells = dataRow.split('|');
                    tableHtml += "<tr>";
                    for (const QString &cell : cells) {
                        QString cleanCell = cell.trimmed();
                        if (!cleanCell.isEmpty()) {
                            tableHtml += "<td style='padding: 8px; border: 1px solid #ddd;'>" + cleanCell + "</td>";
                        }
                    }
                    tableHtml += "</tr>";
                }
                
                tableHtml += "</table>";
                processedText += tableHtml + "\n";
            } else {
                // No es una tabla válida, añadir las líneas normalmente
                for (const QString &tableLine : tableLines) {
                    processedText += tableLine + "\n";
                }
            }
        } else {
            processedText += line + "\n";
        }
    }
    
    return processedText;
}

QString MarkdownEditor::processMarkdownWithTables(const QString &text) {
    QStringList lines = text.split('\n');
    QString htmlResult = "<html><body style='font-family: Arial, sans-serif; line-height: 1.6; margin: 20px;'>";
    
    bool inTable = false;
    QString currentTable;
    
    for (int i = 0; i < lines.size(); i++) {
        QString line = lines[i];
        
        // Detectar si es una línea de tabla
        if (line.contains('|') && !line.trimmed().isEmpty()) {
            if (!inTable) {
                inTable = true;
                currentTable = "";
            }
            currentTable += line + "\n";
        } else {
            // Si estábamos en una tabla, procesarla
            if (inTable) {
                htmlResult += convertTableToHtml(currentTable);
                inTable = false;
                currentTable = "";
            }
            
            // Procesar línea normal de Markdown
            htmlResult += processMarkdownLine(line);
        }
    }
    
    // Si terminamos en una tabla
    if (inTable) {
        htmlResult += convertTableToHtml(currentTable);
    }
    
    htmlResult += "</body></html>";
    return htmlResult;
}

QString MarkdownEditor::convertTableToHtml(const QString &tableText) {
    QStringList lines = tableText.split('\n', Qt::SkipEmptyParts);
    if (lines.size() < 2) return tableText; // No es una tabla válida
    
    QString html = "<table style='border-collapse: collapse; margin: 15px 0; width: 100%; border: 1px solid #ddd;'>";
    
    // Primera fila como encabezado
    QString headerLine = lines[0].trimmed();
    if (headerLine.startsWith('|')) headerLine = headerLine.mid(1);
    if (headerLine.endsWith('|')) headerLine.chop(1);
    
    QStringList headers = headerLine.split('|');
    html += "<tr style='background-color: #f5f5f5;'>";
    for (const QString &header : headers) {
        html += "<th style='border: 1px solid #ddd; padding: 12px; text-align: left; font-weight: bold;'>" 
                + header.trimmed() + "</th>";
    }
    html += "</tr>";
    
    // Saltar línea separadora y procesar filas de datos
    for (int i = 2; i < lines.size(); i++) {
        QString dataLine = lines[i].trimmed();
        if (dataLine.startsWith('|')) dataLine = dataLine.mid(1);
        if (dataLine.endsWith('|')) dataLine.chop(1);
        
        QStringList cells = dataLine.split('|');
        html += "<tr>";
        for (const QString &cell : cells) {
            html += "<td style='border: 1px solid #ddd; padding: 12px;'>" + cell.trimmed() + "</td>";
        }
        html += "</tr>";
    }
    
    html += "</table>";
    return html;
}

QString MarkdownEditor::processMarkdownLine(const QString &line) {
    QString result = line;
    
    // Encabezados
    if (result.startsWith("# ")) {
        return "<h1>" + result.mid(2) + "</h1>";
    } else if (result.startsWith("## ")) {
        return "<h2>" + result.mid(3) + "</h2>";
    } else if (result.startsWith("### ")) {
        return "<h3>" + result.mid(4) + "</h3>";
    }
    
    // Negrita **texto**
    QRegularExpression boldRegex("\\*\\*(.*?)\\*\\*");
    result.replace(boldRegex, "<strong>\\1</strong>");
    
    // Cursiva *texto*
    QRegularExpression italicRegex("\\*(.*?)\\*");
    result.replace(italicRegex, "<em>\\1</em>");
    
    // Código `texto`
    QRegularExpression codeRegex("`(.*?)`");
    result.replace(codeRegex, "<code style='background-color: #f4f4f4; padding: 2px 4px; border-radius: 3px;'>\\1</code>");
    
    // Tachado ~~texto~~
    QRegularExpression strikeRegex("~~(.*?)~~");
    result.replace(strikeRegex, "<del>\\1</del>");
    
    // Citas
    if (result.trimmed().startsWith("> ")) {
        return "<blockquote style='border-left: 4px solid #ddd; padding-left: 16px; margin: 10px 0; color: #666;'>" 
               + result.mid(result.indexOf("> ") + 2) + "</blockquote>";
    }
    
    // Listas
    if (result.trimmed().startsWith("- ")) {
        return "<ul><li>" + result.mid(result.indexOf("- ") + 2) + "</li></ul>";
    } else {
        QRegularExpression listRegex("^\\d+\\. ");
        if (listRegex.match(result.trimmed()).hasMatch()) {
            return "<ol><li>" + result.mid(result.indexOf(". ") + 2) + "</li></ol>";
        }
    }
    
    // Líneas horizontales
    if (result.trimmed() == "---" || result.trimmed() == "***") {
        return "<hr style='border: none; border-top: 2px solid #ddd; margin: 20px 0;'>";
    }
    
    // Párrafos normales
    if (!result.trimmed().isEmpty()) {
        return "<p>" + result + "</p>";
    }
    
    return "<br>";
}

void MarkdownEditor::showTemplates() {
    if (templateManager) {
        templateManager->showTemplateDialog(editor);
    }
}

void MarkdownEditor::createTemplate() {
    if (templateManager) {
        templateManager->showCreateTemplateDialog(editor);
    }
}

// Funciones para manejo de pestañas

TabDocument* MarkdownEditor::createNewDocument() {
    TabDocument* doc = new TabDocument();
    
    // Crear los widgets
    doc->editor = new QTextEdit();
    doc->browser = new QTextBrowser();
    doc->splitter = new QSplitter(Qt::Horizontal);
    
    // Agregar widgets al splitter
    doc->splitter->addWidget(doc->editor);
    doc->splitter->addWidget(doc->browser);
    
    // Configurar documento
    doc->fileName = QString("Sin título %1").arg(untitledCounter++);
    doc->isNewFile = true;
    doc->isModified = false;
    
    // Configurar conexiones
    setupDocumentConnections(doc);
    
    return doc;
}

TabDocument* MarkdownEditor::getCurrentDocument() {
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex >= 0 && currentIndex < documents.size()) {
        return documents[currentIndex];
    }
    return nullptr;
}

void MarkdownEditor::setupDocumentConnections(TabDocument* doc) {
    // Conectar para renderizado automático
    connect(doc->editor, &QTextEdit::textChanged, [this, doc]() {
        if (doc == getCurrentDocument()) {
            renderMarkdown();
        }
        if (!doc->isModified) {
            doc->isModified = true;
            updateTabTitle(documents.indexOf(doc));
        }
    });
    
    // Conectar para numeración de líneas
    connect(doc->editor, &QTextEdit::cursorPositionChanged, this, &MarkdownEditor::updateLineNumbers);
}

void MarkdownEditor::updateTabTitle(int index) {
    if (index >= 0 && index < documents.size()) {
        TabDocument* doc = documents[index];
        QString title = doc->fileName;
        if (doc->isModified) {
            title += " *";
        }
        tabWidget->setTabText(index, title);
    }
}

void MarkdownEditor::newTab() {
    TabDocument* doc = createNewDocument();
    documents.append(doc);
    
    int index = tabWidget->addTab(doc->splitter, doc->fileName);
    tabWidget->setCurrentIndex(index);
    
    // Actualizar punteros de compatibilidad
    editor = doc->editor;
    browser = doc->browser;
    splitter = doc->splitter;
    
    // Recrear formatter para el nuevo editor
    if (formatter) {
        delete formatter;
    }
    formatter = new MarkdownFormatter(editor, this);
    
    // Configurar estilos si está en modo oscuro
    if (darkMode) {
        setDarkMode();
    } else {
        setLightMode();
    }
}

void MarkdownEditor::openFileInNewTab() {
    QString fileName = QFileDialog::getOpenFileName(this, 
        "Abrir archivo", "", "Archivos de texto (*.md *.txt *.m3u *.cpp *.h *.js *.py *.html *.css *.xml *.json);;Archivos Markdown (*.md);;Todos los archivos (*)");
    
    if (!fileName.isEmpty()) {
        // Crear nueva pestaña
        TabDocument* doc = createNewDocument();
        documents.append(doc);
        
        // Cargar archivo
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            doc->editor->setPlainText(in.readAll());
            
            QFileInfo fileInfo(fileName);
            doc->fileName = fileInfo.fileName();
            doc->filePath = fileName;
            doc->isNewFile = false;
            doc->isModified = false;
            
            // Configurar el editor según el tipo de archivo
            QString fileType = getFileType(fileName);
            
            // Si no es archivo Markdown, ocultar la vista previa
            if (!shouldRenderPreview(fileName)) {
                doc->browser->hide();
                // Mostrar solo el editor
                doc->splitter->setSizes({1, 0});
            } else {
                doc->browser->show();
                doc->splitter->setSizes({1, 1});
            }
            
            int index = tabWidget->addTab(doc->splitter, doc->fileName);
            tabWidget->setCurrentIndex(index);
            
            // Actualizar título de ventana con indicador de tipo
            QString windowTitle = "EscribeChanchi - " + doc->fileName;
            if (fileType != "markdown" && fileType != "text") {
                windowTitle += QString(" (%1)").arg(fileType.toUpper());
            }
            setWindowTitle(windowTitle);
        }
    }
}

void MarkdownEditor::closeTab(int index) {
    if (index >= 0 && index < documents.size()) {
        TabDocument* doc = documents[index];
        
        if (closeDocument(doc)) {
            documents.removeAt(index);
            tabWidget->removeTab(index);
            delete doc;
            
            // Si no quedan pestañas, crear una nueva
            if (documents.isEmpty()) {
                newTab();
            }
        }
    }
}

void MarkdownEditor::closeCurrentTab() {
    int currentIndex = tabWidget->currentIndex();
    closeTab(currentIndex);
}

void MarkdownEditor::tabChanged(int index) {
    if (index >= 0 && index < documents.size()) {
        TabDocument* doc = documents[index];
        
        // Actualizar punteros de compatibilidad
        editor = doc->editor;
        browser = doc->browser;
        splitter = doc->splitter;
        
        // Recrear formatter para el editor actual
        if (formatter) {
            delete formatter;
        }
        formatter = new MarkdownFormatter(editor, this);
        
        // Actualizar título de ventana con tipo de archivo
        QString windowTitle = "EscribeChanchi";
        if (!doc->fileName.isEmpty()) {
            windowTitle += " - " + doc->fileName;
            QString fileType = getFileType(doc->filePath);
            if (fileType != "markdown" && fileType != "text") {
                windowTitle += QString(" (%1)").arg(fileType.toUpper());
            }
        }
        setWindowTitle(windowTitle);
        
        // Renderizar el contenido actual
        renderMarkdown();
        
        // Aplicar estilo actual
        if (darkMode) {
            setDarkMode();
        } else {
            setLightMode();
        }
    }
}

bool MarkdownEditor::closeDocument(TabDocument* doc) {
    if (doc->isModified) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
            "Documento modificado",
            QString("El documento '%1' ha sido modificado.\n¿Desea guardar los cambios?")
                .arg(doc->fileName),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (reply == QMessageBox::Save) {
            return saveDocument(doc);
        } else if (reply == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MarkdownEditor::saveDocument(TabDocument* doc) {
    if (doc->isNewFile || doc->filePath.isEmpty()) {
        return saveDocumentAs(doc);
    }
    
    QFile file(doc->filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << doc->editor->toPlainText();
        
        doc->isModified = false;
        updateTabTitle(documents.indexOf(doc));
        return true;
    }
    
    QMessageBox::warning(this, "Error", "No se pudo guardar el archivo.");
    return false;
}

bool MarkdownEditor::saveDocumentAs(TabDocument* doc) {
    QString fileName = QFileDialog::getSaveFileName(this,
        "Guardar archivo", doc->fileName, "Archivos Markdown (*.md);;Archivos de texto (*.txt);;Listas M3U (*.m3u);;Archivos de código (*.cpp *.h *.js *.py);;Todos los archivos (*)");
    
    if (!fileName.isEmpty()) {
        doc->filePath = fileName;
        QFileInfo fileInfo(fileName);
        doc->fileName = fileInfo.fileName();
        doc->isNewFile = false;
        
        if (saveDocument(doc)) {
            updateTabTitle(documents.indexOf(doc));
            return true;
        }
    }
    return false;
}

void MarkdownEditor::saveCurrentFile() {
    TabDocument* doc = getCurrentDocument();
    if (doc) {
        saveDocument(doc);
    }
}

void MarkdownEditor::saveFileAs() {
    TabDocument* doc = getCurrentDocument();
    if (doc) {
        saveDocumentAs(doc);
    }
}

void MarkdownEditor::documentModified() {
    TabDocument* doc = getCurrentDocument();
    if (doc && !doc->isModified) {
        doc->isModified = true;
        updateTabTitle(documents.indexOf(doc));
    }
}

// Funciones para la bandeja del sistema
void MarkdownEditor::setupSystemTray() {
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        return;
    }
    
    createTrayIcon();
    
    // Mostrar el icono en la bandeja
    if (trayIcon) {
        trayIcon->show();
    }
}

void MarkdownEditor::createTrayIcon() {
    // Crear menú de la bandeja del sistema
    trayIconMenu = new QMenu(this);
    
    showAction = new QAction("&Mostrar", this);
    connect(showAction, &QAction::triggered, this, &MarkdownEditor::showFromTray);
    trayIconMenu->addAction(showAction);
    
    hideAction = new QAction("&Minimizar", this);
    connect(hideAction, &QAction::triggered, this, &MarkdownEditor::hideToTray);
    trayIconMenu->addAction(hideAction);
    
    trayIconMenu->addSeparator();
    
    QAction *newAction = new QAction("&Nuevo", this);
    connect(newAction, &QAction::triggered, this, &MarkdownEditor::newTab);
    trayIconMenu->addAction(newAction);
    
    QAction *openAction = new QAction("&Abrir", this);
    connect(openAction, &QAction::triggered, this, &MarkdownEditor::openFileInNewTab);
    trayIconMenu->addAction(openAction);
    
    trayIconMenu->addSeparator();
    
    exitAction = new QAction("&Salir", this);
    connect(exitAction, &QAction::triggered, this, &MarkdownEditor::exitApplication);
    trayIconMenu->addAction(exitAction);
    
    // Crear icono de la bandeja
    trayIcon = new QSystemTrayIcon(this);
    
    // Usar un icono por defecto si no se encuentra el archivo
    QIcon icon = QIcon(":/img/logo_escribe_chanchi.png");  // Usar el icono del programa
    if (icon.isNull()) {
        // Crear un icono simple con texto si no hay imagen
        QPixmap pixmap(32, 32);
        pixmap.fill(QColor(70, 130, 180)); // Color azul
        QPainter painter(&pixmap);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(pixmap.rect(), Qt::AlignCenter, "EC");
        icon = QIcon(pixmap);
    }
    
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setToolTip("Escribe Chanchi - Editor de Markdown");
    
    // Conectar señales
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MarkdownEditor::trayIconActivated);
}

void MarkdownEditor::showFromTray() {
    showNormal();
    raise();
    activateWindow();
}

void MarkdownEditor::hideToTray() {
    hide();
    
    // Mostrar mensaje la primera vez
    static bool firstTime = true;
    if (firstTime && trayIcon) {
        trayIcon->showMessage("Escribe Chanchi",
                             "La aplicación se minimizó a la bandeja del sistema.\n"
                             "Haz clic en el icono para restaurarla.",
                             QSystemTrayIcon::Information, 2000);
        firstTime = false;
    }
}

void MarkdownEditor::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (isVisible()) {
            hideToTray();
        } else {
            showFromTray();
        }
        break;
    default:
        break;
    }
}

void MarkdownEditor::exitApplication() {
    // Forzar el cierre completo
    QApplication::quit();
}

void MarkdownEditor::closeEvent(QCloseEvent *event) {
    // Si hay bandeja del sistema disponible, minimizar en lugar de cerrar
    if (trayIcon && trayIcon->isVisible()) {
        hideToTray();
        event->ignore();
        return;
    }
    
    // Si no hay bandeja del sistema, proceder con el cierre normal
    bool hasModified = false;
    for (TabDocument* doc : documents) {
        if (doc->isModified) {
            hasModified = true;
            break;
        }
    }
    
    if (hasModified) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
            "Cerrar EscribeChanchi",
            "Hay documentos con cambios sin guardar.\n¿Está seguro de que desea cerrar?",
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::No) {
            event->ignore();
            return;
        }
    }
    
    // Limpiar memoria
    for (TabDocument* doc : documents) {
        delete doc;
    }
    documents.clear();
    
    event->accept();
}

void MarkdownEditor::toggleFullScreen() {
    if (isFullScreenMode) {
        // Salir de pantalla completa y volver al estado maximizado
        showNormal();
        showMaximized();
        isFullScreenMode = false;
        
        // Mostrar la barra de menús y herramientas cuando no está en pantalla completa
        menuBar()->show();
        if (mainToolBar) {
            mainToolBar->show();
        }
    } else {
        // Entrar en pantalla completa
        showFullScreen();
        isFullScreenMode = true;
        
        // Ocultar la barra de menús y herramientas en pantalla completa (opcional)
        // menuBar()->hide();
        // if (mainToolBar) {
        //     mainToolBar->hide();
        // }
    }
}

// Funciones para manejo de tipos de archivo
QString MarkdownEditor::getFileType(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();
    
    if (extension == "md" || extension == "markdown") {
        return "markdown";
    } else if (extension == "txt") {
        return "text";
    } else if (extension == "m3u") {
        return "playlist";
    } else if (extension == "cpp" || extension == "h" || extension == "hpp" || extension == "c") {
        return "cpp";
    } else if (extension == "js" || extension == "json") {
        return "javascript";
    } else if (extension == "py") {
        return "python";
    } else if (extension == "html" || extension == "htm") {
        return "html";
    } else if (extension == "css") {
        return "css";
    } else if (extension == "xml") {
        return "xml";
    }
    return "text"; // Por defecto, tratar como texto
}

bool MarkdownEditor::isMarkdownFile(const QString& filePath) {
    return getFileType(filePath) == "markdown";
}

bool MarkdownEditor::shouldRenderPreview(const QString& filePath) {
    QString type = getFileType(filePath);
    // Solo renderizar vista previa para archivos Markdown
    return type == "markdown";
}
