#ifndef MARKDOWN_FORMATTER_H
#define MARKDOWN_FORMATTER_H

#include <QTextEdit>
#include <QTextCursor>
#include <QDialog>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>

class MarkdownFormatter : public QObject {
    Q_OBJECT

public:
    explicit MarkdownFormatter(QTextEdit *editor, QObject *parent = nullptr);

public slots:
    void setBold();
    void setItalic();
    void setCode();
    void setHeader();
    void setStrikethrough();
    void setBlockquote();
    void setUnorderedList();
    void setOrderedList();
    void setLink();
    void setImage();
    void setHorizontalRule();
    void setCodeBlock();
    void insertTable();

private:
    QTextEdit *textEditor;
};

#endif // MARKDOWN_FORMATTER_H
