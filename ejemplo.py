#!/usr/bin/env python3
"""
Archivo de ejemplo Python para probar Escribe Chanchi
Demuestra el soporte para archivos .py
"""

def saludar(nombre):
    """Función de saludo simple"""
    return f"¡Hola, {nombre}!"

def main():
    """Función principal"""
    nombres = ["Ana", "Carlos", "María"]
    
    print("=== Programa de Saludos ===")
    for nombre in nombres:
        mensaje = saludar(nombre)
        print(mensaje)
    
    # Ejemplo de diccionario
    datos = {
        "programa": "Escribe Chanchi",
        "versión": "1.0",
        "lenguaje": "C++ con Qt6"
    }
    
    print("\nInformación del programa:")
    for clave, valor in datos.items():
        print(f"  {clave}: {valor}")

if __name__ == "__main__":
    main()
