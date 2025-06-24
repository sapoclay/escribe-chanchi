# Escribe Chanchi - Editor de Markdown

Un editor de Markdown moderno y potente desarrollado en C++ con Qt6, que incluye sistema de pestañas, plantillas, renderizado mejorado de tablas, barra de herramientas visual, pantalla completa e integración con la bandeja del sistema.

## 🚀 Características

- **Sistema de pestañas** - Múltiples archivos abiertos simultáneamente
- **Múltiples formatos** - Soporte para .md, .txt, .m3u, .cpp, .js, .py, .html, .css, .xml, .json
- **Renderizado de tablas** - Parser manual mejorado para tablas Markdown  
- **Numeración de líneas** - Alternador visual de numeración
- **Plantillas** - Plantillas predefinidas y personalizadas
- **Barra de herramientas** - Iconos generados dinámicamente con tooltips
- **Temas** - Modo claro y oscuro
- **Exportación** - HTML y PDF
- **Pantalla completa** - Inicio en pantalla completa para máxima productividad
- **Bandeja del sistema** - Minimizado inteligente e integración con el sistema
- **Vista previa en tiempo real** - Con Qt6 WebEngine

## 📁 Tipos de Archivo Soportados

### **Funcionalidad Completa (Vista previa + Editor)**
- **`.md`** - Archivos Markdown con renderizado en tiempo real

### **Solo Editor (Optimizado para código/texto)**
- **`.txt`** - Archivos de texto plano
- **`.m3u`** - Listas de reproducción M3U  
- **`.cpp`, `.h`, `.hpp`, `.c`** - Código C/C++
- **`.js`** - JavaScript
- **`.py`** - Python
- **`.html`, `.htm`** - HTML
- **`.css`** - Hojas de estilo CSS
- **`.xml`** - Archivos XML
- **`.json`** - Archivos JSON
- **`*`** - Cualquier archivo de texto (sin filtro)

## 🛠️ Instalación y Compilación

### Requisitos del Sistema
- **Sistema Operativo:** Linux (Ubuntu/Debian recomendado)
- **Compilador:** GCC con soporte C++17 o superior
- **Qt Version:** Qt6.x (Qt6.4+ recomendado)
- **CMake:** 3.16 o superior
- **RAM:** Mínimo 1GB
- **Espacio en disco:** ~100MB para compilación

### 1. Instalación de Dependencias

#### Ubuntu/Debian (Recomendado):
```bash
# Actualizar repositorios
sudo apt update

# Instalar Qt6 y herramientas de desarrollo
sudo apt install qt6-base-dev qt6-tools-dev qt6-webengine-dev

# Instalar CMake y herramientas de compilación
sudo apt install cmake build-essential

# Instalar libcmark para procesamiento avanzado de Markdown
sudo apt install libcmark-dev

# Instalar pkg-config (requerido por CMake para encontrar libcmark)
sudo apt install pkg-config
```

#### Verificar instalación:
```bash
# Verificar Qt6
qmake6 --version

# Verificar CMake
cmake --version

# Verificar GCC
gcc --version

# Verificar libcmark
pkg-config --modversion libcmark
```

### 2. Compilación del Proyecto

#### Método Principal: CMake (Recomendado)
```bash
# 1. Navegar al directorio del proyecto
cd /ruta/al/proyecto/markdown

# 2. Crear directorio de compilación
mkdir -p build
cd build

# 3. Configurar el proyecto con CMake
cmake ..

# 4. Compilar el proyecto
make

# 5. El ejecutable se creará como 'Escribe_Chanchi'
```

#### Método Alternativo: Script automatizado
```bash
# Usar el script incluido (más fácil)
./ejecutar.sh
```

### 3. Ejecución

#### Ejecución directa:
```bash
# Desde el directorio build
cd build
./Escribe_Chanchi

# O ejecutar en segundo plano
./Escribe_Chanchi &
```

### 4. Funcionalidades de la Aplicación

#### 🖥️ **Gestión de Ventana**
- La aplicación se inicia **MAXIMIZADA** (no en pantalla completa)
- Permite usar los botones de ventana normales (minimizar/restaurar/cerrar)
- Se puede desmaximizar haciendo clic en el botón o doble clic en la barra de título
- **F11:** Alternar pantalla completa verdadera (oculta barras)
- **Menú Ver > Pantalla completa:** Misma funcionalidad que F11
- **Botón toolbar:** Icono específico para pantalla completa

