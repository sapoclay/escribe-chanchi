# Escribe Chanchi - Editor de Markdown ✨

![about-escribe-chanchi](https://github.com/user-attachments/assets/a400a351-5648-4979-a9ec-cd4f07d37565)

Este es un editor de Markdown desarrollado en C++ con Qt, que incluye sistema de pestañas, plantillas, barra de herramientas mejorada, búsqueda avanzada y sistema optimizado de emojis. Y todas aquellas otras cosas que me sean útiles en algún u otro momento.

![GitHub](https://img.shields.io/badge/version-v1.6-blue) ![C++](https://img.shields.io/badge/language-C%2B%2B-blue) ![Qt](https://img.shields.io/badge/framework-Qt5%2FQt6-green) ![License](https://img.shields.io/badge/license-MIT-green)

## 🎯 TL;DR (Resumen Ultra-Rápido)
```bash
# 1. Clonar repositorio
git clone https://github.com/sapoclay/escribe-chanchi.git
cd escribe-chanchi

# 2. Instalar dependencias (Ubuntu/Debian)
sudo apt update
sudo apt install build-essential qt5-default libqt5webkit5-dev libcmark-dev cmake

# 3. Compilar automáticamente
./compilar.sh

# 4. Ejecutar automáticamente  
./ejecutar.sh

# ¡Listo! 🚀 El editor se abre maximizado y listo para usar
```

## 🚀 Instalación y Uso

### 📥 Paso 1: Clonar el Repositorio
```bash
git clone https://github.com/sapoclay/escribe-chanchi.git
cd escribe-chanchi
```

### 📦 Paso 2: Instalar Dependencias

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential qt5-default libqt5webkit5-dev libcmark-dev cmake git
```

**Fedora/CentOS:**
```bash
sudo dnf install gcc-c++ qt5-qtbase-devel qt5-qtwebkit-devel libcmark-devel cmake git
```

**Arch Linux:**
```bash
sudo pacman -S base-devel qt5-base qt5-webkit cmark cmake git
```

### 🔨 Paso 3: Compilar
```bash
# Compilar automáticamente (recomendado - detecta el mejor método)
./compilar.sh

# Opciones avanzadas:
./compilar.sh auto      # Automático (igual que sin parámetros)
./compilar.sh cmake     # Forzar CMake → build/Escribe_Chanchi
./compilar.sh make      # Forzar Makefile → markdown_editor
./compilar.sh clean     # Limpiar y recompilar todo
```

### 🚀 Paso 4: Ejecutar
```bash
# Ejecutar automáticamente (detecta el ejecutable disponible)
./ejecutar.sh

# El editor se abrirá maximizado y listo para usar
```

### Instalar usando el paquete .DEB
![lanzador-escribe-chanchi](https://github.com/user-attachments/assets/64d584a3-894b-495a-89cf-af69ec02ed16)


## 💡 Cómo Usar el Editor

![plantilla-escribe-chanchi](https://github.com/user-attachments/assets/754e2c5c-3f8d-4de4-b015-49c4181ba680)

### 📝 Crear y Editar Documentos
1. **Nuevo documento**: Clic en "Nueva" o `Ctrl+N`
2. **Abrir archivo**: Clic en 📁 o `Ctrl+O`
3. **Escribir texto**: ¡Simplemente escribe!
4. **Guardar**: Clic en 💾 o `Ctrl+S`

### 🔍 Buscar y Reemplazar (NUEVO)
1. **Buscar**: Clic en 🔍 o `Ctrl+F`
2. **Reemplazar**: Clic en 🔄 o `Ctrl+H`
3. **Navegar**: Botones ◀ ▶ o `F3`/`Shift+F3`
4. **Opciones**: Sensible a mayúsculas, solo palabras completas

### ✍️ Formato de Texto
- **Negrita**: Selecciona texto → Clic en "B" o `Ctrl+B`
- **Cursiva**: Selecciona texto → Clic en "I" o `Ctrl+I`
- **Código**: Selecciona texto → Clic en "</>" o `Ctrl+``

### � Insertar Emojis (76 emojis optimizados)
- **Abrir selector**: Clic en ":)" o `Ctrl+E`
- **Elegir emoji**: Clic en el emoji deseado
- **Se inserta automáticamente** en el texto

### � Cambiar Tema
- **Modo oscuro/claro**: Clic en 🌙 o `F11`

## 🎯 Características Principales

### ✨ **Funcionalidades Principales**
- ✅ **Sistema de pestañas** - Múltiples archivos simultáneamente
- ✅ **Búsqueda y reemplazo avanzado** - Con opciones de mayúsculas y palabras completas
- ✅ **Barra de herramientas mejorada** - Iconos descriptivos y búsqueda integrada
- ✅ **76 emojis optimizados** - Ultra-básicos y universalmente compatibles
- ✅ **Plantillas predefinidas** - Para blogs, documentos técnicos, README
- ✅ **Modo claro/oscuro** - Alternancia con F11
- ✅ **Vista previa en tiempo real** - Para archivos Markdown
- ✅ **Exportación** - A HTML y PDF
- ✅ **Bandeja del sistema** - Minimizado inteligente

### 📁 **Formatos Soportados**
- **`.md`** - Markdown con vista previa en tiempo real
- **`.txt`, `.cpp`, `.js`, `.py`, `.html`, `.css`, `.xml`, `.json`** - Editor de texto
- **Cualquier archivo de texto** - Edición básica

## ⌨️ Atajos de Teclado

| Función | Atajo | Descripción |
|---------|-------|-------------|
| **� Archivos** | | |
| Nueva pestaña | `Ctrl+N` | Crear nuevo documento |
| Abrir archivo | `Ctrl+O` | Abrir archivo existente |
| Guardar | `Ctrl+S` | Guardar documento actual |
| Guardar como | `Ctrl+Shift+S` | Guardar con nuevo nombre |
| **🔍 Búsqueda** | | |
| Buscar | `Ctrl+F` | Abrir diálogo de búsqueda |
| Buscar y reemplazar | `Ctrl+H` | Abrir diálogo de reemplazo |
| Buscar siguiente | `F3` | Ir al siguiente resultado |
| Buscar anterior | `Shift+F3` | Ir al resultado anterior |
| **✍️ Formato** | | |
| Negrita | `Ctrl+B` | Texto en **negrita** |
| Cursiva | `Ctrl+I` | Texto en *cursiva* |
| Código | `Ctrl+`` | Texto en `código` |
| **🎨 Especiales** | | |
| Insertar emoji | `Ctrl+E` | Abrir selector de emojis |
| Modo oscuro | `F11` | Alternar tema claro/oscuro |
| Pantalla completa | `F10` | Ocultar barras de ventana |

## 🔧 Compilación Avanzada

### Detección Automática (Recomendado)
```bash
./compilar.sh           # Detecta automáticamente CMake o Makefile
./compilar.sh auto      # Mismo resultado
./compilar.sh clean     # Limpiar y recompilar todo
```

### Métodos Específicos
```bash
# Forzar CMake (genera: build/Escribe_Chanchi)
./compilar.sh cmake

# Forzar Makefile tradicional (genera: markdown_editor)
./compilar.sh make
```

### Manual - CMake
```bash
mkdir -p build && cd build
cmake ..
make
# Genera: build/Escribe_Chanchi
```

### Manual - Makefile
```bash
make clean && make
# Genera: markdown_editor
```

## � Solución de Problemas

### ❌ Error: "No se encontró ejecutable"
```bash
# Recompilar automáticamente
./compilar.sh clean

# Luego ejecutar
./ejecutar.sh
```

### ❌ Error: "Qt no encontrado"
```bash
# Ubuntu/Debian
sudo apt install qt5-default libqt5webkit5-dev

# Verificar instalación
qmake --version
```

### ❌ Error: "libcmark no encontrado"
```bash
# Ubuntu/Debian
sudo apt install libcmark-dev pkg-config

# Verificar instalación
pkg-config --modversion libcmark
```

### ❌ La búsqueda no encuentra texto que existe
- Verificar opciones "Sensible a mayúsculas" y "Solo palabras completas"
- Asegurarse de que no hay espacios adicionales en el texto de búsqueda

### ❌ Los iconos no se ven correctamente
- Los nuevos iconos son gráficos dibujados, no dependen de fuentes Unicode
- Si persisten problemas: `./compilar.sh clean && ./compilar.sh`

### ❌ La aplicación se abre maximizada
- Esto es comportamiento normal y deseado
- Para desmaximizar: Usa el botón maximizar/restaurar o doble clic en la barra de título

## 🎨 Funcionalidades Especiales

### 🔍 **Sistema de Búsqueda y Reemplazo**
Acceso rápido:
- `Ctrl+F` - Buscar texto
- `Ctrl+H` - Buscar y reemplazar
- `F3` - Buscar siguiente
- `Shift+F3` - Buscar anterior
- Botones 🔍 🔄 ◀ ▶ en la barra de herramientas

**Características:**
- ✅ **Búsqueda en tiempo real** con resaltado inmediato
- ✅ **Navegación circular** - Continúa desde inicio/final del documento
- ✅ **Opciones avanzadas:** Sensible a mayúsculas, solo palabras completas
- ✅ **Reemplazo individual o masivo** con confirmación
- ✅ **Diálogos no modales** - Permite editar mientras se busca

### 😀 **Sistema de Emojis Optimizado**
**76 emojis ultra-básicos y universalmente compatibles**

Acceso: `Ctrl+E` o botón :) en la barra de herramientas

**Filosofía:** Calidad sobre cantidad - Menos emojis, pero todos funcionan perfectamente.

**Ejemplos incluidos:**
- **Caras:** 😀 😃 😄 😁 😆 😊 😍 😘 😎 😛 😐 😒 😔 😢 😭 😠 😡 😳 😴 😷
- **Corazones:** ❤ 💛 💚 💙 💜 🖤 💔 💕 💖 💗
- **Símbolos:** ⭐ ✨ 🌟 ☀ 🌙 ✅ ❌ ⭕ ❗ ❓ 💯

### 🔧 **Barra de Herramientas Mejorada**
**Completamente renovada con iconos descriptivos dibujados con QPainter**

**Nuevas características:**
- ✅ **Iconos gráficos descriptivos** - No dependen de fuentes Unicode
- ✅ **Botones de búsqueda integrados** - Acceso directo a búsqueda/reemplazo
- ✅ **Colores diferenciados** - Cada función tiene su color distintivo
- ✅ **Organización por secciones:** Archivos, Búsqueda, Formato, Estructura, etc.
- ✅ **Tooltips informativos** - Cada botón incluye descripción y atajo

### Interfaz principal
- **Sistema de pestañas** para múltiples archivos
- **Barra de herramientas renovada** con iconos descriptivos
- **Vista previa en tiempo real** de Markdown
- **Modo claro y oscuro** disponible

### Características destacadas
- **🔍 Sistema de búsqueda avanzado** con opciones de mayúsculas y palabras completas
- **😀 76 emojis optimizados** universalmente compatibles
- **📝 Plantillas predefinidas** para diferentes tipos de documentos
- **🔧 Bandeja del sistema** con minimizado inteligente

*[Las capturas de pantalla se agregarán próximamente]*

## �📂 Estructura del proyecto
```
├── compilar.sh              # Script de compilación inteligente
├── ejecutar.sh              # Script de ejecución inteligente
├── markdow_editor.cpp/.h    # Editor principal con todas las funcionalidades
├── markdown_formatter.cpp/.h # Formateador de Markdown
├── template_manager.cpp/.h   # Gestor de plantillas
├── build/                   # Directorio de compilación CMake
│   └── Escribe_Chanchi     # Ejecutable generado por CMake
├── markdown_editor          # Ejecutable generado por Makefile
├── templates/               # Plantillas predefinidas
│   ├── articulo_blog.md
│   ├── documento_tecnico.md
│   └── readme_proyecto.md
├── PRUEBA_*.sh             # Scripts de prueba automatizada
├── CMakeLists.txt          # Configuración CMake
├── Makefile                # Makefile tradicional
└── README.md               # Este archivo
```

## 📝 Notas de Desarrollo

### Versión Actual (v1.6)
- ✅ **Barra de herramientas completamente renovada** con iconos descriptivos
- ✅ **Botones de búsqueda integrados** en la barra de herramientas  
- ✅ **Scripts inteligentes** de compilación y ejecución automática
- ✅ **Eliminación de dependencias Unicode** para iconos problemáticos
- ✅ **Documentación reorganizada** y simplificada

### Arquitectura Técnica
- **Lenguaje:** C++17 con librerías Qt5/Qt6
- **Build System:** CMake (recomendado) + Makefile tradicional
- **Dependencias:** Qt, libcmark, build-essential
- **Patrón:** Aplicación de escritorio Qt con arquitectura MVC

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Este proyecto está abierto a mejoras y nuevas funcionalidades.

### Cómo Contribuir
1. **Fork** el repositorio
2. Crear una **rama** para tu funcionalidad (`git checkout -b feature/nueva-funcionalidad`)
3. **Commit** tus cambios (`git commit -am 'Agregar nueva funcionalidad'`)
4. **Push** a la rama (`git push origin feature/nueva-funcionalidad`)
5. Crear un **Pull Request**

### Áreas de Contribución
- 🐛 **Corrección de bugs**
- ✨ **Nuevas funcionalidades**
- 📚 **Mejoras en documentación**
- 🎨 **Mejoras en UI/UX**
- 🧪 **Tests y pruebas**
- 🌍 **Traducciones**

### Desarrollo Local
```bash
# Clonar tu fork
git clone https://github.com/TU_USUARIO/escribe-chanchi.git
cd escribe-chanchi

# Compilar en modo desarrollo
./compilar.sh clean
./compilar.sh

# Probar cambios
./ejecutar.sh
```

## 📄 Licencia

Este proyecto está bajo licencia MIT. Ver archivo `LICENSE` para más detalles.

## 🌟 Agradecimientos

- **Qt Framework** - Por la excelente biblioteca de desarrollo
- **libcmark** - Por el procesamiento robusto de Markdown
- **Comunidad Open Source** - Por inspiración y herramientas

---

![logo_escribe_chanchi](https://github.com/user-attachments/assets/07667a04-1324-41e6-9059-7443e8680d77)

**EscribeChanchi v1.6** - Editor de Markdown para mis cosicas - Creado por entreunosyceros ✨

**📦 Repositorio:** https://github.com/sapoclay/escribe-chanchi


