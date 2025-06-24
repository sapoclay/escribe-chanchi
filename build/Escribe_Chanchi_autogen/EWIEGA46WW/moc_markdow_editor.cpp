/****************************************************************************
** Meta object code from reading C++ file 'markdow_editor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../markdow_editor.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'markdow_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MarkdownEditor_t {
    uint offsetsAndSizes[100];
    char stringdata0[15];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[10];
    char stringdata5[8];
    char stringdata6[10];
    char stringdata7[17];
    char stringdata8[14];
    char stringdata9[17];
    char stringdata10[15];
    char stringdata11[8];
    char stringdata12[9];
    char stringdata13[18];
    char stringdata14[13];
    char stringdata15[12];
    char stringdata16[15];
    char stringdata17[11];
    char stringdata18[13];
    char stringdata19[13];
    char stringdata20[12];
    char stringdata21[11];
    char stringdata22[10];
    char stringdata23[18];
    char stringdata24[18];
    char stringdata25[17];
    char stringdata26[14];
    char stringdata27[15];
    char stringdata28[12];
    char stringdata29[15];
    char stringdata30[18];
    char stringdata31[9];
    char stringdata32[13];
    char stringdata33[12];
    char stringdata34[11];
    char stringdata35[7];
    char stringdata36[17];
    char stringdata37[9];
    char stringdata38[6];
    char stringdata39[16];
    char stringdata40[11];
    char stringdata41[16];
    char stringdata42[11];
    char stringdata43[17];
    char stringdata44[13];
    char stringdata45[11];
    char stringdata46[18];
    char stringdata47[34];
    char stringdata48[7];
    char stringdata49[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MarkdownEditor_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MarkdownEditor_t qt_meta_stringdata_MarkdownEditor = {
    {
        QT_MOC_LITERAL(0, 14),  // "MarkdownEditor"
        QT_MOC_LITERAL(15, 14),  // "toggleDarkMode"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 7),  // "setBold"
        QT_MOC_LITERAL(39, 9),  // "setItalic"
        QT_MOC_LITERAL(49, 7),  // "setCode"
        QT_MOC_LITERAL(57, 9),  // "setHeader"
        QT_MOC_LITERAL(67, 16),  // "setStrikethrough"
        QT_MOC_LITERAL(84, 13),  // "setBlockquote"
        QT_MOC_LITERAL(98, 16),  // "setUnorderedList"
        QT_MOC_LITERAL(115, 14),  // "setOrderedList"
        QT_MOC_LITERAL(130, 7),  // "setLink"
        QT_MOC_LITERAL(138, 8),  // "setImage"
        QT_MOC_LITERAL(147, 17),  // "setHorizontalRule"
        QT_MOC_LITERAL(165, 12),  // "setCodeBlock"
        QT_MOC_LITERAL(178, 11),  // "insertTable"
        QT_MOC_LITERAL(190, 14),  // "renderMarkdown"
        QT_MOC_LITERAL(205, 10),  // "saveToFile"
        QT_MOC_LITERAL(216, 12),  // "loadFromFile"
        QT_MOC_LITERAL(229, 12),  // "exportToHTML"
        QT_MOC_LITERAL(242, 11),  // "exportToPDF"
        QT_MOC_LITERAL(254, 10),  // "showManual"
        QT_MOC_LITERAL(265, 9),  // "showAbout"
        QT_MOC_LITERAL(275, 17),  // "toggleLineNumbers"
        QT_MOC_LITERAL(293, 17),  // "updateLineNumbers"
        QT_MOC_LITERAL(311, 16),  // "toggleFullScreen"
        QT_MOC_LITERAL(328, 13),  // "showTemplates"
        QT_MOC_LITERAL(342, 14),  // "createTemplate"
        QT_MOC_LITERAL(357, 11),  // "insertEmoji"
        QT_MOC_LITERAL(369, 14),  // "showFindDialog"
        QT_MOC_LITERAL(384, 17),  // "showReplaceDialog"
        QT_MOC_LITERAL(402, 8),  // "findNext"
        QT_MOC_LITERAL(411, 12),  // "findPrevious"
        QT_MOC_LITERAL(424, 11),  // "replaceNext"
        QT_MOC_LITERAL(436, 10),  // "replaceAll"
        QT_MOC_LITERAL(447, 6),  // "newTab"
        QT_MOC_LITERAL(454, 16),  // "openFileInNewTab"
        QT_MOC_LITERAL(471, 8),  // "closeTab"
        QT_MOC_LITERAL(480, 5),  // "index"
        QT_MOC_LITERAL(486, 15),  // "closeCurrentTab"
        QT_MOC_LITERAL(502, 10),  // "tabChanged"
        QT_MOC_LITERAL(513, 15),  // "saveCurrentFile"
        QT_MOC_LITERAL(529, 10),  // "saveFileAs"
        QT_MOC_LITERAL(540, 16),  // "documentModified"
        QT_MOC_LITERAL(557, 12),  // "showFromTray"
        QT_MOC_LITERAL(570, 10),  // "hideToTray"
        QT_MOC_LITERAL(581, 17),  // "trayIconActivated"
        QT_MOC_LITERAL(599, 33),  // "QSystemTrayIcon::ActivationRe..."
        QT_MOC_LITERAL(633, 6),  // "reason"
        QT_MOC_LITERAL(640, 15)   // "exitApplication"
    },
    "MarkdownEditor",
    "toggleDarkMode",
    "",
    "setBold",
    "setItalic",
    "setCode",
    "setHeader",
    "setStrikethrough",
    "setBlockquote",
    "setUnorderedList",
    "setOrderedList",
    "setLink",
    "setImage",
    "setHorizontalRule",
    "setCodeBlock",
    "insertTable",
    "renderMarkdown",
    "saveToFile",
    "loadFromFile",
    "exportToHTML",
    "exportToPDF",
    "showManual",
    "showAbout",
    "toggleLineNumbers",
    "updateLineNumbers",
    "toggleFullScreen",
    "showTemplates",
    "createTemplate",
    "insertEmoji",
    "showFindDialog",
    "showReplaceDialog",
    "findNext",
    "findPrevious",
    "replaceNext",
    "replaceAll",
    "newTab",
    "openFileInNewTab",
    "closeTab",
    "index",
    "closeCurrentTab",
    "tabChanged",
    "saveCurrentFile",
    "saveFileAs",
    "documentModified",
    "showFromTray",
    "hideToTray",
    "trayIconActivated",
    "QSystemTrayIcon::ActivationReason",
    "reason",
    "exitApplication"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MarkdownEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  284,    2, 0x08,    1 /* Private */,
       3,    0,  285,    2, 0x08,    2 /* Private */,
       4,    0,  286,    2, 0x08,    3 /* Private */,
       5,    0,  287,    2, 0x08,    4 /* Private */,
       6,    0,  288,    2, 0x08,    5 /* Private */,
       7,    0,  289,    2, 0x08,    6 /* Private */,
       8,    0,  290,    2, 0x08,    7 /* Private */,
       9,    0,  291,    2, 0x08,    8 /* Private */,
      10,    0,  292,    2, 0x08,    9 /* Private */,
      11,    0,  293,    2, 0x08,   10 /* Private */,
      12,    0,  294,    2, 0x08,   11 /* Private */,
      13,    0,  295,    2, 0x08,   12 /* Private */,
      14,    0,  296,    2, 0x08,   13 /* Private */,
      15,    0,  297,    2, 0x08,   14 /* Private */,
      16,    0,  298,    2, 0x08,   15 /* Private */,
      17,    0,  299,    2, 0x08,   16 /* Private */,
      18,    0,  300,    2, 0x08,   17 /* Private */,
      19,    0,  301,    2, 0x08,   18 /* Private */,
      20,    0,  302,    2, 0x08,   19 /* Private */,
      21,    0,  303,    2, 0x08,   20 /* Private */,
      22,    0,  304,    2, 0x08,   21 /* Private */,
      23,    0,  305,    2, 0x08,   22 /* Private */,
      24,    0,  306,    2, 0x08,   23 /* Private */,
      25,    0,  307,    2, 0x08,   24 /* Private */,
      26,    0,  308,    2, 0x08,   25 /* Private */,
      27,    0,  309,    2, 0x08,   26 /* Private */,
      28,    0,  310,    2, 0x08,   27 /* Private */,
      29,    0,  311,    2, 0x08,   28 /* Private */,
      30,    0,  312,    2, 0x08,   29 /* Private */,
      31,    0,  313,    2, 0x08,   30 /* Private */,
      32,    0,  314,    2, 0x08,   31 /* Private */,
      33,    0,  315,    2, 0x08,   32 /* Private */,
      34,    0,  316,    2, 0x08,   33 /* Private */,
      35,    0,  317,    2, 0x08,   34 /* Private */,
      36,    0,  318,    2, 0x08,   35 /* Private */,
      37,    1,  319,    2, 0x08,   36 /* Private */,
      39,    0,  322,    2, 0x08,   38 /* Private */,
      40,    1,  323,    2, 0x08,   39 /* Private */,
      41,    0,  326,    2, 0x08,   41 /* Private */,
      42,    0,  327,    2, 0x08,   42 /* Private */,
      43,    0,  328,    2, 0x08,   43 /* Private */,
      44,    0,  329,    2, 0x08,   44 /* Private */,
      45,    0,  330,    2, 0x08,   45 /* Private */,
      46,    1,  331,    2, 0x08,   46 /* Private */,
      49,    0,  334,    2, 0x08,   48 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 47,   48,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MarkdownEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MarkdownEditor.offsetsAndSizes,
    qt_meta_data_MarkdownEditor,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MarkdownEditor_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MarkdownEditor, std::true_type>,
        // method 'toggleDarkMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setBold'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setItalic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setHeader'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setStrikethrough'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setBlockquote'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setUnorderedList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setOrderedList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLink'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setHorizontalRule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCodeBlock'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'renderMarkdown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveToFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadFromFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportToHTML'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportToPDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showManual'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showAbout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleLineNumbers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLineNumbers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleFullScreen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showTemplates'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createTemplate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertEmoji'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showFindDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showReplaceDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'findNext'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'findPrevious'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replaceNext'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replaceAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'newTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openFileInNewTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'closeCurrentTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tabChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'saveCurrentFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveFileAs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'documentModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showFromTray'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideToTray'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'trayIconActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSystemTrayIcon::ActivationReason, std::false_type>,
        // method 'exitApplication'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MarkdownEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MarkdownEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->toggleDarkMode(); break;
        case 1: _t->setBold(); break;
        case 2: _t->setItalic(); break;
        case 3: _t->setCode(); break;
        case 4: _t->setHeader(); break;
        case 5: _t->setStrikethrough(); break;
        case 6: _t->setBlockquote(); break;
        case 7: _t->setUnorderedList(); break;
        case 8: _t->setOrderedList(); break;
        case 9: _t->setLink(); break;
        case 10: _t->setImage(); break;
        case 11: _t->setHorizontalRule(); break;
        case 12: _t->setCodeBlock(); break;
        case 13: _t->insertTable(); break;
        case 14: _t->renderMarkdown(); break;
        case 15: _t->saveToFile(); break;
        case 16: _t->loadFromFile(); break;
        case 17: _t->exportToHTML(); break;
        case 18: _t->exportToPDF(); break;
        case 19: _t->showManual(); break;
        case 20: _t->showAbout(); break;
        case 21: _t->toggleLineNumbers(); break;
        case 22: _t->updateLineNumbers(); break;
        case 23: _t->toggleFullScreen(); break;
        case 24: _t->showTemplates(); break;
        case 25: _t->createTemplate(); break;
        case 26: _t->insertEmoji(); break;
        case 27: _t->showFindDialog(); break;
        case 28: _t->showReplaceDialog(); break;
        case 29: _t->findNext(); break;
        case 30: _t->findPrevious(); break;
        case 31: _t->replaceNext(); break;
        case 32: _t->replaceAll(); break;
        case 33: _t->newTab(); break;
        case 34: _t->openFileInNewTab(); break;
        case 35: _t->closeTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 36: _t->closeCurrentTab(); break;
        case 37: _t->tabChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 38: _t->saveCurrentFile(); break;
        case 39: _t->saveFileAs(); break;
        case 40: _t->documentModified(); break;
        case 41: _t->showFromTray(); break;
        case 42: _t->hideToTray(); break;
        case 43: _t->trayIconActivated((*reinterpret_cast< std::add_pointer_t<QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        case 44: _t->exitApplication(); break;
        default: ;
        }
    }
}

const QMetaObject *MarkdownEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarkdownEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MarkdownEditor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MarkdownEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 45;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