#### 🔔 **Bandeja del Sistema**
- Icono visible en la bandeja del sistema
- **Clic izquierdo:** Mostrar/ocultar ventana
- **Clic derecho:** Menú contextual con opciones
- **Minimizado inteligente:** Al cerrar se minimiza a bandeja (no se cierra)

#### ✍️ **Atajos de Teclado**
- **Ctrl+N:** Nueva pestaña
- **Ctrl+O:** Abrir archivo
- **Ctrl+S:** Guardar archivo
- **Ctrl+B:** Negrita
- **Ctrl+I:** Cursiva
- **Ctrl+T:** Insertar tabla
- **F11:** Alternar pantalla completa
- **Ctrl+H:** Encabezado
- **F12:** Alternar vista previa

### 5. Estructura del Proyecto
```
├── main.cpp                 # Punto de entrada
├── markdow_editor.h/.cpp    # Editor principal con todas las funcionalidades
├── mainwindow.h/.cpp        # Ventana simplificada (legacy)
├── markdown_formatter.h/.cpp # Formateador de Markdown
├── template_manager.h/.cpp   # Gestor de plantillas
├── resources.qrc           # Recursos (iconos, imágenes)
├── templates/              # Plantillas predefinidas
│   ├── articulo_blog.md
│   ├── documento_tecnico.md
│   └── readme_proyecto.md
├── img/                    # Recursos gráficos
│   └── logo.png           # Logo de la aplicación
├── CMakeLists.txt         # Configuración de compilación CMake
├── ejecutar.sh            # Script de ejecución mejorado
└── README.md              # Este archivo
```

### 6. Limpieza del Proyecto
```bash
# Limpiar archivos de compilación
cd build
make clean

# Limpiar completamente (desde directorio raíz)
rm -rf build
```

### 7. Solución de Problemas

#### 🔧 **Problemas Comunes**

**Error: "Qt6 not found"**
```bash
# Verificar que Qt6 esté instalado
dpkg -l | grep qt6

# Si no está instalado
sudo apt install qt6-base-dev qt6-tools-dev qt6-webengine-dev
```

**Error: "libcmark not found"**
```bash
# Instalar libcmark-dev
sudo apt install libcmark-dev

# Verificar instalación
pkg-config --modversion libcmark
```

**Error: "CMake version too old"**
```bash
# Verificar versión de CMake
cmake --version

# Si es menor a 3.16, actualizar
sudo apt install cmake
```

**Error de compilación: "QRegExp not found"**
- ✅ **Ya corregido:** El código ha sido actualizado a Qt6 usando `QRegularExpression`

**Problema: "No se muestra el icono en la bandeja"**
```bash
# Verificar que el sistema soporte bandeja del sistema
echo $XDG_CURRENT_DESKTOP

# Para GNOME, instalar extensión de bandeja
# Para otros escritorios, generalmente funciona por defecto
```

#### 📊 **Versiones Testadas**

| Sistema | Qt Version | CMake | Estado |
|---------|------------|-------|--------|
| Ubuntu 22.04+ | Qt 6.4+ | 3.16+ | ✅ Funcionando |
| Ubuntu 20.04 | Qt 6.2+ | 3.16+ | ✅ Funcionando |
| Debian 11+ | Qt 6.2+ | 3.18+ | ✅ Funcionando |

### 8. Desarrollo y Contribución

#### 🛠️ **Estructura del Código**

```cpp
// Arquitectura principal
main.cpp                    // Punto de entrada
├── MarkdownEditor          // Clase principal (markdow_editor.h/.cpp)
    ├── Sistema de pestañas
    ├── Barra de herramientas
    ├── Bandeja del sistema
    └── Gestión de archivos
├── MarkdownFormatter       // Formateador (markdown_formatter.h/.cpp)  
├── TemplateManager        // Plantillas (template_manager.h/.cpp)
└── MainWindow             // Ventana simple (legacy - mainwindow.h/.cpp)
```

#### 📝 **Modificar el Proyecto**

1. **Agregar nuevas funcionalidades:**
   - Editar `markdow_editor.h` para declaraciones
   - Implementar en `markdow_editor.cpp`
   - Actualizar `CMakeLists.txt` si se agregan archivos

