# PruebaDiagnostica-LenguajesyCompiladores
Ejercicioa de lenguaje y compiladores hecho por Jeannybeth Herrera
# SCRIPT DE INSTALACIÓN AUTOMATIZADA - WINDOWS (PowerShell)
# Autor: Gemini

# --- Variables de Versión y Rutas ---
$JDK_URL = "https://descarga.oficial/ruta/al/jdk-8uXXX-windows-x64.exe" # RUTA REAL DE ORACLE (requiere login)
$DEVCPP_511_URL = "https://descarga.oficial/ruta/al/Dev-Cpp-5.11.exe"   # Por ejemplo, desde SourceForge
$DEVCPP_93_URL = "https://descarga.oficial/ruta/al/Embarcadero_DevCpp_9.2.0.exe" # Version 9.2.0 o similar

$Descargas = "$env:TEMP\Instaladores_IDES"
$LogFile = "$Descargas\instalacion_log.txt"

# --- 1. Preparación del Entorno ---
Write-Host "Iniciando script de instalación..."
New-Item -ItemType Directory -Force -Path $Descargas | Out-Null
"Iniciando instalación el $(Get-Date)" | Out-File $LogFile -Append

# --- 2. Instalación de Java JDK 8 ---
Write-Host "Descargando e instalando Java JDK 8..."
# Nota: La descarga de Oracle JDK 8 requiere un login y aceptación de términos,
# por lo que el modo totalmente silencioso puede fallar o la URL directa puede expirar.
# Se recomienda usar el gestor de paquetes Chocolatey (choco) o un instalador que soporte /s.
# Opcional: Instalar con Chocolatey (si está instalado)
# choco install -y jdk8

# Asumiendo que el instalador es un MSI o soporta el parámetro /s:
Invoke-WebRequest -Uri $JDK_URL -OutFile "$Descargas\jdk8.exe"
Start-Process -FilePath "$Descargas\jdk8.exe" -ArgumentList "/s /quiet" -Wait

# --- 3. Instalación de Dev-C++ 5.11 ---
Write-Host "Descargando e instalando Dev-C++ 5.11..."
Invoke-WebRequest -Uri $DEVCPP_511_URL -OutFile "$Descargas\devcpp511.exe"
# Dev-C++ 5.11 a menudo no soporta instalación silenciosa pura (requiere clics).
# Este comando ejecuta el instalador, pero el usuario debe seguir el asistente:
Start-Process -FilePath "$Descargas\devcpp511.exe" -Wait

# --- 4. Instalación de Dev-C++ 9.3 (Usando 9.2.0 de Embarcadero) ---
Write-Host "Descargando e instalando Dev-C++ 9.3 (v9.2.0)..."
Invoke-WebRequest -Uri $DEVCPP_93_URL -OutFile "$Descargas\devcpp93.exe"
# Este fork de Dev-C++ también puede requerir pasos manuales:
Start-Process -FilePath "$Descargas\devcpp93.exe" -Wait

# --- 5. Verificación (Comandos Manuales Recomendados) ---
Write-Host "--- Verificación de Instalación ---"
Write-Host "Por favor, verifica manualmente las instalaciones (Java y Dev-C++)."
Write-Host "Comandos de verificación de Java:"
Write-Host "java -version"
Write-Host "javac -version"

"Instalación finalizada el $(Get-Date). Revise el log." | Out-File $LogFile -Append
# Clean up:
# Remove-Item -Path $Descargas -Recurse -Force
