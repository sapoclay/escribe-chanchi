#!/bin/bash
# Script para ejecutar Escribe Chanchi - Editor de Markdown

echo "🚀 Ejecutando Escribe Chanchi - Editor de Markdown"
echo "================================================="
echo ""
echo "✨ NUEVAS FUNCIONALIDADES:"
echo "   �️ Inicia MAXIMIZADA (permite desmaximizar)"
echo "   🔔 Icono en la bandeja del sistema"
echo "   🖱️ Clic en bandeja para mostrar/ocultar"
echo "   📋 Menú contextual en bandeja"
echo "   🌐 F11 para pantalla completa verdadera"
echo ""

# Cambiar al directorio build
cd "$(dirname "$0")/build"

# Verificar si el ejecutable existe
if [ ! -f "Escribe_Chanchi" ]; then
    echo "❌ Error: El ejecutable Escribe_Chanchi no encontrado."
    echo "   💡 Ejecuta 'cd build && make' para compilar."
    exit 1
fi

# Ejecutar el programa
echo "🎯 Iniciando aplicación maximizada (no pantalla completa)..."
echo "💡 Tip: Usa F11 para pantalla completa, se minimiza a bandeja al cerrar"
echo ""
./Escribe_Chanchi "$@"
