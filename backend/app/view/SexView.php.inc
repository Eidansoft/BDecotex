<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once "../libs/fastRoute/bootstrap.php";
require_once "../controller/SexController.php.inc";

/**
 * Description of SexView
 *
 * @author alex
 */
class SexView extends BDecotexView{
    
    const GET_ALL_SEX = 0;
    const GET_SEX = 1;
    const CREATE_SEX = 2;
    const DELETE_SEX = 3;
    const UPDATE_SEX = 4;

    protected $controller;
    
    public function __construct() {
        
        $this->controller = new SexController();
        
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute('GET', '/bdecotex/sex', SexView::GET_ALL_SEX);
            // {id} must be a number (\d+)
            $r->addRoute('GET', '/bdecotex/sex/{id:\d+}', SexView::GET_SEX);
            $r->addRoute('POST', '/bdecotex/sex', SexView::CREATE_SEX);
            $r->addRoute('DELETE', '/bdecotex/sex/{id:\d+}', SexView::DELETE_SEX);
            $r->addRoute('PUT', '/bdecotex/sex/{id:\d+}', SexView::UPDATE_SEX);
        });
        parent::__construct($dispatcher);
    }
    
    protected function processHandler($handler, $vars) {
        $res = NULL;
        try {
            switch ($handler) {
                case SexView::GET_SEX:
                    $res = $this->controller->getById($vars['id']);
                    break;
                case SexView::GET_ALL_SEX:
                    $res = $this->controller->getAll();
                    break;
                case SexView::CREATE_SEX:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->createSex($data['name'], $data['code']);
                    break;
                case SexView::DELETE_SEX:
                    $this->controller->delete($vars['id']);
                    break;
                case SexView::UPDATE_SEX:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->updateSex($vars['id'], $data['name'], $data['code']);
                    break;
            }
            parent::returnSuccess($res);
        } catch (BDecotexException $e) {
            $e->throwToClient();
        }
    }

}
