<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once "../libs/fastRoute/bootstrap.php";
require_once "../controller/FamilyController.php.inc";

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
        
        $this->controller = new FamilyController();
        
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute('GET', '/bdecotex/family', FamilyView::GET_ALL_FAMILIES);
            // {id} must be a number (\d+)
            $r->addRoute('GET', '/bdecotex/family/{id:\d+}', FamilyView::GET_FAMILY);
            $r->addRoute('POST', '/bdecotex/family/{name}', FamilyView::CREATE_FAMILY);
            $r->addRoute('DELETE', '/bdecotex/family/{id:\d+}', FamilyView::DELETE_FAMILY);
            $r->addRoute('PUT', '/bdecotex/family/{id:\d+}/{name}', FamilyView::UPDATE_FAMILY);
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
                    $this->controller->createFamily($vars['name']);
                    break;
                case FamilyView::DELETE_FAMILY:
                    $this->controller->delete($vars['id']);
                    break;
                case FamilyView::UPDATE_FAMILY:
                    $this->controller->updateFamily($vars['id'], $vars['name']);
                    break;
            }
            parent::returnSuccess($res);
        } catch (BDecotexException $e) {
            $e->throwToClient();
        }
    }

}
