<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once (dirname(__FILE__).'/../libs/fastRoute/bootstrap.php');
require_once (dirname(__FILE__).'/../controller/FamilyController.php.inc');
require_once (dirname(__FILE__).'/../controller/ControllerException.php.inc');

/**
 * Description of FamilyView
 *
 * @author alex
 */
class FamilyView extends BDecotexView{
    
    const GET_ALL_FAMILIES = 0;
    const GET_FAMILY = 1;
    const CREATE_FAMILY = 2;
    const DELETE_FAMILY = 3;
    const UPDATE_FAMILY = 4;

    protected $controller;
    
    public function __construct() {
        
        $this->controller = new FamilyController;
        
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute('GET', '/bdecotex/family', FamilyView::GET_ALL_FAMILIES);
            // {id} must be a number (\d+)
            $r->addRoute('GET', '/bdecotex/family/{id:\d+}', FamilyView::GET_FAMILY);
            $r->addRoute('POST', '/bdecotex/family', FamilyView::CREATE_FAMILY);
            $r->addRoute('DELETE', '/bdecotex/family/{id:\d+}', FamilyView::DELETE_FAMILY);
            $r->addRoute('PUT', '/bdecotex/family/{id:\d+}', FamilyView::UPDATE_FAMILY);
        });
        parent::__construct($dispatcher);
    }
    
    protected function processHandler($handler, $vars) {
        $res = NULL;
        try {
            switch ($handler) {
                case FamilyView::GET_FAMILY:
                    $res = $this->controller->getById($vars['id']);
                    break;
                case FamilyView::GET_ALL_FAMILIES:
                    $res = $this->controller->getAll();
                    break;
                case FamilyView::CREATE_FAMILY:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->createFamily($data['description'], $data['code']);
                    break;
                case FamilyView::DELETE_FAMILY:
                    $this->controller->delete($vars['id']);
                    break;
                case FamilyView::UPDATE_FAMILY:
                    $data = json_decode(file_get_contents('php://input'), true);
                    $res = $this->controller->updateFamily($vars['id'], $data['description'], $data['code']);
                    break;
            }
            parent::returnSuccess($res);
        } catch (ControllerException $e) {
            $e->throwToClient();
        }
    }

}
