#!/bin/bash
# Script para compilar Escribe Chanchi - Editor de Markdown

echo "🔨 Compilando Escribe Chanchi - Editor de Markdown"
echo "=================================================="
echo ""

SCRIPT_DIR="$(dirname "$0")"
cd "$SCRIPT_DIR"

# Colores para output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Función para mostrar opciones
mostrar_opciones() {
    echo -e "${BLUE}💡 OPCIONES DE COMPILACIÓN DISPONIBLES:${NC}"
    echo ""
    echo "   1️⃣  CMake (Recomendado) - Genera 'Escribe_Chanchi' en build/"
    echo "   2️⃣  Makefile tradicional - Genera 'markdown_editor' en directorio raíz"
    echo "   3️⃣  Automático - Detecta y usa el mejor método disponible"
    echo "   4️⃣  Limpiar todo y recompilar"
    echo "   0️⃣  Salir"
    echo ""
}

# Función para compilar con CMake
compilar_cmake() {
    echo -e "${BLUE}🔧 Compilando con CMake...${NC}"
    
    # Crear directorio build si no existe
    if [ ! -d "build" ]; then
        echo "📁 Creando directorio build/"
        mkdir -p build
    fi
    
    cd build
    
    # Configurar CMake
    echo "⚙️  Configurando CMake..."
    if cmake .. ; then
        echo -e "${GREEN}✅ CMake configurado correctamente${NC}"
    else
        echo -e "${RED}❌ Error al configurar CMake${NC}"
        return 1
    fi
    
    # Compilar
    echo "🔨 Compilando..."
    if make ; then
        echo -e "${GREEN}✅ Compilación CMake exitosa${NC}"
        echo -e "${GREEN}🎯 Ejecutable generado: build/Escribe_Chanchi${NC}"
        return 0
    else
        echo -e "${RED}❌ Error en la compilación CMake${NC}"
        return 1
    fi
}

# Función para compilar con Makefile
compilar_makefile() {
    echo -e "${BLUE}🔧 Compilando con Makefile tradicional...${NC}"
    
    if make clean && make ; then
        echo -e "${GREEN}✅ Compilación Makefile exitosa${NC}"
        echo -e "${GREEN}🎯 Ejecutable generado: markdown_editor${NC}"
        return 0
    else
        echo -e "${RED}❌ Error en la compilación Makefile${NC}"
        return 1
    fi
}

# Función para compilación automática
compilar_automatico() {
    echo -e "${BLUE}🤖 Compilación automática...${NC}"
    echo ""
    
    # Verificar dependencias
    if command -v cmake >/dev/null 2>&1; then
        echo "✅ CMake disponible"
        if compilar_cmake; then
            return 0
        else
            echo -e "${YELLOW}⚠️  CMake falló, intentando Makefile...${NC}"
        fi
    else
        echo -e "${YELLOW}⚠️  CMake no disponible, usando Makefile...${NC}"
    fi
    
    # Fallback a Makefile
    if [ -f "Makefile" ]; then
        echo "✅ Makefile disponible"
        compilar_makefile
        return $?
    else
        echo -e "${RED}❌ Ni CMake ni Makefile están disponibles${NC}"
        return 1
    fi
}

# Función para limpiar todo
limpiar_todo() {
    echo -e "${BLUE}🧹 Limpiando archivos de compilación...${NC}"
    
    # Limpiar CMake
    if [ -d "build" ]; then
        echo "🗑️  Limpiando directorio build/"
        rm -rf build/*
    fi
    
    # Limpiar Makefile
    if [ -f "Makefile" ]; then
        echo "🗑️  Limpiando archivos de Makefile"
        make clean 2>/dev/null || true
        rm -f *.o moc_* markdown_editor
    fi
    
    echo -e "${GREEN}✅ Limpieza completada${NC}"
}

# Verificar dependencias básicas
echo "🔍 Verificando dependencias..."
dependencias_ok=true

if ! command -v g++ >/dev/null 2>&1; then
    echo -e "${RED}❌ g++ no encontrado${NC}"
    dependencias_ok=false
fi

if ! pkg-config --exists Qt5Core 2>/dev/null && ! pkg-config --exists Qt6Core 2>/dev/null; then
    echo -e "${RED}❌ Qt no encontrado (ni Qt5 ni Qt6)${NC}"
    dependencias_ok=false
fi

if ! pkg-config --exists libcmark 2>/dev/null; then
    echo -e "${YELLOW}⚠️  libcmark podría no estar disponible${NC}"
fi

if [ "$dependencias_ok" = false ]; then
    echo ""
    echo -e "${RED}💥 Faltan dependencias críticas. Instala primero:${NC}"
    echo "   sudo apt update"
    echo "   sudo apt install build-essential qt5-default libqt5webkit5-dev libcmark-dev cmake"
    exit 1
fi

echo -e "${GREEN}✅ Dependencias básicas encontradas${NC}"
echo ""

# Si se proporciona argumento, usarlo directamente
case "$1" in
    "cmake"|"1")
        compilar_cmake
        exit $?
        ;;
    "make"|"makefile"|"2")
        compilar_makefile
        exit $?
        ;;
    "auto"|"3"|"")
        compilar_automatico
        exit $?
        ;;
    "clean"|"limpiar"|"4")
        limpiar_todo
        compilar_automatico
        exit $?
        ;;
    *)
        echo -e "${YELLOW}❓ Opción desconocida: $1${NC}"
        ;;
esac

# Menú interactivo
while true; do
    mostrar_opciones
    read -p "Selecciona una opción (1-4, 0 para salir): " opcion
    
    case $opcion in
        1)
            compilar_cmake
            break
            ;;
        2)
            compilar_makefile
            break
            ;;
        3)
            compilar_automatico
            break
            ;;
        4)
            limpiar_todo
            compilar_automatico
            break
            ;;
        0)
            echo "👋 ¡Hasta luego!"
            exit 0
            ;;
        *)
            echo -e "${RED}❌ Opción inválida. Por favor, selecciona 1-4 o 0.${NC}"
            echo ""
            ;;
    esac
done

echo ""
echo -e "${GREEN}🎉 ¡Compilación terminada!${NC}"
echo ""
echo -e "${BLUE}🚀 Para ejecutar el programa:${NC}"
echo "   ./ejecutar.sh"
