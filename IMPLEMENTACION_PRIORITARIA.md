# 🔧 IMPLEMENTACIÓN PRÁCTICA - FUNCIONALIDADES PRIORITARIAS

## 1️⃣ **BUSCAR Y REEMPLAZAR (ALTA PRIORIDAD)**

### 📋 **Funcionalidad**
Implementar diálogo de búsqueda con Ctrl+F y reemplazar con Ctrl+H

### 💻 **Código Ejemplo**

#### Header (markdow_editor.h)
```cpp
private slots:
    void showFindDialog();
    void showReplaceDialog();
    void findNext();
    void findPrevious();
    void replaceNext();
    void replaceAll();

private:
    QDialog* findDialog;
    QDialog* replaceDialog;
    QLineEdit* findLineEdit;
    QLineEdit* replaceLineEdit;
    QString lastSearchText;
    bool caseSensitive;
    bool wholeWords;
```

#### Implementación Básica
```cpp
void MarkdownEditor::showFindDialog() {
    if (!findDialog) {
        findDialog = new QDialog(this);
        findDialog->setWindowTitle("Buscar");
        findDialog->setFixedSize(400, 150);
        
        QVBoxLayout* layout = new QVBoxLayout();
        
        findLineEdit = new QLineEdit();
        findLineEdit->setPlaceholderText("Texto a buscar...");
        
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        QPushButton* findNextBtn = new QPushButton("Siguiente");
        QPushButton* findPrevBtn = new QPushButton("Anterior");
        QPushButton* closeBtn = new QPushButton("Cerrar");
        
        connect(findNextBtn, &QPushButton::clicked, this, &MarkdownEditor::findNext);
        connect(findPrevBtn, &QPushButton::clicked, this, &MarkdownEditor::findPrevious);
        connect(closeBtn, &QPushButton::clicked, findDialog, &QDialog::close);
        
        buttonLayout->addWidget(findNextBtn);
        buttonLayout->addWidget(findPrevBtn);
        buttonLayout->addWidget(closeBtn);
        
        layout->addWidget(new QLabel("Buscar:"));
        layout->addWidget(findLineEdit);
        layout->addLayout(buttonLayout);
        
        findDialog->setLayout(layout);
    }
    
    findDialog->show();
    findLineEdit->setFocus();
    findLineEdit->selectAll();
}

void MarkdownEditor::findNext() {
    TabDocument* doc = getCurrentDocument();
    if (!doc || !doc->editor) return;
    
    QString searchText = findLineEdit->text();
    if (searchText.isEmpty()) return;
    
    QTextDocument::FindFlags flags;
    if (caseSensitive) flags |= QTextDocument::FindCaseSensitively;
    if (wholeWords) flags |= QTextDocument::FindWholeWords;
    
    if (!doc->editor->find(searchText, flags)) {
        // Si no encuentra, ir al inicio y buscar de nuevo
        QTextCursor cursor = doc->editor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        doc->editor->setTextCursor(cursor);
        doc->editor->find(searchText, flags);
    }
}
```

---

## 2️⃣ **IR A LÍNEA (ALTA PRIORIDAD)**

### 📋 **Funcionalidad**
Diálogo para saltar directamente a una línea específica con Ctrl+G

### 💻 **Código Ejemplo**

```cpp
// En header
private slots:
    void goToLine();

// Implementación
void MarkdownEditor::goToLine() {
    TabDocument* doc = getCurrentDocument();
    if (!doc || !doc->editor) return;
    
    bool ok;
    int totalLines = doc->editor->document()->blockCount();
    int line = QInputDialog::getInt(this, 
        "Ir a línea", 
        QString("Línea (1-%1):").arg(totalLines),
        1, 1, totalLines, 1, &ok);
    
    if (ok) {
        QTextCursor cursor = doc->editor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line - 1);
        doc->editor->setTextCursor(cursor);
        doc->editor->centerCursor();
        doc->editor->setFocus();
    }
}

// En setupMenuBar() agregar:
QAction* goToLineAction = new QAction("Ir a línea...", this);
goToLineAction->setShortcut(QKeySequence("Ctrl+G"));
connect(goToLineAction, &QAction::triggered, this, &MarkdownEditor::goToLine);
editMenu->addAction(goToLineAction);
```

---

## 3️⃣ **AUTO-GUARDADO (ALTA PRIORIDAD)**

### 📋 **Funcionalidad**
Guardado automático cada X minutos configurable

### 💻 **Código Ejemplo**

```cpp
// En header
private:
    QTimer* autoSaveTimer;
    int autoSaveInterval; // en segundos
    bool autoSaveEnabled;

private slots:
    void autoSave();
    void setupAutoSave();

// Implementación
void MarkdownEditor::setupAutoSave() {
    autoSaveTimer = new QTimer(this);
    autoSaveInterval = 300; // 5 minutos por defecto
    autoSaveEnabled = true;
    
    connect(autoSaveTimer, &QTimer::timeout, this, &MarkdownEditor::autoSave);
    
    if (autoSaveEnabled) {
        autoSaveTimer->start(autoSaveInterval * 1000);
    }
}

void MarkdownEditor::autoSave() {
    for (TabDocument* doc : documents) {
        if (doc && doc->isModified && !doc->filePath.isEmpty()) {
            saveFile(doc->filePath, doc);
            
            // Mostrar notificación discreta
            statusBar()->showMessage("Auto-guardado: " + doc->fileName, 2000);
        }
    }
}

// En constructor agregar:
setupAutoSave();
```

