<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once (dirname(__FILE__).'/../libs/fastRoute/bootstrap.php');
require_once (dirname(__FILE__).'/../controller/ModelController.php.inc');

/**
 * Description of ModelView
 *
 * @author alex
 */
class ModelView extends BDecotexView{
    
    const GET_ALL_MODEL = 0;
    const GET_MODEL = 1;
    const CREATE_MODEL = 2;
    const DELETE_MODEL = 3;
    const UPDATE_MODEL = 4;

    protected $controller;
    
    public function __construct() {
        
        $this->controller = new ModelController();
        
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
//            $r->addRoute('GET', '/bdecotex/model', ModelView::GET_ALL_MODEL);
            // {id} must be a number (\d+)
//            $r->addRoute('GET', '/bdecotex/model/{id:\d+}', ModelView::GET_MODEL);
            $r->addRoute('POST', '/bdecotex/mod', ModelView::CREATE_MODEL);
            $r->addRoute('DELETE', '/bdecotex/mod/{id:\d+}', ModelView::DELETE_MODEL);
            $r->addRoute('PUT', '/bdecotex/mod/{id:\d+}', ModelView::UPDATE_MODEL);
        });
        parent::__construct($dispatcher);
    }
    
    protected function processHandler($handler, $vars) {
        $res = NULL;
        try {
            switch ($handler) {
                case ModelView::GET_MODEL:
                    $res = $this->controller->getById($vars['id']);
                    break;
                case ModelView::GET_ALL_MODEL:
                    $res = $this->controller->getAll();
                    break;
                case ModelView::CREATE_MODEL:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->createModel($data['family'], $data['line'], $data['sex'], $data['variant']);
                    break;
                case ModelView::DELETE_MODEL:
                    $this->controller->delete($vars['id']);
                    break;
                case ModelView::UPDATE_MODEL:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->updateModel($vars['id'], $data['attribute'], $data['value']);
                    break;
            }
            parent::returnSuccess($res);
        } catch (BDecotexException $e) {
            $e->throwToClient();
        }
    }

}
