<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once (dirname(__FILE__).'/../libs/fastRoute/bootstrap.php');
require_once (dirname(__FILE__).'/../controller/LineController.php.inc');
require_once (dirname(__FILE__).'/../controller/ControllerException.php.inc');

/**
 * Description of LineView
 *
 * @author alex
 */
class LineView extends BDecotexView{
    
    const GET_ALL_LINE = 0;
    const GET_LINE = 1;
    const CREATE_LINE = 2;
    const DELETE_LINE = 3;
    const UPDATE_LINE = 4;

    protected $controller;
    
    public function __construct() {
        
        $this->controller = new LineController;
        
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute('GET', '/bdecotex/line', LineView::GET_ALL_LINE);
            // {id} must be a number (\d+)
            $r->addRoute('GET', '/bdecotex/line/{id:\d+}', LineView::GET_LINE);
            $r->addRoute('POST', '/bdecotex/line', LineView::CREATE_LINE);
            $r->addRoute('DELETE', '/bdecotex/line/{id:\d+}', LineView::DELETE_LINE);
            $r->addRoute('PUT', '/bdecotex/line/{id:\d+}', LineView::UPDATE_LINE);
        });
        parent::__construct($dispatcher);
    }
    
    protected function processHandler($handler, $vars) {
        $res = NULL;
        try {
            switch ($handler) {
                case LineView::GET_LINE:
                    $res = $this->controller->getById($vars['id']);
                    break;
                case LineView::GET_ALL_LINE:
                    $res = $this->controller->getAll();
                    break;
                case LineView::CREATE_LINE:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->createLine($data['name'], $data['code']);
                    break;
                case LineView::DELETE_LINE:
                    $this->controller->delete($vars['id']);
                    break;
                case LineView::UPDATE_LINE:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->updateLine($vars['id'], $data['name'], $data['code']);
                    break;
            }
            parent::returnSuccess($res);
        } catch (ControllerException $e) {
            $e->throwToClient();
        }
    }

}
