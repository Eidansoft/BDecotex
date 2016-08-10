<?php
require_once "./FamilyImporter.php.inc";
require_once "./SexImporter.php.inc";
require_once "./LineImporter.php.inc";
require_once "./ModelImporter.php.inc";

echo "Procesando XML de Familias...";
$familyImporter = new FamilyImporter();
$familyImporter->truncateTable();
$familyImporter->processImport();
echo " XML procesado.\n\n";

echo "Procesando XML de Modelos...";
$modelImporter = new ModelImporter();
$modelImporter->truncateTable();
$modelImporter->processImport();
echo "Procesando XML de Sexo...";
$sexImporter = new SexImporter();
$sexImporter->truncateTable();
$sexImporter->processImport();
echo " XML procesado.\n\n";

echo "Procesando XML de Lineas...";
$lineImporter = new LineImporter();
$lineImporter->truncateTable();
$lineImporter->processImport();
echo " XML procesado.\n\n";