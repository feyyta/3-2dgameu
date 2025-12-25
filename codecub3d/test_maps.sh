#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "========================================="
echo "  TEST DES MAPS INVALIDES"
echo "========================================="
echo ""

# Compile si besoin
if [ ! -f "./cub3D" ]; then
    echo "Compilation du projet..."
    make > /dev/null 2>&1
fi

passed=0
failed=0
crashed=0

# Teste toutes les maps test_*.cub
for map in maps/test_*.cub; do
    mapname=$(basename "$map")
    printf "Testing %-35s " "$mapname"

    # Lance le programme avec timeout de 2 secondes
    timeout 2s ./cub3D "$map" > /tmp/cub3d_output.txt 2>&1
    exitcode=$?

    # Analyse le résultat
    if [ $exitcode -eq 124 ]; then
        # Timeout = le programme est resté bloqué
        echo -e "${RED}[HANG/FREEZE]${NC}"
        ((crashed++))
    elif [ $exitcode -eq 139 ] || [ $exitcode -eq 134 ]; then
        # Segfault ou abort
        echo -e "${RED}[CRASH - SEGFAULT]${NC}"
        ((crashed++))
    elif grep -q "Error" /tmp/cub3d_output.txt; then
        # Le programme a détecté l'erreur correctement
        echo -e "${GREEN}[OK - Error detected]${NC}"
        ((passed++))
    else
        # Exit propre mais sans message d'erreur (problème)
        echo -e "${YELLOW}[SUSPICIOUS - No error message]${NC}"
        ((failed++))
    fi
done

echo ""
echo "========================================="
echo -e "Résultats:"
echo -e "${GREEN}Passed (error detected): $passed${NC}"
echo -e "${YELLOW}Suspicious (no message): $failed${NC}"
echo -e "${RED}Crashed/Hanged: $crashed${NC}"
echo "========================================="

# Nettoyage
rm -f /tmp/cub3d_output.txt
