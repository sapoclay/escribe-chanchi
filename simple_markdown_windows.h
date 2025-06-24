/* 
 * Alternativa simple para Windows sin libcmark
 * Reemplaza las funciones de renderizado de Markdown con HTML básico
 * Solo usar si libcmark no está disponible en Windows
 */

#include <QString>
#include <QStringList>
#include <QRegularExpression>

class SimpleMarkdownRenderer {
public:
    static QString renderToHtml(const QString& markdown) {
        QString html = markdown;
        
        // Convertir encabezados
        html.replace(QRegularExpression("^# (.+)$", QRegularExpression::MultilineOption), 
                    "<h1>\\1</h1>");
        html.replace(QRegularExpression("^## (.+)$", QRegularExpression::MultilineOption), 
                    "<h2>\\1</h2>");
        html.replace(QRegularExpression("^### (.+)$", QRegularExpression::MultilineOption), 
                    "<h3>\\1</h3>");
        
        // Convertir texto en negrita
        html.replace(QRegularExpression("\\*\\*(.+?)\\*\\*"), "<strong>\\1</strong>");
        
        // Convertir texto en cursiva
        html.replace(QRegularExpression("\\*(.+?)\\*"), "<em>\\1</em>");
        
        // Convertir código inline
        html.replace(QRegularExpression("`(.+?)`"), "<code>\\1</code>");
        
        // Convertir enlaces
        html.replace(QRegularExpression("\\[(.+?)\\]\\((.+?)\\)"), 
                    "<a href=\"\\2\">\\1</a>");
        
        // Convertir párrafos (líneas separadas por línea en blanco)
        QStringList lines = html.split('\n');
        QString result;
        bool inParagraph = false;
        
        for (const QString& line : lines) {
            if (line.trimmed().isEmpty()) {
                if (inParagraph) {
                    result += "</p>\n";
                    inParagraph = false;
                }
            } else if (!line.startsWith('<')) {
                if (!inParagraph) {
                    result += "<p>";
                    inParagraph = true;
                }
                result += line + " ";
            } else {
                if (inParagraph) {
                    result += "</p>\n";
                    inParagraph = false;
                }
                result += line + "\n";
            }
        }
        
        if (inParagraph) {
            result += "</p>";
        }
        
        return result;
    }
};

/* 
 * Para usar esta alternativa:
 * 1. Incluir este archivo en tu proyecto
 * 2. En markdow_editor.cpp, reemplazar las llamadas a cmark con:
 *    QString html = SimpleMarkdownRenderer::renderToHtml(markdownText);
 *    browser->setHtml(html);
 * 3. Compilar sin la dependencia -lcmark
 */