---

## 4️⃣ **CONTADOR DE PALABRAS (ALTA PRIORIDAD)**

### 📋 **Funcionalidad**
Contador en tiempo real en la barra de estado

### 💻 **Código Ejemplo**

```cpp
// En header
private:
    QLabel* wordCountLabel;
    QLabel* charCountLabel;

private slots:
    void updateWordCount();

// Implementación
void MarkdownEditor::updateWordCount() {
    TabDocument* doc = getCurrentDocument();
    if (!doc || !doc->editor) {
        wordCountLabel->setText("Palabras: 0");
        charCountLabel->setText("Caracteres: 0");
        return;
    }
    
    QString text = doc->editor->toPlainText();
    
    // Contar palabras (split por espacios y filtrar vacíos)
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    int wordCount = words.size();
    
    // Contar caracteres (con y sin espacios)
    int charCount = text.length();
    int charCountNoSpaces = text.remove(QRegularExpression("\\s")).length();
    
    wordCountLabel->setText(QString("Palabras: %1").arg(wordCount));
    charCountLabel->setText(QString("Caracteres: %1 (%2 sin espacios)").arg(charCount).arg(charCountNoSpaces));
}

// En constructor, después de crear statusBar():
wordCountLabel = new QLabel("Palabras: 0");
charCountLabel = new QLabel("Caracteres: 0");
statusBar()->addPermanentWidget(wordCountLabel);
statusBar()->addPermanentWidget(charCountLabel);

// En setupDocumentConnections agregar:
connect(doc->editor, &QTextEdit::textChanged, this, &MarkdownEditor::updateWordCount);
```

---

## 5️⃣ **DRAG & DROP DE IMÁGENES (MEDIA PRIORIDAD)**

### 📋 **Funcionalidad**
Arrastrar imágenes desde el explorador de archivos al editor

### 💻 **Código Ejemplo**

```cpp
// En header
protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    bool isImageFile(const QString& filePath);
    QString copyImageToProject(const QString& imagePath);

// Implementación
void MarkdownEditor::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        for (const QUrl& url : urls) {
            QString filePath = url.toLocalFile();
            if (isImageFile(filePath)) {
                event->acceptProposedAction();
                return;
            }
        }
    }
    event->ignore();
}

void MarkdownEditor::dropEvent(QDropEvent* event) {
    TabDocument* doc = getCurrentDocument();
    if (!doc || !doc->editor) return;
    
    QList<QUrl> urls = event->mimeData()->urls();
    for (const QUrl& url : urls) {
        QString filePath = url.toLocalFile();
        if (isImageFile(filePath)) {
            // Copiar imagen a directorio del proyecto (opcional)
            QString relativePath = copyImageToProject(filePath);
            
            // Insertar markdown de imagen
            QTextCursor cursor = doc->editor->textCursor();
            QFileInfo fileInfo(filePath);
            QString markdownImg = QString("![%1](%2)")
                .arg(fileInfo.baseName())
                .arg(relativePath.isEmpty() ? filePath : relativePath);
            
            cursor.insertText(markdownImg);
            doc->isModified = true;
            updateTabTitle(documents.indexOf(doc));
        }
    }
    event->acceptProposedAction();
}

bool MarkdownEditor::isImageFile(const QString& filePath) {
    QStringList imageExtensions = {"png", "jpg", "jpeg", "gif", "bmp", "svg", "webp"};
    QFileInfo fileInfo(filePath);
    return imageExtensions.contains(fileInfo.suffix().toLower());
}

// En constructor agregar:
setAcceptDrops(true);
```

---

## 🚀 **PLAN DE IMPLEMENTACIÓN INCREMENTAL**

### **Semana 1:**
- ✅ Implementar buscar/reemplazar básico
- ✅ Agregar ir a línea
- ✅ Configurar shortcuts (Ctrl+F, Ctrl+H, Ctrl+G)

### **Semana 2:**
- ✅ Implementar auto-guardado
- ✅ Agregar contador de palabras
- ✅ Pulir interfaz de búsqueda

### **Semana 3:**
- ✅ Implementar drag & drop de imágenes
- ✅ Mejorar barra de estado
- ✅ Testing y debugging

### **Semana 4:**
- ✅ Documentación de nuevas funcionalidades
- ✅ Testing de integración
- ✅ Optimización de rendimiento

---

## 📊 **IMPACTO ESPERADO**

| Funcionalidad | Antes | Después |
|---------------|-------|---------|
| **Navegación** | Manual/limitada | Rápida con Ctrl+G |
| **Búsqueda** | No disponible | Buscar/reemplazar completo |
| **Seguridad** | Solo guardado manual | Auto-guardado automático |
| **Métricas** | Sin información | Contador palabras/caracteres |
| **Multimedia** | Solo texto | Imágenes drag & drop |

---

## ✅ **BENEFICIOS INMEDIATOS**

1. **🔍 Búsqueda**: Funcionalidad esencial para cualquier editor
2. **📐 Navegación**: Salto rápido en documentos largos  
3. **💾 Seguridad**: Prevención de pérdida de datos
4. **📊 Productividad**: Métricas útiles para escritores
5. **🖼️ Multimedia**: Soporte visual moderno

**Estas 5 funcionalidades transformarían Escribe Chanchi en un editor significativamente más potente y profesional.**

---

*Guía de implementación práctica - 24 de junio de 2025*
