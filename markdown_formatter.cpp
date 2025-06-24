#include "markdown_formatter.h"

MarkdownFormatter::MarkdownFormatter(QTextEdit *editor, QObject *parent) 
    : QObject(parent), textEditor(editor) {
}

void MarkdownFormatter::setBold() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("**" + selectedText + "**");
    } else {
        cursor.insertText("****");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::setItalic() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("*" + selectedText + "*");
    } else {
        cursor.insertText("**");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::setCode() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("`" + selectedText + "`");
    } else {
        cursor.insertText("``");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::setHeader() {
    QTextCursor cursor = textEditor->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("# " + selectedText);
    } else {
        cursor.insertText("# ");
    }
}

void MarkdownFormatter::setStrikethrough() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("~~" + selectedText + "~~");
    } else {
        cursor.insertText("~~~~");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::setBlockquote() {
    QTextCursor cursor = textEditor->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("> ");
}

void MarkdownFormatter::setUnorderedList() {
    QTextCursor cursor = textEditor->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("- ");
}

void MarkdownFormatter::setOrderedList() {
    QTextCursor cursor = textEditor->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("1. ");
}

void MarkdownFormatter::setLink() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("[" + selectedText + "](url)");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 4);
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 3);
        textEditor->setTextCursor(cursor);
    } else {
        cursor.insertText("[texto del enlace](url)");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 21);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 16);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::setImage() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("![" + selectedText + "](ruta/imagen.jpg)");
    } else {
        cursor.insertText("![texto alternativo](ruta/imagen.jpg)");
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 36);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 18);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::setHorizontalRule() {
    QTextCursor cursor = textEditor->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertText("\n---\n");
}

void MarkdownFormatter::setCodeBlock() {
    QTextCursor cursor = textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        cursor.insertText("```\n" + selectedText + "\n```");
    } else {
        cursor.insertText("```\n\n```");
        cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, 1);
        textEditor->setTextCursor(cursor);
    }
}

void MarkdownFormatter::insertTable() {
    QDialog* tableDialog = new QDialog();
    tableDialog->setWindowTitle("Insertar Tabla");
    tableDialog->setFixedSize(300, 150);
    
    QFormLayout* layout = new QFormLayout(tableDialog);
    
    QSpinBox* rowsSpinBox = new QSpinBox();
    rowsSpinBox->setRange(2, 20);
    rowsSpinBox->setValue(3);
    layout->addRow("Filas:", rowsSpinBox);
    
    QSpinBox* colsSpinBox = new QSpinBox();
    colsSpinBox->setRange(2, 10);
    colsSpinBox->setValue(3);
    layout->addRow("Columnas:", colsSpinBox);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancelar");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addRow(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, tableDialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, tableDialog, &QDialog::reject);
    
    if (tableDialog->exec() == QDialog::Accepted) {
        int rows = rowsSpinBox->value();
        int cols = colsSpinBox->value();
        
        QString table = "\n";
        
        // Fila de encabezados
        table += "|";
        for (int j = 0; j < cols; j++) {
            table += " Encabezado " + QString::number(j + 1) + " |";
        }
        table += "\n";
        
        // Fila separadora
        table += "|";
        for (int j = 0; j < cols; j++) {
            table += " --- |";
        }
        table += "\n";
        
        // Filas de datos
        for (int i = 0; i < rows - 1; i++) {
            table += "|";
            for (int j = 0; j < cols; j++) {
                table += " Celda " + QString::number(i + 1) + "," + QString::number(j + 1) + " |";
            }
            table += "\n";
        }
        table += "\n";
        
        QTextCursor cursor = textEditor->textCursor();
        cursor.insertText(table);
    }
    
    tableDialog->deleteLater();
}
