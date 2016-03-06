<?php
require_once "../controller/FamilyController.php.inc";
require_once "../model/BDecotexException.php.inc";
require_once "./fastRoute/bootstrap.php";

const GET_ALL_FAMILIES = 0;
const GET_FAMILY = 1;
const CREATE_FAMILY = 2;
const DELETE_FAMILY = 3;
const UPDATE_FAMILY = 4;

function processQuery($name, $params) {
    try {
        $controller = new FamilyController();
        switch ($name) {
            case GET_FAMILY:
                $res = $controller->getById($params['id']);
                break;
            case GET_ALL_FAMILIES:
                $res = $controller->getAll();
                break;
            case CREATE_FAMILY:
                $controller->createFamily($params['name']);
                break;
            case DELETE_FAMILY:
                $controller->delete($params['id']);
                break;
            case UPDATE_FAMILY:
                $controller->updateFamily($params['id'], $params['name']);
                break;
        }
        
        header($_SERVER['SERVER_PROTOCOL'] . ' 200 Success', true, 200);
        header("Content-Type: application/json");
        if ($res != NULL){
            echo json_encode($res);
        }
        
    } catch (BDecotexException $e) {
        $e->throwToClient();
    }
}

$dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
    $r->addRoute('GET', '/bdecotex/family', GET_ALL_FAMILIES);
    // {id} must be a number (\d+)
    $r->addRoute('GET', '/bdecotex/family/{id:\d+}', GET_FAMILY);
    $r->addRoute('POST', '/bdecotex/family/{name}', CREATE_FAMILY);
    $r->addRoute('DELETE', '/bdecotex/family/{id:\d+}', DELETE_FAMILY);
    $r->addRoute('PUT', '/bdecotex/family/{id:\d+}/{name}', UPDATE_FAMILY);
});

// Fetch method and URI from somewhere
$httpMethod = $_SERVER['REQUEST_METHOD'];
$uri = rawurldecode(parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH));

$routeInfo = $dispatcher->dispatch($httpMethod, $uri);
switch ($routeInfo[0]) {
    case FastRoute\Dispatcher::METHOD_NOT_ALLOWED:
    case FastRoute\Dispatcher::NOT_FOUND:
        // ... 404 Not Found
        $error = new BDecotexException(3, 404, "Invalid call to $httpMethod $uri");
        $error->throwToClient();
        break;
    case FastRoute\Dispatcher::FOUND:
        $handler = $routeInfo[1];
        $vars = $routeInfo[2];
        processQuery($handler, $vars);
        break;
}
?>