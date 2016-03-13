<?php
require_once (dirname(__FILE__).'/MainView.php.inc');

$viewManager = new MainView();

// Fetch method and URI from somewhere
$httpMethod = $_SERVER['REQUEST_METHOD'];
$uri = rawurldecode(parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH));

$viewManager->processUri($httpMethod, $uri);

?>