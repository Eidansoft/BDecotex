<?php
require_once (dirname(__FILE__).'/ViewException.php.inc');
require_once (dirname(__FILE__).'/../libs/fastRoute/bootstrap.php');

/**
 * Description of BDecotexView
 *
 * @author alex
 */
class BDecotexView {
    
    protected $dispatcher;
    
    public function __construct($dispatcher) {
        $this->dispatcher = $dispatcher;
    }
    
    public function processUri($httpMethod, $uri) {
        $routeInfo = $this->dispatcher->dispatch($httpMethod, $uri);
        switch ($routeInfo[0]) {
            case FastRoute\Dispatcher::METHOD_NOT_ALLOWED:
            case FastRoute\Dispatcher::NOT_FOUND:
                // ... 404 Not Found
                $error = new ViewException(3, 404, "Invalid call to $httpMethod $uri");
                $error->throwToClient();
                break;
            case FastRoute\Dispatcher::FOUND:
                $handler = $routeInfo[1];
                $vars = $routeInfo[2];
                $this->processHandler($handler, $vars);
                break;
        }
    }
    
    protected function processHandler($handler, $vars) {
        $error = new ViewException(6, 403, "This process is still in development.");
        $error->throwToClient();
    }
    
    protected function returnSuccess($res = NULL) {
        header($_SERVER['SERVER_PROTOCOL'] . ' 200 Success', true, 200);
        header("Content-Type: application/json");
        if ($res != NULL){
            echo json_encode($res);
        }
    }
}
