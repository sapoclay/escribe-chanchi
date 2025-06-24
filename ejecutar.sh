#!/bin/bash
# Script para ejecutar Escribe Chanchi - Editor de Markdown

echo "🚀 Ejecutando Escribe Chanchi - Editor de Markdown"
echo "================================================="
echo ""
echo "✨ NUEVAS FUNCIONALIDADES:"
echo "   🪟 Inicia MAXIMIZADA (permite desmaximizar)"
echo "   🔔 Icono en la bandeja del sistema"
echo "   🖱️ Clic en bandeja para mostrar/ocultar"
echo "   📋 Menú contextual en bandeja"
echo "   🌐 F11 para pantalla completa verdadera"
echo "   🔍 Sistema completo de búsqueda y reemplazo"
echo "   🔧 Barra de herramientas mejorada con iconos descriptivos"
echo ""

SCRIPT_DIR="$(dirname "$0")"

# Función para ejecutar el programa
ejecutar_programa() {
    local ejecutable="$1"
    local ubicacion="$2"
    
    echo "🎯 Ejecutable encontrado: $ejecutable"
    echo "📁 Ubicación: $ubicacion"
    echo "💡 Tip: Usa F11 para pantalla completa, se minimiza a bandeja al cerrar"
    echo "🔍 Tip: Usa Ctrl+F para buscar, Ctrl+H para buscar y reemplazar"
    echo ""
    
    cd "$ubicacion"
    ./"$ejecutable" "$@"
    return $?
}

# Prioridad 1: Buscar ejecutable en build/ (CMake)
if [ -f "$SCRIPT_DIR/build/Escribe_Chanchi" ] && [ -x "$SCRIPT_DIR/build/Escribe_Chanchi" ]; then
    echo "🔧 Detectado: Compilación CMake (build/Escribe_Chanchi)"
    ejecutar_programa "Escribe_Chanchi" "$SCRIPT_DIR/build"
    exit $?
fi

# Prioridad 2: Buscar ejecutable en directorio raíz (Makefile)
if [ -f "$SCRIPT_DIR/markdown_editor" ] && [ -x "$SCRIPT_DIR/markdown_editor" ]; then
    echo "🔧 Detectado: Compilación Makefile (markdown_editor)"
    ejecutar_programa "markdown_editor" "$SCRIPT_DIR"
    exit $?
fi

# Si no se encuentra ningún ejecutable
echo "❌ Error: No se encontró ningún ejecutable."
echo ""
echo "💡 Opciones de compilación:"
echo ""
echo "   📦 OPCIÓN 1 - CMake (Recomendado):"
echo "      cd build"
echo "      cmake .."
echo "      make"
echo ""
echo "   📦 OPCIÓN 2 - Makefile tradicional:"
echo "      make clean"
echo "      make"
echo ""
echo "🔍 Verificando estado actual:"

# Mostrar información de diagnóstico
if [ -d "$SCRIPT_DIR/build" ]; then
    echo "   ✅ Directorio build/ existe"
    if [ -f "$SCRIPT_DIR/build/Makefile" ]; then
        echo "   ✅ CMake configurado en build/"
    else
        echo "   ❌ CMake no configurado en build/"
    fi
else
    echo "   ❌ Directorio build/ no existe"
fi

if [ -f "$SCRIPT_DIR/Makefile" ]; then
    echo "   ✅ Makefile tradicional existe"
else
    echo "   ❌ Makefile tradicional no existe"
fi

echo ""
echo "🛠️ Para compilar automáticamente, ejecuta:"
echo "   ./compilar.sh (si existe) o sigue las instrucciones arriba"

exit 1
