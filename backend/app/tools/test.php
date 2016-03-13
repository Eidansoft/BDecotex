<?php
require_once "./FamilyImporter.php.inc";

$familyImporter = new FamilyImporter();
$familyImporter->truncateTable();
$familyImporter->processImport();

echo "XML procesado.";