2. **Recompilar después de cambios:**
   ```bash
   cd build
   make
   ```

3. **Limpiar y recompilar completamente:**
   ```bash
   rm -rf build
   mkdir build && cd build
   cmake .. && make
   ```

### 9. Funcionalidades Avanzadas

#### 🎨 **Temas y Personalización**
- **Modo oscuro/claro:** Botón en barra de herramientas
- **Números de línea:** Ctrl+Shift+L
- **Fuentes personalizables:** En configuración

#### 📄 **Plantillas**
- **Predefinidas:** Blog, documento técnico, README
- **Personalizadas:** Crear nuevas plantillas
- **Gestión:** Guardar y cargar plantillas

#### 🔄 **Exportación**
- **HTML:** Vista previa exportable  
- **PDF:** Generación directa desde la aplicación
- **Markdown:** Formato nativo

### 10. Información del Proyecto

#### 📊 **Estadísticas**
- **Lenguaje:** C++17
- **Framework:** Qt6
- **Líneas de código:** ~2000+ líneas
- **Archivos fuente:** 6 archivos .cpp principales
- **Dependencias:** Qt6, libcmark, CMake

#### 🎯 **Estado del Proyecto**
- ✅ **Compilación:** 100% exitosa
- ✅ **Funcionalidades:** Completas y probadas
- ✅ **Pantalla completa:** Implementada
- ✅ **Bandeja del sistema:** Funcionando
- ✅ **Compatibilidad Qt6:** Actualizada

#### 📜 **Licencia**
Proyecto de código abierto para uso educativo y personal.

#### 👨‍💻 **Autor**
Desarrollado como proyecto personal de editor de Markdown con Qt6.

---

## 🚀 **¡PROYECTO LISTO!**

**Para usar inmediatamente:**
```bash
# Método rápido
./ejecutar.sh

# Método manual  
cd build && ./Escribe_Chanchi
```

**¡Disfruta editando Markdown con Escribe Chanchi!** ✨

1. **Ejecutar el programa:**
   ```bash
   ./markdown_editor
   ```

2. **Crear nuevo documento:** Usar `Ctrl+N` o menú "Archivo → Nueva pestaña"

3. **Abrir archivo existente:** Usar `Ctrl+O` o menú "Archivo → Abrir"

4. **Usar barra de herramientas:** Acceso rápido a formato (negrita, cursiva, etc.)

5. **Aplicar plantillas:** Menú "Plantillas" para usar o crear plantillas

6. **Cambiar tema:** Usar `F11` o menú "Vista → Modo oscuro"

## ⌨️ Atajos de Teclado

| Atajo | Función |
|-------|---------|
| `Ctrl+N` | Nueva pestaña |
| `Ctrl+O` | Abrir archivo |
| `Ctrl+S` | Guardar |
| `Ctrl+Shift+S` | Guardar como |
| `Ctrl+W` | Cerrar pestaña |
| `Ctrl+B` | Texto en negrita |
| `Ctrl+I` | Texto en cursiva |
| `Ctrl+U` | Texto subrayado |
| `F11` | Alternar modo oscuro |

## 🔧 Solución de Problemas

### Error: "QApplication: No existe el archivo"
```bash
sudo apt install qtbase5-dev
```

### Error: "libcmark not found"
```bash
sudo apt install libcmark-dev
```

### Error de permisos de ejecución
```bash
chmod +x markdown_editor
```

### ⚠️ Problemas de Ventana

**La aplicación se abre en pantalla completa y no puedo desmaximizar:**
- **Solución:** La aplicación ahora inicia MAXIMIZADA (no en pantalla completa)
- Usa los botones de ventana normales para minimizar/restaurar
- Presiona F11 para alternar pantalla completa verdadera
- Doble clic en la barra de título para desmaximizar

**No aparece el icono en la bandeja del sistema:**
- Verifica que tu entorno de escritorio soporte la bandeja del sistema
- En algunos entornos, puede estar oculta en la configuración del panel

**La ventana no responde correctamente:**
- Reinicia la aplicación
- Verifica que no haya conflictos con gestores de ventana

### Limpiar compilación corrupta
```bash
make clean
qmake markdown_editor.pro
make
```

---
**EscribeChanchi** - Editor de Markdown profesional y multiplataforma
